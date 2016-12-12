#pragma once

#include "stdafx.h"
#include <SimpleUI\SimpleUI.h>

class DialogMain : public SimpleUI::Dialog {
public:
	DialogMain();
	virtual ~DialogMain();
private:
	typedef SimpleUI::Control Control;
	
	GETSET(Control*, l_version);
	GETSET(Control*, l_link);
	GETSET(Control*, t_status);
	
	HFONT bold_font_;

	DISALLOW_COPY_AND_ASSIGN(DialogMain);
};