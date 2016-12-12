#include "stdafx.h"
#ifndef L_UNIT_
#define L_UNIT_

#include <lua.hpp>
#include "Unit.h"
#include "LuaExport.h"

class L_Unit : public Unit {
public:
	static const char* ClassName;
	static LuaExport<L_Unit>::MethodInfoType Methods[];
	static int T__tostring (lua_State *L) {
		return LuaExport<L_Unit>::T__tostring(L);
	}
	static int T__call (lua_State *L) {
		if (lua_gettop(L) > 1) {
			lua_remove(L, 1);
			uint32_t handle = (uint32_t)lua_touserdata(L, 1);
			L_Unit* object = (L_Unit*)GetUnit(handle);
			LuaExport<L_Unit>::push(L, object);
			return 1;
		} else 
			return 0;
	}
	static int T__gc (lua_State *L) {
#ifdef _DEBUG
		OutputDebug("%s::__gc\n", ClassName);
#endif
		return 0;
	}

	typedef int (L_Unit::*LuaPortFuncType)(lua_State*);

	//uint32_t	handleId() const;//获取Jass handle id
	DWORD_GETTER(handleId)

	//const char *name() const;
	STRING_GETTER(name)

	//const char *debugName(bool showHandleId = true, bool showCUnit = false) const;
	int L_debugName(lua_State* L) {
		int top = lua_gettop(L);
		bool showHandleId = top > 0 ? lua_toboolean(L, 1) > 0 : true;
		bool showCUnit = top > 1 ? lua_toboolean(L, 2) > 0 : false;
		lua_pushstring(L, this->debugName(showHandleId, showCUnit));
		return 1;
	}
	
	//float		acquireRange () const;
	FLOAT_GETTER(acquireRange)
	
	//float		acquireRangeDefault () const;
	FLOAT_GETTER(acquireRangeDefault)

	//float		turnSpeed () const;
	FLOAT_GETTER(turnSpeed)

	//float		turnSpeedDefault () const
	FLOAT_GETTER(turnSpeedDefault)

	//float		propWindow () const;
	FLOAT_GETTER(propWindow)

	//float		propWindowDefault () const;
	FLOAT_GETTER(propWindowDefault)
	
	//float		flyHeight () const;
	FLOAT_GETTER(flyHeight)

	//float		flyHeightDefault () const;
	FLOAT_GETTER(flyHeightDefault)

	//float		x () const;
	FLOAT_GETTER(x)

	//float		y () const;
	FLOAT_GETTER(y)

	//Point		position () const;		//坐标

	//float		facing () const;		//模型朝向, 注意这并不是单位真正朝向. 返回角度
	FLOAT_GETTER(facing)

	//float		moveSpeed () const;
	FLOAT_GETTER(moveSpeed)

	//float		moveSpeedDefault () const;
	FLOAT_GETTER(moveSpeedDefault)

	//float		life () const;
	FLOAT_GETTER(life)

	//float		lifeMax () const;
	FLOAT_GETTER(lifeMax)

	//float		mana () const;
	FLOAT_GETTER(mana)

	//float		manaMax () const;
	FLOAT_GETTER(manaMax)

	//int	level ( bool hero ) const;
	int L_level(lua_State* L) {
		int top = lua_gettop(L);
		if (top > 0) {
			lua_pushinteger(L, this->level(lua_toboolean(L, 1) > 0));
			return 1;
		} else
			return 0;
	}	

	//bool		isInvulnerable () const;
	BOOL_GETTER(isInvulnerable)

	//uint32_t	currentOrder() const;
	DWORD_GETTER(currentOrder)

	//Unit*		currentTargetUnit() const;

	//Point		currentTargetPoint() const;
				
	//int	owner () const;			//从属玩家序号, 从0起始
	INT_GETTER(owner)

	//uint32_t	typeId () const;		//获取单位类型ID, 例如'hfoo'
	DWORD_GETTER(typeId)

	//const char* typeIdChar () const;	//获取单位类型ID, 例如"hfoo"
	STRING_GETTER(typeIdChar)

	//uint32_t	race () const;			//参考Jass::RACE_<X>
	DWORD_GETTER(race)

	//int			foodUsed () const;
	INT_GETTER(foodUsed)

	//int			foodMade () const;
	INT_GETTER(foodMade)

	//int			costGold () const;
	INT_GETTER(costGold)

	//int			costLumber () const;
	INT_GETTER(costLumber)
	
	//int			timeBuild () const;
	INT_GETTER(timeBuild)

	//bool		isEnemy (int playerSlot) const;
	int L_isEnemy(lua_State* L) {
		int top = lua_gettop(L);
		if (top > 0) {
			lua_pushboolean(L, this->isEnemy(lua_tointeger(L, 1)) ? 1 : 0);
			return 1;
		} else
			return 0;
	}	

	//bool		isEnemyToLocalPlayer () const;
	BOOL_GETTER(isEnemyToLocalPlayer)

	//bool		isAlly (int playerSlot) const;
	int L_isAlly(lua_State* L) {
		int top = lua_gettop(L);
		if (top > 0) {
			lua_pushboolean(L, this->isAlly(lua_tointeger(L, 1)) ? 1 : 0);
			return 1;
		} else
			return 0;
	}	

	//bool		isAllyToLocalPlayer () const;
	BOOL_GETTER(isAllyToLocalPlayer)
	
	//int			abilityLevel (uint32_t id) const;
	int L_abilityLevel(lua_State* L) {
		int top = lua_gettop(L);
		if (top > 0) {
			lua_pushinteger(L, this->abilityLevel((uint32_t)lua_touserdata(L, 1)));
			return 1;
		} else
			return 0;
	}

	//bool		hasItemType(uint32_t id) const;
	int L_hasItemType(lua_State* L) {
		int top = lua_gettop(L);
		if (top > 0) {
			lua_pushinteger(L, this->hasItemType((uint32_t)lua_touserdata(L, 1)));
			return 1;
		} else
			return 0;
	}	

	//bool		isSelectedLocal(bool subgroupOnly = false) const;
	int L_isSelectedLocal(lua_State* L) {
		int top = lua_gettop(L);
		if (top > 0)
			lua_pushboolean(L, this->isSelectedLocal(lua_toboolean(L, 1) > 0));
		else
			lua_pushboolean(L, this->isSelectedLocal(false));
		return 1;
	}

	//void		cargoUnitGet(UnitGroup *group) const;

	//bool		framepointGet(FramePoint* fp) const;

	//...

	//float		range				(int weapon) const;
	int L_range(lua_State* L) {
		int top = lua_gettop(L);
		if (top > 0) {
			lua_pushnumber(L, this->range(lua_tointeger(L, 1)));
			return 1;
		} else
			return 0;
	}	
private:
	
};

#endif