#include "stdafx.h"
#include "SimpleButton.h"
#include "Offsets.h"
#include "FunctionTemplate.h"
#include "Storm.h"
#include "Tools.h"

namespace SimpleButton {
	war3::CSimpleButton* create(void* parent) {
		war3::CSimpleButton* t = Storm::MemAllocStruct<war3::CSimpleButton>();
		aero::generic_this_call<void>(
			Offset(SIMPLEBUTTON_CONSTRUCT), 
			t,
			parent ? parent : GameUIObjectGet()->simpleConsole
		);
		return t;		
	}

	void destroy(war3::CSimpleButton* t) {
		if (GameUIObjectGet()) {
			aero::generic_this_call<void>(
				VTBL(t)[2],
				t,
				1
			);
		}
	}
	
	void setClickEventObserverData(war3::CSimpleButton* t, uint32_t eventId, war3::CObserver* ob) {
		t->clickEventId = eventId;
		t->clickEventObserver = ob;
	}

	void setMouseEventObserverData(war3::CSimpleButton* t, uint32_t mouseOverEventId, uint32_t mouseOutEventId, war3::CObserver* ob) {
		t->mouseOverEventId = mouseOverEventId;
		t->mouseOutEventId = mouseOutEventId;
		t->mouseEventObserver = ob;
	}

	void setMouseButtonFlags(war3::CSimpleButton* t, uint32_t flags) {
		t->mouseButtonFlags = flags;
	}

	void setStateTexture(war3::CSimpleButton* t, uint32_t state, const char* path) {
		aero::generic_this_call<void>(
			Offset(SIMPLEBUTTON_SETSTATETEXTURE), 
			t,
			state,
			path
		);
	}

	void setState(war3::CSimpleButton* t, uint32_t state) {
		aero::generic_this_call<void>(
			Offset(SIMPLEBUTTON_SETSTATE), 
			t,
			state
		);
	}
}