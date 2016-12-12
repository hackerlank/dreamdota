#include "stdafx.h"
#ifndef UNITTIP_H_INCLUDED_
#define UNITTIP_H_INCLUDED_
#include "GameStructs.h"

class Unit;

war3::CUnitTip* CreateUnitTip(void* parentUIObject = NULL);
void DestroyUnitTip(war3::CUnitTip* tip);
void UnitTipBindUnit(war3::CUnitTip* tip, war3::CUnit* unit);
void UnitTipBindUnit(war3::CUnitTip* tip, Unit* unit);

void UnitTip_Update();

#endif