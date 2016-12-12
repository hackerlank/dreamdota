#include "stdafx.h"
#include "DialogUploadProfile.h"
#include "Utils.h"
#include "ResString.h"

#include "resource.h"

INT_PTR DialogUploadProfile::ON_WM_CLOSE(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	dialog->onCommand.Invoke(((DialogUploadProfile*)dialog)->b_cancel());
	return TRUE;
}

INT_PTR DialogUploadProfile::ON_WM_COMMAND(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	DialogUploadProfile* d = (DialogUploadProfile*)dialog;
	d->UpdateOKBtn();
	return FALSE;
}

DialogUploadProfile::DialogUploadProfile() : Dialog(IDD_UPLOAD_PROFILE) {
	this->SetWindowText(ResString::GetString(ResString::UPLOAD_LOCAL_PROFILE));
	this->AssignItem<Control>(this->l_top_, L_TOP);
	SETCONTROLTEXT(l_top_, PROFILE_NAME);
	this->AssignItem<Control>(this->t_name_, T_NAME);
	this->AssignItem<Control>(this->b_ok_, IDOK);
	SETCONTROLTEXT(b_ok_, UPLOAD);
	this->b_ok_->EnableWindow(FALSE);
	this->AssignItem<Control>(this->b_cancel_, IDCANCEL);
	SETCONTROLTEXT(b_cancel_, CLOSE);
	this->AddDialogMessageHandler(WM_CLOSE, ON_WM_CLOSE);
	this->AddDialogMessageHandler(WM_COMMAND, ON_WM_COMMAND);
}

DialogUploadProfile::~DialogUploadProfile() {
	
}