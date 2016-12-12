#pragma once
#include "stdafx.h"
#include <SimpleUI\SimpleUI.h>

class DialogInstall : public SimpleUI::Dialog {
public:

	DialogInstall();
	virtual ~DialogInstall();
private:
	typedef SimpleUI::Control Control;
	typedef SimpleUI::ProgressBar ProgressBar;

	GETSET(Control*, l_status);
	GETSET(Control*, b_browser);
	GETSET(ProgressBar*, p_progress);

	HFONT font_bold_;
};