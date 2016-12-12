#ifndef UNIT_H_
#define UNIT_H_

#include "Player.h"
#include "Point.h"
#include "Item.h"
#include "Ability.h"
#include "Stochastic.h"
#include "Jass.h"
#include "Action.h"


struct VisibleState;
struct AttackData;
struct DeathRateData;
struct FramePoint;
class UnitFilter;
class Unit;
class UnitGroup;
class DebugPanel;

class UnitFilter {
public:
	//分类属性 - 单位类型
	static const uint64_t GIANT			= (uint64_t)1 << 0;
	static const uint64_t UNDEAD		= (uint64_t)1 << 1;
	static const uint64_t SUMMONED		= (uint64_t)1 << 2;
	static const uint64_t MECHANICAL	= (uint64_t)1 << 3;
	static const uint64_t PEON			= (uint64_t)1 << 4;
	static const uint64_t SAPPER		= (uint64_t)1 << 5;
	static const uint64_t TOWNHALL		= (uint64_t)1 << 6;
	static const uint64_t ANCIENT		= (uint64_t)1 << 7;
	static const uint64_t NEUTRAL		= (uint64_t)1 << 8;
	static const uint64_t WARD			= (uint64_t)1 << 9;
	static const uint64_t STANDON		= (uint64_t)1 << 10;
	static const uint64_t TAUREN		= (uint64_t)1 << 11;

	//分类属性 - 单位
	static const uint64_t HERO				= (uint64_t)1 << 12;
	static const uint64_t DEAD				= (uint64_t)1 << 13;
	static const uint64_t STRUCTURE			= (uint64_t)1 << 14;
	static const uint64_t FLYING			= (uint64_t)1 << 15;
	static const uint64_t GROUND			= (uint64_t)1 << 16;
	static const uint64_t ATTACKS_FLYING	= (uint64_t)1 << 17;
	static const uint64_t ATTACKS_GROUND	= (uint64_t)1 << 18;
	static const uint64_t MELEE_ATTACKER	= (uint64_t)1 << 19;
	static const uint64_t RANGED_ATTACKER	= (uint64_t)1 << 20;

	//状态属性
	static const uint64_t STUNNED		= (uint64_t)1 << 21;
	static const uint64_t PLAGUED		= (uint64_t)1 << 22;
	static const uint64_t SNARED		= (uint64_t)1 << 23;
	static const uint64_t POISONED		= (uint64_t)1 << 24;
	static const uint64_t POLYMORPHED	= (uint64_t)1 << 25;
	static const uint64_t SLEEPING		= (uint64_t)1 << 26;
	static const uint64_t RESISTANT		= (uint64_t)1 << 27;
	static const uint64_t ETHEREAL		= (uint64_t)1 << 28;
	static const uint64_t MAGIC_IMMUNE	= (uint64_t)1 << 29;
	static const uint64_t ILLUSION		= (uint64_t)1 << 30;
	static const uint64_t PAUSED		= (uint64_t)1 << 31;
	static const uint64_t HIDDEN		= (uint64_t)1 << 32;
	static const uint64_t LOADED		= (uint64_t)1 << 33;
	static const uint64_t UNDER_CONSTRUCTION = (uint64_t)1 << 34;
	static const uint64_t UNDER_QUEUE	= (uint64_t)1 << 35;
	static const uint64_t UNDER_UPGRADE	= (uint64_t)1 << 36;
	static const uint64_t INVULNERABLE	= (uint64_t)1 << 37;

	//状态属性 - 相对玩家
	static const uint64_t DETECTED		= (uint64_t)1 << 38;
	static const uint64_t FOGGED		= (uint64_t)1 << 39;
	static const uint64_t MASKED		= (uint64_t)1 << 40;
	static const uint64_t INVISIBLE		= (uint64_t)1 << 41;
	static const uint64_t VISIBLE		= (uint64_t)1 << 42;
	static const uint64_t ALLY			= (uint64_t)1 << 43;
	static const uint64_t ENEMY			= (uint64_t)1 << 44;
	static const uint64_t SELECTED		= (uint64_t)1 << 45;
	static const uint64_t CONTROLLABLE	= (uint64_t)1 << 46;
	static const uint64_t FULLCONTROLLABLE	= (uint64_t)1 << 47;

	//TODO 增加其它属性例如 HAS_MANA, IDLE, CAN_SLEEP, MOVABLE, CONTROLGROUPED, CHANNELING

	UnitFilter (
		uint64_t requireFields, //require1 | require2 | ... | requireN
		uint64_t excludeFields, //exclude1 | exclude2 | ... | excludeN
		int toWhichPlayerId = PLAYER_ANY
	);

	UnitFilter ();
	uint64_t requireFieldsGet() { return require; }
	uint64_t excludeFieldsGet() { return exclude; }
	int toPlayerIdGet() { return player; }
	bool operator==(int rhs);

private:
	uint64_t require;
	uint64_t exclude;
	int player;
};


struct VisibleState {
	bool lastVisible;
	Point lastVisiblePoint;
	VisibleState();
};


class Unit {
	uint32_t handleId_;
	DISALLOW_COPY_AND_ASSIGN(Unit);
public:
	Unit (uint32_t handleId);
	~Unit ();

	uint32_t	handleId() const;//获取Jass handle id
	const char *name() const;
	const char *debugName(bool showHandleId = true, bool showCUnit = false) const;

	float		acquireRange () const;
	float		acquireRangeDefault () const;
	float		turnSpeed () const;
	float		turnSpeedDefault () const;
	float		propWindow () const;
	float		propWindowDefault () const;
	float		flyHeight () const;
	float		flyHeightDefault () const;
	float		x () const;
	float		y () const;
	Point		position () const;		//坐标
	float		facing () const;		//模型朝向, 注意这并不是单位真正朝向. 返回角度
	float		moveSpeed () const;
	float		moveSpeedDefault () const;
	float		life () const;
	float		lifeMax () const;
	float		mana () const;
	float		manaMax () const;
	int			level ( bool hero ) const;
	bool		isInvulnerable () const;
	uint32_t	currentOrder() const;
	Unit*		currentTargetUnit() const;
	Point		currentTargetPoint() const;

	int			owner () const;			//从属玩家序号, 从0起始
	uint32_t	typeId () const;		//获取单位类型ID, 例如'hfoo'
	const char* typeIdChar () const;	//获取单位类型ID, 例如"hfoo"
	uint32_t	race () const;			//参考Jass::RACE_<X>
	int			foodUsed () const;
	int			foodMade () const;

	int			costGold () const;
	int			costLumber () const;
	int			timeBuild () const;

	bool		isEnemy (int playerSlot) const;
	bool		isEnemyToLocalPlayer () const;
	bool		isAlly (int playerSlot) const;
	bool		isAllyToLocalPlayer () const;
	int			abilityLevel (uint32_t id) const;
	bool		hasItemType(uint32_t id) const;
	bool		isSelectedLocal(bool subgroupOnly = false) const;

	void		cargoUnitGet(UnitGroup *group) const;

	bool		framepointGet(FramePoint* fp) const;

	//对应jass IsUnitType，见common.j UNIT_TYPE_<*>常量
	bool typeMatch (
		uint32_t reqField,
		uint32_t excludeField
	) const;

	//当单位对每个需求属性都符合，并且对每个排除属性都不符合时返回真。
	bool filterMatch (
		UnitFilter	filter
	) const;

	//测试单个属性是否符合
	bool testFlag (
		uint64_t	inFilterFlag, 
		int			inPlayerId = PLAYER_ANY
	) const;

	uint32_t typeFlag() const;

	float		distanceToUnit	(Unit *otherUnit) const; //到另一个单位的平面距离
	float		angleToUnit		(Unit *otherUnit) const; //到另一个单位的方向弧度
	float		turnTime			(float angleRadian) const;		//转过方向弧度所需的时间
	float		turnTimeToDirection	(float directionRadian) const;	//从当前方向转向方向弧度所需的时间
	float		turnTimeToUnit		(Unit *otherUnit) const;		//从当前方向转向单位所需的时间

	enum DefenseTypeEnum {
		DEFENSE_TYPE_SMALL,			//轻型
		DEFENSE_TYPE_MEDIUM,		//中型
		DEFENSE_TYPE_LARGE,			//大型
		DEFENSE_TYPE_FORTIFIED,		//城防
		DEFENSE_TYPE_NORMAL,//无用
		DEFENSE_TYPE_HERO,			//英雄
		DEFENSE_TYPE_DIVINE,		//神圣
		DEFENSE_TYPE_UNARMORED		//无护甲
	};

	float		radius			( ) const; //半径, 用于射程计算, 对应编辑器collision
	float		direction		( ) const; //单位真实方向弧度
	float		priority		( ) const; //选择优先权, 影响选择排列与英雄顺序
	float		regenSpeedLife	( ) const;
	float		defense			( ) const;
	uint32_t	defenseType		( ) const;

	enum AttackTypeEnum {
		ATTACK_TYPE_UNKNOWN,		//无用
		ATTACK_TYPE_NORMAL,			//普通
		ATTACK_TYPE_PIERCE,			//穿刺
		ATTACK_TYPE_SIEGE,			//攻城
		ATTACK_TYPE_MAGIC,			//魔法
		ATTACK_TYPE_CHAOS,			//混乱
		ATTACK_TYPE_HERO			//英雄
	};
	enum WeaponTypeEnum {
		WEAPON_TYPE_NONE,			//无用
		WEAPON_TYPE_NORMAL,			//普通
		WEAPON_TYPE_MISSILE,		//箭矢
		WEAPON_TYPE_ARTILLERY,		//火炮
		WEAPON_TYPE_INSTANT,		//立即
		WEAPON_TYPE_MISSILE_SPLASH,	//箭矢 - 溅射
		WEAPON_TYPE_MISSILE_BOUNCE,	//箭矢 - 弹射
		WEAPON_TYPE_MISSILE_LINE,	//箭矢 - 直线
		WEAPON_TYPE_ARTILLERY_LINE	//火炮 - 直线
	};

	int			weaponTo			(Unit *target) const {return 0;}//TODO

	DnDAtkDist	attack				(int weapon) const;
	DnDAtkDist	attackExpected		(int weapon) const;
	uint32_t	attackType			(int weapon) const;
	uint32_t	weaponType			(int weapon) const;
	Unit*		acquiredTarget		( ) const; //当前想要攻击的目标单位, 可用于判断自动攻击及攻击miss时的真正目标

	float		launchX				( ) const;
	float		launchY				( ) const;

	float		range				(int weapon) const;
	float		missileSpeed		(int weapon) const;
	float		cooldown			(int weapon) const;
	float		cooldownRemain		( ) const;
	float		damagePoint			(int weapon) const;
	float		damagePointRemain	( ) const;
	float		backSwing			(int weapon) const;
	float		backSwingRemain		( ) const;
	float		damageBonusFactor	(int weapon, Unit *target) const;	//攻防类型伤害比率，计入特殊状态如建造中、虚无、魔免，但不含无敌
	//TODO 计算技能影响，例如月神祝福
	float		damageFactor		(int weapon, Unit *target) const;	//计算攻防类型、护甲值的伤害比率，含特殊情况如建造中
	float		damageFactorAsTarget(uint32_t attacktype) const;
	DnDAtkDist	damage				(int weapon, Unit *target) const;
	DnDAtkDist	damageExpected		(int weapon, Unit *target) const;
	float		attackTime			(int weapon, Unit *target, bool countDmgPt, bool faceTarget) const;	//从攻击到击中所需的前摇 + 弹道时间

	float		constructionPercent	() const;
	float		upgradePercent() const;
	uint32_t	upgradeType () const;
	float		queuePercent () const;
	uint32_t	queueType () const;

	Ability *AbilityListHead ( ) const;
	Ability *AbilityByHotkey ( uint32_t key, bool includeItem = false ) const;
	Ability *AbilityById(uint32_t typeId) const;


	float	abilityCooldownRemain (uint32_t abilityId) const;

	void sendAction (
		uint32_t	actionId,
		ActionType	actionType,
		uint32_t	actionFlag,
		Item		*usingItem,
		Point		targetPoint,
		Unit		*targetUnit,
		bool		flagReduceAPM,
		bool		sendAsProgramm = true
	);

	void sendActionDropItem (
		uint32_t	actionFlag,
		Point		targetPoint,
		Unit		*targetUnit,
		item		dropItemHandle,
		bool		flagReduceAPM,
		bool		sendAsProgramm = true
	);

	void *heroButton ();
#ifdef _DEBUG
	DebugPanel*		debugPanel;
#endif

	VisibleState	visibleState;//alert记录

	bool lasthitActive;
	Unit *lasthitCurrentTarget;
	std::map<Unit*, Function> lasthitRate; //对目标单位的补刀率曲线
};

int UnitTypeFoodUsed (uint32_t unitTypeId);
int UnitTypeFoodMade (uint32_t unitTypeId);



Unit* GetUnit(uint32_t handle);

void UnitManager_Init();
void UnitManager_Cleanup();

#endif