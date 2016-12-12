#include "stdafx.h"
#include <fp_call.h>
#include "Locale.h"
#include "Auth.h"
#include "LocaleString.h"
#include "InlineUtils.h"
#include "EncryptedData.h"
#include "../DreamWarcraft/Version.h"

#include "ThreadLogin.h"
#include "ThreadLogout.h"
#include "ThreadAlive.h"

namespace Auth {

static bool Inited = false;

static bool LoggedIn = false;
static HANDLE LogoutEvent = NULL;
static SessionDataType SessionData;
static AuthDataType AuthData = {0};
static char SessionId[33];

//Threads
static ThreadLogin* LoginThread = NULL;
static ThreadLogout* LogoutThread = NULL;
static ThreadAlive* AliveThread = NULL;

static void WaitWorkerThreads();

SimpleUI::Delegate<bool> onLoginComplete;
SimpleUI::Delegate<bool> onLogoutComplete;
SimpleUI::Delegate<void> onDisconnect;

const char* GetSessionId() {return SessionId;}

SessionDataType* GetSessionData() {
	return &SessionData;
}

const wchar_t* GetLastLoginPasswordHash() {
	static wchar_t PasswordHashUnicode[33];
	MultiByteToWideChar(CP_UTF8, NULL, LoginThread->GetPasswordHash(), -1, PasswordHashUnicode, 33);
	return PasswordHashUnicode;
}

static void onAliveThreadComplete(WorkerThread* this_thread) {
	LoggedIn = false;
	delete AliveThread;
	AliveThread = NULL;
	onDisconnect.Invoke();
}

static void onLoginThreadComplete(WorkerThread* this_thread) {
	VMProtectBeginVirtualization("Auth::onLoginThreadComplete");
	SessionType session;
	SessionData.GetData(&session);
	AuthData.days_left = session.remain_time ? (int)ceil((double)session.remain_time / (3600.0 * 24.0)) : 0;
	memcpy_s(SessionId, 33, session.id, 32);
	SessionId[32] = '\0';
	memset(&session, 0, sizeof(SessionType));
	LoggedIn = this_thread->result() > 0;
	if (LoggedIn) {
		AliveThread = new ThreadAlive();
		AliveThread->onThreadComplete += onAliveThreadComplete;
		AliveThread->Run((DWORD)&SessionData);
	}
	onLoginComplete.Invoke(LoggedIn);
	VMProtectEnd();
}

NOINLINE void Login(const wchar_t* account, const wchar_t* password) {
	VMProtectBeginVirtualization("Auth::Login");
	if (!LoggedIn) {
		if (AuthData.inited) {
			delete [] AuthData.account;
			delete [] AuthData.password;
		} else 
			AuthData.inited = true;

		AuthData.account = new wchar_t[wcslen(account) + 1];
		wcscpy_s(AuthData.account, wcslen(account) + 1, account);

		AuthData.password = new wchar_t[wcslen(password) + 1];
		wcscpy_s(AuthData.password, wcslen(password) + 1, password);

		LoginThread->SetCredencial(account, password);
		LoginThread->Run((DWORD)&SessionData);
	}
	VMProtectEnd();
}

const AuthDataType* GetAuthData() {
	return &AuthData;
}

static void onLogoutThreadComplete(WorkerThread* this_thread) {
	bool success = this_thread->result() > 0;
	LoggedIn = false;
	AliveThread->Wait();	
	delete AliveThread;
	AliveThread = NULL;
	onLogoutComplete.Invoke(success);
}

NOINLINE void Logout() {
	VMProtectBeginVirtualization("Auth::Logout");
	if (LoggedIn) {
		AliveThread->onThreadComplete -= onAliveThreadComplete;
		AliveThread->StopSignal();
		LogoutThread->Run((DWORD)&SessionData);
	}
	VMProtectEnd();
}

void Init() {
	VMProtectBeginVirtualization("Auth::Init");
	Inited = true;
	LogoutEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	//Threads
	LoginThread = new ThreadLogin();
	LoginThread->onThreadComplete += onLoginThreadComplete;

	LogoutThread = new ThreadLogout();
	LogoutThread->onThreadComplete += onLogoutThreadComplete;

	VMProtectEnd();
}

void Cleanup() {
	if (Inited) {
		VMProtectBeginVirtualization("Auth::Cleanup");

		WaitWorkerThreads();

		//Threads
		delete LogoutThread;
		delete LoginThread;
		delete AliveThread;
		
		CloseHandle(LogoutEvent);

		if (AuthData.inited) {
			delete [] AuthData.account;
			delete [] AuthData.password;
			AuthData.inited = false;
		}
		VMProtectEnd();
	}
}

static void WaitWorkerThreads() {
	LoginThread->Wait();
	LogoutThread->Wait();
}

uint32_t TranslateServerResponse() {
	LoginResultEnumType result = LoginThread->login_result()->server_response;
	uint32_t string_id = STR::CONNECTION_FAILED;
	uint32_t msg_map[0xFF] = {0};
#define MAP_MSG(id) msg_map[Auth::##id] = STR::##id
	MAP_MSG(LOGIN_RESULT_AUTH_FAILED);
	//MAP_MSG(LOGIN_RESULT_SESSION_ERROR);
	MAP_MSG(LOGIN_RESULT_EXPIRED);
	MAP_MSG(LOGIN_RESULT_BANNED);
	MAP_MSG(LOGIN_RESULT_MULTI);
#undef MAP_MSG
	if (msg_map[result])
		string_id = msg_map[result];
	return string_id;
}

LoginResultEnumType GetLastLoginResult() {
	return LoginThread->login_result()->server_response;
}

} //namespace