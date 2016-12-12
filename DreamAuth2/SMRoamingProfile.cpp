#include "stdafx.h"
#include "SMRoamingProfile.h"
#include <json-c\json.h>
#include "../DreamWarcraft/Profile.h"

bool SMRoamingProfile::ParseJSON(const char* json, size_t len) {
	bool rv = false;
	json_tokener* jsontok = json_tokener_new();
	json_object* jsonobj = json_tokener_parse_ex(jsontok, json, len);
	json_object* field;
	SMRoamingProfile::PullOption* po = &this->pull_option_;
	if (jsontok->err == json_tokener_success && json_object_is_type(jsonobj, json_type_array)) {
		int n = json_object_array_length(jsonobj);
		if (n >= 2) { 
			json_object* json_result_code = json_object_array_get_idx(jsonobj, 0);
			po->result = json_object_get_int(json_result_code);

			json_object* json_quota_info = json_object_array_get_idx(jsonobj, 1);
			field = json_object_array_get_idx(json_quota_info, 0);
			po->used = json_object_get_int(field);

			field = json_object_array_get_idx(json_quota_info, 1);
			po->quota = json_object_get_int(field);
			
			this->pull_option_.items.clear();
			this->dialog_->li_items()->ResetContent();
			for (int i = 2; i < n; ++i) {
				json_object* itemobj = json_object_array_get_idx(jsonobj, i);
				SMRoamingProfile::ProfileData pdata;
					
				if (itemobj && json_object_is_type(itemobj, json_type_object)) {
					field = json_object_object_get(itemobj, "id");
					pdata.id = json_object_get_int(field);
					
					field = json_object_object_get(itemobj, "name");
					pdata.name = json_object_get_string(field);

					field = json_object_object_get(itemobj, "url");
					pdata.url = json_object_get_string(field);

					po->items.push_back(pdata);
					
					wchar_t buff[MAX_PATH];
					MultiByteToWideChar(CP_UTF8, NULL, pdata.name.c_str(), -1, buff, MAX_PATH -1);
					int item = this->dialog_->li_items()->AddString(buff);
					this->dialog_->li_items()->SetItemData(item, (DWORD)&po->items.back());
				}
			}

			rv = true;
		}
	}
	json_tokener_free(jsontok);
	return rv;
}

INT_PTR SMRoamingProfile::ON_WM_CLOSE(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	dialog->Show(false);
	SMRoamingProfile::GetInstance()->onPerformComplete.Invoke(true);
	return TRUE;
}

void SMRoamingProfile::onPullThreadComplete(WorkerThread* thread) {
	SMRoamingProfile* t = SMRoamingProfile::GetInstance();
	bool success = thread->result() > 0;
	if (success) {
		if (t->pull_option_.result != 0)
			MessageBox(t->dialog_->handle(), t->TranslateResult(t->pull_option_.result), NULL, MB_ICONERROR);
		t->dialog_->SetLoadedState(t->pull_option_.items.size(), t->pull_option_.quota, t->pull_option_.used);
	} else {
		t->dialog_->Show(false);
		MessageBox(t->dialog_->handle(), ResString::GetString(ResString::SERVICE_UNAVAILABLE), NULL, MB_ICONERROR);
		t->onPerformComplete.Invoke(false);
	}
}

void SMRoamingProfile::onUploadThreadComplete(WorkerThread* thread) {
	SMRoamingProfile* t = SMRoamingProfile::GetInstance();
	bool success = thread->result() > 0;
	if (success) {
		if (t->pull_option_.result != 0)
			MessageBox(t->dialog_->handle(), t->TranslateResult(t->pull_option_.result), NULL, MB_ICONERROR);
		t->dialog_->SetLoadedState(t->pull_option_.items.size(), t->pull_option_.quota, t->pull_option_.used);
	} else {
		t->dialog_->Show(false);
		MessageBox(t->dialog_->handle(), ResString::GetString(ResString::SERVICE_UNAVAILABLE), NULL, MB_ICONERROR);
		t->onPerformComplete.Invoke(false);
	}
}

void SMRoamingProfile::onDownloadThreadComplete(WorkerThread* thread) {
	SMRoamingProfile* t = SMRoamingProfile::GetInstance();
	bool success = thread->result() > 0;
	if (success) {
		if (t->pull_option_.result != 0)
			MessageBox(t->dialog_->handle(), t->TranslateResult(t->pull_option_.result), NULL, MB_ICONERROR);
		t->dialog_->SetLoadedState(t->pull_option_.items.size(), t->pull_option_.quota, t->pull_option_.used);
	} else {
		t->dialog_->Show(false);
		MessageBox(t->dialog_->handle(), ResString::GetString(ResString::SERVICE_UNAVAILABLE), NULL, MB_ICONERROR);
		t->onPerformComplete.Invoke(false);
	}
}

void SMRoamingProfile::onDeleteThreadComplete(WorkerThread* thread) {
	SMRoamingProfile* t = SMRoamingProfile::GetInstance();
	bool success = thread->result() > 0;
	if (success) {
		t->dialog_->SetLoadedState(t->pull_option_.items.size(), t->pull_option_.quota, t->pull_option_.used);
	} else {
		t->dialog_->Show(false);
		MessageBox(t->dialog_->handle(), ResString::GetString(ResString::SERVICE_UNAVAILABLE), NULL, MB_ICONERROR);
		t->onPerformComplete.Invoke(false);
	}
}

void SMRoamingProfile::onProgress(const HTTP::ProgressInfo* pi) {
	DialogRoamingProfile* d = SMRoamingProfile::GetInstance()->dialog_;
	d->p_loading()->SetPos((int)(100.0 * (pi->now / pi->total)));
}

void SMRoamingProfile::onCommand(SimpleUI::Control* ctl) {
	SMRoamingProfile* t = SMRoamingProfile::GetInstance();
	DialogRoamingProfile* d = SMRoamingProfile::GetInstance()->dialog_;
	DialogUploadProfile* du = SMRoamingProfile::GetInstance()->dialog_upload_;
	if (ctl == d->b_upload()) {
		d->EnableWindow(FALSE);
		int sel = d->li_items()->GetCurSel();
		if (sel != LB_ERR) {
			int sellen = d->li_items()->GetTextLen(d->li_items()->GetCurSel());
			if (sellen) {
				wchar_t* buff = new wchar_t[sellen + 1];
				d->li_items()->GetText(d->li_items()->GetCurSel(), buff);
				buff[sellen] = 0;
				du->SetName(buff);
				delete [] buff;
			}
		}
		du->Show(true);
		du->t_name()->SetFocus();
	} else if (ctl == d->b_apply()){
		if (IDYES == MessageBox(d->handle(), ResString::GetString(ResString::ARE_YOU_SURE), L"", MB_YESNO | MB_ICONWARNING)) {
			d->SetLoadingState(ResString::GetString(ResString::LOADING));
			ProfileData* pd = (ProfileData*)d->li_items()->GetItemData(d->li_items()->GetCurSel());
			t->di_.url = pd->url;
			t->thread_download_.Run((DWORD)&(t->di_));
		}
	} else if (ctl == d->b_delete()) {
		if (IDYES == MessageBox(d->handle(), ResString::GetString(ResString::ARE_YOU_SURE), L"", MB_YESNO | MB_ICONWARNING)) {
			d->SetLoadingState(ResString::GetString(ResString::LOADING));
			ProfileData* pd = (ProfileData*)d->li_items()->GetItemData(d->li_items()->GetCurSel());
			t->thread_delete_.Run((DWORD)pd->id);
		}
	}
}

bool SMRoamingProfile::SameNameExists() {
	SMRoamingProfile* t = SMRoamingProfile::GetInstance();
	for (SMRoamingProfile::ParsedItemsListType::iterator iter = t->pull_option_.items.begin();
		iter != t->pull_option_.items.end();++iter) {
			if (0 == iter->name.compare(t->dialog_upload_->GetNameUTF8()))
				return true;
	}
	return false;
}

void SMRoamingProfile::onUploadDialogCommand(SimpleUI::Control* ctl) {
	SMRoamingProfile* t = SMRoamingProfile::GetInstance();
	DialogRoamingProfile* d = SMRoamingProfile::GetInstance()->dialog_;
	DialogUploadProfile* du = SMRoamingProfile::GetInstance()->dialog_upload_;
	if (ctl == du->b_ok()) {
		if (SameNameExists() && IDNO == MessageBox(du->handle(), ResString::GetString(ResString::OVERWRITE_PROFILE), L"", MB_ICONWARNING | MB_YESNO))
			return;
		du->Show(false);
		d->EnableWindow(TRUE);
		d->Show(true);
		d->SetLoadingState(ResString::GetString(ResString::UPLOADING_PROFILE));
		t->thread_upload_.Run((DWORD)du->GetNameUTF8());
	} else if (ctl == du->b_cancel()){
		du->Show(false);
		d->Show(true);
		d->EnableWindow(TRUE);
		d->SetForegroundWindow();
	}
}

void SMRoamingProfile::InitUI() {
	if (!this->ui_inited_) {
		this->dialog_ = new DialogRoamingProfile();
		this->dialog_->AddDialogMessageHandler(WM_CLOSE, ON_WM_CLOSE);
		this->dialog_->onCommand += onCommand;

		this->dialog_upload_ = new DialogUploadProfile();
		this->dialog_upload_->onCommand += onUploadDialogCommand;

		this->ui_inited_ = true;
	}
}

void SMRoamingProfile::DisposeUI() {
	if (this->ui_inited_) {
		this->dialog_->Close();
		delete this->dialog_;

		this->dialog_upload_->Close();
		delete this->dialog_upload_;

		this->ui_inited_ = false;
	}
}

SMRoamingProfile::SMRoamingProfile() {
	this->ui_inited_ = false;

	InitUI();
	
	this->thread_upload_.onThreadComplete += onUploadThreadComplete;
	this->thread_upload_.HTTPObject()->onUploadProgress += onProgress;
	this->thread_pull_.onThreadComplete += onPullThreadComplete;
	this->thread_download_.onThreadComplete += onDownloadThreadComplete;
	this->thread_download_.network_obj()->onDownloadProgress += onProgress;
	this->thread_delete_.onThreadComplete += onDeleteThreadComplete;

	this->di_.save_as = PROFILE_FILENAMEA;
}

SMRoamingProfile::~SMRoamingProfile() {
	this->Term();
}

void SMRoamingProfile::Perform() {
	InitUI();

	this->dialog_->EnableWindow(TRUE);
	this->dialog_->Show(true);
	this->dialog_->SetLoadingState();
	this->thread_pull_.Run((DWORD)&(this->pull_option_));
}

void SMRoamingProfile::Term() {
	this->DisposeUI();

	this->thread_pull_.Term();
	this->thread_upload_.Term();
	this->thread_delete_.Term();
	this->thread_download_.StopSignal();
	this->thread_download_.Wait();
}