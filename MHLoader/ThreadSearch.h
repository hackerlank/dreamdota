#include "stdafx.h"
#ifndef THREADSEARCH_H_
#define THREADSEARCH_H_

#include "WorkerThread.h"

class ThreadSearch : public WorkerThread {
public:
	SimpleUI::Delegate<void> onWar3WindowFound;
	SimpleUI::Delegate<void> onWar3WindowClosed;

	struct ResultType {
		uint32_t version;
		uint32_t game_base;
		DWORD process_id;
		HANDLE process_handle;
		DWORD thread_id;
		void* cgx_device;
		void* cgx_device_vtable;
		void* invoker;
		HWND win;
		HWND msg_win;
	};

	const static uint32_t SEARCH_SLEEP_INTERVAL = 50; 

	ThreadSearch() {
		this->win_ = NULL;
		this->term_ = false;
	}

	void StopSignal() {this->term_ = true;}

	virtual ~ThreadSearch() {}
	virtual void Work();
private:
	HWND win_;
	volatile bool term_;
	DISALLOW_COPY_AND_ASSIGN(ThreadSearch);
};

#endif