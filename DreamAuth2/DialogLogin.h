#include "stdafx.h"
#ifndef DIALOGLOGIN_H_
#define DIALOGLOGIN_H_
#include "resource.h"

#include <SimpleUI\SimpleUI.h>

class DialogLogin : public SimpleUI::Dialog {
public:
	enum DialogLoginStateEnum {
		STATE_INITIAL,
		STATE_READY,
		STATE_LOGGIN_IN
	};

	enum DialogLoginEventEnum {
		EVENT_LOGIN_CLICK,
		EVENT_REMEMBER_PASSWORD_CHANGE,
		EVENT_AUTO_LOGIN_CHANGE,
		EVENT_HELP_CLICK,
		EVENT_BUY_CLICK
	};

	SimpleUI::Delegate<DialogLoginEventEnum> onDialogLoginEvent;

	void SetState(DialogLoginStateEnum state);

	DialogLogin();
	virtual ~DialogLogin();
private:
	typedef SimpleUI::Control Control;
	typedef SimpleUI::CheckBox CheckBox;

	static void OnControlClickHandler(Control* ctl);
	static void OnCommandHandler(Control* ctl);

	void CheckInput();

	HFONT link_font_;
	DialogLoginStateEnum state_;

	GETSET(Control*, l_account)
	GETSET(Control*, l_password)
	GETSET(CheckBox*, c_remember)
	GETSET(CheckBox*, c_auto_login)
	GETSET(Control*, l_help)
	GETSET(Control*, l_buy)

	GETSET(Control*, t_account)
	GETSET(Control*, t_password)

	GETSET(Control*, b_action)
};

#endif