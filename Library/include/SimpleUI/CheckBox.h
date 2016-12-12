#ifndef SIMPLEUI_CHECKBOX_
#define SIMPLEUI_CHECKBOX_

#include "Control.h"

namespace SimpleUI {

class CheckBox : public Control {
public:
	void SetCheck(bool check);
	bool IsChecked();

	CheckBox(HWND handle);
	virtual ~CheckBox();
};

} //namespace


#endif