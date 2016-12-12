#ifndef LUA_EXPORT_H_
#define LUA_EXPORT_H_

#include "LuaHelper.h"

template <class T>
class LuaExport {
	struct UserdataType {
		T *object;
	};
	
public:
	typedef int (T::*ExportMethodType)(lua_State *L);

	struct MethodInfoType {
		const char* name;
		ExportMethodType func;
	};

	static void Register(lua_State *L) {
#ifdef _DEBUG
		int top = lua_gettop(L);
#endif

		lua_newtable(L);
		int methods = lua_gettop(L);

		luaL_newmetatable(L, T::ClassName);  
        int metatable = lua_gettop(L);  

		lua_pushstring(L, T::ClassName);
		lua_pushvalue(L, methods);
		lua_rawset(L, LUA_GLOBALSINDEX);
		
		// hide metatable from Lua getmetatable()  
		lua_pushstring(L, "__metatable");
		lua_pushvalue(L, methods);
		lua_rawset(L, methods);

        // 设置meta table的__index域  
        // 说明：__index域可以是一个函数，也可以是一个表  
        // 当它是一个函数的时候，Lua将table和缺少的域作为  
        // 参数调用这个函数；当它是一个表的时候，Lua将在这  
        // 个表中看是否有缺少的域。
		lua_pushstring(L, "__index");
		lua_pushvalue(L, methods);
		lua_rawset(L, metatable);

		lua_pushstring(L, "__tostring");
		lua_pushcfunction(L, T::T__tostring);
		lua_rawset(L, metatable);

		lua_pushstring(L, "__gc");
		lua_pushcfunction(L, T::T__gc);
		lua_rawset(L, metatable);

		lua_newtable(L);
		lua_pushstring(L, "__call");
		lua_pushcfunction(L, T::T__call);
		lua_rawset(L, -3);
		lua_setmetatable(L, methods);

		lua_pushstring(L, "__call");
		lua_pushcfunction(L, T::T__call);
		lua_rawset(L, metatable);

		for (MethodInfoType *l = T::Methods; l->name; ++l) {
			lua_pushstring(L, l->name);
			lua_pushlightuserdata(L, (void*)l);
			lua_pushcclosure(L, dispatch, 1);
			lua_rawset(L, methods);
		}

		lua_pop(L, 2);

#ifdef _DEBUG
		assert(lua_gettop(L) == top);
#endif
	}

	static int T__tostring (lua_State *L) {
		UserdataType* ud = static_cast<UserdataType*>(lua_touserdata(L, 1));
		T *obj = ud->object;
		lua_pushfstring(L, "%s: %p", T::ClassName, obj);
		return 1;
	}

	static int T__call (lua_State *L) {
		lua_remove(L, 1);
		T *obj = new T();
		push(L, obj);
		return 1;
	}

	static int T__gc (lua_State *L) {
		UserdataType *ud = static_cast<UserdataType*>(lua_touserdata(L, 1));  
		if (ud & ud->object)
			delete ud->object;
		return 0;
	}

	static T *check(lua_State *L, int n) {
		UserdataType *ud = static_cast<UserdataType*>(luaL_checkudata(L, n, T::ClassName));
		if (!ud)
			luaL_typerror(L, n, T::ClassName);
		return ud ? ud->object : NULL; 
	}

	static int push(lua_State *L, T *obj) {
		int top = lua_gettop(L);

		if (!obj) {
			lua_pushnil(L);
			return 0;
		}

		//获取metatable
		luaL_getmetatable(L, T::ClassName);
		int mt = lua_gettop(L);

		if (lua_isnil(L, -1)) {
			luaL_error(L, "%s missing metatable", T::ClassName);
			return 0;
		}

		//获取metatable.objects表
		lua_pushstring(L, "objects");
		lua_rawget(L, -2);
		int objects_t = lua_gettop(L);

		if (lua_isnil(L, -1)) {
			lua_pop(L, 1);
			lh_getweaktable(L, "kv");
			lua_pushstring(L, "objects");
			lua_pushvalue(L, -2);
			lua_rawset(L, mt);	
		}

		//查找是否已有
		lua_pushlightuserdata(L, obj);
		lua_rawget(L, objects_t);

		if (lua_isnil(L, -1)) {
			lua_pop(L, 1);
			UserdataType* ud = (UserdataType*)lua_newuserdata(L, sizeof(UserdataType));
			ud->object = obj;
			lua_pushvalue(L, -3);
			lua_setmetatable(L, -2);

			lua_pushlightuserdata(L, obj);
			lua_pushvalue(L, -2);
			lua_rawset(L, objects_t);
		}

		lua_replace(L, mt);
		lua_pop(L, 1);

#ifdef _DEBUG
		assert(lua_gettop(L) == top + 1);
#endif
		return top + 1;
	}
private:
	static int dispatch(lua_State *L) {
		T *obj = check(L, 1);
		if (obj) {
			lua_remove(L, 1);
			MethodInfoType* l = static_cast<MethodInfoType*>(lua_touserdata(L, lua_upvalueindex(1)));
			return (obj->*(l->func))(L);
		} else
			return 0;
	}
};

#define FLOAT_GETTER(name) \
	int L_##name(lua_State* L) { \
		lua_pushnumber(L, this->##name()); \
		return 1; \
	}

#define INT_GETTER(name) \
	int L_##name(lua_State* L) { \
		lua_pushinteger(L, this->##name()); \
		return 1; \
	}

#define STRING_GETTER(name) \
	int L_##name(lua_State* L) { \
		lua_pushstring(L, this->##name()); \
		return 1; \
	}

#define DWORD_GETTER(name) \
	int L_##name(lua_State* L) { \
		lua_pushlightuserdata(L, (void*)this->##name()); \
		return 1; \
	}

#define BOOL_GETTER(name) \
	int L_##name(lua_State* L) { \
		lua_pushboolean(L, this->##name() ? 1 : 0); \
		return 1; \
	}

#define LUAEXPORT_DECLARE_METHOD(Class, Name) \
	{#Name, &L_##Class##::L_##Name}

#endif