/*
- 所选单位都是陆军，同类型并且移动速度一致：移动时用阵型 + 群组
- 如果当前选择中有空军，并且没有英雄以外的陆军，就取消群组取消阵型

- （待定）alt + 右键拉扯阵型
- （待定）保持阵型？聚集阵型？扩散阵型？
*/

#include "stdafx.h"
#include "DreamWar3Main.h"

namespace Formation {

	void onLocalActionSent (const Event *evt) {
		ActionEventData *data = evt->data<ActionEventData>();
		war3::PacketActionPoint *packet = (war3::PacketActionPoint *)(data->packetSender->packet);
		UnitGroup *group = GroupUnitsOfPlayerSelected(PlayerLocal(), false);

		//陆军阵型
		if (	!data->byProgramm			//非程序所发操作
			&&	data->id == ACTION_SMART		//命令为右键
			&&	data->target == NULL		)	//没有单位目标
		{
			if (	group->size() > 1
				&&	group->countUnitTypeId() == 1
				&&	group->testFlag(UnitFilter::GROUND)	)	//如果全部都是地面单位并且单位类型相同
			{
				packet->flag &= (~IgnoreFormation);		//强制使用阵型移动
				packet->flag |= (GroupPathing);			//强制使用群组移动
			}
		}

		//空军聚团
		if (!data->byProgramm)	//非程序所发操作
		{
			if (	group->size() > 1
				&&	group->filterExistsMatch(	//存在空中单位
						UnitFilter(
							UnitFilter::FLYING,
							NULL))
				&&	!group->filterExistsMatch(	//不存在非英雄地面单位
						UnitFilter(
							UnitFilter::GROUND,
							UnitFilter::HERO))	)
			{
				packet->flag |= (IgnoreFormation);	//强制不使用阵型移动
				packet->flag &= (~GroupPathing);	//强制不使用群组移动
			}
		}

		GroupDestroy(group);
	}

	void Init() {
		MainDispatcher()->listen(EVENT_LOCAL_ACTION, onLocalActionSent);
	}
}