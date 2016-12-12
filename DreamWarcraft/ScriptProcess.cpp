#include "stdafx.h"
#include "ScriptProcess.h"
#include "GameTime.h"
#include "MPQ.h"
#include "Storm.h"

#include "L_Unit.h"

ScriptProcess::ScriptProcess() {
	this->error_handler_ = NULL;

	lua_State* L = this->master_ = lua_open();
		
	LUA_LOADLIB(L, "", luaopen_base);
	LUA_LOADLIB(L, LUA_LOADLIBNAME, luaopen_package);
	LUA_LOADLIB(L, LUA_DBLIBNAME, luaopen_debug);
	LUA_LOADLIB(L, LUA_TABLIBNAME, luaopen_table);
	LUA_LOADLIB(L, LUA_MATHLIBNAME, luaopen_math);
}

ScriptProcess::ScriptProcess(const char * require_path) {
	this->error_handler_ = NULL;

	lua_State* L = this->master_ = lua_open();
		
	LUA_LOADLIB(L, "", luaopen_base);
	LUA_LOADLIB(L, LUA_LOADLIBNAME, luaopen_package);
	LUA_LOADLIB(L, LUA_DBLIBNAME, luaopen_debug);
	LUA_LOADLIB(L, LUA_TABLIBNAME, luaopen_table);
	LUA_LOADLIB(L, LUA_MATHLIBNAME, luaopen_math);

	//设置require路径
	lua_getglobal(L, "package");
	lua_pushstring(L, require_path);
	lua_setfield(L, -2, "path");
	lua_pop(L, 1);

	LuaExport<L_Unit>::Register(L);
}

ScriptProcess::~ScriptProcess() {
	lua_close(this->master_);
}

void ScriptProcess::RegisterNatives(const struct luaL_reg* natives, const char* libname) {
	if (!libname)
		lua_getglobal(this->master_, "_G");
	luaL_register(this->master_, libname, natives);
}

//函数在栈顶，运行完出栈
void ScriptProcess::ThreadExec() {
	if (!lua_isfunction(this->master_, -1)) {
		lua_pushstring(this->master_, "Start thread failed: not function");
		this->ProcessError(this->master_);
		return;
	}
	//function的引用
	int func_ref = luaL_ref(this->master_, LUA_REGISTRYINDEX);
	lua_State* L  = lua_newthread(this->master_);
	//保存一个新线程的引用
	int ref_thread = luaL_ref(this->master_, LUA_REGISTRYINDEX);
	lua_rawgeti(L, LUA_REGISTRYINDEX, func_ref);
	lua_unref(this->master_, func_ref);

	int result = lua_resume(L, 0);
	//如果直接执行完毕就直接清理
	if (result == 0) {
		luaL_unref(L, LUA_REGISTRYINDEX, ref_thread);
	} else if (result == LUA_YIELD) {
		this->thread_ref_map_[L] = ref_thread;
	}
	else {
		this->ProcessError(L);
	}
}

bool ScriptProcess::LoadScript(const char* filename, bool sandbox) {
	lua_State* L = this->master_;
	if (luaL_loadfile(this->master_, filename) != 0) {
		this->ProcessError(L);
		return false;
	}

	this->ThreadExec();

	return true;
}

//Callback在栈顶, 加入完毕以后清出栈
void ScriptProcess::AddCallback(lua_State* L, uint32_t type) {
	int ref_callback = luaL_ref(L, LUA_REGISTRYINDEX);
	this->callback_map_[type].push_back(ref_callback);
}

//Callback在栈顶, 执行完毕以后清出栈
void ScriptProcess::RemoveCallback(lua_State* L, uint32_t type) {
	if (this->callback_map_.count(type) > 0) {
		if (this->callback_map_[type].size() > 0) {
			ScriptCallbackRefListType* list = &(this->callback_map_[type]);
			bool found = false;
			for (ScriptCallbackRefListType::iterator iter = list->begin(); !found && iter != list->end();) {
				lua_rawgeti(L, LUA_REGISTRYINDEX, *iter);
				if (1 == lua_rawequal(L, -1, -2)) {
					luaL_unref(L, LUA_REGISTRYINDEX, *iter);
					found = true;
					list->erase(iter);
				} else 
					++iter;
				lua_pop(L, 1);
			}
		}
	}
	lua_pop(L, 1);
}

void ScriptProcess::SleepThread(lua_State* thread_state, uint32_t length) {
	uint32_t resume_time = TimeRaw() + length;
	this->yield_thread_map_[resume_time].push_back(thread_state);
}

void ScriptProcess::Tick(uint32_t time) {
	if (this->yield_thread_map_.size() == 0)
		return;

	lua_State* L;
	ScriptYieldThreadListMapType::iterator iter;
	ScriptYieldThreadListType::iterator iter_list;
	ScriptYieldThreadListType* list;
	for (iter = this->yield_thread_map_.begin(); iter != this->yield_thread_map_.end(); ) {
		if (iter->first > time)
			break;

		list = &(iter->second);
		for (iter_list = iter->second.begin(); iter_list != iter->second.end();) {
			L = *iter_list;
			int result = lua_resume(L, 0);
			//如果直接执行完毕就直接清理
			if (result == 0) {
				luaL_unref(L, LUA_REGISTRYINDEX, this->thread_ref_map_[L]);
				this->thread_ref_map_.erase(L);
			} else if (result == LUA_YIELD) {
				//如果继续Sleep,那么只删除当前的记录，继续保持thread的引用
			}
			else {
				this->ProcessError(L);
			}
			//无论如何都要删除当前的记录，因为时间必定不一样
			list->erase(iter_list++);
		}
		//如果所有的线程都执行完了，就在map中删除当前时间点的记录
		if (list->size() == 0) {
			this->yield_thread_map_.erase(iter++);
		} else
			iter++;
	}
}

void ScriptProcess::ExecuteCallbacks(uint32_t type) {
	if (this->callback_map_.count(type) == 0) 
		return;

	ScriptCallbackRefListType* list = &(this->callback_map_[type]);
	ScriptCallbackRefListType::iterator iter;

	for(iter = list->begin(); iter != list->end();) {
		int ref = *(iter++);
		lua_rawgeti(this->master_, LUA_REGISTRYINDEX, ref);
		this->ThreadExec();
	}
}

void ScriptProcess::ProcessError(lua_State* L) {
	if (lua_isstring(L, -1) && NULL != this->error_handler_) {
		this->error_handler_(lua_tostring(L, -1));
	}
	lua_pop(L, 1);
	
	lua_getglobal(L, "debug");
	lua_pushstring(L, "traceback");
	lua_rawget(L, -2);
	lua_call(L, 0, 1);
	OutputDebugString(lua_tostring(L, -1));
	lua_pop(L, 1);
}