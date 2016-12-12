#include "stdafx.h"
#ifndef DIALOGMAIN_H_
#define DIALOGMAIN_H_

#include <SimpleUI\SimpleUI.h>
#include <stdarg.h>
#include <ctime>

class DialogMain : public SimpleUI::Dialog {
public:
	static INT_PTR ON_WM_NOTIFY(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam); 
	static void OnLinkClick(SimpleUI::Control* ctl);

	DialogMain();
	virtual ~DialogMain();

	void CleanOutput() {
		this->t_output_->SetWindowText(L"");
	}

	void Output(const wchar_t* format, va_list args) {
		time_t rawtime;
		struct tm timeinfo;
		time ( &rawtime );
		localtime_s(&timeinfo, &rawtime);

		wchar_t buffer[BUFSIZ];
		wcsftime(buffer, BUFSIZ, L"%X  ", &timeinfo);
		size_t timestr_len = wcslen(buffer);


		vswprintf_s(buffer + timestr_len, BUFSIZ - timestr_len, format, args);
		this->t_output_->AppendText(buffer);
		SendMessage(this->t_output_->handle(), EM_LINESCROLL, NULL , SendMessage(this->t_output_->handle(), EM_GETLINECOUNT, NULL, NULL));
	}

	void Output(const wchar_t* format, ...) {
		va_list args;
		va_start(args, format);
		Output(format, args);
		va_end(args);
	}

	enum StateEnum {
		STATE_INITIAL,
		STATE_LOCK,
		STATE_UNLOCK
	};
	void SetState(StateEnum s);
private:
	typedef SimpleUI::Control Control;
	typedef SimpleUI::RadioBox RadioBox;

	GETSET(Control*, l_version);
	GETSET(Control*, l_version_value);
	GETSET(Control*, l_help);
	GETSET(Control*, l_buy);
	GETSET(Control*, g_account);
	GETSET(Control*, l_account);
	GETSET(Control*, g_inject);
	GETSET(RadioBox*, r_inject_auto);
	GETSET(RadioBox*, r_inject_passive);
	GETSET(Control*, b_logout);
	GETSET(Control*, t_output);
	GETSET(Control*, b_services);

	HFONT link_font_;
	HFONT bold_font_;
	HFONT version_font_;

	HWND tooltip_;
};

#endif