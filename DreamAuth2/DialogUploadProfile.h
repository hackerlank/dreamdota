#ifndef DIALOG_UPLOAD_PROFILE_
#define DIALOG_UPLOAD_PROFILE_

#include <SimpleUI\SimpleUI.h>

class DialogUploadProfile : public SimpleUI::Dialog {
public:
	static INT_PTR DialogUploadProfile::ON_WM_CLOSE(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR ON_WM_COMMAND(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam);

	DialogUploadProfile();
	virtual ~DialogUploadProfile();

	void SetName(const wchar_t* name) {this->t_name_->SetWindowText(name);UpdateOKBtn();}
	const wchar_t* GetName() {return this->t_name_->GetText();}
	const char* GetNameUTF8() {
		WideCharToMultiByte(CP_UTF8, NULL, GetName(), -1, this->name_utf8_, MAX_PATH - 1, NULL, NULL);
		this->name_utf8_[MAX_PATH - 1] = '\0';
		return this->name_utf8_;
	}
private:
	typedef SimpleUI::Control Control;

	void UpdateOKBtn() {this->b_ok_->EnableWindow(this->t_name_->GetWindowTextLength() > 0 ? TRUE : FALSE);}
	
	GETSET(Control*, l_top);
	GETSET(Control*, t_name);
	GETSET(Control*, b_ok);
	GETSET(Control*, b_cancel);

	char name_utf8_[MAX_PATH];
};

#endif