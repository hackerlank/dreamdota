#include "stdafx.h"

#include "Foundation.h"

#include <VMP.h>
#include <process.h>
#include <new>
#include <time.h>
#include <stdlib.h>
#include "Tools.h"
#include "Offsets.h"
#include "Jass.h"
#include "Hook.h"
#include "Storm.h"
#include "MPQ.h"
#include "Input.h"
#include "War3Window.h"
#include "TextTagManager.h"
#include "ObjectHookManager.h"
#include "RefreshManager.h"
#include "WindowResizer.h"
#include "../DreamAuth2/StringManager.h"
#include "HideModule.h"
#include "Version.h"
#include "AuthConnection.h"
#include "Language.h"
#include "../DreamAuth2/RSA.h"
#include "../DreamAuth2/InlineUtils.h"
#include "../DreamAuth2/SharedMemory.h"
#include "../DreamProtect/main.h"
#include "SystemTools.h"
#include "Game.h"

HMODULE ModuleGame;		//Game.dll 模块
HMODULE ModuleStorm;		//Storm.dll 模块
HMODULE ModuleDream;		//自身模块
static DWORD VersionGame;	//Game.dll版本
static bool Inited = false;			//标记是否需要清理
uint8_t PUBLIC_ENCRYPTED_KEY[RSA_SIZE] = {0};
char RootPath[MAX_PATH];

HMODULE GetSelfModule() {	return ModuleDream; }
int GetGameVersion() { return (int)VersionGame; }
char ModulePath[MAX_PATH];
char ModuleFileName[MAX_PATH];
char PathBuffer[MAX_PATH];
const char* GetSelfPath() {return ModulePath;}
const char* GetSelfFileName() {return ModuleFileName;}
const char* GetPath(const char* filename) {sprintf_s(PathBuffer, MAX_PATH, "%s\\%s", ModulePath, filename);return PathBuffer;}

static CRITICAL_SECTION g_at_cs;
typedef std::set<DWORD> active_threads_set_t;
static active_threads_set_t g_active_threads;

BOOL CALLBACK EnumWar3WindowsProc(
  __in  HWND hwnd,
  __in  LPARAM lParam
) {
	DWORD pid = 0;
	if (GetWindowThreadProcessId(hwnd, &pid) && pid == GetCurrentProcessId()) {
		ShowWindow(hwnd, SW_SHOWMINIMIZED);
		MessageBox(NULL, GetACP() == 936 ? "您必须重启魔兽争霸才可以使用DreamDota。" : "Please restart Warcraft III to use DreamDota.", "DreamDota", MB_ICONINFORMATION | MB_SYSTEMMODAL);
		return FALSE;
	}
	return TRUE;
}

void newhandler() {
	MessageBox(NULL, "Bad alloc!", NULL, MB_ICONERROR);
	ExitProcess(-1);
}

void ThreadDreamProtect(void* arg) {
	while(!GetModuleHandle("11xp.dll"))
		Sleep(200);
	//InitDreamProtect();
}

__declspec(noinline) void Init (HMODULE selfModule) {
	std::set_new_handler(newhandler);

	VMProtectBeginVirtualization("Foundation Init");

#ifdef _DEBUG
	OutputDebug("DreamWarcraft Init... Base: 0x%X", selfModule);
#endif
	char buffer[MAX_PATH];
	GetModuleFileNameA(selfModule,(LPCH)buffer, MAX_PATH);
	char *filename = strrchr(buffer,'\\');
	strcpy_s(ModuleFileName, MAX_PATH, filename + 1);

	*filename = '\0';
	strcpy_s(ModulePath, MAX_PATH, buffer);

	ModuleDream	= selfModule;
	ModuleStorm = GetModuleHandleA("Storm.dll");
	ModuleGame =  GetModuleHandleA("Game.dll");

	if (ModuleGame != NULL) {
		//_beginthread(ThreadDreamProtect, NULL, NULL);

		VersionGame = VersionGet("Game.dll", 4);

		//随机种子
		srand ( (unsigned int)(time(NULL)) );

		jmp_buf env;

		int val = setjmp(env);
		if (val == 0) {
			Storm::Init(ModuleStorm);

			void *sm = SharedMemory::Open();
#ifdef _SERVERSTRING
			if (!sm)
				longjmp(env, -1);
#endif
			if (!AuthConnection_Init(sm)) {
				longjmp(env, 1);
			}

			if (!Language_Init(ModuleDream)) {
				longjmp(env, 2);
			}

			if (!Offset_Init(VersionGame, reinterpret_cast<DWORD>(ModuleGame))) {
				longjmp(env, 3);
			}
			
			if (*(war3::CGameWar3 **)(Offset(GLOBAL_WARCRAFT_GAME))) {
				EnumWindows(EnumWar3WindowsProc, NULL);
				return; //如果已经在游戏内，不装载。（会导致功能不正常）
			}

			//初始化		
			ObjectHookManager_Init(); 
			MPQ_Init();
			Jass_Init(VersionGame, reinterpret_cast<DWORD>(ModuleGame));
			Tools_Init();
			Hook_Init();
			War3Window_Init();
			Input_Init();
			TextTagManager_Init();
			RefreshManager_Init();
			WindowResizer::Init();

			InitializeCriticalSection(&g_at_cs);

			OutputDebugString("DreamDota initialization completed.");
			Inited = true;
		} else {
			char buff[100];
			sprintf_s(buff, sizeof(buff), "Initialization faild, code %i.", val);
			OutputDebugString(buff);
		}

#ifdef _VMP
		HideModule(selfModule);
#endif
	}
	VMProtectEnd();
}

__declspec(noinline) void Cleanup() {
	VMProtectBeginVirtualization("Foundation Cleanup");

#ifdef _DEBUG
	OutputDebug("DreamWarcraft Cleanup...");
#endif
	if (Inited) { 
		DeleteCriticalSection(&g_at_cs);

		WindowResizer::Cleanup();
		RefreshManager_Cleanup();
		War3Window_Cleanup();
		Jass_Cleanup();
		ObjectHookManager_Cleanup();

		Language_Cleanup();
		AuthConnection_Cleanup();
	}
	Storm::Cleanup();

	VMProtectEnd();
}

extern "C" uint32_t GetRevision() {
	return VERSION.revision;
}