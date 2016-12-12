#include "stdafx.h"
#include "DialogMain.h"
#include "resource.h"

static void onLinkClick(SimpleUI::Control* ctl) {
	ShellExecute(NULL, NULL, L"http://item.taobao.com/item.htm?id=15814572741", NULL, NULL, SW_MAXIMIZE);
}

DialogMain::DialogMain() : SimpleUI::Dialog(IDD_MH) {
	this->bold_font_ = 	CreateFont(
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

	this->AssignItem<Control>(this->l_version_, L_VERSION);
	this->l_version_->SetWindowText(L"1.0.0228");

	this->AssignItem<Control>(this->l_link_, L_LINK);
	this->l_link_->SetLinkMode(true);
	this->l_link_->SetColor(RGB(0x33, 0x99, 0xFF));
	this->l_link_->SetFont(this->bold_font_);
	this->l_link_->onClick += onLinkClick;

	this->AssignItem<Control>(this->t_status_, T_STATUS);
	this->t_status_->SetFont(this->bold_font_);

	this->t_status_->SetWindowText(L"µÈ´ýÓÎÏ·¿ªÆô");
}

DialogMain::~DialogMain() {
	DeleteObject(this->bold_font_);
}