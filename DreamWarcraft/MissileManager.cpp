#include "stdafx.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Tools.h"

typedef std::map<void*, MissileInfo> MissileMapType;

static MissileMapType MissileMap;
static std::list<MissileInfo*> UnitMissileInfoList;

void MissileManager_Init() {

}

void MissileManager_Cleanup() {
	MissileMap.clear();
	UnitMissileInfoList.clear();
}

void MissileManager_AddMissile(Unit::WeaponTypeEnum type, void* object, war3::HashGroup* hashGroup) {
	war3::CAgent* agent = (war3::CAgent*)ObjectFromHashOffset(hashGroup, 0x54);
	if (agent && AgentTypeIdGet(agent) == '+w3u') {
		MissileInfo& tmp = MissileMap[object];
		tmp.type = type;
		tmp.object = object;
	}
}

void MissileManager_RemoveMissile(void* object) {
	MissileMapType::iterator iter;
	if ((iter = MissileMap.find(object)) != MissileMap.end()) {
		MissileMap.erase(iter);
	}
}

const MissileInfo* MissileManager_TargetUnitMissileFetch(war3::CUnit* unit) {
	if (!unit) return NULL;

	static std::list<MissileInfo*>::iterator Iter;
	static bool Inited = false;

	if (!Inited) { //第一次调用，初始化
		UnitMissileInfoList.clear();
		for (MissileMapType::iterator iter = MissileMap.begin(); 
			iter != MissileMap.end();
			) 
		{
				war3::CMissile* missile = (war3::CMissile*)iter->first;
				war3::CAgent* agent = (war3::CAgent*)ObjectFromHashOffset(&(missile->targetHash), 0x54);
				if (!agent) {
					iter = MissileMap.erase(iter);
#ifndef _VMP
					OutputDebug("[WARNING] Invalidated missile removed!");
#endif
					continue;
				}
				if ((war3::CUnit*)agent == unit)
					UnitMissileInfoList.push_back(&(iter->second));
				++iter;
		}
		if (UnitMissileInfoList.size() > 0) {
			Inited = true;
			Iter = UnitMissileInfoList.begin();
		} else {
			return NULL;
		}
	}

	if (Iter != UnitMissileInfoList.end()) {
		const MissileInfo* rv = *Iter;
		++Iter;
		return rv;
	} else {
		Inited = false;
		return NULL;
	}
}

const MissileInfo* MissileManager_TargetUnitMissileFetch(Unit* unit) {
	return MissileManager_TargetUnitMissileFetch(UnitGetObject(unit->handleId()));
}

float MissileInfo::timeNeeded () const {
	float x, y, z, dist = 0, spd, rv = 0; Unit *target; //TODO 子弹类型不全导致不正确
	spd = ((war3::CBullet *)object)->baseBulletBase.speed.value;
	if (spd <= 0) return 0;

	BulletPositionGet(&((war3::CBullet *)object)->posData, x, y, z);
	//OutputScreen(10, "BulletPositionGet result : %.4f, %.4f, %.4f", x,y,z);
	if (!(	x >= Jass::GetCameraBoundMinX() && x <= Jass::GetCameraBoundMaxX()
		&&	y >= Jass::GetCameraBoundMinY() && y <= Jass::GetCameraBoundMaxY()
		)) return -1.f;//说明坐标无效

	switch(type){
	case Unit::WEAPON_TYPE_ARTILLERY:
		//break;
	case Unit::WEAPON_TYPE_ARTILLERY_LINE:
		target = GetUnit(ObjectToHandle(CUnitFromHash(&((war3::CArtillery *)object)->targetHash)));
		if (target)	dist = target->position().distanceTo(x, y);
		break;
	case Unit::WEAPON_TYPE_MISSILE:
		//break;
	case Unit::WEAPON_TYPE_MISSILE_BOUNCE:
		//break;
	case Unit::WEAPON_TYPE_MISSILE_LINE:
		//break;
	case Unit::WEAPON_TYPE_MISSILE_SPLASH:
		target = GetUnit(ObjectToHandle(CUnitFromHash(&((war3::CMissile *)object)->targetHash)));
		if (target)	dist = target->position().distanceTo(x, y);
		break;
	}
	rv = dist / spd;
	//OutputScreen(10, "bullet pos = %.3f, %.3f, time left = %.3f", x, y, dist/spd);
	return rv;
}

float MissileInfo::attackTotal () const {
	float rv = ((war3::CBullet *)object)->baseBulletBase.attack.value;
	rv += ((war3::CBullet *)object)->baseBulletBase.crit.value;
	return rv;
}

uint32_t MissileInfo::attackType () const {
	return ((war3::CBullet *)object)->baseBulletBase.attackType;
}