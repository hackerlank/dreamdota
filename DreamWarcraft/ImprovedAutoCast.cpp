//ctrl + 开关技能自动 = 设置所有同类型单位，以及未来单位自动开关

#include "stdafx.h"
#include "DreamWar3Main.h"


namespace ImprovedAutoCast{

	void onActionSent(const Event* evt) {
		ActionEventData *data = evt->data<ActionEventData>();
		if (	!data->byProgramm && 
				(data->flag & AutoCast) &&
				KeyIsDown(KEYCODE::KEY_CONTROL) &&
				!KeyIsDown(KEYCODE::KEY_SHIFT) &&
				!KeyIsDown(KEYCODE::KEY_ALT)
		){
			uint32_t actionId = data->id;
			UnitGroup *group = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
			if (group->size() > 0){
				ProfileSetInt("AutoCastForceState", group->getUnit(0)->typeIdChar(), actionId);
			}
			GroupDestroy(group);
		}
	}

	void onUnitCreated(const Event* evt) {
		UnitCreationEventData *data = evt->data<UnitCreationEventData>();
		Unit *u = GetUnit(data->createdUnit);
		uint32_t actionId = ProfileGetInt("AutoCastForceState", u->typeIdChar(), 0);
		if (actionId){
			//TODO: 应当改为任务解决升级完成后开启/关闭自动的问题
			u->sendAction(
				actionId,
				TargetNone,
				Concurrent | AutoCast,
				NULL,
				POINT_NONE,
				NULL,
				false
			);
		}
	}

	void Init () {
		//检测action
		MainDispatcher()->listen(EVENT_LOCAL_ACTION, onActionSent);
	
		//检测单位被创造
		MainDispatcher()->listen(EVENT_UNIT_CREATED, onUnitCreated);
	}

}