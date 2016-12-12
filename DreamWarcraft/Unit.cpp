#include "stdafx.h"

#include "Foundation.h"
#include "Unit.h"
#include "Player.h"
#include "Jass.h"
#include "Tools.h"
#include "UnitGroup.h"
#include "HeroBar.h"
#include "DebugPanel.h"

VisibleState::VisibleState() : lastVisible(), lastVisiblePoint() { }
UnitFilter::UnitFilter (uint64_t requireFields, uint64_t excludeFields, int toWhichPlayerId)
		: require(requireFields), exclude(excludeFields), player(toWhichPlayerId) { }
UnitFilter::UnitFilter () : require(), exclude(), player() { }
bool UnitFilter::operator==(int rhs) {	return rhs == NULL ? (!require && !exclude && !player) : false;	}


Unit::Unit(uint32_t handleId) : 
	handleId_(handleId), visibleState(), 
	lasthitActive(false), lasthitCurrentTarget(NULL), lasthitRate() 
	{
#ifdef _DEBUG
		debugPanel = GetDebugPanel(this);
#endif
	}
Unit::~Unit (void) {
}

uint32_t Unit::handleId (void) const { return handleId_; }
const char *Unit::name() const { return ObjectIdToNameChar(typeId());}

static char UnitDebugNameBuffer[0x30];
const char *Unit::debugName(bool showHandleId, bool showCUnit) const { 
	if (showHandleId && showCUnit){
		sprintf_s(UnitDebugNameBuffer, 0x30, "%s (%d, 0x%X)", ObjectIdToNameChar(typeId()), handleId_, UnitGetObject(handleId_));
	}
	else if (showHandleId && !showCUnit){
		sprintf_s(UnitDebugNameBuffer, 0x30, "%s (%d)", ObjectIdToNameChar(typeId()), handleId_);
	}
	else if (!showHandleId && showCUnit){
		sprintf_s(UnitDebugNameBuffer, 0x30, "%s (0x%X)", ObjectIdToNameChar(typeId()), UnitGetObject(handleId_));
	}
	else {
		sprintf_s(UnitDebugNameBuffer, 0x30, "%s", ObjectIdToNameChar(typeId()));
	}
	return UnitDebugNameBuffer;
}

float Unit::acquireRange () const {return Jass::GetUnitAcquireRange(handleId_);}
float Unit::turnSpeed () const {return Jass::GetUnitTurnSpeed(handleId_);}
float Unit::propWindow () const {return Jass::GetUnitPropWindow(handleId_);}
float Unit::flyHeight () const {return Jass::GetUnitFlyHeight(handleId_);}
float Unit::acquireRangeDefault () const {return Jass::GetUnitDefaultAcquireRange(handleId_);}
float Unit::turnSpeedDefault () const {return Jass::GetUnitDefaultTurnSpeed(handleId_);}
float Unit::propWindowDefault () const {return Jass::GetUnitDefaultPropWindow(handleId_);}
float Unit::flyHeightDefault () const {return Jass::GetUnitDefaultFlyHeight(handleId_);}

float Unit::x () const { return Jass::GetUnitX(handleId_); }
float Unit::y () const { return Jass::GetUnitY(handleId_); }
Point Unit::position () const {	return Point (Jass::GetUnitX(handleId_), Jass::GetUnitY(handleId_)); }
float Unit::facing () const { return Jass::GetUnitFacing(handleId_); }
float Unit::moveSpeed () const { return Jass::GetUnitMoveSpeed(handleId_); }
float Unit::moveSpeedDefault () const { return Jass::GetUnitDefaultMoveSpeed(handleId_); }
float Unit::life () const{ return Jass::GetUnitState(handleId_, 0);}
float Unit::lifeMax () const{return Jass::GetUnitState(handleId_, 1);}
float Unit::mana () const{return Jass::GetUnitState(handleId_, 2);}
float Unit::manaMax () const{return Jass::GetUnitState(handleId_, 3);}
uint32_t Unit::currentOrder() const {return Jass::GetUnitCurrentOrder(handleId_);}
int Unit::owner () const {return Jass::GetPlayerId(Jass::GetOwningPlayer(handleId_));}
uint32_t Unit::typeId () const { return Jass::GetUnitTypeId(handleId_); }
const char* Unit::typeIdChar () const { return IntegerIdToChar(typeId()); }
uint32_t Unit::race () const { return Jass::GetUnitRace(handleId_); }
int Unit::foodUsed () const {return Jass::GetUnitFoodUsed(handleId_);}
int Unit::foodMade () const {return Jass::GetUnitFoodMade(handleId_);}
int Unit::abilityLevel (uint32_t id) const {return Jass::GetUnitAbilityLevel(handleId_, id);}

bool Unit::isSelectedLocal(bool subgroupOnly) const{
	UnitGroup *g = GroupUnitsOfPlayerSelected(PlayerLocal(), subgroupOnly);
	bool rv = g->has((Unit *)this);
	GroupDestroy(g);
	return rv;
}

bool Unit::isInvulnerable() const{
	if (this){
		war3::CUnit *u_obj = UnitGetObject(handleId_);
		if (u_obj){
			return (((u_obj->stateFlag) >> 3) & 1) != 0;
		}
	}
	return false;
}

void Unit::cargoUnitGet(UnitGroup *group) const{
	group->clear();
	war3::CAbilityCargoHold *abil = 0;
	war3::CUnit *lpUnit = UnitGetObject(handleId_);
	Unit *u = NULL;
	if (lpUnit) { 
		abil = (war3::CAbilityCargoHold *)AbilityObjGet(lpUnit, 'Abun');
		if (!abil) abil = (war3::CAbilityCargoHold *)AbilityObjGet(lpUnit, 'Aenc');
		//if (!abil) abil = (war3::CAbilityCargoHold *)AbilityObjGet(lpUnit, 'Sch2');
		if (!abil) abil = (war3::CAbilityCargoHold *)AbilityObjGet(lpUnit, 'Sch3');
		if (!abil) abil = (war3::CAbilityCargoHold *)AbilityObjGet(lpUnit, 'Sch4');
		if (!abil) abil = (war3::CAbilityCargoHold *)AbilityObjGet(lpUnit, 'Sch5');

		if (abil) {
			uint32_t count = abil->cargoSpaceUsed;
			for (uint32_t i = 0; i < count; i++){
				u = GetUnit(ObjectToHandle(CUnitFromHash(&(abil->cargoObjectHash[i].hash))));
				if (u) { group->add(u); }
			}
		}
	}
}

bool Unit::framepointGet(FramePoint* fp) const {
	bool rv = false;
	war3::CUnit *u = UnitGetObject(handleId_);
	if (u)
		rv = GetUnitFramePoint(u, fp) > 0;
	return rv;
}

bool Unit::isEnemy (int playerSlot) const {
	return Jass::IsUnitEnemy(handleId_, Jass::Player(playerSlot));
}

bool Unit::isAlly (int playerSlot) const {
	return Jass::IsUnitAlly(handleId_, Jass::Player(playerSlot));
}

bool Unit::isEnemyToLocalPlayer () const {
	return isEnemy(PlayerLocal());
}

bool Unit::isAllyToLocalPlayer () const {
	return isAlly(PlayerLocal());
}

float Unit::distanceToUnit	(Unit *otherUnit) const{
	return position().distanceTo(otherUnit->position());
}

float Unit::angleToUnit (Unit *otherUnit) const{
	return position().angleTo(otherUnit->position());
}

float Unit::direction () const {
	war3::CUnit *lpUnit = UnitGetObject(handleId_);
	if (lpUnit){
		void *someStateObj = ObjectFromHash(&lpUnit->hash_unk16C);
		if (someStateObj){
			return ObjectFieldGet<float>(someStateObj, 0x8C);
		}
	}
	return 0;
}

float Unit::regenSpeedLife () const {
	war3::CUnit *lpUnit;
	if (lpUnit = UnitGetObject(handleId_)){
		void *someStateObj = ObjectFromHash(&lpUnit->hash_unkA0);
		if (someStateObj){
			return ObjectFieldGet<float>(someStateObj, 0x7C); //TODO: 继续研究
		}
	}
	return 0;
}

float Unit::defense () const {
	war3::CUnit *lpUnit = UnitGetObject(handleId_);
	return lpUnit ? lpUnit->defense : 0;
}

uint32_t Unit::defenseType () const{
	war3::CUnit *lpUnit = UnitGetObject(handleId_);
	return lpUnit ? lpUnit->defenseType : 0;
}

DnDAtkDist Unit::attack (int weapon) const {
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk) {
		uint32_t dmgplus = 0, buffs = 0, dice = 0, sides = 0;
		switch(weapon){
		case 0:
			dmgplus = abilAtk->dmgPlus_weap0;
			buffs = abilAtk->buffs_weap0;
			dice = abilAtk->dice_weap0;
			sides = abilAtk->sides_weap0;
			break;
		case 1:
			dmgplus = abilAtk->dmgPlus_weap1;
			buffs = abilAtk->buffs_weap1;
			dice = abilAtk->dice_weap1;
			sides = abilAtk->sides_weap1;
			break;
		default:	return DnDAtkDist();	break;
		}
		return DnDAtkDist((float)(dmgplus + buffs), Dice(sides), dice);
	}
	return DnDAtkDist();
}

DnDAtkDist Unit::attackExpected (int weapon) const {
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk) {
		uint32_t dmgplus = 0, buffs = 0, dice = 0, sides = 0;
		switch(weapon){
		case 0:
			dmgplus = abilAtk->dmgPlus_weap0;
			buffs = abilAtk->buffs_weap0;
			dice = abilAtk->dice_weap0;
			sides = abilAtk->sides_weap0;
			break;
		case 1:
			dmgplus = abilAtk->dmgPlus_weap1;
			buffs = abilAtk->buffs_weap1;
			dice = abilAtk->dice_weap1;
			sides = abilAtk->sides_weap1;
			break;
		default:	return DnDAtkDist();	break;
		}
		return DnDAtkDist((float)(dmgplus + buffs + ((1+sides)/2) * dice));
	}
	return DnDAtkDist();
}

uint32_t Unit::attackType (int weapon) const{
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk) {	return weapon ? abilAtk->atkType_weap1 : abilAtk->atkType_weap0; 	}
	return 0;
}

uint32_t Unit::weaponType (int weapon) const{
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk) { return weapon ? abilAtk->weapTp_weap1 : abilAtk->weapTp_weap0; }
	return 0;
}

float Unit::cooldown (int weapon) const {
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk && abilAtk->factor.value) {
		return weapon ? (abilAtk->cool_weap1.value / abilAtk->factor.value) : (abilAtk->cool_weap0.value / abilAtk->factor.value);
	}
	return 0;
}

float Unit::cooldownRemain () const {
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk) {	return AgentTimerRemainingTimeGet(&abilAtk->timer_cool);	}
	return 0;
}

float Unit::damagePoint (int weapon) const{
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk && abilAtk->factor.value) {
		return weapon ? (abilAtk->dmgPt_weap1.value / abilAtk->factor.value) : (abilAtk->dmgPt_weap0.value / abilAtk->factor.value);
	}
	return 0;
}

float Unit::damagePointRemain () const {
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk) {	return AgentTimerRemainingTimeGet(&abilAtk->timer_dmgPt);	}
	return 0;
}

float Unit::backSwing (int weapon) const{
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk && abilAtk->factor.value) {
		return weapon ? (abilAtk->backSw_weap1.value / abilAtk->factor.value) : (abilAtk->backSw_weap0.value / abilAtk->factor.value);
	}
	return 0;
}

float Unit::backSwingRemain () const {
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk) {	return AgentTimerRemainingTimeGet(&abilAtk->timer_backSw);	}
	return 0;
}

float Unit::abilityCooldownRemain (uint32_t abilityId) const {
	war3::CAbility *abil = 0;
	war3::CUnit *lpUnit = UnitGetObject(handleId_);
	if (lpUnit) { 
		abil = (war3::CAbility *)AbilityObjGet (lpUnit, abilityId);
		//if (abil && (abil->flag2 & 0x200)) //判断技能是否在CD中
		//	return AgentTimerRemainingTimeGet(&((war3::CAbilitySpell*)abil)->timer_cooldown);
		return ((Ability *)abil)->cooldownRemain();
	}
	return 0;
}

float Unit::range (int weapon) const{
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk && abilAtk->factor.value) {
		return weapon ? abilAtk->range_weap1.value : abilAtk->range_weap0.value;
	}
	return 0;
}

float Unit::missileSpeed (int weapon) const{
	return UnitTypeMissileSpeedGet(typeId(), weapon);
}

float Unit::priority () const{
	return UnitSelectionPrioGet(UnitGetObject(handleId_));
}

static std::map<int, float> UnitTypeRadiusMap;//储存单位碰撞体积的map
float	Unit::radius () const{
	int id = typeId();
	if (UnitTypeRadiusMap.count(id)>0) return UnitTypeRadiusMap.find(id)->second;
	else {
		float hi = 300.f, lo = 0, mid;
		for (int i = 0; i < 15; i++)
		{
			if ((hi-lo)<0.4f)break;
			mid = (lo+hi)/2;
			if (Jass::IsUnitInRangeXY(handleId_, x()+mid, y(), 0)) lo=mid;
			else hi=mid;
		}
		mid = floor(mid+0.5f); //round to int
		UnitTypeRadiusMap[id] = mid;
		return mid;
	}
	return 0;
}

bool Unit::hasItemType(uint32_t id) const{//TODO 优化
	if (!Jass::IsUnitIllusion(this->handleId())) {
		for (int i = 0; i < 5; i++){
			item it = Jass::UnitItemInSlot(this->handleId(), i);
			if (it && Jass::GetItemTypeId(it)==id) return true;
		}
	}
	return false;
}

static char *DamageBonusString[7] = {
	"DamageBonusNormal",//废弃占位
	"DamageBonusNormal",
	"DamageBonusPierce",
	"DamageBonusSiege",
	"DamageBonusMagic",
	"DamageBonusChaos",
	"DamageBonusHero"
};
static uint32_t AttackTypeEtherealBonusIndex[7] = {0, 0, 1, 2, 3, 4, 6};
static float DefenseArmor;
static bool MagicImmunesResistDamage;
float	damageBonusFactorByType (uint32_t atkType, const Unit *target) {
	float rv;
	if (	MagicImmunesResistDamage//处理魔免
		&&	atkType == Jass::ATTACK_TYPE_MAGIC
		&&	target->testFlag(UnitFilter::MAGIC_IMMUNE)	){
		return 0;
	}

	if ( target->abilityLevel('ABnP') > 0 && target->testFlag(UnitFilter::STRUCTURE) ){	rv = 1.f;}//处理建造中建筑
	else {	rv = GameDataProfileGetFloat("Misc", DamageBonusString[atkType], target->defenseType());}

	if (target->testFlag(UnitFilter::ETHEREAL)) {//处理虚无
		rv *= GameDataProfileGetFloat("Misc", "EtherealDamageBonus", AttackTypeEtherealBonusIndex[atkType]);
	}
	return rv;
}

float	Unit::damageBonusFactor (int weapon, Unit *target) const{
	return damageBonusFactorByType(attackType(weapon), target);
}

float	Unit::damageFactor (int weapon, Unit *target) const{
	float rv = damageBonusFactor(weapon, target);
	if (rv > 0) {
		if (!( target->abilityLevel('ABnP') > 0 && target->testFlag(UnitFilter::STRUCTURE))){
			float defense = target->defense();
			rv *= (defense > 0) ? (1 / (1+defense*DefenseArmor)) : (2 - pow((1-DefenseArmor), -defense));
		}
		//MUSTDO 暂时处理dota环境下特例，以后要改用地图数据库
		if (target->filterMatch(
			UnitFilter(
				UnitFilter::ENEMY,
				UnitFilter::HERO | UnitFilter::MECHANICAL | UnitFilter::STRUCTURE | UnitFilter::FLYING,
				PlayerLocal()
			)
		)){
			if (this->hasItemType('I0HR')) rv *= 1.32f;
			else if (this->hasItemType('I0HP')) rv *= 1.12f;
		}
	}
	return rv;
}

float Unit::damageFactorAsTarget(uint32_t attacktype) const {
	float rv = damageBonusFactorByType(attacktype, this);
	if (rv > 0) {
		float def = 0;
		if (!( abilityLevel('ABnP') > 0 && testFlag(UnitFilter::STRUCTURE))){
			def = defense();
		}
		rv *= (def > 0) ? (1 / (1+def*DefenseArmor)) : (2 - pow((1-DefenseArmor), -def));
	}
	return rv;
}

DnDAtkDist Unit::damage (int weapon, Unit *target) const {
	DnDAtkDist rv = attack(weapon);
	rv *= damageFactor(weapon, target);
	return rv;
}

DnDAtkDist Unit::damageExpected (int weapon, Unit *target) const {
	DnDAtkDist rv = attackExpected(weapon);
	rv *= damageFactor(weapon, target);
	return rv;
}

Unit *Unit::acquiredTarget () const {
	war3::CAbilityAttack *abilAtk = AttackAbilityObjGet(handleId_);
	if (abilAtk) {
		return GetUnit(ObjectToHandle(CUnitFromHash(&(abilAtk->hashAcquired))));
	}
	return NULL;
}

float Unit::turnTime (float angleRadian) const {
	float turnSpd = turnSpeed();
	if (turnSpd)
	{
		if (angleRadian < 0.2f) //tolerance FIXME 误差测量 0.2还是0.3
			return 0.015f;
		else
			return 0.03f * ceil(angleRadian / turnSpd);
	}
	return 0;
}

float Unit::turnTimeToDirection	(float directionRadian) const {
	return turnTime(directionRadian - direction());
}

float Unit::turnTimeToUnit (Unit *otherUnit) const {
	return turnTime(angleToUnit(otherUnit) - (direction()));
}

float Unit::launchX() const {
	war3::CUnit *lpUnit = UnitGetObject(handleId_);
	uint32_t offset = (GetGameVersion() <= 6378) ? 0x22C/4 : 0x230/4;
	return lpUnit? 
		//0x230	Projectile launch X
		*(((float *)lpUnit)+offset)
		: 0;
}
float Unit::launchY() const {
	war3::CUnit *lpUnit = UnitGetObject(handleId_);
	uint32_t offset = (GetGameVersion() <= 6378) ? 0x230/4 : 0x234/4;
	return lpUnit? 
		//0x234	Projectile launch Y
		*(((float *)lpUnit)+offset)
		: 0;
}


float Unit::attackTime (int weapon, Unit *target, bool countDmgPt, bool faceTarget) const {
	float rv = 0;
	if(countDmgPt) rv += damagePoint(weapon);
	float missileSpd = missileSpeed(weapon);
	uint32_t wpTp = weaponType(weapon);

	if (	missileSpd > 0
		&&	Jass::IsUnitType(handleId_, Jass::UNIT_TYPE_RANGED_ATTACKER)
		&&	wpTp != WEAPON_TYPE_NORMAL
		&&	wpTp != WEAPON_TYPE_INSTANT
	){
		float dist = position().offsetFacing(
			faceTarget? angleToUnit(target) : direction(), 
			launchX(), launchY()).distanceTo(target->position());
		if (dist > 0) {
			rv += dist / missileSpd;
		}
	}
	return rv;
}

void Unit::sendAction (
	uint32_t	actionId,
	ActionType	actionType,
	uint32_t	actionFlag,
	Item		*usingItem,
	Point		targetPoint,
	Unit		*targetUnit,
	bool		flagReduceAPM,
	bool		sendAsProgramm
){
	UnitGroup g;
	g.add(this);
	g.sendAction(actionId, actionType, actionFlag, usingItem, targetPoint, targetUnit, NULL, flagReduceAPM, sendAsProgramm);
}

void Unit::sendActionDropItem (
	uint32_t	actionFlag,
	Point		targetPoint,
	Unit		*targetUnit,
	item		dropItemHandle,
	bool		flagReduceAPM,
	bool		sendAsProgramm
){
	UnitGroup g;
	g.add(this);
	g.sendActionDropItem(actionFlag, targetPoint, targetUnit, dropItemHandle, flagReduceAPM, sendAsProgramm);
}

bool Unit::typeMatch (
	uint32_t reqField,
	uint32_t excludeField
	) const 
{
	for (uint32_t field = 0; field <= 26; ++field){
		if (reqField & (1 << field)){
			if (!Jass::IsUnitType(handleId_, field)) return false;
		}
		if (excludeField & (1 << field)){
			if (Jass::IsUnitType(handleId_, field)) return false;
		}
	}
	return true;
}

uint32_t Unit::typeFlag () const{
	war3::CUnit *u = UnitGetObject(handleId_);
	//unitTypeFlag;		//0x248
	uint32_t offset = (GetGameVersion() <= 6378) ? 0x244/4 : 0x248/4;
	return u? 
		*(((uint32_t *)u)+offset)
		: 0;

	//return u ? u->unitTypeFlag : NULL;//FIXME UnitGetObject有可能返回NULL!
}

bool Unit::filterMatch (
	UnitFilter filter
) const
{
	if (!UnitGetObject(handleId_)) return false;
	uint64_t reqField = filter.requireFieldsGet();
	uint64_t excludeField = filter.excludeFieldsGet();
	int toPlayerId = filter.toPlayerIdGet();
	#define PROC(val, val2) \
	if (reqField		& (UnitFilter::val)){ if (!Jass::IsUnitType(handleId_, Jass::val2)) return false; }\
	if (excludeField	& (UnitFilter::val)){ if (Jass::IsUnitType(handleId_, Jass::val2)) return false; }\

	//0 ~ 11
	uint32_t unitTypeFlag = typeFlag();

	for (uint64_t field = 0; field <= 11; ++field){
		if (reqField & ((uint64_t)1 << field)){
			if (!(unitTypeFlag & ((uint64_t)1 << field))) return false;
		}
		if (excludeField & ((uint64_t)1 << field)){
			if (unitTypeFlag & ((uint64_t)1 << field)) return false;
		}
	}

	PROC(HERO, UNIT_TYPE_HERO)
	PROC(DEAD, UNIT_TYPE_DEAD)
	PROC(STRUCTURE, UNIT_TYPE_STRUCTURE)
	PROC(FLYING, UNIT_TYPE_FLYING)
	PROC(GROUND, UNIT_TYPE_GROUND)
	PROC(ATTACKS_FLYING, UNIT_TYPE_ATTACKS_FLYING)
	PROC(ATTACKS_GROUND, UNIT_TYPE_ATTACKS_GROUND)
	PROC(MELEE_ATTACKER, UNIT_TYPE_MELEE_ATTACKER)
	PROC(RANGED_ATTACKER, UNIT_TYPE_RANGED_ATTACKER)
	PROC(STUNNED, UNIT_TYPE_STUNNED)
	PROC(PLAGUED, UNIT_TYPE_PLAGUED)
	PROC(SNARED, UNIT_TYPE_SNARED)
	PROC(POISONED, UNIT_TYPE_POISONED)
	PROC(POLYMORPHED, UNIT_TYPE_POLYMORPHED)
	PROC(SLEEPING, UNIT_TYPE_SLEEPING)
	PROC(RESISTANT, UNIT_TYPE_RESISTANT)
	PROC(ETHEREAL, UNIT_TYPE_ETHEREAL)
	PROC(MAGIC_IMMUNE, UNIT_TYPE_MAGIC_IMMUNE)

	if (reqField		& (UnitFilter::ILLUSION)){ if (!Jass::IsUnitIllusion(handleId_)) return false; }
	if (excludeField	& (UnitFilter::ILLUSION)){ if (Jass::IsUnitIllusion(handleId_)) return false; }

	if (reqField		& (UnitFilter::PAUSED)){ if (!Jass::IsUnitPaused(handleId_)) return false; }
	if (excludeField	& (UnitFilter::PAUSED)){ if (Jass::IsUnitPaused(handleId_)) return false; }

	if (reqField		& (UnitFilter::HIDDEN)){ if (!Jass::IsUnitHidden(handleId_)) return false; }
	if (excludeField	& (UnitFilter::HIDDEN)){ if (Jass::IsUnitHidden(handleId_)) return false; }

	if (reqField		& (UnitFilter::LOADED)){ if (!Jass::IsUnitLoaded(handleId_)) return false; }
	if (excludeField	& (UnitFilter::LOADED)){ if (Jass::IsUnitLoaded(handleId_)) return false; }

	if (reqField		& (UnitFilter::UNDER_CONSTRUCTION)){ if (Jass::GetUnitAbilityLevel(handleId_, 'ABnP')<=0) return false; }
	if (excludeField	& (UnitFilter::UNDER_CONSTRUCTION)){ if (Jass::GetUnitAbilityLevel(handleId_, 'ABnP')>0) return false; }

	if (reqField		& (UnitFilter::UNDER_QUEUE))
	{
		war3::CAbilityQueue *abil;
		if ( NULL != ( abil = (war3::CAbilityQueue *)AbilityById('Aque') ) )
		{
			bool hasQueue = ( abil->queueItemType[0] != 0 && abil->queueItemType[0] != 0xFFFFFFFF );
			if (!hasQueue) return false;
		}
	}
	if (excludeField	& (UnitFilter::UNDER_QUEUE))
	{ 
		war3::CAbilityQueue *abil;
		if ( NULL != ( abil = (war3::CAbilityQueue *)AbilityById('Aque') ) )
		{
			bool hasQueue = ( abil->queueItemType[0] != 0 && abil->queueItemType[0] != 0xFFFFFFFF );
			if (hasQueue) return false;
		}
	}

	if (reqField		& (UnitFilter::UNDER_UPGRADE)){ if (Jass::GetUnitAbilityLevel(handleId_, 'AUnP')<=0) return false; }
	if (excludeField	& (UnitFilter::UNDER_UPGRADE)){ if (Jass::GetUnitAbilityLevel(handleId_, 'AUnP')>0) return false; }

	if (reqField		& (UnitFilter::INVULNERABLE)){if (!isInvulnerable()) return false;}
	if (excludeField	& (UnitFilter::INVULNERABLE)){if (isInvulnerable()) return false;}

	if (toPlayerId != PLAYER_ANY) {
		player p = Jass::Player(toPlayerId);

		if (reqField		& (UnitFilter::DETECTED)){ if (!Jass::IsUnitDetected(handleId_, p)) return false; }
		if (excludeField	& (UnitFilter::DETECTED)){ if (Jass::IsUnitDetected(handleId_, p)) return false; }

		if (reqField		& (UnitFilter::FOGGED)){ if (!Jass::IsUnitFogged(handleId_, p)) return false; }
		if (excludeField	& (UnitFilter::FOGGED)){ if (Jass::IsUnitFogged(handleId_, p)) return false; }

		if (reqField		& (UnitFilter::MASKED)){ if (!Jass::IsUnitMasked(handleId_, p)) return false; }
		if (excludeField	& (UnitFilter::MASKED)){ if (Jass::IsUnitMasked(handleId_, p)) return false; }

		if (reqField		& (UnitFilter::INVISIBLE)){ if (!Jass::IsUnitInvisible(handleId_, p)) return false; }
		if (excludeField	& (UnitFilter::INVISIBLE)){ if (Jass::IsUnitInvisible(handleId_, p)) return false; }

		if (reqField		& (UnitFilter::VISIBLE)){ if (!Jass::IsUnitVisible(handleId_, p)) return false; }
		if (excludeField	& (UnitFilter::VISIBLE)){ if (Jass::IsUnitVisible(handleId_, p)) return false; }

		if (reqField		& (UnitFilter::ALLY)){ if (!Jass::IsUnitAlly(handleId_, p)) return false; }
		if (excludeField	& (UnitFilter::ALLY)){ if (Jass::IsUnitAlly(handleId_, p)) return false; }

		if (reqField		& (UnitFilter::ENEMY)){ if (!Jass::IsUnitEnemy(handleId_, p)) return false; }
		if (excludeField	& (UnitFilter::ENEMY)){ if (Jass::IsUnitEnemy(handleId_, p)) return false; }

		if (reqField		& (UnitFilter::SELECTED)){ if (!Jass::IsUnitSelected(handleId_, p)) return false; }
		if (excludeField	& (UnitFilter::SELECTED)){ if (Jass::IsUnitSelected(handleId_, p)) return false; }

		if (reqField		& (UnitFilter::CONTROLLABLE)){ 
			if (!PlayerFilterMatch(Jass::GetPlayerId(Jass::GetOwningPlayer(handleId_)),	PlayerFilter(PlayerFilter::ALLIANCE_SHARED_CONTROL,NULL,toPlayerId))){	return false;	}
		}
		if (excludeField	& (UnitFilter::CONTROLLABLE)){ 
			if (PlayerFilterMatch(Jass::GetPlayerId(Jass::GetOwningPlayer(handleId_)),	PlayerFilter(PlayerFilter::ALLIANCE_SHARED_CONTROL,NULL,toPlayerId))){	return false;	}
		}

		if (reqField		& (UnitFilter::FULLCONTROLLABLE)){ 
			if (!PlayerFilterMatch(Jass::GetPlayerId(Jass::GetOwningPlayer(handleId_)),	PlayerFilter(PlayerFilter::ALLIANCE_SHARED_ADVANCED_CONTROL,NULL,toPlayerId))){	return false;	}
		}
		if (excludeField	& (UnitFilter::FULLCONTROLLABLE)){ 
			if (PlayerFilterMatch(Jass::GetPlayerId(Jass::GetOwningPlayer(handleId_)),	PlayerFilter(PlayerFilter::ALLIANCE_SHARED_ADVANCED_CONTROL,NULL,toPlayerId))){	return false;	}
		}


	}

	return true;
}

bool Unit::testFlag (uint64_t inFilterFlag, int inPlayerId) const {
	return filterMatch(UnitFilter(inFilterFlag, NULL, inPlayerId));
}

void * Unit::heroButton (){
	return HeroGetButton(UnitGetObject(handleId_));
}

Ability * Unit::AbilityListHead() const
{
	war3::CUnit *u = UnitGetObject(handleId_);
	uint32_t offset = (GetGameVersion() <= 6378) ? 0x1D8/4 : 0x1DC/4;
	return u? 
		GetAbility(AgentFromHash((war3::HashGroup*)((((uint32_t *)u)+offset))))
		: 0;
	//return u ? GetAbility(AgentFromHash(&(u->abilityHash))) : NULL;
}

int Unit::level( bool hero ) const
{
	return hero ? (uint32_t)Jass::GetHeroLevel(handleId_) : (uint32_t)Jass::GetUnitLevel(handleId_);
}

Unit* Unit::currentTargetUnit() const
{
	war3::CUnit *u = UnitGetObject(handleId_);
	uint32_t *u_addr = (uint32_t*)u;
	void *ObjGet = Offset(TRIGGER_CALL_1);
	if ( ( *(u_addr + 0x1A0/4) & *(u_addr + 0x19C/4) ) != 0xFFFFFFFF )
	{
		uint32_t *OrderTarg = aero::generic_this_call<uint32_t *>(ObjGet, (u_addr + 0x19C/4) );
		if (OrderTarg)
		{
			war3::CUnit *targetCUnit = CUnitFromHash((war3::HashGroup *)(OrderTarg + 0x58/4));
			if (targetCUnit)
			{
				return GetUnit(ObjectToHandle(targetCUnit));
			}
		}
	}
	return NULL;
}

Point Unit::currentTargetPoint() const
{
	war3::CUnit *u = UnitGetObject(handleId_);
	uint32_t *u_addr = (uint32_t*)u;
	void *ObjGet = Offset(TRIGGER_CALL_1);
	uint32_t someHash = *(u_addr + 0x1A0/4) & *(u_addr + 0x19C/4);
	if ( someHash != 0xFFFFFFFF )
	{
		uint32_t *OrderTarg = aero::generic_this_call<uint32_t *>(ObjGet, (u_addr + 0x19C/4));
		if (OrderTarg)
		{
			war3::CUnit *targetCUnit = CUnitFromHash((war3::HashGroup *)(OrderTarg + 0x58/4));
			Unit *targetUnit = NULL;
			if (targetCUnit)
			{
				targetUnit = GetUnit(ObjectToHandle(targetCUnit));
			}

			if (targetUnit)
			{
				return targetUnit->position();
			}
			else
			{
				float x = *(float *)(OrderTarg + 0x48/4);
				float y = *(float *)(OrderTarg + 0x50/4);

				return Point(x, y);
			}
		}
	}
	return POINT_NONE;
}

Ability * Unit::AbilityByHotkey(uint32_t key, bool includeItem) const
{
	Ability *abil = AbilityListHead();
	while (abil)
	{
		if ( includeItem || !(abil->flag() & 0x20) )
		{
			if (abil->hotkey() == key)
			{
				return abil;
			}
		}
		abil = abil->nextNode();
	}

	return NULL;
}

Ability * Unit::AbilityById(uint32_t typeId) const
{
	war3::CUnit *lpUnit = UnitGetObject(handleId_);
	if (lpUnit) 
	{ 
		return (Ability *)(AbilityObjGet(lpUnit, typeId));
	}
	return NULL;
}

float Unit::constructionPercent() const
{
	/*CUnit -> ABnP -> CPoReal ->

	abil'ABnP' + 0x78: floatmini buildtime
	abil'ABnP' + 0x84: hashgroup hashPoReal

	thiscall 6F497460(&someval)

	thiscall 6F477180(&rv, &someval)

	rv is time left*/
	war3::CAbilityBuildInProgress *abil = (war3::CAbilityBuildInProgress *)AbilityById('ABnP');
	if ( abil )
	{
		float total = abil->buildTimeTotal.value;
		if ( total > 0)
		{
			void *pPoReal = ObjectFromHash( &abil->hashPoReal );
			if ( pPoReal )
			{
				void *CPoRealFunc1 = Offset(CPOREAL_FUNC1);
				void *CPoRealFunc2 = Offset(CPOREAL_FUNC2);
				float someVal, rv;
				aero::generic_this_call<float *>(CPoRealFunc1, pPoReal, &someVal);
				aero::generic_this_call<float *>(CPoRealFunc2, pPoReal, &rv, &someVal);

				return 1 - (rv / total);
			}
		}
	}
	return 1;
}

float Unit::queuePercent() const
{
	war3::CAbilityQueue *abil = (war3::CAbilityQueue *)AbilityById('Aque');
	if ( abil )
	{
		float total = abil->queueTimeTotal.value;
		if ( total > 0)
		{
			void *pPoReal = ObjectFromHash( &abil->hashPoReal );
			if ( pPoReal )
			{
				void *CPoRealFunc1 = Offset(CPOREAL_FUNC1);
				void *CPoRealFunc2 = Offset(CPOREAL_FUNC2);
				float someVal, rv;
				aero::generic_this_call<float *>(CPoRealFunc1, pPoReal, &someVal);
				aero::generic_this_call<float *>(CPoRealFunc2, pPoReal, &rv, &someVal);
				return 1 - (rv / abil->queueTimeTotal.value);
			}
		}
	}
	return 1;
}

std::uint32_t Unit::queueType() const
{
	war3::CAbilityQueue *abil = (war3::CAbilityQueue *)AbilityById('Aque');
	if ( abil )
	{
		uint32_t typeId = abil->queueItemType[0];
		if (typeId != 0 && typeId != 0xFFFFFFFF)
		{
			return typeId;
		}
	}
	return NULL;
}

float Unit::upgradePercent() const
{
	war3::CAbilityUpgradeInProgress *abil = (war3::CAbilityUpgradeInProgress *)AbilityById('AUnP');
	if ( abil )
	{
		float total = abil->buildTimeTotal.value;
		if ( total > 0)
		{
			void *pPoReal = ObjectFromHash( &abil->hashPoReal );
			if ( pPoReal )
			{
				void *CPoRealFunc1 = Offset(CPOREAL_FUNC1);
				void *CPoRealFunc2 = Offset(CPOREAL_FUNC2);
				float someVal, rv;
				aero::generic_this_call<float *>(CPoRealFunc1, pPoReal, &someVal);
				aero::generic_this_call<float *>(CPoRealFunc2, pPoReal, &rv, &someVal);
				return 1 - (rv / abil->buildTimeTotal.value);
			}
		}
	}
	return 1;
}

std::uint32_t Unit::upgradeType() const
{
	war3::CAbilityUpgradeInProgress *abil = (war3::CAbilityUpgradeInProgress *)AbilityById('AUnP');
	if ( abil )
	{
		uint32_t typeId = abil->upgradeTypeId;
		if (typeId != 0 && typeId != 0xFFFFFFFF)
		{
			return typeId;
		}
	}
	return NULL;
}

int Unit::costGold() const
{
	war3::UnitDataNode* n = GetUnitDataNode(typeId());
	if ( n != NULL ) 
	{
		return n->goldCost;
	}
	return 0;
}

int Unit::costLumber() const
{
	war3::UnitDataNode* n = GetUnitDataNode(typeId());
	if ( n != NULL ) 
	{
		return n->woodCost;
	}
	return 0;
}

int Unit::timeBuild() const
{
	war3::UnitDataNode* n = GetUnitDataNode(typeId());
	if ( n != NULL ) 
	{
		return n->buildTime;
	}
	return 0;
}


typedef std::map<unit, Unit*> UnitMapType;

UnitMapType UnitMap;

void UnitManager_Init() {

	//初始化一局游戏中的平衡性常数
	DefenseArmor = GameDataProfileGetFloat("Misc", "DefenseArmor", 0);
	MagicImmunesResistDamage = GameDataProfileGetInt("Misc", "MagicImmunesResistDamage", 0) >= 1;
}

void UnitManager_Cleanup(){ 
	for (UnitMapType::iterator iter = UnitMap.begin(); iter != UnitMap.end(); ++iter) {
		delete iter->second;
	}
	UnitMap.clear();
	UnitTypeRadiusMap.clear();
}

Unit* GetUnit(uint32_t handle) {
	if (!handle) return NULL;
	Unit* rv = NULL;
	if (UnitMap.count(handle) == 0)
	{
		//验证是否单位
		war3::CUnit *u_obj = UnitGetObject(handle);
		if (u_obj)
		{
			if (AgentTypeIdGet((war3::CAgent *)u_obj) == '+w3u')
			{
				rv = UnitMap[handle] = new Unit(handle);
			}
		}
	}
	else
	{
		rv = UnitMap[handle];
	}
	return rv;
}



int UnitTypeFoodUsed (uint32_t unitTypeId){	return Jass::GetFoodUsed(unitTypeId);}
int UnitTypeFoodMade (uint32_t unitTypeId){	return Jass::GetFoodMade(unitTypeId);}