#include "stdafx.h"
#ifndef THREADFILEDOWNLOAD_H_
#define THREADFILEDOWNLOAD_H_

#include "WorkerThread.h"
#include <SimpleUI\Delegate.h>
#include "HTTP.h"

class ThreadFileDownload : public WorkerThread {
public:
	struct FileDownloadInfo {
		std::string url;
		std::string save_as;
	};

	ThreadFileDownload() {
		this->network_obj_.SetCancelFlag(false);
	}

	void StopSignal() {
		this->network_obj_.SetCancelFlag(true);
	}

	virtual ~ThreadFileDownload() {}
	virtual void Work();

	HTTP* network_obj() {return &(this->network_obj_);}
private:
	HTTP network_obj_;
	DISALLOW_COPY_AND_ASSIGN(ThreadFileDownload);
};

#endif