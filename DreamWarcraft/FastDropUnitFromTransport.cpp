#include "stdafx.h"
#include "DreamWar3Main.h"

namespace FastDropUnitFromTransport{
	void onKeyDown (const Event *evt){
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (data->code == KEYCODE::KEY_C
			&& !data->ctrl
			&& !data->shift
			&& !data->alt	)
		{
			UnitGroup *g_currentSelected = GroupUnitsOfPlayerSelected(PlayerLocal(), true);//本地玩家当前所选高亮单位
			if (g_currentSelected->size()
				&& g_currentSelected->filterAllMatch( 
					UnitFilter(
						UnitFilter::CONTROLLABLE,
						NULL,
						PlayerLocal()
					)
				)	
			){
				UnitGroup *g_cargo = new UnitGroup();
				//TODO 如何处理多个单位
				Unit *u = g_currentSelected->getUnit(0);
				u->cargoUnitGet(g_cargo);
				if (g_cargo->size()){
					u->sendAction(
						ACTION_UNLOAD,
						Target,
						Concurrent,
						NULL,
						u->position(),
						g_cargo->getUnit(0),//TODO
						true
					);
					SoundPlay("InterfaceClick", NULL, 0);
					data->discard();	 DiscardCurrentEvent();
				}
				GroupDestroy(g_cargo);
			}

		}
	}

	void Init(){
		MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);
	}

	void Cleanup(){
	}
}