#include "stdafx.h"
#ifndef THREADMESSAGE_H_
#define THREADMESSAGE_H_

#include "WorkerThread.h"

class ThreadMessage : public WorkerThread {
public:
	SimpleUI::Delegate<HWND> onWindowCreated;
	SimpleUI::Delegate<const MSG*> onMessage;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void StopSignal();

	ThreadMessage();
	virtual ~ThreadMessage();
	virtual void Work();
private:
	GETSET(HWND, win);

	DISALLOW_COPY_AND_ASSIGN(ThreadMessage);
};

#endif