#ifndef LUA_HELPER_H_
#define LUA_HELPER_H_

#include <lua.hpp>

inline void lh_getweaktable(lua_State* L, const char* mode) {
	lua_newtable(L);

	lua_newtable(L);
	lua_pushstring(L, "__mode");
	lua_pushstring(L, mode);
	lua_rawset(L, -3);
		
	lua_setmetatable(L, -2);
}

#endif