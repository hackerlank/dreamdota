#include "stdafx.h"
#include "Game.h"
#include "EventDispatcher.h"
#include "overdate.h"

#include "UnitGroup.h"
#include "Tools.h"
#include "Packet.h"
#include "Jass.h"
#include "JassTrigger.h"
#include "Timer.h"
#include "Hook.h"
#include "RefreshManager.h"
#include "GameEventObserver.h"
#include "MissileManager.h"
#include "Latency.h"
#include "UnitWalker.h"

#include "DebugPanel.h"
#include "Button.h"
#include "OptionMenu.h"
#include "InfoPanelRow.h"//MUSTDO
#include "IUIObject.h"
#include "StatePanel.h"
#include "GameLog.h"

//include 功能模块
#include "ModuleTest.h"
#include "DreamWar3Main.h"
#include "DreamDotaMain.h"
#include "DreamScript.h"

static EventDispatcher* Dispatcher;
void onGlobalTimerCheck(Timer *tm) {
#ifndef _FREEPLUGIN
	//VMProtectBeginVirtualization("GlobalOverdateTimer");
	//if (isOverdate()){
	//	if (RandomFloat(0, 1.f) <= 0.05f){
	//		Jass::CreateTimer();
	//		tm->destroy();
	//	}
	//}
	//VMProtectEnd();
#endif
}

typedef void (*initfunctype) ();
#define INITFUNC_ENCRYPT_KEY 0x012B70C	//这个不是地址而是密钥
#define INITFUNC_ENCRYPT_ADD 0x7FFE		//随意想出的一个数字
#define INITFUNC_ENCRYPT(a) (initfunctype)(((~((uint32_t)a))+INITFUNC_ENCRYPT_ADD)^INITFUNC_ENCRYPT_KEY)
#define INITFUNC_DECRYPT(x) (initfunctype)(~((((uint32_t)x)^INITFUNC_ENCRYPT_KEY)-INITFUNC_ENCRYPT_ADD))

static initfunctype GameInitFuncArr[8] =
{
	INITFUNC_ENCRYPT(JassTrigger_Init),
	INITFUNC_ENCRYPT(UnitManager_Init),
	INITFUNC_ENCRYPT(ItemManager_Init),
	INITFUNC_ENCRYPT(Timer_Init),
	INITFUNC_ENCRYPT(Packet_Init),
	INITFUNC_ENCRYPT(Latency_Init),
	INITFUNC_ENCRYPT(MissileManager_Init),
	INITFUNC_ENCRYPT(DebugPanel_Init),
};

Game::Game() {
	GameTime_Reset();
	//基础组件初始化
	Dispatcher = new EventDispatcher();
	GameLog_Init();
	JassTrigger_Init();
	UnitManager_Init();
	ItemManager_Init();
	Timer_Init();
	Packet_Init();
	Latency_Init();
	MissileManager_Init();
	DebugPanel_Init();
	StatePanelInit();
	UnitWalker_Init();
	UI_Init();
	OptionMenu_Init();
	InfoPanel::PullDown::Init();
	
	//功能模块初始化
#if !defined(_DREAMWAR3) && !defined(_DREAMDOTA)
	ModuleTest_Init();
#endif

VMProtectBeginVirtualization("ModuleInit");
	DreamScript_Init();
	DreamWar3_Init();
	DreamDota_Init();
	GetTimer(RandomFloat(15.f, 30.f), onGlobalTimerCheck, true)->start();
VMProtectEnd();
}

Game::~Game() {
	//功能模块清理
	DreamDota_Cleanup();
	DreamWar3_Cleanup();
	DreamScript_Cleanup();

#if !defined(_DREAMWAR3) && !defined(_DREAMDOTA)
	ModuleTest_Cleanup();
#endif

	//基础组件清理
	OptionMenu_Cleanup();//负责清理所有UI自定义复杂结构
	UI_Cleanup();
	UnitWalker_Cleanup();
	StatePanelCleanup();
	DebugPanel_Cleanup();
	MissileManager_Cleanup();
	RefreshManager_CleanupGame();
	Latency_Cleanup();
	Packet_Cleanup();
	Timer_Cleanup();
	ItemManager_Cleanup();
	UnitManager_Cleanup();
	JassTrigger_Cleanup();
	GameLog_Cleanup();
	delete Dispatcher;
}


static Game* CurrentGameObject = NULL;
static uint32_t LastRecordedTime = 0;
static bool GameStarted = false;

Game* CurrentGame() {
	return CurrentGameObject;
}

void Game_Init() {
	CurrentGameObject = new Game();
	GameStarted = true;
	GameEventObserver_ProcessPreGameEvents();
}

void Game_Cleanup() {
	//因为GameLeave事件从玩家列表退出时也会触发
	if (GameStarted) {
		GameStarted = false;
		delete CurrentGameObject;
	}
}

bool IsInGame() {
	return GameStarted;
}

EventDispatcher* MainDispatcher() {
	return Dispatcher;
}