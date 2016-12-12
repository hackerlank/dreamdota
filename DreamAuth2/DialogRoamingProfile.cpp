#include "stdafx.h"
#include "DialogRoamingProfile.h"

#include "resource.h"
#include "Utils.h"

DialogRoamingProfile::DialogRoamingProfile() : SimpleUI::Dialog(IDD_RP) {
	this->font_top_ = CreateFont(
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

	this->SetWindowText(ResString::GetString(ResString::ROAMING_PROFILE));

	this->AssignItem<Control>(this->l_top_, L_TOP);
	SETCONTROLTEXT(l_top_, LOADING);
	this->l_top_->SetFont(this->font_top_);

	this->AssignItem<ListBox>(this->li_items_, LI_ITEMS);
	this->AssignItem<ProgressBar>(this->p_loading_, P_LOADING);
	this->p_loading_->SetMarquee(true);

	this->AssignItem<Control>(this->b_upload_, B_UPLOAD);
	SETCONTROLTEXT(b_upload_, UPLOAD_LOCAL_PROFILE);

	this->AssignItem<Control>(this->b_apply_, B_APPLY);
	SETCONTROLTEXT(b_apply_, APPLY_SELECTED_PROFILE);

	this->AssignItem<Control>(this->b_delete_, B_DELETE);
	SETCONTROLTEXT(b_delete_, DELETE_SELECTED_PROFILE);

	this->AddDialogMessageHandler(WM_COMMAND, ON_WM_COMMAND);
}

DialogRoamingProfile::~DialogRoamingProfile() {
	DeleteObject(this->font_top_);
}