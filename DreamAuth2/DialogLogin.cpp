#include "stdafx.h"
#include "DialogLogin.h"

#include "resource.h"
#include "ResString.h"

#include "Utils.h"
#include "../DreamWarcraft/Version.h"

void DialogLogin::OnControlClickHandler(SimpleUI::Control* ctl) {
	DialogLogin* dialog = (DialogLogin*)ctl->parent();
	if (ctl == dialog->l_buy_) {
		dialog->onDialogLoginEvent.Invoke(EVENT_BUY_CLICK);
	} else if (ctl == dialog->l_help_) {
		dialog->onDialogLoginEvent.Invoke(EVENT_HELP_CLICK);
	}
}

void DialogLogin::OnCommandHandler(Control* ctl) {
	DialogLogin* dialog = (DialogLogin*)ctl->parent();
	if (ctl == dialog->t_account_ || ctl == dialog->t_password_) {
		dialog->CheckInput();
	} else if (ctl == dialog->c_remember_) {
		dialog->onDialogLoginEvent(EVENT_REMEMBER_PASSWORD_CHANGE);
	} else if (ctl == dialog->c_auto_login_) {
		dialog->onDialogLoginEvent(EVENT_AUTO_LOGIN_CHANGE);
	} else if (ctl == dialog->b_action_) {
		dialog->onDialogLoginEvent(EVENT_LOGIN_CLICK);
	}
}

DialogLogin::DialogLogin() : SimpleUI::Dialog(IDD_LOGIN) {
	this->link_font_ = 	CreateFont(
		14, //__in  int nHeight,
		0, //__in  int nWidth,
		0, //__in  int nEscapement,
		0, //  int nOrientation,
		FW_BOLD, //__in  int fnWeight,
		false, //__in  DWORD fdwItalic,
		true, //__in  DWORD fdwUnderline,
		false, //__in  DWORD fdwStrikeOut,
		ANSI_CHARSET, //__in  DWORD fdwCharSet,
		OUT_OUTLINE_PRECIS, //__in  DWORD fdwOutputPrecision,
		CLIP_DEFAULT_PRECIS, //__in  DWORD fdwClipPrecision,
		CLEARTYPE_QUALITY, //__in  DWORD fdwQuality,
		VARIABLE_PITCH, //__in  DWORD fdwPitchAndFamily,
		NULL
	);

	AssignItem<Control>(l_account_, L_ACCOUNT);
	SETCONTROLTEXT(l_account_, ACCOUNT);

	AssignItem<Control>(l_password_, L_PASSWORD);
	SETCONTROLTEXT(l_password_, PASSWORD);

	AssignItem<CheckBox>(c_remember_, C_REMEMBER);
	SETCONTROLTEXT(c_remember_, REMEMBER_PASSWORD);

	AssignItem<CheckBox>(c_auto_login_, C_AUTO_LOGIN);
	SETCONTROLTEXT(c_auto_login_, AUTO_LOGIN);

	AssignItem<Control>(l_help_, L_HELP);
	SETCONTROLTEXT(l_help_, HELP);
	this->l_help_->SetColor(RGB(0x2E,0xB0,0xDF));
	this->l_help_->SetFont(this->link_font_);
	this->l_help_->SetLinkMode(true);

	AssignItem<Control>(l_buy_, L_BUY);
	SETCONTROLTEXT(l_buy_, PURCHASE_AND_TOP_UP);
	this->l_buy_->SetColor(RGB(0x2E,0xB0,0xDF));
	this->l_buy_->SetFont(this->link_font_);
	this->l_buy_->SetLinkMode(true);

	AssignItem<Control>(t_account_, T_ACCOUNT);
	AssignItem<Control>(t_password_, T_PASSWORD);

	AssignItem<Control>(b_action_, B_ACTION);
	SETCONTROLTEXT(b_action_, LOGIN);

	wchar_t version_string[32];
	swprintf_s(version_string, 31, L"%u.%02u.%u.%04u", VERSION.main, VERSION.release, VERSION.build, VERSION.revision);
#ifdef _BETA
	wcscat_s(version_string, L" (BETA)");
#endif
	::SetWindowText(this->GetItem(L_VERSION), version_string);

	this->SetState(STATE_INITIAL);

	this->onCommand += OnCommandHandler;
	this->onControlClick += OnControlClickHandler;
}

DialogLogin::~DialogLogin() {
	DeleteObject(this->link_font_);
}

void DialogLogin::SetState(DialogLoginStateEnum state) {
	this->state_ = state;
	switch (state) {
	case STATE_INITIAL:
		this->t_account_->EnableWindow(TRUE);
		this->t_password_->EnableWindow(TRUE);
		this->c_auto_login_->EnableWindow(TRUE);
		this->c_remember_->EnableWindow(TRUE);
		this->b_action_->SetWindowText(ResString::GetString(ResString::LOGIN));
		this->b_action_->EnableWindow(FALSE);
		break;
	case STATE_READY:
		this->t_account_->EnableWindow(TRUE);
		this->t_password_->EnableWindow(TRUE);
		this->c_auto_login_->EnableWindow(TRUE);
		this->c_remember_->EnableWindow(TRUE);
		this->b_action_->SetWindowText(ResString::GetString(ResString::LOGIN));
		this->b_action_->EnableWindow(TRUE);
		break;
	case STATE_LOGGIN_IN:
		this->t_account_->EnableWindow(FALSE);
		this->t_password_->EnableWindow(FALSE);
		this->c_auto_login_->EnableWindow(FALSE);
		this->c_remember_->EnableWindow(FALSE);
		this->b_action_->SetWindowText(ResString::GetString(ResString::LOGGING_IN));
		this->b_action_->EnableWindow(FALSE);
		break;
	}
}

void DialogLogin::CheckInput() {
	if (this->t_account_->GetWindowTextLength() && this->t_password_->GetWindowTextLength()) {
		if (this->state_ == STATE_INITIAL) {
			this->SetState(STATE_READY);
		}
	} else {
		if (this->state_ == STATE_READY) {
			this->SetState(STATE_INITIAL);
		}
	}
}