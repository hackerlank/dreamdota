#include "stdafx.h"
#include "DreamWar3Main.h"
#include "PreselectUIBind.h"

void DreamWar3_Init ( ) {

#ifdef _DREAMWAR3
	PreselectUIBind::Init();
	KeyRepeat::Init();//按键重复
	DynamicHotkey::Init();//动态物品热键
	SlotHotkey::Init();//槽位改键
	QuickDropItem::Init();//快捷传递物品
	CameraToEnemyHero::Init();//切换镜头到敌人英雄
	ControlGroup::Init();//编队优化
	Surrounding::Init();//围杀
	ImprovedAutoCast::Init();//ctrl + 开关自动施法，设置强制开关并记忆
	EnemyAlert::Init();//敌人单位进入视野警告
	Formation::Init();//阵型
	FastPullToBase::Init();//快速拉单位回基地
	FastDropUnitFromTransport::Init();//从载具单位快速卸载单位
	OptAttack::Init();//自动优化齐射
	InformationPanel::Init();
	ShowLatency::Init();
	ReplayMode::Init();
	ScorePanel::Init();
	Blocking::Init();//卡位
#endif

#ifdef _DREAMDOTA
	PreselectUIBind::Init();
	KeyRepeat::Init();//按键重复
	DynamicHotkey::Init();//动态物品热键
	SlotHotkey::Init();//槽位改键
	QuickDropItem::Init();//快捷传递物品
	InformationPanel::Init();
	ShowLatency::Init();
	//ReplayMode::Init();
	ScorePanel::Init();
	CameraToEnemyHero::Init();//切换镜头到敌人英雄
#endif

#ifdef _FREEPLUGIN
	PreselectUIBind::Init();
	KeyRepeat::Init();//按键重复
	DynamicHotkey::Init();//动态物品热键
	SlotHotkey::Init();//槽位改键
	InformationPanel::Init();
	ShowLatency::Init();
	ReplayMode::Init();
	ScorePanel::Init();
#endif

#ifdef _GLEAGUE
	GLeagueDota::Init();
#endif
	
}

void DreamWar3_Cleanup() {

#ifdef _DREAMWAR3
	Blocking::Cleanup();//卡位
	ScorePanel::Cleanup();
	ReplayMode::Cleanup();
	ShowLatency::Cleanup();
	InformationPanel::Cleanup();
	OptAttack::Cleanup();
	FastDropUnitFromTransport::Cleanup();
	FastPullToBase::Cleanup();
	SlotHotkey::Cleanup();
	DynamicHotkey::Cleanup();
	PreselectUIBind::Cleanup();
#endif

#ifdef _DREAMDOTA	//DreamDota 共享功能
	CameraToEnemyHero::Cleanup();
	ScorePanel::Cleanup();
	ReplayMode::Cleanup();
	ShowLatency::Cleanup();
	InformationPanel::Cleanup();
	SlotHotkey::Cleanup();
	DynamicHotkey::Cleanup();
	PreselectUIBind::Cleanup();
#endif

#ifdef _FREEPLUGIN
	ScorePanel::Cleanup();
	ReplayMode::Cleanup();
	ShowLatency::Cleanup();
	InformationPanel::Cleanup();
	SlotHotkey::Cleanup();
	DynamicHotkey::Cleanup();
	PreselectUIBind::Cleanup();
#endif

#ifdef _GLEAGUE
	GLeagueDota::Cleanup();
#endif

	

}