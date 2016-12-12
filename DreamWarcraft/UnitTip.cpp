#include "stdafx.h"
#include "Offsets.h"
#include "Tools.h"
#include "UI.h"
#include "Unit.h"
#include "Storm.h"

void UnitTipRefresh(war3::CUnitTip* tip, war3::CUnit* unit);

void* UnitTip_Construct = NULL;
void* UnitTip_Destruct = NULL;
void* UnitTip_Refresh = NULL;

typedef std::set<war3::CUnitTip*> UnitTipSetType;

static UnitTipSetType UnitTipSet;

void UnitTip_Update() {
	war3::CUnitTip* tip;
	for (UnitTipSetType::iterator iter = UnitTipSet.begin(); iter != UnitTipSet.end(); ++ iter) {
		tip = *iter;
		UnitTipRefresh(tip, tip->unit);
	}
}

void (__thiscall *RCAssign)(void* dst, void* src) = 0;
void UnitTipBindUnit(war3::CUnitTip* tip, war3::CUnit* unit) {
	if (!RCAssign)
		RCAssign = (void (__thiscall *)(void* dst, void* src))Offset(RC_ASSIGN);
	RCAssign(&(tip->unit), unit);
}

void UnitTipBindUnit(war3::CUnitTip* tip, Unit* unit) {
	if (!RCAssign)
		RCAssign = (void (__thiscall *)(void* dst, void* src))Offset(RC_ASSIGN);
	RCAssign(&(tip->unit), UnitGetObject(unit->handleId()));
}

war3::CUnitTip* CreateUnitTip(void* parentUIObject) {
	if (!UnitTip_Construct)
		UnitTip_Construct = Offset(UNITTIP_CONSTRUCT);
	war3::CUnitTip* rv = Storm::MemAllocStruct<war3::CUnitTip>();
	memset(rv, 0, sizeof(war3::CUnitTip));
	aero::generic_this_call<void>(UnitTip_Construct, rv, parentUIObject ? parentUIObject : GameUIObjectGet()->simpleConsole);

	//初始化
	//其实刚初始化needUpdate一定是0...
	uint32_t needUpdate = rv->baseSimpleFrame.needUpdate;
	uint32_t tip_84 = rv->baseSimpleFrame.unk_84;

	if (needUpdate) {
		rv->baseSimpleFrame.visible = 0;
		aero::generic_this_call<void>(vtableFpAtOffset(VTBL(rv), 0x64), rv);
	}
	rv->baseSimpleFrame.unk_84 = tip_84 + 2;
	if (needUpdate) {
		rv->baseSimpleFrame.visible = 1;
		aero::generic_this_call<void>(vtableFpAtOffset(VTBL(rv), 0x68), rv);
	}
	
	UnitTipSet.insert(rv);
	return rv;
}

war3::CUnit* __fastcall updateFunc(war3::CUnitTip* tip) {
	return tip->unit;
}

void UnitTipRefresh(war3::CUnitTip* tip, war3::CUnit* unit) {
	FramePoint p;
	uint32_t rv = GetUnitFramePoint(unit, &p);
	//OutputDebug("rv = %u, x = %.2f, y = %.2f", rv, p.x, p.y);
	if (unit->preSelectUI) {
		tip->levelUpdateFunc = updateFunc;
		tip->baseSimpleFrame.needUpdate = 1;
		tip->baseSimpleFrame.visible = 1;
		tip->updateSize = 1;
		LayoutFrame::setRelativePosition(tip, LayoutFrame::Position::BOTTOM_CENTER, unit->preSelectUI->statBarHP, LayoutFrame::Position::TOP_CENTER, 0.0, 0.0, 0);
		aero::generic_this_call<void>(vtableFpAtOffset(VTBL(tip), 0x6C), tip);
		aero::generic_this_call<void>(vtableFpAtOffset(VTBL(tip), 0x64), tip);
		aero::generic_this_call<void>(vtableFpAtOffset(VTBL(tip), 0x68), tip);
	} else {
		tip->baseSimpleFrame.visible = 0;
		aero::generic_this_call<void>(vtableFpAtOffset(VTBL(tip), 0x64), tip);
	}
}

void DestroyUnitTip(war3::CUnitTip* tip) {
	if (!UnitTip_Destruct)
		UnitTip_Destruct = Offset(UNITTIP_DESTRUCT);
	aero::generic_this_call<void>(UnitTip_Destruct, tip);
	UnitTipSet.erase(tip);
	Storm::MemFree(tip);
}