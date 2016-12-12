#include "stdafx.h"
#include "DreamWar3Main.h"

namespace CameraToEnemyHero 
{
	void onKeyEvent (const Event *evt)
	{
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (	data->code >= KEYCODE::KEY_1 && 
				data->code <= KEYCODE::KEY_9 && 
				data->alt && 
				!data->ctrl && 
				!data->shift		)
		{
			//屏蔽原消息
			data->discard();
			//寻找敌人玩家所有英雄, 敌人=对本地玩家不友好或者没有共享视野
			UnitGroup *groupAllHeroes = 
				GroupUnits(
					NULL,
					NULL,
					PlayerGroup(
						NULL,
						PlayerFilter::ALLIANCE_PASSIVE | PlayerFilter::ALLIANCE_SHARED_VISION,
						PlayerLocal()
					),
					NULL,
					UnitFilter(
						UnitFilter::HERO,
						NULL
					)
				);
			//UnitGroup默认就是按选择优先级排序

			int index = (data->code - KEYCODE::KEY_1);
			Unit *hero = groupAllHeroes->getUnit(index);
			if (	hero != NULL &&
					hero->life() > 0		)
			{
				Jass::SetCameraPosition(hero->x(), hero->y());
				//TODO: IsUnitInTransport / IsUnitLoaded
			}
			//如果alt 1没有英雄，切换到敌人基地
			if (index==0 && hero == NULL) 
			{
				UnitGroup *groupBase = 
					GroupUnits(
						NULL,
						NULL,
						PlayerGroupAll(),
						NULL,
						UnitFilter(
							UnitFilter::TOWNHALL | UnitFilter::ENEMY,
							NULL,
							PlayerLocal()
						), 1
					);

				if (groupBase->size()) 
				{
					Unit *base = groupBase->getUnit(0);
					Jass::SetCameraPosition(base->x(), base->y());
				}
				GroupDestroy(groupBase);
			}


			GroupDestroy(groupAllHeroes);
		}
	}


	void Init() 
	{
		//alt + 数字
		MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyEvent);
	}

	void Cleanup()
	{

	}

}