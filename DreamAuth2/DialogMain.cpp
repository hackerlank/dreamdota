#include "DialogMain.h"

#include "resource.h"
#include "ResString.h"
#include "Utils.h"
#include "../DreamWarcraft/Version.h"
#include "Main.h"

INT_PTR DialogMain::ON_WM_NOTIFY(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	/*
	NMHDR *nm = (NMHDR *) lParam;
	switch (nm->code)
	{
		break;
	}
	//OutputDebug("nm->code = 0x%08X\n", nm->code);
	*/
	return FALSE;
}

void DialogMain::OnLinkClick(SimpleUI::Control* ctl) {
	DialogMain* dialog = (DialogMain*)ctl->parent();
	if (ctl == dialog->l_buy_) {
		ShellExecute(NULL, NULL, L"http://www.dreamdota.com/dd3/buy", NULL, NULL, SW_MAXIMIZE);
	} else if (ctl == dialog->l_help_) {
		ShellExecute(NULL, NULL, L"http://www.dreamdota.com/dd3/help", NULL, NULL, SW_MAXIMIZE);
	}
}

DialogMain::DialogMain() : SimpleUI::Dialog(IDD_MAIN) {
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

	this->bold_font_ = 	CreateFont(
		14, //__in  int nHeight,
		0, //__in  int nWidth,
		0, //__in  int nEscapement,
		0, //  int nOrientation,
		FW_BOLD, //__in  int fnWeight,
		false, //__in  DWORD fdwItalic,
		false, //__in  DWORD fdwUnderline,
		false, //__in  DWORD fdwStrikeOut,
		ANSI_CHARSET, //__in  DWORD fdwCharSet,
		OUT_OUTLINE_PRECIS, //__in  DWORD fdwOutputPrecision,
		CLIP_DEFAULT_PRECIS, //__in  DWORD fdwClipPrecision,
		CLEARTYPE_QUALITY, //__in  DWORD fdwQuality,
		VARIABLE_PITCH, //__in  DWORD fdwPitchAndFamily,
		NULL
	);

	this->version_font_ = 	CreateFont(
		12, //__in  int nHeight,
		0, //__in  int nWidth,
		0, //__in  int nEscapement,
		0, //  int nOrientation,
		FW_BOLD, //__in  int fnWeight,
		false, //__in  DWORD fdwItalic,
		false, //__in  DWORD fdwUnderline,
		false, //__in  DWORD fdwStrikeOut,
		ANSI_CHARSET, //__in  DWORD fdwCharSet,
		OUT_OUTLINE_PRECIS, //__in  DWORD fdwOutputPrecision,
		CLIP_DEFAULT_PRECIS, //__in  DWORD fdwClipPrecision,
		CLEARTYPE_QUALITY, //__in  DWORD fdwQuality,
		VARIABLE_PITCH, //__in  DWORD fdwPitchAndFamily,
		L"Verdana"
	);

	this->AssignItem<Control>(this->l_version_, L_VERSION);
	SETCONTROLTEXT(l_version_, VERSION);
	//this->l_version_->SetColor(RGB(0x99, 0xCC, 0xCC));
	//this->l_version_->SetFont(this->bold_font_);

	this->AssignItem<Control>(this->l_version_value_, L_VERSION_VALUE);
	this->l_version_value_->SetFont(this->version_font_);
	wchar_t version_string[64];
	swprintf_s(version_string, 64, L"%u.%02u.%u.%04u", VERSION.main, VERSION.release, VERSION.build, VERSION.revision);
#ifdef _BETA
	wcscat_s(version_string, L"\nBETA");
#endif
	this->l_version_value_->SetWindowText(version_string);
	this->l_version_value_->SetColor(RGB(0x00, 0x33, 0x66));


	AssignItem<Control>(l_help_, L_HELP);
	SETCONTROLTEXT(l_help_, HELP);
	this->l_help_->SetColor(RGB(0x2E,0xB0,0xDF));
	this->l_help_->SetFont(this->link_font_);
	this->l_help_->SetLinkMode(true);
	this->l_help_->onClick += OnLinkClick;

	AssignItem<Control>(l_buy_, L_BUY);
	SETCONTROLTEXT(l_buy_, PURCHASE_AND_TOP_UP);
	this->l_buy_->SetColor(RGB(0x2E,0xB0,0xDF));
	this->l_buy_->SetFont(this->link_font_);
	this->l_buy_->SetLinkMode(true);
	this->l_buy_->onClick += OnLinkClick;

	this->AssignItem<Control>(this->g_account_, G_ACCOUNT);
	SETCONTROLTEXT(g_account_, ACCOUNT);

	this->AssignItem<Control>(this->l_account_, L_ACCOUNTNAME);
	SETCONTROLTEXT(l_account_, ACCOUNT);
	this->l_account_->SetFont(this->bold_font_);

	this->AssignItem<Control>(this->g_inject_, G_INJECT);
	SETCONTROLTEXT(g_inject_, INJECT);

	this->AssignItem<RadioBox>(this->r_inject_auto_, R_AUTO);
	SETCONTROLTEXT(r_inject_auto_, REMOTE_INJECT_AUTO);

	this->AssignItem<RadioBox>(this->r_inject_passive_, R_PASSIVE);
	SETCONTROLTEXT(r_inject_passive_, PASSIVE_INJECT);

	this->AssignItem<Control>(this->b_logout_, B_LOGOUT);
	SETCONTROLTEXT(b_logout_, LOGOUT);

	this->AssignItem<Control>(this->t_output_, T_OUTPUT);
	this->t_output_->SetSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	//this->li_output_->SetFont(this->bold_font_);

	AssignItem<Control>(b_services_, B_SERVICES);
	SETCONTROLTEXT(b_services_, SERVICES);

	/*
	this->AssignItem<Control>(this->l_loading_, L_LOADING);
	this->l_loading_->SetColor(RGB(0x66, 0x66, 0x66));
	SETCONTROLTEXT(l_loading_, INITIALIZING);

	this->bg_brush_ = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	this->border_pen_ = CreatePen(PS_SOLID, 5, RGB(0xC4, 0xF3, 0xFF));

	this->AddDialogMessageHandler(WM_CLOSE, ON_WM_CLOSE);
	this->AddDialogMessageHandler(WM_PAINT, ON_WM_PAINT);
	*/
	
	this->AddDialogMessageHandler(WM_NOTIFY, ON_WM_NOTIFY);
}

void DialogMain::SetState(StateEnum s) {
	switch(s) {
	case STATE_INITIAL:
		this->b_logout_->EnableWindow(TRUE);
		this->b_services_->EnableWindow(TRUE);
		this->r_inject_auto_->EnableWindow(TRUE);
		this->r_inject_passive_->EnableWindow(TRUE);
		this->EnableSystemMenuItem(SC_CLOSE, TRUE);
		break;
	case STATE_LOCK:
		this->b_logout_->EnableWindow(FALSE);
		this->r_inject_auto_->EnableWindow(FALSE);
		this->r_inject_passive_->EnableWindow(FALSE);
		this->b_services_->EnableWindow(FALSE);
		this->EnableSystemMenuItem(SC_CLOSE, FALSE);
		break;
	case STATE_UNLOCK:
		this->b_logout_->EnableWindow(TRUE);
		this->b_services_->EnableWindow(TRUE);
		this->r_inject_auto_->EnableWindow(TRUE);
		this->r_inject_passive_->EnableWindow(TRUE);
		this->EnableSystemMenuItem(SC_CLOSE, TRUE);
		break;
	}
	if (!IsAdminPrivilegeAvaliable())
		this->r_inject_auto_->EnableWindow(FALSE);
}

DialogMain::~DialogMain() {
	DeleteObject(this->link_font_);
	DeleteObject(this->bold_font_);
	DeleteObject(this->version_font_);
}