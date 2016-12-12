#ifndef THREAD_UPLOAD_PROFILE_
#define THREAD_UPLOAD_PROFILE_

#include "WorkerThread.h"
#include "HTTP.h"
#include <SimpleUI\Delegate.h>

class ThreadUploadProfile : public WorkerThread {
public:
	virtual void Work();
	virtual void Term();

	ThreadUploadProfile() {}
	virtual ~ThreadUploadProfile() {}

	HTTP* HTTPObject() {return &this->http_;}
private:
	std::string url_;
	HTTP http_;
};

#endif