#ifndef THREAD_ROAMING_PROFILE_PULL_
#define THREAD_ROAMING_PROFILE_PULL_

#include "WorkerThread.h"
#include "HTTP.h"

class SMRoamingProfile;

class ThreadRoamingProfilePull : public WorkerThread {
public:
	virtual void Work();
	virtual void Term();
	
	ThreadRoamingProfilePull() {}
	virtual ~ThreadRoamingProfilePull() {}
private:
	HTTP http_;
	std::string url_;
};

#endif