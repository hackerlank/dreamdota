#ifndef SIMPLEUI_RADIOBOX_
#define SIMPLEUI_RADIOBOX_

#include "Control.h"

namespace SimpleUI {

class RadioBox : public Control {
public:
	void SetCheck(bool check);
	bool IsChecked();

	RadioBox(HWND handle);
	virtual ~RadioBox();
};

} //namespace


#endif