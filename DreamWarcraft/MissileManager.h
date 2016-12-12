#include "stdafx.h"
#ifndef MISSILE_MANAGER_H_INCLUDED
#define MISSILE_MANAGER_H_INCLUDED
#include "GameStructs.h"
#include "Unit.h"

struct MissileInfo {
	Unit::WeaponTypeEnum type;
	void* object;

	float timeNeeded() const;
	float attackTotal() const;
	uint32_t attackType () const;
};

void MissileManager_Init();
void MissileManager_Cleanup();
void MissileManager_AddMissile(Unit::WeaponTypeEnum type, void* object, war3::HashGroup* hashGroup);
void MissileManager_RemoveMissile(void* object);
const MissileInfo* MissileManager_TargetUnitMissileFetch(war3::CUnit* unit);
const MissileInfo* MissileManager_TargetUnitMissileFetch(Unit* unit);

#endif