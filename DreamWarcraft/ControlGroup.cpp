#include "stdafx.h"
#include "DreamWar3Main.h"

namespace ControlGroup {

	void onControlGroupAssign (const Event *evt) {
		ControlGroupEventData *data = evt->data<ControlGroupEventData>();
		SoundPlay("InterfaceClick", NULL, 0);
	}

	void Init(){
		MainDispatcher()->listen(EVENT_CONTROL_GROUP_ASSIGN, onControlGroupAssign);
	}

	void Cleanup(){
	}
}