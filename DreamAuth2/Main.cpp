#include "Main.h"
#include "Loggedin.h"
#include "DialogLogin.h"
#include "LanguageSelect.h"
#include "LocaleString.h"
#include "Auth.h"
#include "NTDLL.h"
#include "GameModule.h"
#include "AutoUpdate.h"
#include "../DreamWarcraft/Profile.h"

static DialogLogin* Dialog = NULL;

static void Login();

bool AdminPrivilegeAvaliable = false;
bool IsAdminPrivilegeAvaliable() {
	return AdminPrivilegeAvaliable;
}

bool WantRememberPassword() {
	return ProfileGetInt(L"Auth", L"RememberPassword", 0) > 0;
}

bool WantAutoLogin() {
	return ProfileGetInt(L"Auth", L"AutoLogin", 0) > 0;
}

static bool RestoreSavedPassword() {
	Dialog->t_account()->SetWindowText(ProfileGetString(L"Auth", L"Account", L""));
	const wchar_t* saved_pswd = ProfileGetString(L"Auth", L"Password", L"");
	if (wcslen(saved_pswd) == 32) {
		Dialog->t_password()->SetWindowText(saved_pswd);
	}
	return Dialog->t_account()->GetWindowTextLength() > 0 && Dialog->t_password()->GetWindowTextLength() == 32;
}

static void SavePassword(bool want) {
	if (want) {
		ProfileSetString(L"Auth", L"Account", Dialog->t_account()->GetText());
		ProfileSetString(L"Auth", L"Password", Auth::GetLastLoginPasswordHash());
	} else {
		ProfileSetString(L"Auth", L"Account", L"");
		ProfileSetString(L"Auth", L"Password", L"");
	}
}

static void OnDialogLoginEventHandler(DialogLogin::DialogLoginEventEnum event_id) {
	switch(event_id) {
	case DialogLogin::EVENT_HELP_CLICK:
		ShellExecute(NULL, NULL, L"http://www.dreamdota.com/dd3/help", NULL, NULL, SW_MAXIMIZE);
		break;
	case DialogLogin::EVENT_BUY_CLICK:
		ShellExecute(NULL, NULL, L"http://www.dreamdota.com/dd3/buy", NULL, NULL, SW_MAXIMIZE);
		break;
	case DialogLogin::EVENT_LOGIN_CLICK:
		Login();
		break;
	case DialogLogin::EVENT_REMEMBER_PASSWORD_CHANGE:
		ProfileSetInt(L"Auth", L"RememberPassword", Dialog->c_remember()->IsChecked() ? 1 : 0);
		break;
	case DialogLogin::EVENT_AUTO_LOGIN_CHANGE:
		ProfileSetInt(L"Auth", L"AutoLogin", Dialog->c_auto_login()->IsChecked() ? 1 : 0);
		break;
	}
}

static void OnLoginComplete(bool success) {
	if (success) {
		bool want_remember_password = WantRememberPassword();
		if (!want_remember_password) {
			Dialog->t_account()->SetWindowText(L"");
			Dialog->t_password()->SetWindowText(L"");
		}
		SavePassword(want_remember_password);

		Dialog->EnableWindow(FALSE);
		Dialog->Show(false);
		Loggedin::MainDialog();
	} else {
		if (Auth::GetLastLoginResult() == Auth::LOGIN_RESULT_CLIENT_VERSION_EXPIRED) {
			Dialog->EnableWindow(FALSE);
			Dialog->Show(false);
			if (AutoUpdate::AutoUpdate())
				Dialog->Close();
			else {
				Dialog->SetState(DialogLogin::STATE_READY);
				Dialog->EnableWindow(TRUE);
				Dialog->Show(true);
			}
		} else {
			MessageBox(Dialog->handle(), StringManager::StringUnicode(Auth::TranslateServerResponse()).c_str(), NULL, MB_ICONERROR);
			Dialog->SetState(DialogLogin::STATE_READY);
		}
	}
}

static void OnLoggedinEvent(Loggedin::EventEnum e) {
	switch (e) {
	case Loggedin::EVENT_LOGOUT:
		Dialog->EnableWindow(TRUE);
		Dialog->SetState(DialogLogin::STATE_READY);
		Dialog->Show(true);
		break;

	case Loggedin::EVENT_EXIT:
		Dialog->Close();
		break;
	}
}

int Main() {
	LanguageSelect();

	BOOLEAN enabled;
	AdminPrivilegeAvaliable = true;
	if (!NT_SUCCESS(NTDLL::RtlAdjustPrivilege(NTDLL::SE_DEBUG_PRIVILEGE, 1, 0, &enabled))) {
		MessageBox(NULL, StringManager::StringUnicode(STR::REQUIRE_ADMIN).c_str(), L"", MB_ICONWARNING);
		AdminPrivilegeAvaliable = false;
	}

	Auth::onLoginComplete += OnLoginComplete;

	Loggedin::Init();
	Loggedin::onEvent += OnLoggedinEvent;

	GameModule::Init();

	Dialog = new DialogLogin();

	Dialog->c_remember()->SetCheck(WantRememberPassword());
	Dialog->c_auto_login()->SetCheck(WantAutoLogin());

	Dialog->onDialogLoginEvent += OnDialogLoginEventHandler;
	Dialog->Show(true);

	if (RestoreSavedPassword() && WantAutoLogin()) {
		Login();
	}

	Dialog->WaitClose();
	
	GameModule::Cleanup();

	Loggedin::onEvent -= OnLoggedinEvent;
	Loggedin::Cleanup();

	Auth::onLoginComplete -= OnLoginComplete;

	delete Dialog;
	return 0;
}

static void Login() {
	Dialog->SetState(DialogLogin::STATE_LOGGIN_IN);

	wchar_t account[64], password[64];
	Dialog->t_account()->GetWindowText(account, sizeof(account) / sizeof(wchar_t));
	Dialog->t_password()->GetWindowText(password, sizeof(password) / sizeof(wchar_t));
	Auth::Login(account, password);
}

