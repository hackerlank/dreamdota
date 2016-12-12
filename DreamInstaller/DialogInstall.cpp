#include "DialogInstall.h"
#include "resource.h"
#include "LocaleString.h"
#include "../DreamWarcraft/Version.h"

DialogInstall::DialogInstall() : SimpleUI::Dialog(D_INSTALL) {
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
	wchar_t title[50];
	swprintf_s(title, 50, _(LocaleString::TITLE), VERSION.main, VERSION.release, VERSION.build, VERSION.revision);
	this->SetWindowText(title);
	this->AssignItem<Control>(this->l_status_, L_STATUS);
	this->l_status_->SetFont(this->font_bold_);
	this->AssignItem<Control>(this->b_browser_, B_BROWSER);
	this->b_browser_->SetFont(this->font_bold_);
	this->b_browser()->SetWindowText(_(LocaleString::SELECT_DIR));
	this->AssignItem<ProgressBar>(this->p_progress_, P_PROGRESS);
	this->p_progress()->SetMarquee(true);
}

DialogInstall::~DialogInstall() {
	DeleteObject(this->font_bold_);
}