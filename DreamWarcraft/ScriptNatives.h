#include "stdafx.h"
#ifndef SCRIPT_NATIVES_H_INCLUDED_
#define SCRIPT_NATIVES_H_INCLUDED_

#include <lua.hpp>

namespace ScriptNatives {
	extern const struct luaL_reg reg[];

	//General
	int DebugPrint(lua_State *L);
	int ScreenPrint(lua_State *L);
	int ScreenClear(lua_State *L);
	int Wait(lua_State *L);
	int GameTime(lua_State *L);
	int GetHandleId(lua_State *L);
	int Handle(lua_State *L);
	int S2ObjectId(lua_State *L);
	int ObjectId2S(lua_State *L);
	int ProfileGetInt(lua_State *L);

	//Event
	int AddEventFunction(lua_State *L);
	int GetEventKey(lua_State *L);
	int GetEventCtrlKeyStatus(lua_State *L);
	int GetEventShiftKeyStatus(lua_State *L);
	int GetEventTimer(lua_State *L);

	//Unit
	int GroupUnitAll(lua_State *L);
	int GroupUnitsOfType(lua_State *L);
	int GroupUnitsOfTypeId(lua_State *L);
	int GroupUnitsOfPlayerSelected(lua_State *L);
	int GroupUnitsOfPlayer(lua_State *L);
	int GroupUnitsInRange(lua_State *L);
	int GroupSize(lua_State *L);
	int ForGroup(lua_State *L);
	int FilterGroup(lua_State *L);
	int GroupHasUnit(lua_State *L);

	//Timer
	int CreateTimer(lua_State *L);
	int StartTimer(lua_State *L);
	int PauseTimer(lua_State *L);
	int DestoryTimer(lua_State *L);
	int TimerGetElapsed(lua_State *L);
	int TimerGetRemaining(lua_State *L);
	int TimerGetTimeout(lua_State *L);
}

#endif