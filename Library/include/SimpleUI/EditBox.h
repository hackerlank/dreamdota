#ifndef SIMPLEUI_EDITBOX_
#define SIMPLEUI_EDITBOX_

#include "Control.h"

namespace SimpleUI {

class EditBox : public Control {
public:
	EditBox(HWND handle);
	virtual ~EditBox();
};

} //namespace


#endif