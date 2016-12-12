#include "DialogLanguageSelect.h"

#include "resource.h"
#include "ResString.h"
#include "Locale.h"

DialogLanguageSelect::~DialogLanguageSelect() {

}

void DialogLanguageSelect::onOKCommandHandler(Control* ctl) {
	DialogLanguageSelect* dialog = (DialogLanguageSelect*)ctl->parent();
	int sel = dialog->l_list_->GetCurSel();
	if (sel != CB_ERR)
		dialog->onLanguageSelect.Invoke(dialog->l_list_->GetItemData(sel));
	dialog->Close();
}

DialogLanguageSelect::DialogLanguageSelect() : Dialog(IDD_LANGSEL) {
	this->AssignItem<ComboBox>(this->l_list_, LI_LANG);
	this->AssignItem<Control>(this->b_ok_, IDOK);

	this->b_ok_->onCommand += DialogLanguageSelect::onOKCommandHandler;
}

int DialogLanguageSelect::AddLocale(const wchar_t* name, LCID lcid) {
	int index = this->l_list_->AddString(name);
	this->l_list_->SetItemData(index, LPARAM(lcid));
	return index;
}