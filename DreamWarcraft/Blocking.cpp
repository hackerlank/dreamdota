/*
当控制一个单位右键目标为一个敌人单位旁（TODO 距离限制？）

根据目标单位的命令推测目标单位的移动方向，
从单位的当前坐标 p 推测出一个新的偏移坐标：
当前坐标，向当前移动方向偏移54 * (移动速度/270)距离，坐标记为p' TODO 考虑延迟

如果右键目标点在以p'为中心，2*d为边长的方形范围内，则clip到方形外。

其中 d 根据目标单位的碰撞体积，对于小体积（16~31），d = 118
对于中体积（32~ ），d = 128
*/

#include "stdafx.h"
#include "DreamWar3Main.h"

namespace Blocking
{
	void onActionSent(const Event* evt) 
	{
		ActionEventData *data = evt->data<ActionEventData>();
		if (	!data->byProgramm && 
			data->id == ACTION_SMART&& 
			data->target == NULL &&
			!(data->flag & Queued)
		){
			Point pointClicked = Point(data->x, data->y);

			UnitGroup *group;
			group = GroupUnitsOfPlayerSelected(PlayerLocal(), false);

			//判断所选单位是一个单位 TODO 必须为可控制单位!
			if (group->size() == 1)
			{
				Unit *blocker = group->getUnit(0);
				//获取范围内非自身单位
				UnitGroup *g_targets;
				g_targets = GroupUnitsInRange(data->x, data->y, 300);
				g_targets->remove(blocker);
				//TODO 判定是敌人，非尸体，非空军，。。。

				if (g_targets->size() > 0) //TODO 如何处理多个单位
				{
					Unit *target = g_targets->nearestUnit(blocker->position());
					Point p = target->position();
					float angle = target->direction();

					if (target->currentOrder() == ACTION_SMART) //TODO 更多命令判断
					{
						angle = p.angleTo(target->currentTargetPoint());

						//TODO 考虑延迟
						p = p.offsetPolar( 
							0.25f * target->moveSpeed(),
							angle
						);
					}

					float dist = 96.f + max(0, (target->moveSpeed() - blocker->moveSpeed())*0.25f);

					if ( pointClicked.maxXYDistanceTo(p) < dist )
					{
						pointClicked = p.offsetPolarMaxXY( dist, angle );

						//改写操作
						PacketSenderDestroy (data->packetSender);
						blocker->sendAction(	
							ACTION_SMART,
							Target,
							None,
							NULL,
							pointClicked,
							NULL,
							true
						);

						OutputScreen(1, "action! %s", pointClicked.toString().c_str());
					}

				}

				GroupDestroy(g_targets);
			}

			GroupDestroy(group);
		}

		

	}

	void Init()
	{
		//检测本地操作：smart / move到一个地面点
		//MainDispatcher()->listen(EVENT_LOCAL_ACTION, onActionSent);
	}

	void Cleanup()
	{

	}
}