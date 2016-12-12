#include "stdafx.h"
#ifndef DIALOGINIT_H_
#define DIALOGINIT_H_

#include <SimpleUI\SimpleUI.h>

class DialogInit : public SimpleUI::Dialog {
public:
	DialogInit();
	virtual ~DialogInit();

private:
	typedef SimpleUI::Control Control;
	
	static INT_PTR ON_WM_CLOSE(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR ON_WM_PAINT(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam);

	Control* l_loading_;
	HBRUSH bg_brush_;
	HPEN border_pen_;
};

#endif