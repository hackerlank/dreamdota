#include "stdafx.h"
#include "Main.h"
#include "DialogInstall.h"
#include "LocaleString.h"
#include "ThreadFileIO.h"
#include "Files.h"
#include <Shlobj.h>

static DialogInstall* Dialog = NULL;
static ThreadFileIO* FileIOThread = NULL;
static wchar_t InstallPath[MAX_PATH] = {0};
const wchar_t* GetInstallPath() {return InstallPath;}
static wchar_t ExePath[MAX_PATH] = {0};
static OSVERSIONINFO OsVer = {0};

static void SelectDir(bool fl) {
	if (fl) {
		Dialog->l_status()->ShowWindow(SW_HIDE);
		Dialog->p_progress()->ShowWindow(SW_HIDE);
		Dialog->b_browser()->ShowWindow(SW_SHOW);
	} else {
		Dialog->l_status()->ShowWindow(SW_SHOW);
		Dialog->p_progress()->ShowWindow(SW_SHOW);
		Dialog->b_browser()->ShowWindow(SW_HIDE);
	}
}

void StartInstallation() {
	swprintf_s(ExePath, L"%s\\%s", InstallPath, Files::GetFileList()[0].name);
	Dialog->EnableSystemMenuItem(SC_CLOSE, FALSE);
	FileIOThread->Run((DWORD)Dialog->handle());
}

void onCommand(SimpleUI::Control* ctl) {
	if (ctl == Dialog->b_browser()) {
		Dialog->b_browser()->EnableWindow(FALSE);
		BROWSEINFO bInfo = {0};  
		bInfo.hwndOwner = Dialog->handle();  
		bInfo.lpszTitle = _(LocaleString::SELECT_DIR);
		bInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI | BIF_UAHINT;  
		LPITEMIDLIST lpDlist;
		lpDlist = SHBrowseForFolder(&bInfo);
		if (lpDlist != NULL) {
			Dialog->b_browser()->ShowWindow(SW_HIDE);
			Dialog->b_browser()->EnableWindow(TRUE);
			SHGetPathFromIDList(lpDlist, InstallPath);
			SelectDir(false);
			StartInstallation();
		} else {
			Dialog->b_browser()->EnableWindow(TRUE);
		}
	}
}

void onProgress(const ThreadFileIO::ProgressInfo* pi) {
	//Dialog->p_progress()->SetPos((int)(100.0 * (pi->now / pi->total)));
}

void onFileChange(const wchar_t* name) {
	wchar_t buff[MAX_PATH];
	swprintf_s(buff, MAX_PATH, _(LocaleString::COPYING), name);
	Dialog->l_status()->SetWindowText(buff);
}

void onComplete(WorkerThread* thread) {
	Dialog->l_status()->SetWindowText(_(LocaleString::SUCCESS));
	if (thread->result()) {
		if (OsVer.dwMajorVersion >= 6) {
			if (ShellExecute( NULL, 
				L"runas",  
				ExePath,  
				NULL,     
				InstallPath,
				SW_SHOWNORMAL  
			) <= (HINSTANCE)32)
				ShellExecute(NULL, NULL, ExePath, NULL, InstallPath, SW_SHOWNORMAL);
		} else
			ShellExecute(NULL, NULL, ExePath, NULL, InstallPath, SW_SHOWNORMAL); 
		Sleep(1000);
	} else {
		MessageBox(Dialog->handle(), _(LocaleString::FAILURE), L"", MB_ICONERROR);
	}
	Dialog->Close();
}

BOOL ON_WM_CLOSE(SimpleUI::Dialog* d, UINT msg, WPARAM WParam, LPARAM lParam) {
	return FileIOThread->Running() ? TRUE : FALSE;
}

int Main(int argc, wchar_t* argv[]) {
	OsVer.dwOSVersionInfoSize = sizeof(OsVer);
	GetVersionEx(&OsVer);

	FileIOThread = new ThreadFileIO();
	FileIOThread->onProgress += onProgress;
	FileIOThread->onFileChange += onFileChange;
	FileIOThread->onThreadComplete += onComplete;

	Dialog = new DialogInstall();
	Dialog->onCommand += onCommand;
	Dialog->AddDialogMessageHandler(WM_CLOSE, ON_WM_CLOSE);
	if (argc != 3) {
		SelectDir(true);
		Dialog->Show(true);
	} else {
		SelectDir(false);
		wcscpy_s(InstallPath, MAX_PATH, argv[1]);
		Dialog->Show(true);
		DWORD pid = (DWORD)_wtoi(argv[2]);
		HANDLE process = OpenProcess(SYNCHRONIZE, NULL, pid);
		if (process) {
			Dialog->l_status()->SetWindowText(_(LocaleString::WAIT_EXIT));
			WaitForSingleObject(process, INFINITE);
		}
		StartInstallation();
	}

	Dialog->WaitClose();
	Dialog->onCommand -= onCommand;
	
	FileIOThread->onThreadComplete -= onComplete;
	FileIOThread->onFileChange -= onFileChange;
	FileIOThread->onProgress -= onProgress;
	FileIOThread->Wait();
	
	delete Dialog;
	delete FileIOThread;
	return 0;
}