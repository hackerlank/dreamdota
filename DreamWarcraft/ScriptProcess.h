#include "stdafx.h"
#ifndef SCRIPT_PROCESS_H_INCLUDED_
#define SCRIPT_PROCESS_H_INCLUDED_

#include <lua.hpp>
#include <list>

typedef void (*ScriptProcessErrorHandler)(const char* msg);

#define LUA_LOADLIB(L, name, function) \
	lua_pushcfunction(L, function); \
	lua_pushstring(L, name); \
	lua_call(L, 1, 0)

//功能:
//	从脚本注册回调，输入id和function
//	从C++执行回调，输入id
//	Sleep和Resume

typedef std::list<int> ScriptCallbackRefListType;
typedef std::map<uint32_t, ScriptCallbackRefListType> ScriptCallbackMapType;
typedef std::list<lua_State*> ScriptYieldThreadListType;
typedef std::map<uint32_t, ScriptYieldThreadListType> ScriptYieldThreadListMapType;
typedef std::map<lua_State*, int> ScriptThreadRefMapType;

class ScriptProcess {
public:
	ScriptProcess();
	ScriptProcess(const char * require_path);
	~ScriptProcess();

	bool LoadScript(const char* filename, bool sandbox = false);

	void RegisterNatives(const struct luaL_reg* natives, const char* libname = NULL);

	void ThreadExec();

	void SleepThread(lua_State* thread_state, uint32_t time);
	void Tick(uint32_t time);

	void ExecuteCallbacks(uint32_t type);
	
	void AddCallback(lua_State* L, uint32_t type);
	void RemoveCallback(lua_State* L, uint32_t type);

	lua_State* L() {return this->master_;}
	void set_error_handler(ScriptProcessErrorHandler v){this->error_handler_ = v;};
private:
	void ProcessError(lua_State* L);

	lua_State* master_;
	ScriptProcessErrorHandler error_handler_;

	ScriptCallbackMapType callback_map_;
	ScriptYieldThreadListMapType yield_thread_map_;
	ScriptThreadRefMapType thread_ref_map_;

	DISALLOW_COPY_AND_ASSIGN(ScriptProcess);
};

#endif