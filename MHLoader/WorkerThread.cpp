#include "stdafx.h"
#include "WorkerThread.h"
#include <process.h>

WorkerThread::~WorkerThread() {

}

void WorkerThread::Run(DWORD arg) {
	if (!this->thread_) {
		this->running_ = true;
		this->arg_ = arg;
		this->thread_ = (HANDLE)_beginthreadex(NULL, NULL, WorkerThread::ThreadProc, this, CREATE_SUSPENDED, NULL);
		ResumeThread(this->thread_);
	}
}

unsigned int WorkerThread::ThreadProc(LPVOID arg) {
	WorkerThread* t = (WorkerThread*)arg;
	HANDLE thread = t->thread_;
	t->Work();
	t->thread_ = NULL;
	t->running_ = false;
	t->onThreadComplete.Invoke(t);
	CloseHandle(thread);
	return 0;
}