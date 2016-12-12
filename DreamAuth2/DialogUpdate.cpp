#include "DialogUpdate.h"

#include "resource.h"
#include "ResString.h"
#include "Utils.h"

DialogUpdate::DialogUpdate() : SimpleUI::Dialog(IDD_UPDATE) {
	this->font_bold_ = CreateFont(
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
	this->SetWindowText(ResString::GetString(ResString::DREAMDOTA_UPDATE));
	this->AssignItem<Control>(this->t_changelog_, T_CHANGELOG);
	this->t_changelog_->SetSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	this->AssignItem<ProgressBar>(this->p_progress_, P_PROGRESS);
	this->AssignItem<Control>(this->b_update_, B_UPDATE);
	this->AssignItem<Control>(this->l_status_, L_STATUS);
	this->l_status_->SetFont(this->font_bold_);
	SETCONTROLTEXT(l_status_, UPDATE_LOADING);
	SETCONTROLTEXT(b_update_, AUTO_UPDATE);
	this->AssignItem<Control>(this->b_copy_, B_COPY);
	SETCONTROLTEXT(b_copy_, COPY_LINK);
	this->AssignItem<Control>(this->b_open_, B_OPEN);
	SETCONTROLTEXT(b_open_, OPEN_LINK);

	this->SetState(STATE_INITIAL);
}

DialogUpdate::~DialogUpdate() {
	DeleteObject(this->font_bold_);
}

void DialogUpdate::SetState(DialogUpdateStateEnum state) {
	switch (state) {
	case STATE_INITIAL:
		this->p_progress_->SetMarquee(true);
		this->b_copy_->EnableWindow(FALSE);
		this->b_open_->EnableWindow(FALSE);
		this->b_update_->EnableWindow(FALSE);
		break;
	case STATE_INFO_LOADED:
		this->p_progress_->SetMarquee(false);
		this->b_copy_->EnableWindow(TRUE);
		this->b_open_->EnableWindow(TRUE);
		this->b_update_->EnableWindow(TRUE);
		break;
	case STATE_DOWNLOADING:
		this->b_update_->EnableWindow(FALSE);
		break;
	case STATE_CANCEL:
		this->p_progress_->SetMarquee(true);
		this->EnableSystemMenuItem(SC_CLOSE, FALSE);
		break;
	}
}