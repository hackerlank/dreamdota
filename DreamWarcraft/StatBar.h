#include "stdafx.h"
#ifndef STATBAR_H_INCLUDED
#define STATBAR_H_INCLUDED

#include "UIStructs.h"

namespace StatBar {
	war3::CStatBar* create(void* parent = 0, war3::CUnit* owner = 0, uint32_t type = 0);
	war3::CStatBar* init(war3::CStatBar* t, void* parent = 0, war3::CUnit* owner = 0, uint32_t type = 0);
	void destroy(war3::CStatBar* t);

	uint32_t setOwner(war3::CStatBar* t, war3::CUnit* unit);
	uint32_t update(war3::CStatBar* t);
}

#endif