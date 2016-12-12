#include "stdafx.h"
#include "DreamDotaMain.h"

static bool GameDebugPaused;
#ifndef _VMP
void FastPauseGame (const Event *evt) {
	KeyboardEventData *data = evt->data<KeyboardEventData>();
	if (data->code == ProfileFetchInt("Debug", "PauseGameHotkey", KEYCODE::KEY_SPACE)
		&& !data->alt
		&& !data->ctrl
		&& !data->shift	)
	{
		data->discard();	 DiscardCurrentEvent();
		GameDebugPaused = !GameDebugPaused;
		Jass::PauseGame(GameDebugPaused);
	}
}
#endif

void DreamDota_Init() {
#ifndef _VMP
	if (ProfileFetchInt("Debug", "PauseGameOnHotkey", 0)>=1){
		MainDispatcher()->listen(EVENT_KEY_DOWN, FastPauseGame);//debug目的，快速暂停游戏
	}
#endif

#ifdef _DREAMDOTA
	//不卡
	CustomCamera::Init();
	MapHack::Init();
	LastHit::Init();
	MinimapPingEnemyHero::Init();


	//可能有点卡
	RuneNotify::Init();
	DamageDisplay::Init();
	DirectionMove::Init();


	SmartDeny::Init();

	//很卡
	ShowCooldown::Init();

	//未测试卡不卡
	CommandThrough::Init();
	Invoker::Init();
	InvisibleDisplay::Init();
#endif

#ifdef _DREAMWAR3
	CustomCamera::Init();
#endif

#ifdef _FREEPLUGIN
	CustomCamera::Init();
	ShowCooldown::Init();
#endif

}

void DreamDota_Cleanup() {

#ifdef _DREAMDOTA
	InvisibleDisplay::Cleanup();
	Invoker::Cleanup();
	CommandThrough::Cleanup();
	ShowCooldown::Cleanup();
	CustomCamera::Cleanup();
	SmartDeny::Cleanup();
	DirectionMove::Cleanup();
	DamageDisplay::Cleanup();
	RuneNotify::Cleanup();
	MinimapPingEnemyHero::Cleanup();
	LastHit::Cleanup();
	MapHack::Cleanup();
#endif

#ifdef _DREAMWAR3
	CustomCamera::Cleanup();
#endif

#ifdef _FREEPLUGIN
	ShowCooldown::Cleanup();
	CustomCamera::Cleanup();
#endif

}