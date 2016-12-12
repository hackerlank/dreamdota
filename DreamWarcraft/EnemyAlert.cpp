/*
当敌方单位由不可见变为可见时发出警告。（可考虑合适的延迟 + 再判断缓冲时间）

不警告：单位由不可见变为被检测（被我方主动显隐）
不警告：进入的单位处于敌我交战范围内（大战中敌兵增援）

*/
#include "stdafx.h"
#include "DreamWar3Main.h"

namespace EnemyAlert {

	const char *underAttackSoundLink(bool useTownAlert, bool useAllyAlert) {
		switch(PlayerRace(PlayerLocal())) {
		case Jass::RACE_HUMAN:
			if (!useTownAlert && !useAllyAlert)	return "UnderAttackHuman";
			if (!useTownAlert && useAllyAlert)	return "AllyUnderAttackHuman";
			if (useTownAlert && !useAllyAlert)	return "TownAttackHuman";
			if (useTownAlert && useAllyAlert)	return "AllyTownUnderAttackHuman";
			break;
		case Jass::RACE_ORC:
			if (!useTownAlert && !useAllyAlert)	return "UnderAttackOrc";
			if (!useTownAlert && useAllyAlert)	return "AllyUnderAttackOrc";
			if (useTownAlert && !useAllyAlert)	return "TownAttackOrc";
			if (useTownAlert && useAllyAlert)	return "AllyTownUnderAttackOrc";
			break;
		case Jass::RACE_UNDEAD:
			if (!useTownAlert && !useAllyAlert)	return "UnderAttackUndead";
			if (!useTownAlert && useAllyAlert)	return "AllyUnderAttackUndead";
			if (useTownAlert && !useAllyAlert)	return "TownAttackUndead";
			if (useTownAlert && useAllyAlert)	return "AllyTownUnderAttackUndead";
			break;
		case Jass::RACE_NIGHTELF:
			if (!useTownAlert && !useAllyAlert)	return "UnderAttackNightElf";
			if (!useTownAlert && useAllyAlert)	return "AllyUnderAttackNightElf";
			if (useTownAlert && !useAllyAlert)	return "TownAttackNightElf";
			if (useTownAlert && useAllyAlert)	return "AllyTownUnderAttackNightElf";
			break;
		}
		return NULL;
	}

	static std::set<Point> LastAlertPoints;

	static float NotifyInitDelay;
	static float NotifyCycleTime;
	static float NotifyDelay;
	static float NotifyRange;
	static Timer* NotifyCycleTimer;

	void AlertPointClear(Timer *eventTimer) {
		Point *p = eventTimer->data<Point>();
		LastAlertPoints.erase(*p);
		//OutputScreen(10, "Point %s erased.", p->toString().c_str());
	}

	void AlertPoint(Point p, bool useTownAlert, bool useAllyAlert) {
		std::set<Point>::iterator iter;
		for (iter = LastAlertPoints.begin(); iter != LastAlertPoints.end(); ++iter) {
			if ((*iter).distanceTo(p) < NotifyRange) return;
		}

		//OutputScreen(10, "Alert : %s", p.toString().c_str());
		PingMinimapEx(p.x, p.y, 3, 255, 0, 0, false);
		Jass::SetCameraQuickPosition(p.x, p.y);
		SoundPlay(underAttackSoundLink(useTownAlert, useAllyAlert), NULL, 0);

		//地点性质：一个警告之后，在其屏幕范围内设置间隔（x秒），在间隔结束之前，这个范围内发生的警告被忽略
		LastAlertPoints.insert(p);
		Timer *tm = GetTimer(NotifyDelay, AlertPointClear, false);
		tm->setData<Point>(&p);
		tm->start();
		
	}

	void alertPerform(Unit *u) {
		//不警告：这次与上次位置没有变化的单位（例如不会移动的建筑）
		if (u->position() == u->visibleState.lastVisiblePoint) { return; }

		//不警告：在当前屏幕
		if (u->position().distanceTo(Point(Jass::GetCameraTargetPositionX(), Jass::GetCameraTargetPositionY())) < NotifyRange){
			return;
		}

		//获取距离单位最近的单位
		UnitGroup *g = GroupUnits(
			NULL,
			NULL,
			PlayerGroup(
				PlayerFilter::ALLIANCE_PASSIVE | PlayerFilter::ALLIANCE_SHARED_CONTROL,
				NULL,
				PlayerLocal()
			),
			&RegionCircle(
				u->position(),
				2000.f
			),
			UnitFilter()
		);
		//
		Unit *alertUnit = g->nearestUnit(u->position());
		if (alertUnit) {
			AlertPoint(
				u->position().offsetPolar(
					min( 500, u->distanceToUnit(alertUnit) ), 
					u->angleToUnit(alertUnit)
				),
				alertUnit->testFlag(UnitFilter::STRUCTURE),
				alertUnit->owner() != PlayerLocal()
			);
		}

		GroupDestroy(g);
	}

	void onTimerAction (Timer *eventTimer){
		
		//单位名不限，所属玩家必须在游戏状态，非中立, 非野怪，单位必须为本地玩家敌人，非召唤、非守卫、非幻象
		UnitGroup *g = GroupUnits(
			NULL,
			NULL,
			PlayerGroup(
				PlayerFilter::STATE_PLAYING,
				PlayerFilter::CONTROL_NEUTRAL |	PlayerFilter::CONTROL_CREEP
			),
			NULL,
			UnitFilter(
				UnitFilter::ENEMY,
				UnitFilter::SUMMONED | UnitFilter::WARD | UnitFilter::ILLUSION,
				PlayerLocal()
			)
		);
		
		//对每个单位: 更新现在visible状态以及现在时间, 如果由不可见到可见，触发
		GroupForEachUnit(g, enumUnit,
			bool visible = enumUnit->testFlag(UnitFilter::VISIBLE, PlayerLocal());
			if (!enumUnit->visibleState.lastVisible && visible) {
				if (Time() > NotifyInitDelay) {//判断游戏时间, 前15秒不警告
					alertPerform(enumUnit);
				}
			}
			enumUnit->visibleState.lastVisible = visible;
			enumUnit->visibleState.lastVisiblePoint = enumUnit->position();
		);

		GroupDestroy(g);
	}

	void Init () {
		NotifyInitDelay = 15.0f;
		NotifyCycleTime = 0.5f;
		NotifyDelay = GameDataProfileGetFloat("Misc", "AttackNotifyDelay", 0);
		NotifyRange = GameDataProfileGetFloat("Misc", "AttackNotifyRange", 0);

		NotifyCycleTimer = GetTimer(NotifyCycleTime, onTimerAction, true);
		NotifyCycleTimer->start();
	}
}