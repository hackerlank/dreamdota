#include "stdafx.h"
#ifndef WORKERTHREAD_H_
#define WORKERTHREAD_H_

#include <SimpleUI\Delegate.h>

class WorkerThread {
public:
	SimpleUI::Delegate<WorkerThread*> onThreadComplete;

	void Run(DWORD arg = NULL);
	virtual void Work() = 0;
	virtual void Term() {}
	void Pause() {
		this->running_ = false;
		if (this->thread_)
			SuspendThread(this->thread_);
	}

	void Resume() {
		if (this->thread_) {
			ResumeThread(this->thread_);
			this->running_ = true;
		}
	}

	void Wait(uint32_t timeout = 0) {
		if (this->thread_)
			WaitForSingleObject(this->thread_, timeout ? timeout : INFINITE);
		if (this->thread_) {
			TerminateThread(this->thread_, 0xFFFFFFFF);
			this->thread_ = NULL;
		}
	}

	bool Running() {
		return this->running_;
	}

	bool Started() {
		return this->thread_ != NULL;
	}

	WorkerThread() {
		this->thread_ = NULL;
		this->result_ = 0xFFFFFFFF;
		this->running_ = false;
	}

	virtual ~WorkerThread();

	DWORD result() {return this->result_;}
	void set_result(DWORD result) {this->result_ = result;}

	DWORD arg() {return this->arg_;}
private:
	static unsigned int WINAPI ThreadProc(LPVOID arg);
	volatile HANDLE thread_;
	volatile DWORD result_;
	DWORD arg_;
	volatile bool running_;
};

#endif