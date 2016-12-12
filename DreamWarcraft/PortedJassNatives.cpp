#include "stdafx.h"
#include "PortedJassNatives.h"
#include "Jass.h"

using namespace Jass;

#define LUA_PUSHDWORD(L, v) \
	lua_pushlightuserdata(L, reinterpret_cast<void*>(v))
#define LUA_TODWORD(L, index) \
	reinterpret_cast<DWORD>(lua_touserdata(L, index))

namespace PortedJassNatives {
#include "JassLuaNativesData.h.inc"
#include "JassLuaNatives.impl.inc"
}