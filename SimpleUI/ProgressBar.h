#ifndef SIMPLEUI_PROGRESSBAR_
#define SIMPLEUI_PROGRESSBAR_

#include "Control.h"

namespace SimpleUI {

class ProgressBar : public Control {
public:
	UINT GetPos() {return SendMessage(this->handle(), PBM_GETPOS, 0, 0);}
	UINT SetPos(int pos) {return SendMessage(this->handle(), PBM_SETPOS, WPARAM(pos), 0);}
	UINT DeltaPos(int amount) {return SendMessage(this->handle(), PBM_DELTAPOS, WPARAM(amount), 0);}
	int GetRange(PBRANGE* data) {return SendMessage(this->handle(), PBM_GETRANGE, WPARAM(FALSE), LPARAM(data));}
	int SetRange(int low, int high) {return SendMessage(this->handle(), PBM_SETRANGE32, WPARAM(low), LPARAM(high));}
	void SetMarquee(bool v, UINT update_interval = 0) {
		if (v) {
			this->SetWindowLong(GWL_STYLE, this->GetWindowLong(GWL_STYLE) | PBS_MARQUEE);
		}
		SendMessage(this->handle(), PBM_SETMARQUEE, WPARAM(v ? TRUE : FALSE), LPARAM(update_interval));
		if (!v) {
			this->SetWindowLong(GWL_STYLE, this->GetWindowLong(GWL_STYLE) &~ PBS_MARQUEE);
		}
	}

	ProgressBar(HWND handle);
	virtual ~ProgressBar() {}
};

} //namespace


#endif