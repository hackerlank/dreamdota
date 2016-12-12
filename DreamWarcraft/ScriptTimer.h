#include "stdafx.h"
#ifndef SCRIPT_TIMER_H_INCLUDED_
#define SCRIPT_TIMER_H_INCLUDED_
#include "Timer.h"
#include "DreamScript.h"
#include "Game.h"
#include <lua.hpp>

void ScriptTimerHandler(Timer* tm);

class ScriptTimer : public Timer {
public:
	ScriptTimer(lua_State* state, int userdata_ref, int callback_ref, uint32_t interval, bool periodic = false) : Timer(interval, ScriptTimerHandler, periodic, TimeGame, false) {
		this->callback_ref_ = callback_ref;
		this->userdata_ref_ = userdata_ref;
		this->L_ = state;
	}

	~ScriptTimer() {
		if (IsInGame()) {
			lua_State* L = GetScriptProcess()->L();
			luaL_unref(L, LUA_REGISTRYINDEX, this->callback_ref_);
			luaL_unref(L, LUA_REGISTRYINDEX, this->userdata_ref_);
		}
	}
	
	lua_State* L() {return this->L_;}
	int callbackRef() const {return this->callback_ref_;}
	int userdataRef() {return this->userdata_ref_;}
private:
	int callback_ref_;
	int userdata_ref_;
	lua_State* L_;
};

#endif