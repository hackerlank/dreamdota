#include "stdafx.h"
#ifndef THREADALIVE_H_
#define THREADALIVE_H_

#include "WorkerThread.h"

class ThreadAlive : public WorkerThread {
public:
	static const long MAX_FAILED_ALIVE = 3;

	ThreadAlive() {
		this->evt_stop_ = CreateEvent(NULL, NULL, FALSE, NULL);
		this->term_ = false;
		this->success_count_ = this->failed_count_ = 0;
	}

	void StopSignal() {
		this->term_ = true;
		SetEvent(this->evt_stop_);
	}

	virtual ~ThreadAlive() {}
	virtual void Work();
private:
	HANDLE evt_stop_;
	GETSET(volatile bool, term);
	volatile long success_count_;
	volatile long failed_count_;

	DISALLOW_COPY_AND_ASSIGN(ThreadAlive);
};

#endif