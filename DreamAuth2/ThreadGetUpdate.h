#include "stdafx.h"
#ifndef THREADGETUPDATE_H_
#define THREADGETUPDATE_H_

#include "WorkerThread.h"

class ThreadGetUpdate : public WorkerThread {
public:
	static const long MAX_FAILED_ALIVE = 3;
	struct UpdateInfo {
		uint32_t build;
		std::wstring link;
		std::string link_utf8;
		std::wstring desc;
		uint32_t date;
	};

	const UpdateInfo* GetUpdateInfo() {return &(this->update_info_);}

	ThreadGetUpdate() {
		
	}

	virtual ~ThreadGetUpdate() {
		
	}

	virtual void Work();
private:
	UpdateInfo update_info_;

	DISALLOW_COPY_AND_ASSIGN(ThreadGetUpdate);
};

#endif