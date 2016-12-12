#ifndef DIALOGROAMINGPROFILE_H_
#define DIALOGROAMINGPROFILE_H_
#include "resource.h"

#include <SimpleUI\SimpleUI.h>
#include "ResString.h"

class DialogRoamingProfile : public SimpleUI::Dialog {
public:
	void SetLoadingState(const wchar_t* top = NULL) {
		this->l_top_->SetWindowText(top ? top : ResString::GetString(ResString::LOADING));
		this->li_items_->EnableWindow(FALSE);
		this->p_loading_->ShowWindow(SW_SHOW);
		this->b_upload_->EnableWindow(FALSE);
		this->b_apply_->EnableWindow(FALSE);
		this->b_delete_->EnableWindow(FALSE);
		this->EnableSystemMenuItem(SC_CLOSE, FALSE);
	}

	void SetLoadedState(int n, int quota, int used) {
		this->li_items_->EnableWindow(TRUE);
		this->p_loading_->SetMarquee(false);
		this->p_loading_->SetPos((int)ceil(static_cast<double>(used) / static_cast<double>(quota) * 100.0));
		this->b_upload_->EnableWindow(used < quota ? TRUE : FALSE);
		wchar_t buff[100];
		if (n) {
			swprintf_s(buff, 100, ResString::GetString(ResString::N_RP_FOUND), n, used, max(0, quota - used));
			this->l_top_->SetWindowText(buff);
		} else {
			swprintf_s(buff, 100, ResString::GetString(ResString::NO_RP_FOUND), quota);
			this->l_top_->SetWindowText(buff);
		}
		this->EnableSystemMenuItem(SC_CLOSE, TRUE);
		this->UpdateBtnState();
	}

	DialogRoamingProfile();
	virtual ~DialogRoamingProfile();
private:
	typedef SimpleUI::Control Control;
	typedef SimpleUI::ProgressBar ProgressBar;
	typedef SimpleUI::ListBox ListBox;

	static INT_PTR DialogRoamingProfile::ON_WM_COMMAND(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		DialogRoamingProfile* d = (DialogRoamingProfile*)dialog;
		d->UpdateBtnState();
		return FALSE;
	}

	void UpdateBtnState() {
		bool selected = this->li_items_->GetCurSel() != LB_ERR;
		this->b_apply_->EnableWindow(selected ? TRUE : FALSE);
		this->b_delete_->EnableWindow(selected ? TRUE : FALSE);
	}

	GETSET(Control*, l_top);
	GETSET(ListBox*, li_items);
	GETSET(ProgressBar*, p_loading);
	GETSET(Control*, b_upload);
	GETSET(Control*, b_apply);
	GETSET(Control*, b_delete);

	HFONT font_top_;
};

#endif