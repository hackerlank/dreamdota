#include "stdafx.h"
#include "DreamScript.h"
#include "ScriptProcess.h"
#include "ScriptNatives.h"
#include "PortedJassNatives.h"
#include "Tools.h"
#include "Timer.h"
#include "Game.h"
#include "Foundation.h"
#include "Event.h"
#include "Storm.h"
#include <io.h>
#include <direct.h>

static const char* REQUIRE_PATH = "./DreamDota/?.lua;./DreamDota/plugins/?.lua;./DreamDota/plugins/?/?.lua;./DreamDota/core/?.lua;./DreamDota/core/?/?.lua";
static const char* MAIN_PATH = "./DreamDota/core/dreamdota.lua";
static const char* PLUGIN_PATH = "./DreamDota/plugins/";
static const char* PLUGIN_PATTERN = "./DreamDota/plugins/*.lua";

static ScriptProcess* Process = NULL;

void onPluginError(const char* msg) {
	OutputScreen(60, "|CFFFFF799Plugin Error: |R|CFFFF0000%s|R", msg);
	//OutputDebug("Plugin Error: %s", msg);
}

ScriptProcess* GetScriptProcess() {
	return Process;
}

void EventSubscriber(const Event* evt) {
	Process->ExecuteCallbacks(evt->id());
}

void DreamScript_Init() {
	char cwd[MAX_PATH];
	if (NULL != _getcwd(cwd, sizeof(cwd)) && 0 == _chdir(RootPath)) {
		Process = new ScriptProcess(REQUIRE_PATH);

		//注册错误处理
		Process->set_error_handler(onPluginError);

		//注册函数
		Process->RegisterNatives(ScriptNatives::reg);

		//注册Jass函数
		Process->RegisterNatives(PortedJassNatives::reg, "jass");

		//加载库文件
		Process->LoadScript(MAIN_PATH);

		//装载所有插件文件
		struct _finddata_t c_file;
		int handle;
		char name_buffer[256];
		if ( (handle = _findfirst(PLUGIN_PATTERN, &c_file)) != -1L ) {
			do {
				strcpy_s(name_buffer, 255, PLUGIN_PATH);
				strcat_s(name_buffer, 255, c_file.name);
				Process->LoadScript(name_buffer);
				//debug_printf("Plugin loaded: %s\n", c_file.name);
			} while (_findnext(handle, &c_file) == 0);
			_findclose(handle);
		}
	
		Timer_AddTickCallback(DreamScript_Tick);
		MainDispatcher()->subscribe(EventSubscriber);

		_chdir(cwd);
	} else {
		onPluginError("Initialize plugin failed: Unable to change current working directory.");
	}
}

void DreamScript_Tick(uint32_t time) {
	Process->Tick(time);
}

void DreamScript_Cleanup() {
	if (Process) {
		delete Process;
		Process = NULL;
	}
}
