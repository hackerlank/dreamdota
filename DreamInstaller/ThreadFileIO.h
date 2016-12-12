#pragma once
#include "../DreamAuth2/WorkerThread.h"

class ThreadFileIO : public WorkerThread {
public:
	struct ProgressInfo {
		double now;
		double total;
	};

	SimpleUI::Delegate<const ProgressInfo*> onProgress;
	SimpleUI::Delegate<const wchar_t*> onFileChange;

	virtual void Work();

	ThreadFileIO() {}
	virtual ~ThreadFileIO() {}
};