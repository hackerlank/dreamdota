extern "C" {
#include "../../lualib/lua.h"
#include "../../lualib/lualib.h"
#include "../../lualib/lauxlib.h"
}

#ifdef _DEBUG
	#pragma comment(lib, "../Debug/lualib.lib")
#else
	#pragma comment(lib, "../Release/lualib.lib")
#endif