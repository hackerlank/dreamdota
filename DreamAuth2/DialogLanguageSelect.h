#include "stdafx.h"
#ifndef DIALOGLANGUAGESELECT_H_
#define DIALOGLANGUAGESELECT_H_

#include <SimpleUI\SimpleUI.h>

class DialogLanguageSelect : public SimpleUI::Dialog {
public:
	SimpleUI::Delegate<LCID> onLanguageSelect;

	int AddLocale(const wchar_t* name, LCID lcid);
	void SelectString(const wchar_t* string) {this->l_list_->SelectString(string);}

	DialogLanguageSelect();
	virtual ~DialogLanguageSelect();

private:
	typedef SimpleUI::Control Control;
	typedef SimpleUI::ComboBox ComboBox;

	static void DialogLanguageSelect::onOKCommandHandler(Control* ctl);

	ComboBox* l_list_;
	Control* b_ok_;
};

#endif