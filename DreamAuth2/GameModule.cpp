#include "stdafx.h"
#include <SimpleUI\SimpleUI.h>
#include "GameModule.h"
#include "ResString.h"
#include "Exception.h"
#include "DialogMain.h"
#include "LocaleString.h"
#include "Injection.h"
#include "SharedMemory.h"

#include "ThreadMessage.h"
#include "ThreadSearch.h"
#include "ThreadPipe.h"
#include "Loggedin.h"
#include "Main.h"
#include "../DreamWarcraft/Profile.h"

namespace GameModule {

SimpleUI::Delegate<bool> onActionComplete;

//static ThreadMessage* MessageThread = NULL;
static ThreadPipe* PipeThread = NULL;
static ThreadSearch* SearchThread = NULL;

static SearchResultType SearchResult = {0};
static InjectMethodEnum InjectMethod, ToInjectMethod;
static std::wstring* LastErrorMessage;

static void* SharedMemory = NULL;

volatile static enum StateEnum {
	STATE_UNINITED,
	STATE_INITED,
	STATE_STARTED,
	STATE_STARTING,
	STATE_STOPPING,
} State = STATE_UNINITED;

InjectMethodEnum GetCurrentMethod() {return InjectMethod;}

static void SetLastErrorMessage(const wchar_t* msg) {
	LastErrorMessage->assign(msg);
}

const wchar_t* GetLastErrorMessage() {
	return LastErrorMessage->c_str();
}

static void onInjectResult(WorkerThread* thread) {

	Loggedin::OutputEncryptedMessage(thread->arg() ? STR::SUCCESS : STR::FAILURE);
}

static void onWar3WindowFound() {
	Loggedin::OutputMessage(ResString::GetString(ResString::GAME_DETECTED), SearchResult.version);
	Loggedin::OutputEncryptedMessage(War3Inject(L"DreamWarcraft.dll") ? STR::SUCCESS : STR::FAILURE);
}

static void onWar3WindowClosed() {
	Loggedin::OutputMessage(ResString::GetString(ResString::GAME_EXITED));
}

static void DoChange() {
	if (ToInjectMethod == GameModule::INJECT_METHOD_AUTO) {
		SearchThread->Run((DWORD)&SearchResult);
	}
	InjectMethod = ToInjectMethod;

	onActionComplete.Invoke(true);
}

static void onThreadEndForCleanup(WorkerThread* thread) {
	thread->onThreadComplete -= onThreadEndForCleanup;
	if (!SearchThread->Running()) {
		DoChange();
	}
}

void Change(InjectMethodEnum method) {
	ProfileSetInt(L"Auth", L"InjectMethod", method);

	//清理
	bool need_wait = false;
	if (SearchThread->Running()) {
		need_wait = true;
		SearchThread->onThreadComplete += onThreadEndForCleanup;
		SearchThread->StopSignal();
	}

	ToInjectMethod = method;
	if (!need_wait) {
		DoChange();
	}
	
}

void StartChangeComplete(bool success) {
	onActionComplete -= StartChangeComplete;
	State = STATE_STARTED;
}

void Start() {
	assert(State == STATE_INITED);

	State = STATE_STARTING;

	int saved_inject_method = ProfileGetInt(L"Auth", L"InjectMethod", 0);
	if (saved_inject_method < GameModule::INJECT_METHOD_AUTO || saved_inject_method > GameModule::INJECT_METHOD_PASSIVE) {
		saved_inject_method = GameModule::INJECT_METHOD_AUTO;
	} else {
		saved_inject_method = (GameModule::InjectMethodEnum)saved_inject_method;
	}

	if (!IsAdminPrivilegeAvaliable())
		saved_inject_method = GameModule::INJECT_METHOD_PASSIVE;

	PipeThread->Run((DWORD)SharedMemory);

	onActionComplete += StartChangeComplete;
	Change((InjectMethodEnum)saved_inject_method);
}

static void DoStop() {
	State = STATE_INITED;

	onActionComplete.Invoke(true);
}

static void onThreadEndForModuleCleanup(WorkerThread* thread) {
	thread->onThreadComplete -= onThreadEndForCleanup;
	if (!SearchThread->Running() && !PipeThread->Running()) {
		DoStop();
	}
}

void Stop() {
	assert(State == STATE_STARTED);

	State = STATE_STOPPING;

	//清理
	bool need_wait = false;
	if (SearchThread->Running()) {
		need_wait = true;
		SearchThread->onThreadComplete += onThreadEndForModuleCleanup;
		SearchThread->StopSignal();
	}
	if (PipeThread->Running()) {
		need_wait = true;
		PipeThread->onThreadComplete += onThreadEndForModuleCleanup;
		PipeThread->StopSignal();
	}
	if (!need_wait) {
		DoStop();
	}
}

static void onMessageWindowCreated(HWND win) {
	SearchResult.win = win;
}

static void onPipeData(const ThreadPipe::PipeData* data) {

}

void Init() {
	LastErrorMessage = new std::wstring(L"");

	SharedMemory = SharedMemory::Create();

	//MessageThread = new ThreadMessage();
	//MessageThread->onWindowCreated += onMessageWindowCreated;
	//MessageThread->Run();

	PipeThread = new ThreadPipe();
	PipeThread->onPipeData += onPipeData;

	SearchThread = new ThreadSearch();
	SearchThread->onWar3WindowFound += onWar3WindowFound;
	SearchThread->onWar3WindowClosed += onWar3WindowClosed;

	State = STATE_INITED;
}

void Cleanup() {
	if (State == STATE_STARTED) {
		Stop();
	}

	while (State != STATE_INITED) 
		Sleep(100);

	SearchThread->onWar3WindowClosed -= onWar3WindowClosed;
	SearchThread->onWar3WindowFound -= onWar3WindowFound;
	SearchThread->StopSignal();
	SearchThread->Wait();
	delete SearchThread;
	
	//MessageThread->StopSignal();
	//MessageThread->Wait();
	//delete MessageThread;

	PipeThread->StopSignal();
	PipeThread->Wait();
	delete PipeThread;

	delete LastErrorMessage;

	if (SearchResult.process_handle)
		CloseHandle(SearchResult.process_handle);

	SharedMemory::Close();
	SharedMemory = NULL;

	State = STATE_UNINITED;
}

const SearchResultType* GetLastSearchResult() {
	return &SearchResult;
}

}//namespace