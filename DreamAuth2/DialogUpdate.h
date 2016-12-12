#include "stdafx.h"
#ifndef DIALOGUPDATE_H_
#define DIALOGUPDATE_H_
#include "resource.h"

#include <SimpleUI\SimpleUI.h>

class DialogUpdate : public SimpleUI::Dialog {
public:
	static INT_PTR ON_WM_CLOSE(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam);

	enum DialogUpdateStateEnum {
		STATE_INITIAL,
		STATE_INFO_LOADED,
		STATE_DOWNLOADING,
		STATE_CANCEL
	};

	void SetState(DialogUpdateStateEnum state);
	DialogUpdateStateEnum GetState() {return this->state_;}

	DialogUpdate();
	virtual ~DialogUpdate();
private:
	typedef SimpleUI::Control Control;
	typedef SimpleUI::ProgressBar ProgressBar;
	DialogUpdateStateEnum state_;
	GETSET(Control*, t_changelog)
	GETSET(ProgressBar*, p_progress)
	GETSET(Control*, b_update)
	GETSET(Control*, b_open)
	GETSET(Control*, b_copy)
	GETSET(Control*, l_status)
	HFONT font_bold_;
};

#endif