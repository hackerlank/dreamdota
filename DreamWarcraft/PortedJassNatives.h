#include "stdafx.h"
#ifndef PORTED_JASS_NATIVE_H_INCLUDED_
#define PORTED_JASS_NATIVE_H_INCLUDED_

#include <lua.hpp>
namespace PortedJassNatives {
	extern const struct luaL_reg reg[];

#include "JassLuaNatives.h.inc"

}
#endif