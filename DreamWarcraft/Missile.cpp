#include "stdafx.h"
#include "Missile.h"
#include "BaseStructs.h"
#include "GameStructs.h"
#include "Unit.h"

void* MissileHookInfoArray[10] = {NULL};

std::map<uint32_t, uint32_t> MissileStatsMap;

DECLARE_MISSILE_TYPE(war3::MissileInstanceGenerator, war3::CMissile, Unit::WEAPON_TYPE_MISSILE, IG_MISSILE,	0xA0, 51);
DECLARE_MISSILE_TYPE(war3::MissileSplashInstanceGenerator, war3::CMissileSplash, Unit::WEAPON_TYPE_MISSILE_SPLASH, IG_MISSILESPLASH, 0xA0, 53);
DECLARE_MISSILE_TYPE(war3::MissileBounceInstanceGenerator, war3::CMissileBounce, Unit::WEAPON_TYPE_MISSILE_BOUNCE, IG_MISSILEBOUNCE, 0xA0, 52);
DECLARE_MISSILE_TYPE(war3::MissileLineInstanceGenerator, war3::CMissileLine, Unit::WEAPON_TYPE_MISSILE_LINE, IG_MISSILELINE, 0xA0, 51);
DECLARE_MISSILE_TYPE(war3::ArtilleryInstanceGenerator, war3::CArtillery, Unit::WEAPON_TYPE_ARTILLERY, IG_ARTILLERY, 0x94, 53);
DECLARE_MISSILE_TYPE(war3::ArtilleryLineInstanceGenerator,	war3::CArtilleryLine, Unit::WEAPON_TYPE_ARTILLERY_LINE,	IG_ARTILLERYLINE, 0x94, 55);

void Missile_Init() {
	MissileGeneratorHookInit<war3::CMissile>();
	MissileGeneratorHookInit<war3::CMissileSplash>();
	MissileGeneratorHookInit<war3::CMissileBounce>();
	MissileGeneratorHookInit<war3::CMissileLine>();
	MissileGeneratorHookInit<war3::CArtillery>();
	MissileGeneratorHookInit<war3::CArtilleryLine>();
}

void Missile_Cleanup() {
	for (int i = 0; i < sizeof(MissileHookInfoArray) / sizeof(void*); ++i) {
		if (MissileHookInfoArray[i])
			delete MissileHookInfoArray[i];
	}
}