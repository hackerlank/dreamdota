#include "stdafx.h"
#ifndef AUTH_H_
#define AUTH_H_

#include <SimpleUI\Delegate.h>
#include "EncryptedData.h"
#include "RSA.h"

namespace Auth {
	const uint32_t SESSION_ID_SIZE = 32;
#ifdef _DEBUG
	const uint32_t ALIVE_INTERVAL = 5000; //5√Î
#else
	const uint32_t ALIVE_INTERVAL = 60000; //60√Î
#endif

	struct SessionType {
		BYTE KeyData[RSA_SIZE];

		uint32_t remain_time;
		
		char id[SESSION_ID_SIZE];
	};

	typedef EncryptedData<SessionType> SessionDataType;

	struct AuthDataType {
		bool inited;
		wchar_t* account;
		wchar_t* password;
		int days_left;
	};

	const wchar_t* GetLastLoginPasswordHash();

	//Server
	enum LoginResultEnumType {
		LOGIN_RESULT_OK,
		LOGIN_RESULT_FAILED,
		LOGIN_RESULT_AUTH_FAILED,
		LOGIN_RESULT_SESSION_ERROR,
		LOGIN_RESULT_EXPIRED,
		LOGIN_RESULT_BANNED,
		LOGIN_RESULT_MULTI,
		LOGIN_RESULT_CLIENT_VERSION_EXPIRED
	};

	uint32_t TranslateServerResponse();

	extern SimpleUI::Delegate<bool> onLoginComplete;
	extern SimpleUI::Delegate<bool> onLogoutComplete;
	extern SimpleUI::Delegate<void> onDisconnect;

	void Init();
	void Cleanup();

	NOINLINE void Login(const wchar_t* account, const wchar_t* password);
	NOINLINE void Logout();

	const AuthDataType* GetAuthData();
	SessionDataType* GetSessionData();
	const char* GetSessionId();
	LoginResultEnumType GetLastLoginResult();

} //namespace

#endif