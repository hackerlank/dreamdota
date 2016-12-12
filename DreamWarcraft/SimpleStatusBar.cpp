#include "stdafx.h"
#include "SimpleStatusBar.h"
#include "FunctionTemplate.h"

namespace SimpleStatusBar {
	void setValue(war3::CSimpleStatusBar* t, float value) {
		aero::generic_this_call<void>(
			aero::offset_element_get<void*>(VTBL(t), 0x6C),
			t,
			value
		);
	}
}