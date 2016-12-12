/*
补刀

TODO

研究如何判定武器使用0还是1
添加safedelay以外的攻击方式

【在预测单位补刀时机中，增加考虑补刀者本身当前攻击CD（避免短暂移动后开启补刀，玩家的移动操作本身导致的攻击cd的扰动）】

【做出对acquire事件的响应！！同时要考虑对线时候的敌人取消操作的risk！如何计算！！】
【添加任务队列系统（用于优化攻击目标的选择，包括决定是否只正补等）】
【建立显示曲线的debug系统！！】
【miss事件时，应当无视update cooldown强制更新！】

*/





#include "stdafx.h"
#include <VMP.h>
#include "DreamDotaMain.h"
#include <process.h>
#include "Benchmark.h" 

#include "DebugPanel.h"

namespace LastHit {

	void LastHitUnitInitProc(Unit *u);
	void LastHitUnitEndProc(Unit *u);

	uint32_t GetHotkey(){
		return ProfileFetchInt("LastHit", "Hotkey", KEYCODE::KEY_TILDE);
	}
	

	
	typedef std::map<float, DnDAtkDist, DistributionLess>	damagemaptype;
	typedef std::map<float, float, DistributionLess>		distributiontype;
	typedef std::map<Unit*, float>		unitvaluetype;

	static UnitGroup				LastHitUnits;
	static unitvaluetype			UpdateCooldownMap;
	static float					ReactionDelay;			//平衡性常量，最大反应延迟
	static bool						EnableHit;
	static bool						EnableDeny;
	
	static UnitGroup* UnitAttackers;

	//常量
	static const float	PREDICT_TIME_MAX = 6.f;
	static const float	PREDICT_EXACT_TIME_MAX = 4.f;
	static const int	PREDICT_EXACT_COUNT_MAX = 15;
	static const int	PREDICT_COUNT_MAX = 30;
	static const int	PREDICT_COUNT_MAX_SINGLE = 8;
	static const float	PREDICT_COOLDOWN = 0.15f;	//是否对不同的攻击者进行判断决策 ?
	static const float	PREDICT_MIN_DISTANCE = 1500.f;//表示单位至少距离一个补刀者多远才会预测
	
	static const int STRATEGY_ERROR = -1;
	static const int STRATEGY_DONTMIND		= 0;
	static const int STRATEGY_ENEMYONLY		= 1;
	static const int STRATEGY_ALLYONLY		= 2;

	struct Action	//TODO 标准化
	{
		uint32_t	actionId;
		ActionType	actionType;
		uint32_t	actionFlag;
		Item		*usingItem;
		Point		targetPoint;
		Unit		*targetUnit;
	};

	static std::map<Unit*, Action> UnitLastActionMap;


	int LastHitStrategy() {
		if (EnableHit && EnableDeny) return STRATEGY_DONTMIND;
		else if (EnableHit && !EnableDeny) return STRATEGY_ENEMYONLY;
		else if (!EnableHit && EnableDeny) return STRATEGY_ALLYONLY;
		else return STRATEGY_ERROR;
	}

	void NormalAttack(Unit *attacker, Unit *target) {
		if (!(attacker && target))
			return;

		attacker->sendAction(
			ACTION_ATTACK,
			Target,
			None,
			NULL,
			target->position(),
			target,
			true
		);
	}

	void SafeDelayAttack_waited(Timer *tm){
		std::pair<Unit *, Unit *> *pData = tm->data<std::pair<Unit *, Unit *>>();
		Unit *attacker = pData->first;
		Unit *target = pData->second;

		if (!(attacker && target))
			return;

		NormalAttack(attacker, target);
	}

	void SafeDelayAttack(Unit *attacker, Unit *target){
		if (!(attacker && target))
			return;

		attacker->sendAction(
			ACTION_SMART,
			Target,
			None,
			NULL,
			attacker->position(),
			NULL,
			true
		);
		Timer *tm = GetTimer(0.03, SafeDelayAttack_waited);
		std::pair<Unit *, Unit *> data (attacker, target);
		tm->setData<std::pair<Unit *, Unit *>>(&data);
		tm->start();
	}
	
	void StandStillAndCool(Unit *attacker) {
		if (!attacker)
			return;

		attacker->sendAction(
			ACTION_ATTACKGROUND,
			TargetPoint,
			None,
			NULL,
			attacker->position().offsetPolar(50.f, attacker->direction()),
			NULL,
			true
		);
	}

	bool UnitIsStandStillAndCool (Unit *attacker) {//TODO 使用本地系统
		if (!attacker)
			return false;
		return (attacker->currentOrder() == ACTION_ATTACKGROUND);
	}

	bool UnitIsValid(Unit *u) {
		if (u) {
			if (u->handleId()){
				if (u->life() > 0){
					return true;
				}
			}
		}
		return false;
	}

	bool UnitNearAnyLastHitter (Unit *u, float minimumDistance){
		int lastHitUnitCount = LastHitUnits.size();//补刀者数量
		if (lastHitUnitCount <= 0) return false;//如果补刀者数量为0，单位肯定不在任何补刀者附近
		if (!UnitIsValid(u)) return false;//如果单位本身无效，肯定不在任何补刀者附近
		GroupForEachUnit(&LastHitUnits, lasthitter,
			if (UnitIsValid(lasthitter) && u->distanceToUnit(lasthitter) <= minimumDistance){
				return true;
			}
		);
		return false;
	}

	UnitGroup *UnitGetAttackers (Unit *u, float range){
		if (UnitAttackers) {
			GroupDestroy(UnitAttackers); 
			UnitAttackers = NULL;
		}

		if (!u)
			return UnitAttackers = new UnitGroup();

		UnitGroup *tmpGroup = GroupUnits(
			NULL,
			NULL,
			PlayerGroupAll(),
			&RegionCircle(u->position(), range),//只考虑单位附近的攻击者 TODO 应该改为sight ?
			UnitFilter(
				NULL,
				(UnitFilter::DEAD | UnitFilter::HIDDEN)
			)
		);

		UnitAttackers = new UnitGroup();
		GroupForEachUnit(tmpGroup, attacker,
			if (UnitIsValid(attacker) && attacker->acquiredTarget() == u){
				UnitAttackers->add(attacker);
			}
		);
		GroupDestroy(tmpGroup);
		return UnitAttackers;
	}

	//用于debug distribution内容
	void DistributionMapContentPrint(distributiontype *pDistMap, const char *identStr, bool clearScreenBefore = false){
#ifndef _VMP
		if (pDistMap->empty()) {
			OutputScreen(10,"pDistMap of |cffffcc00%s|r : Empty", identStr);
			return;
		}
		if (clearScreenBefore) Jass::ClearTextMessages();
		OutputScreen(10,"pDistMap of |cffffcc00%s|r :", identStr);
		for (distributiontype::const_iterator it = pDistMap->begin();
			it != pDistMap->end(); ++it)	
		{
			OutputScreen(10, "  [%.3f] = %.3f", it->first, it->second);
		}
#endif
	}

	//用于debug damagemap内容
	void DamageMapContentPrint(damagemaptype *pDamageMap, const char *identStr, bool clearScreenBefore = false){
#ifndef _VMP
		if (pDamageMap->empty()) {
			OutputScreen(10,"DamageMap of |cffffcc00%s|r : Empty", identStr);
			return;
		}
		if (clearScreenBefore) Jass::ClearTextMessages();
		OutputScreen(10,"DamageMap of |cffffcc00%s|r :", identStr);
		for (damagemaptype::const_iterator it = pDamageMap->begin();
			it != pDamageMap->end(); ++it)	
		{
			OutputScreen(10, "  [%.3f] = %s", it->first, it->second.toString().c_str());
		}
#endif
	}

	//向damagemap写入所有指向目标单位的子弹伤害
	void DamageMapAddAllMissile(damagemaptype *pDamageMap, Unit *targetUnit){
		if (!targetUnit)
			return;
		const MissileInfo* info; float timeNeed;
		while(NULL != (info = MissileManager_TargetUnitMissileFetch(targetUnit))) {
			timeNeed = info->timeNeeded();//为子弹到达击中目标所需的时间
			if (timeNeed > -1.f){//说明有效
				(pDamageMap->operator[](Time() + timeNeed)) 
					&= DnDAtkDist( //由于子弹拥有确定伤害值，因此生成一个只有基础值而不含骰子的攻击分布
						info->attackTotal() //包含普通伤害 + 暴击伤害
						* targetUnit->damageFactorAsTarget(info->attackType()) //为子弹所属攻击类型对目标单位的伤害比例
					);
			}
		}
	}

	//向damagemap写入目标单位所有攻击者的攻击伤害
	void DamageMapAddAllDamages(damagemaptype *pDamageMap, Unit *targetUnit, bool countLastHitter) {
		if (!targetUnit)
			return;
		UnitGroup *groupAttackers = UnitGetAttackers(targetUnit, 1400.f);
		if (!countLastHitter) groupAttackers->remove(&LastHitUnits);
		float time, dmgptRemain, coolRemain, cd;
		float timePredictMaximum = Time() + PREDICT_TIME_MAX;
		int SinglePredictCount;
		for (UnitGroup::iterator iter = groupAttackers->begin(); iter != groupAttackers->end(); ++iter){
			Unit *attacker = *iter;//TODO 判断单位射程范围等状态
			DnDAtkDist u_dmg = attacker->damage(attacker->weaponTo(targetUnit), targetUnit);
			time = -1.f;
			if ((dmgptRemain = attacker->damagePointRemain()) > 0) {
				time = Time() + dmgptRemain + attacker->attackTime(attacker->weaponTo(targetUnit), targetUnit, false, false);
			}
			else if ((coolRemain = attacker->cooldownRemain()) > 0) {
				time = Time() + coolRemain + attacker->attackTime(attacker->weaponTo(targetUnit), targetUnit, true, false);
			}
			else {//TODO 还需要处理acquire但尚未攻击的情况
				continue;
			}
			
			cd = attacker->cooldown(attacker->weaponTo(targetUnit));
			if (time <= 0 || cd <= 0) continue;
			SinglePredictCount = 0;
			while (time < timePredictMaximum && SinglePredictCount < PREDICT_COUNT_MAX_SINGLE){
				(pDamageMap->operator[](time)) &= u_dmg;
				time += cd; ++SinglePredictCount;
			}
		}
	}

	static uint32_t FunctionResultMax;//debug
	static damagemaptype damageMap;	//用于储存所有按时间排序到来的伤害分布
	void UpdateUnitTiming (Unit *targetUnit, bool forceIgnoreCooldown = false) {
		if (!targetUnit) return;

		damageMap.clear();

		//类型检测：如果需更新的目标单位(targetUnit，以下简称目标)是英雄，不更新
		if (targetUnit->testFlag(UnitFilter::HERO)) return;

		//范围：如果不存在补刀者，或目标不在任何补刀者附近的PREDICT_MIN_DISTANCE距离内，直接结束
		if (!UnitNearAnyLastHitter(targetUnit, PREDICT_MIN_DISTANCE)) return;

		//频率：避免过频繁的更新，如果目标距离上次更新时间不到PREDICT_COOLDOWN，直接结束；如果指定参数forceIgnoreCooldown强制更新则例外
		if (!forceIgnoreCooldown && (Time() < UpdateCooldownMap[targetUnit] + PREDICT_COOLDOWN)) return;

		//统计与预测目标未来所有伤害：物理子弹为确定时间造成确定伤害值，而其他攻击者为预测时间造成伤害分布
		DamageMapAddAllMissile(&damageMap, targetUnit);

		//其他攻击
		DamageMapAddAllDamages(&damageMap, targetUnit, false);//不包含补刀者

		//测试
		//DamageMapContentPrint(&damageMap, targetUnit->debugName(), false);

		//如果数量或时间超过exact，就把伤害改为平均值，以减少计算量
		int TotalPredictCount = 0;
		float timePredictExactMaximum = Time() + PREDICT_EXACT_TIME_MAX;
		damagemaptype damageMapTemp;
		for (damagemaptype::const_iterator iterOuter = damageMap.begin(); 
			iterOuter != damageMap.end(); 
			++iterOuter, ++TotalPredictCount) 
		{
			float time = iterOuter->first;
			if ( 
					TotalPredictCount >= PREDICT_EXACT_COUNT_MAX
				||	time > timePredictExactMaximum
			){
				damageMapTemp[time]	= DnDAtkDist(iterOuter->second.expectValue());
			}
			else{
				damageMapTemp[time] = iterOuter->second;
			}
		}
		damageMap.swap(damageMapTemp);

		std::map<Unit *, distributiontype> lasthitMap;
		float deathRate = 0;
		float deathCDF = 0;
		float currentHP;
		damagemaptype::const_iterator iterOuter = damageMap.begin(); 
		int iterOuterLoopCount = 0;
		DnDAtkDist deathRateDist;
		while(
			(iterOuter != damageMap.end()) && 
			(iterOuterLoopCount < PREDICT_COUNT_MAX)
		){
			//OutputScreen(10, "iterOuterLoopCount = %d, iterOuter->first = %.3f", iterOuterLoopCount, iterOuter->first);
			deathRateDist = DnDAtkDist();
			//对所有1..i次伤害
			damagemaptype::const_iterator 
				iterInner = iterOuter;
			while(true){
				//OutputScreen(10, "iterInner");
				DnDAtkDist d = iterInner->second;
				deathRateDist &= d;
				if (iterInner == damageMap.begin()) break;
				--iterInner;
			}
			
			currentHP = targetUnit->life();
			currentHP -= 0.405f;
			currentHP += max(0, ((iterOuter->first)-Time())*(targetUnit->regenSpeedLife()));
			deathRate = deathRateDist.chanceGreaterEqual(currentHP, false);
			deathRate = max(deathRate, 0);
			deathRate = min(deathRate, 1);

			//OutputScreen(10, "[%s] deathRate at %.3f is %.2f", targetUnit->debugName(), iterOuter->first, deathRate);

			deathCDF += (1 - deathCDF) * deathRate;//

			//OutputScreen(10, "[%s] deathCDF at %.3f is %.2f", targetUnit->debugName(), iterOuter->first, deathCDF);

			DnDAtkDist lastHitRateDist;
			float lastHitRate;
			for (uint32_t i = 0; i < LastHitUnits.size(); i++){ //对所有补刀者计算该次攻击叠加单位本身攻击的结果
				Unit *u = LastHitUnits.getUnit(i);
				lastHitRateDist = deathRateDist;
				lastHitRateDist &= u->damage(0, targetUnit);

				lastHitRate = lastHitRateDist.chanceGreaterEqual(currentHP, false);
				lastHitRate *= (1 - deathCDF);//(1 - deathRate);
				lastHitRate = max(lastHitRate, 0);
				lastHitRate = min(lastHitRate, 1);

				//OutputScreen(10, "[%s] lastHitRate at %.3f is %.2f", targetUnit->debugName(), iterOuter->first, lastHitRate);

				lasthitMap[u][iterOuter->first] = lastHitRate;//iterOuter->first的限制
			}

			//if (deathRate >= 1.0f){
			if (deathCDF >= 1.0f){
				break;
			}

			++iterOuter; ++iterOuterLoopCount;
		}
		
		//把结果转换为连续函数写回Unit
		std::pair<float, float> chancePair;
		GroupForEachUnit(&LastHitUnits, u,
			//OutputScreen(10, "Before transform:");
			//DistributionMapContentPrint(&(lasthitMap[u]), targetUnit->debugName());
			u->lasthitRate[targetUnit].setValueFromDiscrete(&(lasthitMap[u]), 0);//TODO
			//OutputScreen(10, "Before conv:");
			//u->lasthitRate[targetUnit].print();
			u->lasthitRate[targetUnit].convolution(LatencyGetNegDist());
			//OutputScreen(10, "AFTER conv:");
			//u->lasthitRate[targetUnit].print();
			//LatencyDistPrint();//debug

				//chancePair = u->lasthitRate[targetUnit].maxima();
				//OutputScreen(10, "maxima of %s is (%.3f, %.3f)", targetUnit->debugName(), chancePair.first, chancePair.second);

			//FunctionResultMax = max(FunctionResultMax, u->lasthitRate[targetUnit].size());
			//DefaultDebugPanel->set("functionSize","%d (max %d)",
			//	u->lasthitRate[targetUnit].size(), 
			//	FunctionResultMax
			//);

			//OutputScreen(10, "transfer to function");
			//u->lasthitRate[targetUnit].print();
		);

		//更新完成，更新“上次更新时间”
		UpdateCooldownMap[targetUnit] = Time();
	}

	void onTimerExpire (Timer *tm){
		if (STRATEGY_ERROR == LastHitStrategy()) return;

		//DefaultDebugPanel->set("time", "|cffffcc00%.3f|r", Time());

		Unit *lasthitter;
		float timeNeedTotal = 0;
		std::pair<float, float> chancePair;
		float chance;
		float lasthitterCurrentCooldown;

		bool lasthitterIsRanged = false;
		bool missionFound = false;
		Function lasthitFunctionCopy;

		for (UnitGroup::iterator iter = LastHitUnits.begin(); iter != LastHitUnits.end(); ++iter){
			lasthitter = *iter;

			//如果补刀者没有被本地玩家选中，直接清理并跳过
			if (!lasthitter->isSelectedLocal()){
				LastHitUnits.remove(lasthitter);
				LastHitUnitEndProc(lasthitter);
				return;
			}

			if (lasthitter->lasthitCurrentTarget){
				if (UnitIsValid(lasthitter->lasthitCurrentTarget)) continue;//如果当前有任务就略过
				else lasthitter->lasthitCurrentTarget = NULL;
			}
			missionFound = false;
			lasthitterIsRanged = lasthitter->testFlag(UnitFilter::RANGED_ATTACKER);

			std::map<Unit*, Function> * pLasthitRateMap = &(lasthitter->lasthitRate);
			//得到单位周围的单位
			UnitGroup *unitsNearby = 
				GroupUnits(
				NULL,
				NULL,
				PlayerGroupAll(),
				&RegionCircle(lasthitter->position(), lasthitter->range(0)+
					(lasthitterIsRanged ? 100.f : 150.f)
				),//buffer
				UnitFilter(
					NULL,
					UnitFilter::HIDDEN | UnitFilter::DEAD | UnitFilter::INVULNERABLE
				)
			);
			//DefaultDebugPanel->set("Nearby Unit Count", "%d", unitsNearby->size());

			lasthitterCurrentCooldown = lasthitter->cooldownRemain();

			//对每个目标的补刀function扣去所需时间
			if (unitsNearby->size()){
				GroupForEachUnit(unitsNearby, target,
					if (LastHitStrategy() == STRATEGY_ENEMYONLY  &&  !target->isEnemyToLocalPlayer() ) continue;
					if (LastHitStrategy() == STRATEGY_ALLYONLY  &&  !target->isAllyToLocalPlayer() ) continue;
					if (pLasthitRateMap->count(target)){
						lasthitFunctionCopy = pLasthitRateMap->operator[](target);
						timeNeedTotal = lasthitterIsRanged ?
							max(lasthitterCurrentCooldown, 0.5f)
							+ lasthitter->attackTime(lasthitter->weaponTo(target), target, true, false)//远程用safe delay 从操作到击中所需时间 = 延迟 + 0.5 + 前摇 + 子弹时间
							:
							max(lasthitterCurrentCooldown, lasthitter->turnTimeToUnit(target))//TODO 与反应延迟的计算？
							+
							lasthitter->attackTime(lasthitter->weaponTo(target), target, true, false);//近战用普通并且需要转身

						//lasthitFunctionCopy.smooth(uint32_t((0.03f/RASTER_UNIT-1.f)/2.f));//模拟0.03秒的命令不稳定性

						if (!lasthitterIsRanged){
							uint32_t smoothRadius = uint32_t((ReactionDelay/RASTER_UNIT-1.f)/2.f);
							lasthitFunctionCopy.smooth(smoothRadius);
							lasthitFunctionCopy.shift((-ReactionDelay/2.f));
						}

						chancePair = lasthitFunctionCopy.maxima();//TODO 数值(概率)按5%颗粒化?
						chance = chancePair.second;
						if (chance > 0.05f){//TODO 最小允许概率：常数化/配置化
							if (
								//Time() < chancePair.first &&//TODO 是否有意义？
								Time() + timeNeedTotal >= chancePair.first //当前时间已经超过补刀时机
							){
								//补刀
								//Jass::ClearTextMessages();
								//OutputScreen(10, "[%.3f] lasthit unit %s(%d) chance = |cffffcc00%.2f|r", Time(), target->name(), target->handleId(), chance);
								//lasthitFunctionCopy.print();

								lasthitter->lasthitCurrentTarget = target;
								if (lasthitterIsRanged){
									SafeDelayAttack(lasthitter, target);
								}
								else{
									NormalAttack(lasthitter, target);
								}
								missionFound = true;
							}
						}
					}
					if (!missionFound) {//直接判断血量
						if (//TODO 区分敌我
							target != lasthitter
							&&	lasthitter->damage(lasthitter->weaponTo(target), target).minValue() >= target->life()	)		//直接杀死目标
						{
							//补刀
							//OutputScreen(10, "lasthit low HP unit %s(%d)", target->name(), target->handleId() );
							lasthitter->lasthitCurrentTarget = target;
							NormalAttack(lasthitter, target);
							missionFound = true;
						}
					}
					if (missionFound) break;//TODO 优先级，喜好
				);
				if (!missionFound) {
					if (!UnitIsStandStillAndCool(lasthitter)){
						StandStillAndCool(lasthitter);
					}
				}
			}

			GroupDestroy(unitsNearby);
		}

		//debug
		//DefaultDebugPanel->set("Last Hit | LastHitter count", "%d", LastHitUnits.size());		
	}

	//单位进入补刀模式时的行为
	void LastHitUnitInitProc(Unit *u){
		if (!u)	return;

		//记录当前命令
		//只记录smart
		if (u->currentOrder() == 0xD0003)
		{
			Unit *targetUnit = u->currentTargetUnit();

			Action action;
			action.actionId = ACTION_SMART;
			action.actionType = Target;//targetUnit ? Target : TargetPoint;
			action.actionFlag = None;
			action.targetPoint = u->currentTargetPoint();
			action.targetUnit = targetUnit;
			UnitLastActionMap[u] = action;
		}

		UnitGroup *unitsNearby = //得到单位周围的单位
			GroupUnits(
			NULL,
			NULL,
			PlayerGroupAll(),
			&RegionCircle(u->position(), PREDICT_MIN_DISTANCE),
			UnitFilter(
				NULL,
				UnitFilter::HIDDEN | UnitFilter::DEAD | UnitFilter::INVULNERABLE
			)
		);
		GroupForEachUnit(unitsNearby, target,
			//OutputScreen(10, "init update for unit %s (%d)", target->name(), target->handleId() );
			UpdateUnitTiming(target, true);
		);
		GroupDestroy(unitsNearby);
	}

	//单位退出补刀模式时的行为
	void LastHitUnitEndProc(Unit *u){
		if (!u) return;
		//TODO 改为收集补刀模式时的玩家操作（例如想要右键移动），而后释放操作
		//现在为退出补刀时按stop
		/*u->sendAction(
			ACTION_STOP, 
			TargetNone, 
			None, 
			NULL, 
			POINT_NONE, 
			NULL, 
			true
		);*/

		if (UnitLastActionMap.count(u))
		{
			Action action = UnitLastActionMap[u];
			u->sendAction(
				action.actionId, 
				action.actionType,
				action.actionFlag, 
				NULL,//action.usingItem,
				action.targetPoint,
				action.targetUnit, 
				false
			);
			UnitLastActionMap.erase(u);
		}
		else
		{
			u->sendAction(
				ACTION_STOP, 
				TargetNone, 
				None, 
				NULL, 
				POINT_NONE, 
				NULL, 
				true
			);
		}
		
	}

	void onAttackReleased_Waited (Timer *tm) {
		Unit *target = *(tm->data<Unit *>());
		if (target)
			UpdateUnitTiming(target);
	}

	void onAttackReleased(const Event *evt) {
		UnitAttackReleasedEventData* data = evt->data<UnitAttackReleasedEventData>();	
		Unit *attacker = GetUnit(data->attacker);
		if (attacker) {
			Unit *target = attacker->acquiredTarget();
			if (target) {
				if ( true
				//&&	!LastHitUnits.has(attacker)	//单位不是补刀者
				){				
					Timer *tm = GetTimer(0, onAttackReleased_Waited, false);
					tm->setData<Unit *>(&target);
					tm->start();
				}

				//清理补刀目标
				if (attacker->lasthitCurrentTarget){//TODO 如果考虑到1轮以上攻击可能不正确
					attacker->lasthitCurrentTarget = NULL;
					//OutputScreen(10, "last hit target cleanup");
				}
			}
		}
		
	}

	void onAttackMissed_Waited(Timer *tm) {
		Unit *target = *(tm->data<Unit *>());
		//OutputScreen(10, "[%.3f] missed , update!", Time());
		if (target)
			UpdateUnitTiming(target, true);//强制更新
	}

	void onAttackMissed(const Event *evt) {
		UnitAttackMissedEventData* data = evt->data<UnitAttackMissedEventData>();
		Unit *attacker = GetUnit(data->attacker);
		if (attacker) {
			Unit *target = attacker->acquiredTarget();
			if (target) {
				if ( !LastHitUnits.has(attacker)	//单位不是补刀者
				){
					Timer *tm = GetTimer(0, onAttackReleased_Waited, false);
					tm->setData<Unit *>(&target);
					tm->start();
				}
			}
		}
	}

	void onUnitDamaged (const Event *evt) {
		UnitDamagedEventData *data = evt->data<UnitDamagedEventData>();
		Unit *targetUnit = GetUnit(data->target);
		Unit *sourceUnit = GetUnit(data->source);

		if (!(targetUnit && sourceUnit))
			return;

		float damage = data->damage;
		/*
		if (sourceUnit->testFlag(UnitFilter::HERO)){
			OutputScreen(10, "|cffffcc00[%.3f]|r Damaged : %.3f damage dealt", Time(), damage);
		}
		else{
			OutputScreen(10, "[%.3f] Damaged : %.3f damage dealt", Time(), damage);
		}
		*/
	}

	void onUnitAcquireStart (const Event *evt){
		UnitAcquireEventData *data = evt->data<UnitAcquireEventData>();
		//OutputScreen(10, "|cffffcc00[%.3f]|r %d starts to acquire %d", Time(), data->eventUnit, data->target);
		Unit *eventUnit = GetUnit(data->eventUnit);
		Unit *targetUnit = GetUnit(data->target);

		if (!(eventUnit && targetUnit))
			return;
		//TODO
	}

	void onUnitAcquireReady (const Event *evt){
		UnitAcquireEventData *data = evt->data<UnitAcquireEventData>();
		//OutputScreen(10, "|cffffcc00[%.3f]|r %d is ready acquire %d", Time(), data->eventUnit, data->target);
		Unit *eventUnit = GetUnit(data->eventUnit);
		Unit *targetUnit = GetUnit(data->target);

		if (!(eventUnit && targetUnit))
			return;
		//TODO
	}

	void onUnitAcquireStop (const Event *evt){
		UnitAcquireEventData *data = evt->data<UnitAcquireEventData>();
		//OutputScreen(10, "|cffffcc00[%.3f]|r %d stops acquire %d", Time(), data->eventUnit, data->target);
		Unit *eventUnit = GetUnit(data->eventUnit);
		Unit *targetUnit = GetUnit(data->target);
		
		if (!(eventUnit && targetUnit))
			return;
		
		UpdateUnitTiming(targetUnit, true);//TODO !!!
	}

	void onUnitDeath (const Event *evt) {
		Unit *killer = GetUnit(Jass::GetKillingUnit());
		Unit *deadUnit = GetUnit(Jass::GetDyingUnit());

		if (!(killer && deadUnit))
			return;

		Unit *acquiredUnit = deadUnit->acquiredTarget();
		if (acquiredUnit){
			UpdateUnitTiming(acquiredUnit, true);
		}
		GroupForEachUnit(&LastHitUnits, lasthitter,
			if (deadUnit == lasthitter->lasthitCurrentTarget) lasthitter->lasthitCurrentTarget = NULL;
		);
	}


	static bool				Enabled;
	void SetLastHitActivate (const Event *evt) {
		
		VMProtectBeginVirtualization("LastHitActivate");

		if (!Enabled) return;

		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if ( data->code == GetHotkey() ) {//判断按键是补刀键
			data->discard();	 DiscardCurrentEvent();
			UnitGroup *g_currentSelected = GroupUnitsOfPlayerSelected(PlayerLocal(), false);//本地玩家当前所选单位
			bool active = (evt->id() == EVENT_KEY_DOWN);//按下为进入补刀，弹起为退出补刀
			uint32_t countChanged = 0, countValid = 0;
			GroupForEachUnit(g_currentSelected, enumUnit, 
				if(	enumUnit->testFlag(UnitFilter::CONTROLLABLE, PlayerLocal())	) {//单位必须为本地玩家可控制
					if (enumUnit->lasthitActive != active){//设置补刀开关
						enumUnit->lasthitActive = active; ++countChanged;
						active ? LastHitUnits.add(enumUnit) : LastHitUnits.remove(enumUnit);
						if (active) LastHitUnitInitProc(enumUnit);
						else		LastHitUnitEndProc(enumUnit);
					} ++countValid;
				}
			);
			if (countChanged)				SoundPlay("InterfaceClick", NULL, 0);
			else if (!countValid && active)	SoundPlay("InterfaceError", NULL, 0);
			GroupDestroy(g_currentSelected);
		}
		
		VMProtectEnd();
	}

	static CheckBox*		CbEnabled;
	static Label*			LbEnabled;

	static CheckBox*		CbEnableHit;
	static Label*			LbEnableHit;

	static CheckBox*		CbEnableDeny;
	static Label*			LbEnableDeny;

	static Button*			BtnHotkey;

	void Dependency(CheckBox* cb, bool flag) {
		CbEnableHit->activate(flag);
		LbEnableHit->activate(flag);
		CbEnableDeny->activate(flag);
		LbEnableDeny->activate(flag);
		BtnHotkey->enable(flag);
	}

	void UpdateBtnText(Button *btn) {
		std::string str;
		str+=StringManager::GetString(STR::LASTHIT_BTNSETHOTKEY);
		str+=": |cffffcc00";
		str+=KEYCODE::
			//ToString(GetHotkey());
			getStr(GetHotkey());
		str+="|r";
		btn->setText(str.c_str());
	}

	static bool EditingHotkey;
	static Button* EditingHotkeyBtn;
	void BtnCallback(Button *btn) {
		btn->setText(StringManager::GetString(STR::LASTHIT_BTNSETHOTKEY_NOTE));
		EditingHotkey = true;
		EditingHotkeyBtn = btn;
	}

	void DetectHotkey(const Event* evt){
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (EditingHotkey){
			ProfileSetInt("LastHit", "Hotkey", data->code);
			UpdateBtnText(EditingHotkeyBtn);
			EditingHotkey = false;
			EditingHotkeyBtn = NULL;
			data->discard();	 DiscardCurrentEvent();
			SoundPlay("GlueScreenClick", NULL, 0);
		}
	}

	void onActionSent(const Event *evt)
	{
		ActionEventData *data = evt->data<ActionEventData>();
		if ( !data->byProgramm )		//玩家操作
		{
			//获得当前补刀单位
			UnitGroup *g_currentSelected = GroupUnitsOfPlayerSelected(PlayerLocal(), false);//本地玩家当前所选单位
			Unit *u;
			for (UnitGroup::iterator iter = g_currentSelected->begin(); 
				iter != g_currentSelected->end(); ++iter)
			{
				u = *iter;
				if (u)
				{
					if (LastHitUnits.has(u))
					{
						Action action;
						action.actionId = data->id;
						action.actionType = data->type;
						action.actionFlag = data->flag;
						action.usingItem = GetItem(data->usingItem);
						action.targetPoint = Point(data->x, data->y);
						action.targetUnit = GetUnit(data->target);
						UnitLastActionMap[u] = action;
						data->discard(); DiscardCurrentEvent();
					}
				}
			}


			GroupDestroy(g_currentSelected);
		}
	}

	void CreateMenuContent(){

		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::LASTHIT_CATEGORYNAME), NULL); //TODO fix tooltip

		CbEnabled = new CheckBox(Panel);
		CbEnabled->bindProfile("LastHit", "Enabled", true);//默认开启
		CbEnabled->bindVariable(&Enabled);
		CbEnabled->bindCallback(Dependency);
		CbEnabled->setRelativePosition( POS_UL,	Panel, POS_UL, 0.03f, -0.03f );
		LbEnabled = new Label( Panel, StringManager::GetString(STR::LASTHIT_ENABLE), 0.013f );
		LbEnabled->setRelativePosition(	POS_L, CbEnabled, POS_R, 0.01f, 0 );

		CbEnableHit = new CheckBox( Panel );
		CbEnableHit->bindProfile( "LastHit", "EnableHit", true );
		CbEnableHit->bindVariable( &EnableHit );
		CbEnableHit->setRelativePosition( POS_UL, Panel, POS_UL, 0.03f, -0.057f );
		LbEnableHit = new Label( Panel, StringManager::GetString(STR::LASTHIT_ENABLEHIT), 0.013f );
		LbEnableHit->setRelativePosition( POS_L, CbEnableHit, POS_R, 0.01f, 0 );

		CbEnableDeny = new CheckBox(Panel);
		CbEnableDeny->bindProfile("LastHit", "EnableDeny", true);
		CbEnableDeny->bindVariable(&EnableDeny);
		CbEnableDeny->setRelativePosition(POS_UL,Panel,POS_UL,0.03f, -0.084f);
		LbEnableDeny = new Label(Panel, StringManager::GetString(STR::LASTHIT_ENABLEDENY), 0.013f);
		LbEnableDeny->setRelativePosition(POS_L, CbEnableDeny, POS_R, 0.01f, 0);

		BtnHotkey = new Button(
			Panel,
			0.135f,
			0.035f,
			UISimpleButton::MOUSEBUTTON_LEFT,
			UISimpleButton::STATE_ENABLED,
			BtnCallback
		);
		UpdateBtnText(BtnHotkey);
		BtnHotkey->setRelativePosition(
			POS_UL, 
			Panel, 
			POS_UL,
			0.03f + Panel->width()/2, -0.03f);

		MainDispatcher()->listen(EVENT_KEY_DOWN, DetectHotkey);
		EditingHotkeyBtn = NULL;
		EditingHotkey  = false;

		Dependency(CbEnabled, CbEnabled->isChecked());
	}

	void Init() {

		VMProtectBeginVirtualization("LastHitInit");

		//UI
		CreateMenuContent();

		//LastHitStrategy = ProfileFetchInt("LastHit", "Strategy", STRATEGY_DONTMIND);
		ReactionDelay = GameDataProfileGetFloat("Misc", "ReactionDelay", 0);
		

		MainDispatcher()->listen(EVENT_UNIT_RECEIVE_DAMAGE, onUnitDamaged);//用于debug
		MainDispatcher()->listen(EVENT_UNIT_ATTACK_RELEASED, onAttackReleased);//常规攻击发出，更新目标单位数据
		MainDispatcher()->listen(EVENT_UNIT_ATTACK_MISS, onAttackMissed);//常规攻击并且miss

		//开始注意到一个目标 --> 反应延迟 + [转身 + 移动] + 攻击事件开始所有所需时间，更新目标单位数据
		//完成注意到一个目标 --> 攻击事件开始所有所需时间，更新目标单位数据 TODO 是否正确？
		//停止注意到一个目标 --> 无条件去掉任何对原目标的攻击，更新原目标单位数据
		MainDispatcher()->listen(EVENT_UNIT_ACQUIRE_START, onUnitAcquireStart);
		MainDispatcher()->listen(EVENT_UNIT_ACQUIRE_READY, onUnitAcquireReady);
		MainDispatcher()->listen(EVENT_UNIT_ACQUIRE_STOP,  onUnitAcquireStop);

		//TODO 单位死亡事件，用于防范bug的清理
		//TODO 实际上应该为“单位变为不能被补刀者攻击”事件
		MainDispatcher()->listen(Jass::EVENT_PLAYER_UNIT_DEATH, onUnitDeath);

		//不断循环计算是否补刀
		GetTimer(0.03, onTimerExpire, true)->start();

		//进入/退出补刀模式：判断按键状态
		MainDispatcher()->listen(EVENT_KEY_DOWN, SetLastHitActivate);
		MainDispatcher()->listen(EVENT_KEY_UP, SetLastHitActivate);

		//检测玩家操作：记录补刀中最后一次操作
		MainDispatcher()->listen(EVENT_LOCAL_ACTION, onActionSent);

		VMProtectEnd();
	}

	void Cleanup() {
		VMProtectBeginVirtualization("LastHitClean");

		LastHitUnits.clear();
		UpdateCooldownMap.clear();
		if (UnitAttackers) GroupDestroy(UnitAttackers); UnitAttackers = NULL;

		UnitLastActionMap.clear();

		VMProtectEnd();
	}
}