#include "stdafx.h"
#ifndef THREADPIPE_H_
#define THREADPIPE_H_

#include "WorkerThread.h"
#include "Pipe.h"

class ThreadPipe : public WorkerThread {
public:
	struct PipeData {
		void* data;
		size_t size;
	};

	SimpleUI::Delegate<const PipeData*> onPipeData;

	NOINLINE bool GameConnection_Loop();
	void StopSignal();
	bool Write(const void* data, size_t data_size);

	ThreadPipe();
	virtual ~ThreadPipe();
	virtual void Work();
private:
	volatile bool term_;
	PipeContext ctx_;
	DISALLOW_COPY_AND_ASSIGN(ThreadPipe);
};

#endif