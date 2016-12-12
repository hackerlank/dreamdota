#ifndef COMBOBOX_H_
#define COMBOBOX_H_

#include "Control.h"

namespace SimpleUI {

class ComboBox : public Control {
public:
	ComboBox(HWND handle);
	virtual ~ComboBox();

	int GetCurSel() {return ComboBox_GetCurSel(this->handle());}
	int SetCurSel(int index) {return ComboBox_SetCurSel(this->handle(), index);}
	int AddString(const wchar_t* string) {return ComboBox_AddString(this->handle(), string);}
	int SelectString(const wchar_t* string, int indexStart = -1) {return ComboBox_SelectString(this->handle(), indexStart, string);}
	int FindString(const wchar_t* string, int indexStart = -1) {return ComboBox_FindString(this->handle(), indexStart, string);}
	int FindStringExact(const wchar_t* string, int indexStart = -1) {return ComboBox_FindStringExact(this->handle(), indexStart, string);}
	int SetItemData(int index, LPARAM data) {return ComboBox_SetItemData(this->handle(), index, data);}
	LRESULT GetItemData(int index) {return ComboBox_GetItemData(this->handle(), index);}
};

} //namespace

#endif