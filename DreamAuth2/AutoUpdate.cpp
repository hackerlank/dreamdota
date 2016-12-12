#include "AutoUpdate.h"
#include "DialogUpdate.h"
#include "ResString.h"
#include "ThreadFileDownload.h"
#include "ThreadGetUpdate.h"
#include "Locale.h"
#include "../DreamWarcraft/Version.h"
#include <cmath>
#include <ZLibWrap.h>
#include "Utils.h"

namespace AutoUpdate {

static volatile bool UpdateSuccess = false;
static DialogUpdate* Dialog;
static ThreadGetUpdate* GetInfoThread = NULL;
static ThreadFileDownload* DownloadThread = NULL;
static char* DOWNLOAD_FILENAME = "DreamDota.tmp";
static wchar_t* DOWNLOAD_FILENAMEW = L"DreamDota.tmp";
static wchar_t* INSTALLER_FILENAMEW = L"DreamInstaller.exe";

void onCancelComplete(WorkerThread* thread) {
	UpdateSuccess = false;
	Dialog->Close();
}

INT_PTR ON_WM_CLOSE(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	DialogUpdate* t = (DialogUpdate*)dialog;
	BOOL rv = FALSE;
	if (GetInfoThread->Running() || DownloadThread->Running()) {
		if (IDYES != MessageBox(Dialog->handle(), 
			ResString::GetString(ResString::CANCEL_UPDATE_WARNING), L"", MB_YESNO | MB_ICONWARNING)) {
			return TRUE;
		} else {
			Dialog->SetState(DialogUpdate::STATE_CANCEL);
			DownloadThread->onThreadComplete.RemoveAll();
			DownloadThread->onThreadComplete += onCancelComplete;
			DownloadThread->StopSignal();
		}
	}
	return rv;
}

static void UnixTimeToFileTime(time_t t, LPFILETIME pft) {
	// Note that LONGLONG is a 64-bit value
	LONGLONG ll;
	ll = Int32x32To64(t, 10000000) + 116444736000000000;
	pft->dwLowDateTime = (DWORD)ll;
	pft->dwHighDateTime = ll >> 32;
}

static int LastProgressValue = 0;
static DWORD StartTime = 0;
static void onProgress(const HTTP::ProgressInfo* pi) {
	wchar_t buff[64];
	int value = (int)ceil(100.0 * (pi->now / pi->total));
	double speed = 0;
	if (StartTime == 0)
		StartTime = GetTickCount();
	else
		speed = pi->now / (GetTickCount() - StartTime);
	if (LastProgressValue != value) {
		swprintf_s(buff, 64, ResString::GetString(ResString::DOWNLOAD_PROGRESS), pi->now / pi->total * 100.0, speed);
		Dialog->l_status()->SetWindowText(buff);
		Dialog->p_progress()->SetPos(value);
		LastProgressValue = value;
	}
}

static void onCommand(SimpleUI::Control* ctl) {
	static ThreadFileDownload::FileDownloadInfo FDInfo;
	const ThreadGetUpdate::UpdateInfo* info = GetInfoThread->GetUpdateInfo();
	if (ctl == Dialog->b_update()) {
		Dialog->SetState(DialogUpdate::STATE_DOWNLOADING);
		FDInfo.url = info->link_utf8.c_str();
		char tmppath[MAX_PATH] = {0};
		//GetTempPathA(MAX_PATH, tmppath);
		strcat_s(tmppath, MAX_PATH, DOWNLOAD_FILENAME); 
		FDInfo.save_as = tmppath;
		StartTime = 0;
		Dialog->l_status()->SetWindowText(ResString::GetString(ResString::CONNECTING));		
		DownloadThread->Run((DWORD)&FDInfo);
	} else if (ctl == Dialog->b_copy()) {
		if (OpenClipboard(Dialog->handle())) {
			EmptyClipboard();
			HANDLE hclip;
			wchar_t *buf;
			hclip = GlobalAlloc(GMEM_MOVEABLE, (info->link.size() + 1) * sizeof(wchar_t));
			buf = (wchar_t*)GlobalLock(hclip);
			memset(buf, 0, (info->link.size() + 1) * sizeof(wchar_t));
			wcscpy_s(buf, info->link.size() + 1, info->link.c_str());
			GlobalUnlock(hclip);
			SetClipboardData(CF_UNICODETEXT, hclip);
			CloseClipboard();
			GlobalFree(hclip);
		}
	} else if (ctl == Dialog->b_open()) {
		ShellExecute(Dialog->handle(), NULL, info->link.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
	}
}

static void onInfoThreadComplete(WorkerThread* thread) {
	GetInfoThread->onThreadComplete -= onInfoThreadComplete;
	bool success = thread->result() > 0;
	if (success) {
		const ThreadGetUpdate::UpdateInfo* info = GetInfoThread->GetUpdateInfo();
		Dialog->t_changelog()->SetWindowText(info->desc.c_str());
		
		FILETIME ft;
		SYSTEMTIME st;
		UnixTimeToFileTime((time_t)info->date, &ft);
		FileTimeToSystemTime(&ft, &st);
		int len = GetDateFormat(Locale::CurrentLocaleInfo()->lcid, DATE_SHORTDATE, &st, NULL, NULL, 0);
		wchar_t* date = new wchar_t[len];
		GetDateFormat(Locale::CurrentLocaleInfo()->lcid, DATE_SHORTDATE, &st, NULL, date, len);
		

		wchar_t buffw[64];
		swprintf_s(buffw, 64, ResString::GetString(ResString::UPDATE_VERSION), VERSION.revision, info->build, date);
		Dialog->l_status()->SetWindowText(buffw);

		delete [] date;
		Dialog->SetState(DialogUpdate::STATE_INFO_LOADED);
	} else {
		MessageBox(Dialog->handle(), ResString::GetString(ResString::DOWNLOAD_UPDATE_DATA_FAILED), NULL, MB_ICONERROR);
		Dialog->Close();
	}
}

static bool RunInstaller() {
	if (TRUE == ZWZipExtract(DOWNLOAD_FILENAMEW, L".")) {
		wchar_t args[MAX_PATH + 10];
		swprintf_s(args, MAX_PATH + 10, 
			L"\"%s\" %u", Utils::GetSelfPath(), GetCurrentProcessId()); 
		ShellExecute(
			NULL, 
			NULL, 
			INSTALLER_FILENAMEW, 
			args, 
			Utils::GetSelfPath(), 
			SW_SHOWNORMAL
		);
		return true;
	} else {
		MessageBox(Dialog->handle(), ResString::GetString(ResString::EXTRACT_PACKAGE_FAILED), NULL, MB_ICONERROR);
		return false;
	}
}

static void onDowloadThreadComplete(WorkerThread* thread) {
	if (thread->result()) {
		Dialog->p_progress()->SetMarquee(true);
		Dialog->l_status()->SetWindowText(ResString::GetString(ResString::EXTRACTING));
		UpdateSuccess = RunInstaller();
		_wremove(DOWNLOAD_FILENAMEW);
	} else {
		MessageBox(Dialog->handle(), ResString::GetString(ResString::DOWNLOAD_FAILED), NULL, MB_ICONERROR);
		UpdateSuccess = false;
	}
	Dialog->Close();
}

bool AutoUpdate() {
	Dialog = new DialogUpdate();
	Dialog->AddDialogMessageHandler(WM_CLOSE, ON_WM_CLOSE);
	Dialog->onCommand += onCommand;

	Dialog->Show(true);
	GetInfoThread = new ThreadGetUpdate();
	GetInfoThread->onThreadComplete += onInfoThreadComplete;
	DownloadThread = new ThreadFileDownload();
	DownloadThread->onThreadComplete += onDowloadThreadComplete;
	DownloadThread->network_obj()->onDownloadProgress += onProgress;

	GetInfoThread->Run();

	Dialog->WaitClose();
	delete Dialog;
	delete DownloadThread;
	delete GetInfoThread;
	return UpdateSuccess;
}

} //namespace