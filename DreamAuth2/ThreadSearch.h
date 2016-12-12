#include "stdafx.h"
#ifndef THREADSEARCH_H_
#define THREADSEARCH_H_

#include "WorkerThread.h"
#include "GameModule.h"

class ThreadSearch : public WorkerThread {
public:
	SimpleUI::Delegate<void> onWar3WindowFound;
	SimpleUI::Delegate<void> onWar3WindowClosed;

	const static uint32_t SEARCH_SLEEP_INTERVAL = 50; 

	typedef GameModule::SearchResultType ResultType;

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