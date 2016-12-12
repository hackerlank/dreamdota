#include "stdafx.h"
#include "Exception.h"
#include "ThreadPipe.h"
#include "Auth.h"
#include "Locale.h"
#include "Connection.h"
#include "Message.h"
#include "SharedMemory.h"
#include "RemoteMemory.h"
#include "Loggedin.h"
#include "Utils.h"
#include "SystemTools.h"
#include "Injection.h"
#include "../DreamWarcraft/Version.h"
#include "../DreamWarcraft/Profile.h"

static const uint32_t BUFFER_SIZE = 10240;

enum GameConnectionEnum {
	GC_E_READ_FAILED = 1,
	GC_E_WRITE_FAILED
};

static std::pair<DWORD, DWORD> g_11game_range;
static std::pair<DWORD, DWORD> g_war3shell_range;
static void CheckThread(HANDLE process, DWORD tid) {
	SystemTools::ThreadInfo ti;
	if (SystemTools::GetThreadInfo(tid, &ti)) {
		if ((DWORD)ti.start_address > g_11game_range.first && (DWORD)ti.start_address < g_11game_range.second) {
			OutputDebugString(L"Suspend 11game.dll Thread!\n");
			HANDLE thread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, tid); 
			if (!thread)
				OutputDebugString(L"Open failed!\n");
			if (-1 == SuspendThread(thread))
				OutputDebugString(L"Subspend failed!\n");
			CloseHandle(thread);
		}
		else if ((DWORD)ti.start_address > g_war3shell_range.first && (DWORD)ti.start_address < g_war3shell_range.second) {
			OutputDebugString(L"Suspend war3shell.dll Thread!\n");
			HANDLE thread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, tid); 
			if (-1 == SuspendThread(thread))
				OutputDebugString(L"Subspend failed!\n");
			CloseHandle(thread);
		}
	}
}

/*
static void Patch11() {
	DWORD pid = GetWar3PID();
	if (!pid)
		return;

	HANDLE war3 = NTFindProcessHandle(pid, NULL, 0);

	SystemTools::ModuleInfo mi;
	if (SystemTools::GetModuleInfoEx(war3, L"11game.dll", &mi)) {
		g_11game_range.first = (DWORD)mi.handle;
		g_11game_range.second = (DWORD)mi.handle + mi.image_size;
	} else {
		g_11game_range.first = 0;
		g_11game_range.second = 0;
	}

	if (SystemTools::GetModuleInfoEx(war3, L"war3shell.dll", &mi)) {
		g_war3shell_range.first = (DWORD)mi.handle;
		g_war3shell_range.second = (DWORD)mi.handle + mi.image_size;
	} else {
		g_war3shell_range.first = 0;
		g_war3shell_range.second = 0;
	}
	
	HANDLE ss = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (INVALID_HANDLE_VALUE != ss) {
		THREADENTRY32 te32;
		te32.dwSize = sizeof(THREADENTRY32);
		// Retrieve information about the first thread,
		// and exit if unsuccessful
		if(!Thread32First(ss, &te32 )) {
			//OutputDebugString("no thread!");
			CloseHandle(ss);
		}

		// Now walk the thread list of the system,
		// and display information about each thread
		// associated with the specified process
		do { 
			if(te32.th32OwnerProcessID == pid)
				CheckThread(war3, te32.th32ThreadID);
		} while(Thread32Next(ss, &te32));
		CloseHandle(ss);
	}

	CloseHandle(war3);

}
*/

static void PatchPlatforms() {
	DWORD pid = GetWar3PID();
	if (!pid)
		return;

	HANDLE war3 = NTFindProcessHandle(pid, NULL, 0);
	//如果是11，启用安全模式
	SystemTools::ModuleInfo mi;
	if (SystemTools::GetModuleInfoEx(war3, L"war3shell.dll", &mi)) {
		ProfileSetBool(L"Misc", L"SafeMode", true);
	} else {
		ProfileSetBool(L"Misc", L"SafeMode", false);
	}
}

#pragma optimize( "", off ) 
NOINLINE bool ThreadPipe::GameConnection_Loop() {
	bool rv = true;
	VMProtectBeginVirtualization("GameConnection_Loop");
	BYTE* buffer = new BYTE[BUFFER_SIZE];
	HANDLE pipe = this->ctx_.pipe;
	Connection* conn = NULL;
	Auth::SessionType session;
	Auth::GetSessionData()->GetData(&session);
	jmp_buf env;
	int val = setjmp(env);
	if (val == 0) {
		BYTE null = 0;
		DWORD bytes;
		const Locale::LocaleInfo* locale = Locale::CurrentLocaleInfo();
		bool exit = false;
		const Connection::ResponseData* response;
		while (!exit) {

			bytes = 0;
			if (FALSE == ReadFile(pipe, buffer, BUFFER_SIZE, &bytes, NULL) || bytes == 0)
				longjmp(env, GC_E_READ_FAILED); //异常

			Loggedin::OutputEncryptedMessage(STR::TRANSMITTING_DATA);
		
			BYTE type = *(BYTE*)buffer;
			BYTE* data = buffer + 1;
			size_t data_size = bytes - 1;
			switch(type) {
			case PIPE_MESSAGE_NULL: //空请求，表示退出
				exit = true;
				break;
			case PIPE_MESSAGE_REQUEST_DATA: //请求通讯加密KEY和Profile地址
				if (data_size < sizeof(VERSION.revision) || memcmp(&VERSION.revision, data, sizeof(VERSION.revision) != 0)) { //版本不符
					Loggedin::OutputEncryptedMessage(STR::MODULE_VERSION_MISMATCH);
					if (TRUE != WriteFile(pipe, &null, 1, &bytes, NULL) || bytes != 1) {
						longjmp(env, GC_E_WRITE_FAILED); //异常
					}
				} else {
					memcpy_s(buffer, BUFFER_SIZE, session.KeyData, RSA_SIZE);
					const char* path;
					size_t path_size;
					path = Utils::GetSelfPathA();
					path_size = strlen(path) + 1;
					memcpy_s(buffer + RSA_SIZE, BUFFER_SIZE - RSA_SIZE, path, path_size);
					if (TRUE != WriteFile(pipe, buffer, RSA_SIZE + path_size, &bytes, NULL) || bytes != RSA_SIZE + path_size) {
						longjmp(env, GC_E_WRITE_FAILED); //异常
					}
				}
				//PatchPlatforms();
				break;
			case PIPE_MESSAGE_REQUEST_LANG: //请求语言数据
				if (TRUE != WriteFile(pipe, locale->data, locale->data_size, &bytes, NULL) || bytes != locale->data_size) {
					longjmp(env, GC_E_WRITE_FAILED); //异常
				}
				break;
			case PIPE_MESSAGE_NET: //请求网络连接
				if (bytes > 1) {
					conn = new Connection();
					//为数据包写入Session Id
					MessageHeader* header = reinterpret_cast<MessageHeader*>(data);
					memcpy_s(header->session_id, sizeof(header->session_id), session.id, sizeof(header->session_id));
					if (NULL == (response = conn->Request(data, data_size))) {
						if (TRUE != WriteFile(pipe, &null, 1, &bytes, NULL) || bytes != 1) {
							longjmp(env, GC_E_WRITE_FAILED); //异常
						}
					} else {
						if (TRUE != WriteFile(pipe, response->data, response->size, &bytes, NULL) && bytes > 0) {
							longjmp(env, GC_E_WRITE_FAILED); //异常
						}
					}
					delete conn;
					conn = NULL;
				}
				break;
			default:
				if (TRUE != WriteFile(pipe, &null, 1, &bytes, NULL) || bytes != 1) {
					longjmp(env, GC_E_WRITE_FAILED); //异常
				}
				break;
			}

			Loggedin::OutputEncryptedMessage(STR::COMPLETED);
		}
	} else {
		rv = false;
		if (conn) {
			delete conn;
			conn = NULL;
		}
	}

	memset(&session, 0, sizeof(Auth::SessionType));
	delete buffer;

	VMProtectEnd();
	return rv;
}
#pragma optimize( "", on ) 

ThreadPipe::ThreadPipe() {
	this->term_ = false;
	memset(&this->ctx_, 0, sizeof(this->ctx_));
}

ThreadPipe::~ThreadPipe() {
	
}

void ThreadPipe::StopSignal() {
	VMProtectBeginVirtualization("ThreadMessage::StopSignal");
	this->term_ = true;
	Pipe_Term(&this->ctx_);
	VMProtectEnd();
}

bool ThreadPipe::Write(const void* data, size_t data_size) {
	DWORD bytes = 0;
	return Pipe_Write(&this->ctx_, data, data_size, &bytes) && bytes == data_size;
}

void ThreadPipe::Work() {
	VMProtectBeginVirtualization("ThreadMessage::Work");
	this->term_ = false;
	while (!this->term_) {
		if (!Pipe_Create(&this->ctx_))
			Abort(EXCEPTION_PIPE_CREATE_FAILED);
			void *smem = (void*)this->arg();
			memcpy_s(smem, SharedMemory::SMEM_SIZE, &this->ctx_, sizeof(PipeContext));
		if (!Pipe_Listen(&this->ctx_) && !this->term_) {
#ifdef _DEBUG
			OutputDebug("Pipe listen failed.\n");
#endif
			continue;
		}

		this->GameConnection_Loop();

		if (!this->term_)
			Pipe_Term(&this->ctx_);
	}
	VMProtectEnd();
}