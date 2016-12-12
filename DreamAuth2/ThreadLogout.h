#include "stdafx.h"
#ifndef THREADLOGOUT_H_
#define THREADLOGOUT_H_

#include "WorkerThread.h"

class ThreadLogout : public WorkerThread {
public:
	ThreadLogout() {}
	virtual ~ThreadLogout() {}
	virtual void Work();
private:
	DISALLOW_COPY_AND_ASSIGN(ThreadLogout);
};

#endif