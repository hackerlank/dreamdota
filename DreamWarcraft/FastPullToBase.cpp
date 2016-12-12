#include "stdafx.h"
#include "DreamWar3Main.h"

namespace FastPullToBase {


	void onKeyDown (const Event *evt){
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (data->code == KEYCODE::KEY_ESC
			&& !data->ctrl
			&& !data->shift
			&& !data->alt	)
		{
			UnitGroup *g_currentSelected = GroupUnitsOfPlayerSelected(PlayerLocal(), false);//本地玩家当前所选单位
			if (g_currentSelected->size()
				&& g_currentSelected->filterExistsMatch( 
					UnitFilter(
						UnitFilter::CONTROLLABLE,
						UnitFilter::STRUCTURE,
						PlayerLocal()
					)
				)	
			){
				UnitGroup *mybase = GroupUnits(NULL,NULL,
					PlayerGroupSingle(PlayerLocal()),
					NULL,
					UnitFilter(	UnitFilter::TOWNHALL, NULL ),
					1
				);
				if (mybase->size()){
					g_currentSelected->sendAction(
						ACTION_SMART,
						Target,
						None,
						NULL,
						mybase->getUnit(0)->position().offset(RandomFloat(-350.f, 350.f), RandomFloat(-350.f, 350.f)),
						NULL,
						NULL,
						true
					);
					SoundPlay("InterfaceClick", NULL, 0);
				}
				else SoundPlay("InterfaceError", NULL, 0);
				GroupDestroy(mybase);
			}
			GroupDestroy(g_currentSelected);
		}
	}

	void Init(){
		MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);
	}
	void Cleanup(){
	}
}