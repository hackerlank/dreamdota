#ifndef SIMPLEUI_LISTVIEW_
#define SIMPLEUI_LISTVIEW_

#include "Control.h"

namespace SimpleUI {

class ListView : public Control {
public:
	int SetView(DWORD view) {
		return ListView_SetView(this->handle(), view);
	}

	int InsertItem(const LPLVITEM pitem) {
		return ListView_InsertItem(this->handle(), pitem);
	}

	ListView(HWND handle);
	virtual ~ListView();
};

} //namespace


#endif