#ifndef SIMPLEUI_LISTBOX_
#define SIMPLEUI_LISTBOX_

#include "Control.h"

namespace SimpleUI {

class ListBox : public Control {
public:
	int AddString(const wchar_t* v) {
		return SendMessage(this->handle(), LB_ADDSTRING, NULL, LPARAM(v));
	}

	int DeleteString(int index) {
		return SendMessage(this->handle(), LB_DELETESTRING, WPARAM(index), NULL);
	}

	int GetCount() {
		return SendMessage(this->handle(), LB_GETCOUNT, NULL, NULL);
	}

	int GetCurSel() {
		return SendMessage(this->handle(), LB_GETCURSEL, NULL, NULL);
	}

	int SetCurSel(int index) {
		return SendMessage(this->handle(), LB_SETCURSEL, WPARAM(index), NULL);
	}

	int ResetContent() {
		return SendMessage(this->handle(), LB_RESETCONTENT, NULL, NULL);
	}

	int SetItemData(int index, DWORD data) {
		return SendMessage(this->handle(), LB_SETITEMDATA, index, data);
	}

	DWORD GetItemData(int index) {
		return SendMessage(this->handle(), LB_GETITEMDATA, index, NULL);
	}

	using Window::GetText;

	int GetText(int index, wchar_t* buffer) {
		return SendMessage(this->handle(), LB_GETTEXT, index, LPARAM(buffer)); 
	}

	int GetTextLen(int index) {
		return SendMessage(this->handle(), LB_GETTEXTLEN, index, NULL); 
	}

	ListBox(HWND handle);
	virtual ~ListBox();
};

} //namespace


#endif