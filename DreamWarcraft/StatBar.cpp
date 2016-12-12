#include "stdafx.h"
#include "StatBar.h"

#include "GameStructs.h"
#include "Storm.h"
#include "FunctionTemplate.h"
#include "Offsets.h"
#include "Tools.h"

namespace StatBar {
	war3::CStatBar* create(void* parent, war3::CUnit* owner, uint32_t type) {
		war3::CStatBar* t = Storm::MemAllocStruct<war3::CStatBar>();
		return init(t, parent, owner, type);
	}

	war3::CStatBar* init(war3::CStatBar* t, void* parent, war3::CUnit* owner, uint32_t type) {
		return aero::generic_this_call<war3::CStatBar*>(
			Offset(STATBAR_CONSTRUCT),
			t,
			parent,
			owner,
			type
		);
	}

	void destroy(war3::CStatBar* t) {
		if (GameUIObjectGet()) {
			aero::generic_this_call<void>(
				VTBL(t)[2],
				t,
				1
			);
		}
	}

	uint32_t setOwner(war3::CStatBar* t, war3::CUnit* unit) {
		return aero::generic_this_call<uint32_t>(
			VTBL(t)[29],
			t,
			unit
		);
	}

	uint32_t update(war3::CStatBar* t) {
		return aero::generic_this_call<uint32_t>(
			VTBL(t)[30],
			t,
			t->owner
		);
	}
}