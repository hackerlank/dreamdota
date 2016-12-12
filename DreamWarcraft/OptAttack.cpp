/*
最优攻击OptAttack：

收集我方单位（实际可控制）。排除掉不应自动的单位（被玩家手控的单位）
收集敌方单位。

每个敌方单位有单位预计剩余hp，初始＝当前hp - 预计来自被手控单位的伤害。

排除掉射程内没有敌人的我方单位。排除掉我方射程内没有的敌人单位。
将我方单位按照"到最近的敌人的距离"排序。（不能攻击的话，距离=inf）

对于每个我方单位（按排序）:

挑选目标单位，使得max : 单位价值 / 该单位杀死目标单位所需次数 (由预计剩余hp计算)
-- 如何处理范围伤害等
记忆该单位攻击目标单位, 目标单位预计剩余hp -= 预计伤害值。如果预计剩余hp < 0，排除出组。
-- 如何处理范围伤害等造成的预计伤害

结果：得到若干个子组，每个子组所有单位攻击一个目标。
优化1：对于任意两个单位，如果他们属于不同子组，但对目标造成伤害相近，
并且交换子组可以使得操作数减少，则交换子组。（按照现有攻击目标判断操作数是否减少）
优化2：排除掉每个子组中当前攻击目标已经为应攻击目标的单位。

操作：对每个子组，攻击目标单位

【判断自动/手动】：
TODO 欠缺从abilityflag把本地发包对应到单位命令的方法
- 电脑所发操作：不改变状态
- 本地发包事件：有flag concurrent：不改变状态
- 本地发包事件：有flag queue：暂不改变状态

- 本地发包事件：单位A地面/P地面，自动
- 本地发包事件：单位按stop/hold，自动
- 本地发包事件：其余所有，手动
- 循环判断当前指令：当前命令变为0 (idle事件)，自动（自动A别人的时候acquire为目标，但命令为0）
- 循环判断当前指令：当前命令变为A地面/P地面，自动
*/


#include "stdafx.h"
#include "DreamWar3Main.h"

namespace OptAttack {

	typedef std::map<Unit*, bool> AutoStateMapType;
	static AutoStateMapType StateMap;

	void debug(Unit *u){
#ifdef _DEBUG
		u->debugPanel->set("auto", "%s", StateMap[u]? "|cff00ff00Y|r":"|cffff0000N|r");
#endif
	}

	void AutoStateSet(Unit *u, bool flag){
		StateMap[u] = flag;
		debug(u);
	}

	void onActionSent(const Event* evt){
		ActionEventData *data = evt->data<ActionEventData>();

		if (data->byProgramm) return;//电脑所发操作：不改变状态
		if (data->flag & Concurrent) return;//本地发包事件：有flag concurrent：不改变状态
		if (data->flag & Queued) return;//本地发包事件：有flag queue：暂不改变状态

		//玩家A地板或P地板，设所有控制单位为自动
		if ((data->id == ACTION_ATTACK || data->id == ACTION_PATROL) && 
			data->target == NULL
		){
			//控制的单位普通情况下为全部所选，有子组flag为高亮子组
			UnitGroup* g = GroupUnitsOfPlayerSelected( PlayerLocal(), (data->flag & Subgroup)!=0 );
			GroupForEachUnit(g, u, AutoStateSet(u, true););
			GroupDestroy(g);
		}
		else if (
			(data->id == ACTION_STOP || data->id == ACTION_HOLD)
		){
			//控制的单位普通情况下为全部所选，有子组flag为高亮子组
			UnitGroup* g = GroupUnitsOfPlayerSelected( PlayerLocal(), (data->flag & Subgroup)!=0 );
			GroupForEachUnit(g, u, AutoStateSet(u, true););
			GroupDestroy(g);
		}
		else {
			UnitGroup* g = GroupUnitsOfPlayerSelected( PlayerLocal(), (data->flag & Subgroup)!=0 );
			GroupForEachUnit(g, u, AutoStateSet(u, false););
			GroupDestroy(g);
		}
	}

	void Init() {
		MainDispatcher()->listen(EVENT_LOCAL_ACTION, onActionSent);
	}

	void Cleanup() {
		StateMap.clear();
	}
}