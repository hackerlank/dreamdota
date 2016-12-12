#include "stdafx.h"
#include "Loggedin.h"
#include "GameModule.h"
#include "DialogMain.h"
#include "Auth.h"
#include "LocaleString.h"
#include "ResString.h"
#include "Main.h"
#include "../DreamWarcraft/Profile.h"

#include "SMRoamingProfile.h"

namespace Loggedin {
SimpleUI::Delegate<EventEnum> onEvent;

DialogMain* Dialog = NULL;

static ServiceModule* ActiveModule = NULL;
static SMRoamingProfile* RoamingProfileSM;

static EventEnum Event;
typedef std::map<uint32_t, std::wstring> StringCacheType;
static std::map<uint32_t, std::wstring>* StringCache = NULL;
static CRITICAL_SECTION StringCacheCs;
enum ServiceMenuItemEnum {
	SERVICE_MENU_RP = 1
};
static HMENU ServiceMenu;

void OutputEncryptedMessage(uint32_t id, ...) {
	const wchar_t* msg;
	EnterCriticalSection(&StringCacheCs);
	if (!StringCache->count(id)) {
		std::wstring& str = StringCache->operator[](id);
		str.assign(StringManager::StringUnicode(id));
		msg = str.c_str();
	} else {
		msg = StringCache->operator[](id).c_str();
	}
	va_list args;
	va_start(args, id);
	Dialog->Output(msg, args);
	va_end(args);
	LeaveCriticalSection(&StringCacheCs);
}

void OutputMessage(const wchar_t* format, ...) {
	va_list args;
	va_start(args, format);
	Dialog->Output(format, args);
	va_end(args);
}

static INT_PTR ON_WM_CLOSE(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Event = EVENT_EXIT;
	Dialog->SetState(DialogMain::STATE_LOCK);

	Dialog->Output(ResString::GetString(ResString::LOGGING_OUT));
	Auth::Logout();

	return TRUE;
}

static void onServiceModulePerformComplete(bool success) {
	Dialog->EnableWindow(TRUE);
	Dialog->Show(true);
	ActiveModule = NULL;
}

static INT_PTR ON_WM_COMMAND(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == 0 && LOWORD(wParam) == SERVICE_MENU_RP) {
		ActiveModule = RoamingProfileSM;
		Dialog->EnableWindow(FALSE);
		Dialog->Show(false);
		RoamingProfileSM->Perform();
	}
	return FALSE;
}

static SimpleUI::RadioBox* GetInjectMethodControl(GameModule::InjectMethodEnum method) {
	switch (method) {
	case GameModule::INJECT_METHOD_AUTO:
		return Dialog->r_inject_auto();
	case GameModule::INJECT_METHOD_PASSIVE:
		return Dialog->r_inject_passive();
	}
	return NULL;
}

static void UpdateInjectMethodUI(GameModule::InjectMethodEnum method) {
	SimpleUI::RadioBox* c = GetInjectMethodControl(method);
	if (c) {
		switch (method) {
		case GameModule::INJECT_METHOD_AUTO:
			
			break;
		case GameModule::INJECT_METHOD_PASSIVE:
				
			break;
		}
		c->SetCheck(true);
	}
}

static void UpdateInjectMethodComplete(bool success) {
	GameModule::onActionComplete -= UpdateInjectMethodComplete;
	GameModule::InjectMethodEnum m = GameModule::GetCurrentMethod();
	if (success)
		OutputEncryptedMessage(STR::SUCCESS);
	else {
		OutputEncryptedMessage(STR::FAILURE);
		Dialog->Output(GameModule::GetLastErrorMessage());
	}
	Dialog->SetState(DialogMain::STATE_UNLOCK);
	Dialog->r_inject_auto()->SetCheck(false);
	Dialog->r_inject_passive()->SetCheck(false);
	GetInjectMethodControl(m)->SetCheck(true);
}

static void UpdateInjectMethod() {
	GameModule::InjectMethodEnum m;
	if (Dialog->r_inject_auto()->IsChecked()) {
		m = GameModule::INJECT_METHOD_AUTO;
	} else if (Dialog->r_inject_passive()->IsChecked()) {
		m = GameModule::INJECT_METHOD_PASSIVE;
	}

	if (m != GameModule::GetCurrentMethod()) {
		OutputEncryptedMessage(STR::PREPARING_INJECTION);
		Dialog->SetState(DialogMain::STATE_LOCK);
		GameModule::onActionComplete += UpdateInjectMethodComplete;
		GameModule::Change(m);
	}
}

static void OnCommand(SimpleUI::Control* ctl) {
	if (ctl == Dialog->b_logout()) {
		Dialog->SetState(DialogMain::STATE_LOCK);
		Event = EVENT_LOGOUT;
		ctl->EnableWindow(FALSE);

		Dialog->Output(ResString::GetString(ResString::LOGGING_OUT));
		Auth::Logout();
	} else if (ctl == Dialog->r_inject_auto() 
		|| ctl == Dialog->r_inject_passive()) {
			UpdateInjectMethod();
	} else if (ctl == Dialog->b_services()) {
		RECT rb;
		GetWindowRect(Dialog->b_services()->handle(), &rb);
		TrackPopupMenu(ServiceMenu, TPM_TOPALIGN, rb.left, rb.bottom, 0, Dialog->handle(), 0);
	}
}

static void onLogoutComplete2(bool success) {
	GameModule::onActionComplete -= onLogoutComplete2;
	if (Event == EVENT_LOGOUT) {
		Dialog->EnableWindow(FALSE);
		Dialog->Show(false); 
	} else {
		Dialog->Close();
	}
	onEvent.Invoke(Event);
}

static void OnLogoutComplete(bool success) {
	GameModule::onActionComplete += onLogoutComplete2;
	GameModule::Stop();
}

static void onDisconnectComplete(bool success) {
	GameModule::onActionComplete -= onDisconnectComplete;
	Dialog->EnableWindow(FALSE);
	Dialog->Show(false); 	
	Dialog->SetState(DialogMain::STATE_UNLOCK);
	onEvent.Invoke(EVENT_LOGOUT);
}

static void OnDisconnect() {
	if (ActiveModule) {
		ActiveModule->Term();
		ActiveModule = NULL;
	}
	Dialog->SetState(DialogMain::STATE_LOCK);
	GameModule::onActionComplete += onDisconnectComplete;
	GameModule::Stop();
	MessageBox(Dialog->handle(), StringManager::StringUnicode(STR::CONNECTION_FAILED).c_str(), NULL, MB_ICONERROR);
}

void Init() {
	RoamingProfileSM = SMRoamingProfile::GetInstance();
	RoamingProfileSM->onPerformComplete += onServiceModulePerformComplete;

	Dialog = new DialogMain();
	Dialog->AddDialogMessageHandler(WM_CLOSE, ON_WM_CLOSE);
	Dialog->AddDialogMessageHandler(WM_COMMAND, ON_WM_COMMAND);

	Dialog->onCommand += OnCommand;

	Auth::onLogoutComplete += OnLogoutComplete;
	Auth::onDisconnect += OnDisconnect;

	StringCache = new StringCacheType();
	InitializeCriticalSection(&StringCacheCs);
	
	ServiceMenu = CreatePopupMenu();
	AppendMenu(ServiceMenu, MF_STRING, SERVICE_MENU_RP, ResString::GetString(ResString::ROAMING_PROFILE));
}

void Cleanup() {
	DeleteCriticalSection(&StringCacheCs);
	delete StringCache;

	Auth::onDisconnect -= OnDisconnect;
	Auth::onLogoutComplete -= OnLogoutComplete;

	delete Dialog;

	SMRoamingProfile::DestoryInstance();
}

void MainDialog() {
	Dialog->SetState(DialogMain::STATE_INITIAL);

	Dialog->EnableWindow(TRUE);
	Dialog->l_account()->SetWindowText(Auth::GetAuthData()->account);
	Dialog->CleanOutput();
	if (Auth::GetAuthData()->days_left) {
		OutputEncryptedMessage(STR::LOGIN_WELCOME, Auth::GetAuthData()->days_left);
	} else
		OutputEncryptedMessage(STR::LOGIN_WELCOME_UNLIMITED);
	
	Dialog->Output(ResString::GetString(ResString::WAR3_NOTE));
	
	Dialog->Show(true);
	
	Dialog->SetState(DialogMain::STATE_LOCK);

	OutputEncryptedMessage(STR::PREPARING_INJECTION);
	GameModule::onActionComplete += UpdateInjectMethodComplete;
	GameModule::Start();
}

}//namespace