#include "stdafx.h"
#include "ThreadSearch.h"
#include "NTDLL.h"
#include "RemoteMemory.h"
#include "Injection.h"
#include "GameVersion.h"


static HWND FindWar3Window() {
	return FindWindowEx(NULL, NULL, L"Warcraft III", NULL);
}

#pragma optimize( "", off ) 
static const bool VerifyWindow(HWND win, ThreadSearch::ResultType* result) {
	bool rv = false;
	VMProtectBeginVirtualization("GameModule::VerifyWindow");

	DWORD pid, tid;
	tid = GetWindowThreadProcessId(win, &pid);

	HANDLE process = NTFindProcessHandle(pid, NULL, 0);
	if (process) {
		GameVersion::GameInfo info;
		if (GameVersion::GetGameInfo(win, process, &info)) {
			result->game_base = info.base;
			if (result->process_handle)
				CloseHandle(result->process_handle);
			result->process_handle = process;
			result->process_id = pid;
			result->thread_id = tid;
			result->version = info.version;
			result->cgx_device = info.cgx_device;
			result->cgx_device_vtable = info.cgx_device_vtable;
			result->win = win;
			result->invoker = info.invoker;
			rv = true;
		}
	}

	VMProtectEnd();
	return rv;
}
#pragma optimize( "", on ) 

void ThreadSearch::Work() {
#ifdef _DEBUG
	OutputDebug("Search thread(0x%08X) started.\n", this);
#endif
	this->term_ = false;
	while(!this->term_) {
		HWND win;
		if (NULL != (win = FindWar3Window())) {
			bool need_verify = false;
			if (this->win_ == NULL) {
				need_verify = true;
			} else { 
				if (!IsWindow(this->win_)) { //在Sleep的间隔内上个窗口被关闭，新的被开启。

#ifdef _DEBUG
					OutputDebug("Search thread(0x%08X) : window 0x%X closed.\n", this, this->win_);
#endif	

					this->win_ = NULL;
					this->onWar3WindowClosed.Invoke();
					need_verify = true;
				}
			}
			if (need_verify) {
				ThreadSearch::ResultType* verify_result = (ThreadSearch::ResultType*)(this->arg());
				if (VerifyWindow(win, verify_result)) {

#ifdef _DEBUG
					OutputDebug("Search thread(0x%08X) found window 0x%X.\n", this, win);
#endif					

					this->win_ = win;
					this->onWar3WindowFound.Invoke();
				}
			}
		} else {
			if (this->win_) { //之前的窗口被关闭

#ifdef _DEBUG
				OutputDebug("Search thread(0x%08X) : window 0x%X closed.\n", this, this->win_);
#endif	

				this->win_ = NULL;
				this->onWar3WindowClosed.Invoke();
			}
		}
		Sleep(ThreadSearch::SEARCH_SLEEP_INTERVAL);
	}
	this->win_ = NULL;
#ifdef _DEBUG
	OutputDebug("Search thread(0x%08X) ended.\n", this);
#endif
}