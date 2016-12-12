#include "stdafx.h"
#include "ScriptTimer.h"
#include "DreamScript.h"
#include <lua.hpp>

void ScriptTimerHandler(Timer* tm) {
	ScriptTimer* current = reinterpret_cast<ScriptTimer*>(tm);
	lua_State* L = GetScriptProcess()->L();
	lua_rawgeti(L, LUA_REGISTRYINDEX, current->callbackRef());
	GetScriptProcess()->ThreadExec();
}