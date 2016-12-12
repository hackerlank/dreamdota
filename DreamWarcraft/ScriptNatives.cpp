#include "stdafx.h"
#include "ScriptNatives.h"
#include "Jass.h"
#include "GameTime.h"
#include "ScriptTimer.h"
#include "Tools.h"
#include "Event.h"
#include "Game.h"
#include "DreamScript.h"
#include "Profile.h"
#include "UnitGroup.h"

#define LUA_PUSHDWORD(L, v) \
	lua_pushlightuserdata(L, reinterpret_cast<void*>(v))
#define LUA_TODWORD(L, index) \
	reinterpret_cast<DWORD>(lua_touserdata(L, index))

namespace ScriptNatives {
	const struct luaL_reg reg [] = {
		{"ScreenPrint", ScreenPrint},
		{"ScreenClear", ScreenClear},
		{"DebugPrint", DebugPrint},
		{"Wait", Wait},
		{"GameTime", GameTime},
		{"GetHandleId", GetHandleId},
		{"Handle", Handle},
		{"S2ObjectId", S2ObjectId},
		{"ObjectId2S", ObjectId2S},
		{"ProfileGetInt", ProfileGetInt},
		
		{"AddEventFunction", AddEventFunction},
		{"GetEventKey", GetEventKey},
		{"GetEventCtrlKeyStatus", GetEventCtrlKeyStatus},
		{"GetEventShiftKeyStatus", GetEventShiftKeyStatus},
		{"GetEventTimer", GetEventTimer},

		{"GroupUnitAll", GroupUnitAll},
		{"GroupUnitsOfTypeId", GroupUnitsOfTypeId},
		{"GroupUnitsOfPlayerSelected", GroupUnitsOfPlayerSelected},
		{"GroupUnitsOfPlayer", GroupUnitsOfPlayer},
		{"GroupUnitsInRange", GroupUnitsInRange},
		{"GroupSize", GroupSize},
		{"ForGroup", ForGroup},
		{"FilterGroup", FilterGroup},
		{"GroupHasUnit", GroupHasUnit},
		
		{"CreateTimer", CreateTimer},
		{"StartTimer", StartTimer},
		{"PauseTimer", PauseTimer},
		{"DestoryTimer", DestoryTimer},
		{"TimerGetElapsed", TimerGetElapsed},
		{"TimerGetRemaining", TimerGetRemaining},
		{"TimerGetTimeout", TimerGetTimeout},

		{NULL, NULL}
	};

	int ProfileGetInt(lua_State *L) {
		if (lua_gettop(L) >= 3 && lua_isstring(L, 1) && lua_isstring(L, 2) && lua_isnumber(L, 3)) {
			const char* app = lua_tostring(L, 1);
			const char* key = lua_tostring(L, 2);
			if (app && key) {
				lua_pushinteger(L, ::ProfileGetInt(app, key, lua_tointeger(L, 3)));
				return 1;
			} else 
				return 0;
		} else {
			luaL_argcheck(L, lua_isstring(L, 1), 1, "'string' expected");
			luaL_argcheck(L, lua_isstring(L, 2), 2, "'string' expected");
			luaL_argcheck(L, lua_isstring(L, 3), 3, "'number' expected");
		}
		return 0;
	}

	//void ScreenPrint(string str, number duration = 10, number x = 0, number y = 0);
	int ScreenPrint(lua_State *L) {
		int top = lua_gettop(L);
		if (top == 0 || lua_tostring(L, 1) == NULL)
			return 0;
		lua_Number d;
		d = (top > 1 && lua_isnumber(L, 2)) ? lua_tonumber(L, 2) : 10.0;
		OutputScreen(static_cast<float>(d), lua_tostring(L, 1));
		return 0;
	}

	//void ScreenClear()
	int ScreenClear(lua_State *L) {
		Jass::ClearTextMessages();
		return 0;
	}

	//void DebugPrint(string str)
	int DebugPrint(lua_State *L) {
		if (lua_gettop(L) == 0 || lua_tostring(L, 1) == NULL)
			return 0;
		OutputDebugString(lua_tostring(L, 1));
		return 0;
	}

	//void Wait(number duration)
	int Wait(lua_State *L) {
		if (lua_gettop(L) == 0)
			return 0;
		if (!lua_isnumber(L, 1)) {
			luaL_argcheck(L, lua_isnumber(L, 1), 1, "'number' expected");
			return 0;
		}

		double ms = lua_tonumber(L, 1) * 1000.0;
		uint32_t time = static_cast<uint32_t>(ms < 4294967295.0 ? ms : 4294967295);
		
		GetScriptProcess()->SleepThread(L, time < 0 ? 0 : time);
		return lua_yield(L, 0);
	}

	//void AddEventFunction(number eventid, function callback)
	int AddEventFunction(lua_State *L) {
		if (lua_gettop(L) == 2 && lua_islightuserdata(L, 1) && lua_isfunction(L, 2)) {
			GetScriptProcess()->AddCallback(L, LUA_TODWORD(L, 1));
		} else {
			luaL_argcheck(L, lua_islightuserdata(L, 1), 1, "'handle' expected");
			luaL_argcheck(L, lua_isfunction(L, 2), 2, "'function' expected");
		}
		return 0;
	}

	//number GetGameTime()
	int GameTime(lua_State *L) {
		bool raw = lua_gettop(L) > 0 && lua_toboolean(L, 1);
		if (raw)
			lua_pushinteger(L, (int)TimeRaw());
		else
			lua_pushnumber(L, static_cast<lua_Number>(static_cast<lua_Number>(Time())));
		return 1;
	}

	//number GetHandleId()
	int GetHandleId(lua_State *L) {
		if (lua_gettop(L) == 1 && lua_islightuserdata(L, 1)) {
			lua_pushnumber(L, static_cast<lua_Number>(LUA_TODWORD(L, 1)));
			return 1;
		} else {
			luaL_argcheck(L, lua_islightuserdata(L, 1), 1, "'handle' expected");
		}
		return 0;
	}

	int Handle(lua_State *L) {
		if (lua_gettop(L) == 1 && lua_isnumber(L, 1)) {
			LUA_PUSHDWORD(L, lua_tointeger(L, 1));
			return 1;
		} else {
			luaL_argcheck(L, lua_isnumber(L, 1), 1, "'integer' expected");
		}
		return 0;
	}

	//number S2ID(string id)
	int S2ObjectId(lua_State *L) {
		if (lua_gettop(L) > 0 && lua_isstring(L, 1)) {
			const char* str = lua_tostring(L, 1);
			uint32_t r = str[0];
			for (uint32_t i = 1; i < strlen(str); i++) {
				r *= 256;
				r += str[i];
			}
			lua_pushinteger(L, r);
			return 1;
		} else {
			luaL_argcheck(L, lua_isstring(L, 1), 1, "'string' expected");
		}
		return 0;
	}

	int ObjectId2S(lua_State *L) {
		if (lua_gettop(L) > 0 && lua_isnumber(L, 1)) {
			uint32_t id = static_cast<uint32_t>(lua_tonumber(L, 1));
			lua_pushstring(L, IntegerIdToChar(id));
			return 1;
		} else {
			luaL_argcheck(L, lua_isnumber(L, 1), 1, "'number' expected");
		}
		return 0;
	}

	int GetEventKey(lua_State *L) {
		const Event* evt = MainDispatcher()->currentEvent();
		if (!evt)
			return 0;
		if (evt->id() != EVENT_KEY_UP && evt->id() != EVENT_KEY_DOWN)
			return 0;
		else
			lua_pushinteger(L, evt->data<KeyboardEventData>()->code);
		return 1;
	}

	int GetEventCtrlKeyStatus(lua_State *L) {
		const Event* evt = MainDispatcher()->currentEvent();
		if (!evt)
			return 0;
		if (evt->id() != EVENT_KEY_UP && evt->id() != EVENT_KEY_DOWN)
			return 0;
		else
			lua_pushboolean(L, evt->data<KeyboardEventData>()->ctrl);
		return 1;
	}

	int GetEventShiftKeyStatus(lua_State *L) {
		const Event* evt = MainDispatcher()->currentEvent();
		if (!evt)
			return 0;
		if (evt->id() != EVENT_KEY_UP && evt->id() != EVENT_KEY_DOWN)
			return 0;
		else
			lua_pushboolean(L, evt->data<KeyboardEventData>()->shift);
		return 1;
	}

	int GetEventTimer(lua_State *L) {
		ScriptTimer* timer = reinterpret_cast<ScriptTimer*>(GetCurrentTimer());
		if (!timer)
			return 0;
		else
			lua_rawgeti(L, LUA_REGISTRYINDEX, timer->userdataRef());
		return 1;
	}

	namespace impl {
#define LUA_NEWUNITGROUP(L) \
	lua_newtable(L); \
	luaL_newmetatable(L, "unitgroup"); \
	lua_setmetatable(L, -2)

		static UnitGroup GroupAll;

		UnitGroup* GetUnitGroupAll() {
			static uint32_t last_grab_time = 0;
			if (last_grab_time != TimeRaw()) {
				last_grab_time = TimeRaw();
				GroupAll.clear();
				GroupAddUnitAll(&GroupAll);
			}
			return &GroupAll;
		}
	}

	int GroupUnitAll(lua_State *L) {
		UnitGroup* g = impl::GetUnitGroupAll();
		LUA_NEWUNITGROUP(L);
		int i = 0;
		for (UnitGroup::iterator iter = g->begin(); iter != g->end(); ++i, ++iter) {
			LUA_PUSHDWORD(L, (*iter)->handleId());
			lua_rawseti(L, -2, i + 1);
		}
		return 1;
	}

	int GroupUnitsOfType(lua_State *L) {
		if (lua_gettop(L) == 1 && lua_islightuserdata(L, 1)) {
			uint32_t type = LUA_TODWORD(L, 1);
			UnitGroup* g = impl::GetUnitGroupAll();
			LUA_NEWUNITGROUP(L);
			int count = 1;
			for (UnitGroup::iterator iter = g->begin(); iter != g->end(); ++iter) {
				Unit* u = *iter;
				if (Jass::IsUnitType(u->handleId(), type)) {
					LUA_PUSHDWORD(L, u->handleId());
					lua_rawseti(L, -2, count);
					++count;
				}
			}
			return 1;
		} else 
			luaL_argcheck(L, lua_islightuserdata(L, 1), 1, "'handle' expected");
		return 0;
	}

	int GroupUnitsOfTypeId(lua_State *L) {
		if (lua_gettop(L) == 1 && lua_isnumber(L, 1)) {		
			int type_id = lua_tointeger(L, 1);
			UnitGroup* g = impl::GetUnitGroupAll();
			LUA_NEWUNITGROUP(L);
			int count = 1;
			for (UnitGroup::iterator iter = g->begin(); iter != g->end(); ++iter) {
				Unit* u = *iter;
				if (u->typeId() == type_id) {
					LUA_PUSHDWORD(L, u->handleId());
					lua_rawseti(L, -2, count);
					++count;
				}
			}
			return 1;
		} else
			luaL_argcheck(L, lua_isnumber(L, 1), 1, "'integer' expected");
		return 0;
	}
	
	int GroupUnitsOfPlayer(lua_State *L) {
		if (lua_gettop(L) == 1 && lua_isnumber(L, 1)) {
			int player_id = lua_tointeger(L, 1);
			UnitGroup* g = impl::GetUnitGroupAll();
			LUA_NEWUNITGROUP(L);
			int count = 1;
			for (UnitGroup::iterator iter = g->begin(); iter != g->end(); ++iter) {
				Unit* u = *iter;
				if (u->owner() == player_id) {
					LUA_PUSHDWORD(L, u->handleId());
					lua_rawseti(L, -2, count);
					++count;
				}
			}
			return 1;
		} else
			luaL_argcheck(L, lua_isnumber(L, 1), 1, "'integer' expected");
		return 0;
	}

	int GroupUnitsInRange(lua_State *L) {
		if (lua_gettop(L) == 3 && lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3)) {
			double x = lua_tonumber(L, 1);
			double y = lua_tonumber(L, 2);
			double r = lua_tonumber(L, 3);
			UnitGroup* g = impl::GetUnitGroupAll();
			LUA_NEWUNITGROUP(L);
			int count = 1;
			for (UnitGroup::iterator iter = g->begin(); iter != g->end(); ++iter) {
				Unit* u = *iter;
				if (Jass::IsUnitInRangeXY(u->handleId(), static_cast<float>(x), static_cast<float>(y), static_cast<float>(r))) {
					LUA_PUSHDWORD(L, u->handleId());
					lua_rawseti(L, -2, count);
					++count;
				}
			}
			return 1;
		} else {
			luaL_argcheck(L, lua_isnumber(L, 1), 1, "'number' expected");
			luaL_argcheck(L, lua_isnumber(L, 2), 2, "'number' expected");
			luaL_argcheck(L, lua_isnumber(L, 3), 3, "'number' expected");
		}
		return 0;
	}

	int GroupUnitsOfPlayerSelected(lua_State *L) {
		if (lua_gettop(L) == 1 && lua_isnumber(L, 1)) {
			int player_id = lua_tointeger(L, 1);
			UnitGroup g;
			GroupAddUnitsOfPlayerSelected(&g, player_id, false);
			LUA_NEWUNITGROUP(L);
			int i = 0;
			for (UnitGroup::iterator iter = g.begin(); iter != g.end(); ++i, ++iter) {
				LUA_PUSHDWORD(L, (*iter)->handleId());
				lua_rawseti(L, -2, i + 1);
			}
			return 1;
		} else {
			luaL_argcheck(L, lua_isnumber(L, 1), 1, "'integer' expected");
		}
		return 0;
	}

	int GroupSize(lua_State *L) {
		if (lua_gettop(L) == 1 && lua_istable(L, 1)) {
			lua_pushinteger(L, luaL_getn(L, 1));
			return 1;
		} else
			luaL_argcheck(L, lua_istable(L, 1), 1, "'table' expected");
		return 0;
	}

	int ForGroup(lua_State *L) {
		if (lua_gettop(L) == 2 && lua_istable(L, 1) && lua_isfunction(L, 2)) {
			for (int i = 1; i <= luaL_getn(L, 1); i++) {
				lua_pushvalue(L, 2);
				lua_rawgeti(L, 1, i);
				lua_call(L, 1, 0);
			}
			return 0;
		} else {
			luaL_argcheck(L, lua_istable(L, 1), 1, "'table' expected");
			luaL_argcheck(L, lua_isfunction(L, 2), 2, "'function' expected");
		}
		return 0;
	}

	int FilterGroup(lua_State *L) {
		if (lua_gettop(L) == 2 && lua_istable(L, 1) && lua_isfunction(L, 2)) {
			int pass_i = 1, i, n = luaL_getn(L, 1);
			for (i = 1; i <= n; ++i) {
				lua_pushvalue(L, 2);
				lua_rawgeti(L, 1, i);
				unit u = LUA_TODWORD(L, -1);
				lua_call(L, 1, 1);

				if (lua_toboolean(L, -1) > 0) {
					if (i != pass_i) {
						LUA_PUSHDWORD(L, u);
						lua_rawseti(L, 1, pass_i);
					}
					++pass_i;
				}
				lua_pop(L, 1);
			}

			for (i = pass_i; i <= n; ++i) {
				lua_pushnil(L);
				lua_rawseti(L, 1, i);
			}
			return 0;
		} else {
			luaL_argcheck(L, lua_istable(L, 1), 1, "'table' expected");
			luaL_argcheck(L, lua_isfunction(L, 2), 2, "'function' expected");
		}
		return 0;
	}

	int GroupHasUnit(lua_State *L) {
		int i;
		if (lua_gettop(L) == 2 && lua_istable(L, 1) && lua_islightuserdata(L, 2)) {
			unit target = LUA_TODWORD(L, 2);
			for (i = 1; i <= luaL_getn(L, 1); ++i) {
				lua_rawgeti(L, 1, i);
				unit u = LUA_TODWORD(L, -1);
				lua_pop(L, 1);

				if (u == target) {
					lua_pushinteger(L, i);
					return 1;
					break;
				}
			}
		} else {
			luaL_argcheck(L, lua_istable(L, 1), 1, "'table' expected");
			luaL_argcheck(L, lua_islightuserdata(L, 2), 2, "'handle' expected");
		}
		lua_pushboolean(L, 0);
		return 1;
	}

	struct TimerInfo {
		ScriptTimer* timer;
	};

	int CreateTimer(lua_State *L) {
		if (lua_gettop(L) == 3 && lua_isnumber(L, 1) && lua_isboolean(L, 2) && lua_isfunction(L, 3)) {
			double ims = lua_tonumber(L, 1) * 1000.0;
			uint32_t interval = ims < 4294967295.0 ? static_cast<uint32_t>(ims) : 4294967295;
			bool p = lua_toboolean(L, 2) > 0 ? true : false;
			lua_pushvalue(L, 3);
			int ref_c = luaL_ref(L, LUA_REGISTRYINDEX);

			TimerInfo* info = (TimerInfo*)lua_newuserdata(L, sizeof(TimerInfo));
			luaL_newmetatable(L, "timer");
			lua_setmetatable(L, -2);
			lua_pushvalue(L, -1);
			int ref_u = luaL_ref(L, LUA_REGISTRYINDEX);

			info->timer = new ScriptTimer(L, ref_u, ref_c, interval, p);
			return 1;
		} else {
			luaL_argcheck(L, lua_isnumber(L, 1), 1, "'number' expected");
			luaL_argcheck(L, lua_isboolean(L, 2), 2, "'boolean' expected");
			luaL_argcheck(L, lua_isfunction(L, 3), 3, "'function' expected");
		}
		return 0;
	}
	
	int StartTimer(lua_State *L) {
		TimerInfo* tm = (TimerInfo*)luaL_checkudata(L, 1, "timer");
		if (lua_gettop(L) == 1 && NULL != tm ) {
			TimerInfo* tm = (TimerInfo*)lua_touserdata(L, 1);
			tm->timer->start();
			return 0;
		} else
			luaL_argcheck(L, luaL_checkudata(L, 1, "timer"), 1, "'timer' expected");
		return 0;
	}

	int PauseTimer(lua_State *L) {
		TimerInfo* tm = (TimerInfo*)luaL_checkudata(L, 1, "timer");
		if (lua_gettop(L) == 1 && NULL != tm ) {
			TimerInfo* tm = (TimerInfo*)lua_touserdata(L, 1);
			tm->timer->pause();
			return 0;
		} else
			luaL_argcheck(L, luaL_checkudata(L, 1, "timer"), 1, "'timer' expected");
		return 0;
	}

	int DestoryTimer(lua_State *L) {
		TimerInfo* tm = (TimerInfo*)luaL_checkudata(L, 1, "timer");
		if (lua_gettop(L) == 1 && NULL != tm ) {
			TimerInfo* tm = (TimerInfo*)lua_touserdata(L, 1);
			tm->timer->destroy();
			return 0;
		} else
			luaL_argcheck(L, luaL_checkudata(L, 1, "timer"), 1, "'timer' expected");
		return 0;
	}

	int TimerGetElapsed(lua_State *L) {
		TimerInfo* tm = (TimerInfo*)luaL_checkudata(L, 1, "timer");
		if (lua_gettop(L) == 1 && NULL != tm ) {
			TimerInfo* tm = (TimerInfo*)lua_touserdata(L, 1);
			lua_pushnumber(L, static_cast<double>(tm->timer->elapsed()) / 1000.0);
			return 1;
		} else
			luaL_argcheck(L, luaL_checkudata(L, 1, "timer"), 1, "'timer' expected");
		return 0;
	}

	int TimerGetRemaining(lua_State *L) {
		TimerInfo* tm = (TimerInfo*)luaL_checkudata(L, 1, "timer");
		if (lua_gettop(L) == 1 && NULL != tm ) {
			TimerInfo* tm = (TimerInfo*)lua_touserdata(L, 1);
			lua_pushnumber(L, static_cast<double>(tm->timer->remaining()) / 1000.0);
			return 1;
		} else
			luaL_argcheck(L, luaL_checkudata(L, 1, "timer"), 1, "'timer' expected");
		return 0;
	}

	int TimerGetTimeout(lua_State *L) {
		TimerInfo* tm = (TimerInfo*)luaL_checkudata(L, 1, "timer");
		if (lua_gettop(L) == 1 && NULL != tm ) {
			TimerInfo* tm = (TimerInfo*)lua_touserdata(L, 1);
			lua_pushnumber(L, static_cast<double>(tm->timer->timeout()) / 1000.0);
			return 1;
		} else
			luaL_argcheck(L, luaL_checkudata(L, 1, "timer"), 1, "'timer' expected");
		return 0;
	}
}