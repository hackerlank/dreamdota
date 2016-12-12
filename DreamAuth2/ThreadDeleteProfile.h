#ifndef THREAD_DELETE_PROFILE_
#define THREAD_DELETE_PROFILE_

#include "WorkerThread.h"
#include "HTTP.h"
#include <SimpleUI\Delegate.h>

class ThreadDeleteProfile : public WorkerThread {
public:
	virtual void Work();
	virtual void Term();

	ThreadDeleteProfile() {}
	virtual ~ThreadDeleteProfile() {}
private:
	std::string url_;
	HTTP http_;
};

#endif