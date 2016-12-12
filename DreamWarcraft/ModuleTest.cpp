#include "stdafx.h"
#include "ModuleTest.h"

#include "Game.h"
#include "Event.h"
#include "Jass.h"
#include "Tools.h"
#include "RTTIHelper.h"
#include "GameTime.h"

#include "UnitGroup.h"
#include "Timer.h"
#include "Event.h"
#include "UnitTip.h"
#include "LayoutFrame.h"
#include "UI.h"
#include "RCString.h"
#include "Observer.h"
#include "Player.h"

#include "GameStructs.h"
#include "Stochastic.h"
#include "Benchmark.h"
#include "PreselectUIBind.h"
#include "ObjectHookManager.h"
#include "UnitStateTag.h"
#include "MissileManager.h"
#include "DebugPanel.h"
#include "Button.h"
#include "Observer.h"
#include "../DreamAuth2/StringManager.h"
#include "UnitWalker.h"

#include "UISimpleButton.h"
#include "OptionMenu.h"
#include "CheckBox.h"

#include "AbilityTest.h"
#include "UITest.h"
#include "CommandButtonTest.h"
#include "UISimpleStatusBar.h"

#include "MultiIcon.h"
#include "Ability.h"

#include "BinaryDumper.h"

#include "Foundation.h"

war3::CUnitTip* tip = NULL;
static UnitGroup SelectionGroup;
void panelUpdateFunction(DebugPanel* panel);
static OptionMenu* MENU;

#define OFFSET(o) aero::pointer_calc<void*>(GetModuleHandle("Game.dll"), o)

uint32_t __fastcall eventProcessFunc(void* t, void* dummy, war3::CEvent* evt) {
#ifndef _VMP
	OutputDebug("[%.3f] AbilityAttack object = %X, Event: ID = 0x%X, Remain time: %.3f", Time(), t, evt->id, AgentTimerRemainingTimeGet(&(((war3::CAbilityAttack*)t)->timer_dmgPt)));
#endif	
	return aero::generic_this_call<uint32_t>(
		GetObjectHookManager()->getOrignal(t, 0xC),
		t,
		evt
	);
}

OBSERVER_EVENT_HANDLER(OEH) {
	//OutputDebug("EVT");
	return 0;
}

war3::CUnit* test;
void onTimer(Timer* tm) {
	//OutputDebug("RefCount = %u", test->refCount);
}

void ObserverHandler(Observer* obs, uint32_t evt) {
	//OutputDebug("observer: 0x%X, event id: %u", obs, evt);
}

void ButtonTestCallback (Button *button) {
	button->setAbsolutePosition(UILayoutFrame::POSITION_CENTER, RandomFloat(0,0.5f), RandomFloat(0, 0.4f));
}

static bool CheckBoxIsChecked;
void CheckBoxTestCallback(CheckBox* cb, bool checked) {
	//OutputScreen(10, "checkbox 0x%X %s, CheckBoxIsChecked = %s", cb, checked? "checked" : "unchecked", CheckBoxIsChecked? "true":"false");
}

/*
void Overflow() {
	char buff[1024];
	buff;
	Overflow();
}
*/

void TestOverflow() {
	//Overflow();
}

#include "Frame.h"
#include "Texture.h"
#include "CheckBox.h"

void TestHeroBoard() {


	CheckBox *cb = new CheckBox(UI_NULL);
	cb->setAbsolutePosition(POS_C, 0.4f, 0.3f);
	cb->setTexture(
		"UI\\Widgets\\Glues\\GlueScreen-Checkbox-Background.blp",
		"UI\\Widgets\\Glues\\GlueScreen-Checkbox-BackgroundDisabled.blp",
		"UI\\Widgets\\Glues\\GlueScreen-Checkbox-BackgroundPressed.blp",
		"UI\\Widgets\\Glues\\GlueScreen-Checkbox-Check.blp",
		"UI\\Widgets\\Glues\\GlueScreen-Checkbox-CheckDisabled.blp"
	);
	
	
	return;


	float scale = 1.1f;

	float heroFrameSize = 0.042f;
	UISimpleFrame *heroFrame = UISimpleFrame::Create();
	heroFrame->setWidth(heroFrameSize * scale);	heroFrame->setHeight(heroFrameSize * scale);
	heroFrame->setBackground("DreamDota3\\Textures\\GreyBackground.tga");
	heroFrame->setPadding(0.002f * scale);
	heroFrame->setBorder("UI\\Widgets\\ToolTips\\Human\\human-tooltip-border.blp");
	heroFrame->setBorderWidth(0.005f * scale);
	heroFrame->applyTextureSettings();
	heroFrame->setAbsolutePosition(UILayoutFrame::POSITION_CENTER, 0.1f, 0.50f);

	UISimpleFrame *playeNameFrame = UISimpleFrame::Create();
	playeNameFrame->setHeight(0.012f * scale);
	playeNameFrame->setWidth(0.08f * scale);
	playeNameFrame->setBackground("DreamDota3\\Textures\\GreyBackground.tga");
	playeNameFrame->setPadding(0.002f * scale);
	playeNameFrame->setBorder("UI\\Widgets\\ToolTips\\Human\\human-tooltip-border.blp");
	playeNameFrame->setBorderWidth(0.005f * scale);
	playeNameFrame->applyTextureSettings();
	playeNameFrame->setRelativePosition(UILayoutFrame::POSITION_BOTTOM_LEFT, heroFrame, POS_UL, 0, -0.001f * scale);

	Label *lbPlayerName = new Label(playeNameFrame, "SomePlayerName", 0.008f * scale);
	lbPlayerName->setTextColor(Color(1.f,0,0));
	lbPlayerName->setRelativePosition(POS_L, playeNameFrame, POS_L, 0.005f * scale, 0);

	
	

	UISimpleTexture *heroIcon = UISimpleTexture::Create(heroFrame);
	heroIcon->setWidth(0.038f * scale); heroIcon->setHeight(0.038f * scale); 
	heroIcon->fillBitmap("ReplaceableTextures\\CommandButtons\\BTNFurion.blp");
	heroIcon->setRelativePosition(UILayoutFrame::POSITION_CENTER, heroFrame, UILayoutFrame::POSITION_CENTER,0,0);

	Label *lbHeroLevel = new Label(heroFrame, "Lv 3", 0.008f * scale, Color(1.f, 1.f, 1.f));
	lbHeroLevel->setRelativePosition(UILayoutFrame::POSITION_BOTTOM_RIGHT, heroIcon, UILayoutFrame::POSITION_BOTTOM_RIGHT, -0.002f * scale, 0.002f * scale);

	UISimpleStatusBar *heroHP = UISimpleStatusBar::Create(heroFrame);
	heroHP->setWidth(0.05f * scale); heroHP->setHeight(0.008f * scale);
	heroHP->setTexture("UI\\Feedback\\HPBarConsole\\human-healthbar-fill.blp");
	heroHP->setColor(0, 1, 0, 1);
	heroHP->setValueRange(0.f, 1.f);
	heroHP->setRelativePosition(UILayoutFrame::POSITION_BOTTOM_LEFT, heroFrame, UILayoutFrame::POSITION_BOTTOM_RIGHT, 0, 
		0.004 * scale + 0.008f * scale);

	UISimpleStatusBar *heroMana = UISimpleStatusBar::Create(heroFrame);
	heroMana->setWidth(0.05f * scale); heroMana->setHeight(0.008f * scale);
	heroMana->setTexture("UI\\Feedback\\HPBarConsole\\human-healthbar-fill.blp");
	heroMana->setColor(0, 0.25f, 1, 1);
	heroMana->setValueRange(0.f, 1.f);
	heroMana->setRelativePosition(UILayoutFrame::POSITION_TOP_CENTER, heroHP, UILayoutFrame::POSITION_BOTTOM_CENTER, 0, -0.0005f*scale);

	Label *lbHP = new Label(heroHP, "750/750", 0.008f * scale);
	lbHP->setTextColor(Color(1.f,1.f,1.f));
	lbHP->setRelativePosition(UILayoutFrame::POSITION_CENTER, heroHP, UILayoutFrame::POSITION_CENTER, 0, 0);
	Label *lbMana = new Label(heroMana, "325/325", 0.008f * scale);
	lbMana->setTextColor(Color(1.f,1.f,1.f));
	lbMana->setRelativePosition(UILayoutFrame::POSITION_CENTER, heroMana, UILayoutFrame::POSITION_CENTER, 0, 0);

	float AbilityIconSize = 0.038f - 2 * 0.008f - 0.004f;
	UISimpleTexture *AbilityIcon1 = UISimpleTexture::Create(heroFrame);
	AbilityIcon1->setWidth(AbilityIconSize * scale); 
	AbilityIcon1->setHeight(AbilityIconSize * scale); 
	AbilityIcon1->fillBitmap("ReplaceableTextures\\CommandButtons\\BTNChainLightning.blp");
	AbilityIcon1->setRelativePosition(UILayoutFrame::POSITION_BOTTOM_LEFT, heroHP, POS_UL,0,0.0008f * scale);

	UISimpleTexture *AbilityIcon2 = UISimpleTexture::Create(heroFrame);
	AbilityIcon2->setWidth(AbilityIconSize * scale); 
	AbilityIcon2->setHeight(AbilityIconSize * scale); 
	AbilityIcon2->fillBitmap("ReplaceableTextures\\CommandButtons\\BTNColdArrows.blp");
	AbilityIcon2->setRelativePosition(POS_L, AbilityIcon1, POS_R,0.0008f * scale,0);

	UISimpleTexture *AbilityIcon3 = UISimpleTexture::Create(heroFrame);
	AbilityIcon3->setWidth(AbilityIconSize * scale); 
	AbilityIcon3->setHeight(AbilityIconSize * scale); 
	AbilityIcon3->fillBitmap("ReplaceableTextures\\CommandButtons\\BTNDrum.blp");
	AbilityIcon3->setRelativePosition(POS_L, AbilityIcon2, POS_R,0.0008f * scale,0);

	UISimpleTexture *AbilityIcon4 = UISimpleTexture::Create(heroFrame);
	AbilityIcon4->setWidth(AbilityIconSize * scale); 
	AbilityIcon4->setHeight(AbilityIconSize * scale); 
	AbilityIcon4->fillBitmap("ReplaceableTextures\\CommandButtons\\BTNHolyBolt.blp");
	AbilityIcon4->setRelativePosition(POS_L, AbilityIcon3, POS_R,0.0008f * scale,0);
}

void onLocalChat (const Event *evt) {
#ifndef _VMP
	LocalChatEventData* data = evt->data<LocalChatEventData>();
	const char* text = data->content;

	war3::CSimpleFontString* sfs;
	war3::CSimpleTexture* st;
	war3::CSimpleFrame *sf, *sfNavigation, *sfContent;
	war3::CSimpleCheckbox* sc;
//	war3::CObserver* cob;
	Observer* ob;

	war3::SimpleFrameTextureSettings* settings;
//	war3::CSimpleButton* sb;
	Button * button;

	//UISimpleFrame *UIsf;
	UISimpleButton *UINaviItem1, *UIsb;
	UISimpleFontString *UINaviItem1sfs, *UIsfs;

	DnDAtkDist atkDist;
	wchar_t bufferW[0x100];

	Benchmark *benchm = new Benchmark();
	if (text[0] == '/' && strlen(text) > 1) {
		OutputScreen(10, "Command: %s", text + 1);
		switch(text[1]) {
		case '1'://测试一下骰子计算
			SelectionGroup.clear();
			GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
			if (SelectionGroup.size()) {
				Unit* u1 = SelectionGroup.getUnit(0);
				for (uint32_t i = 0; i < 40; i++) {//单位自身攻击叠加40次
					atkDist &= u1->attack(0);
				}
				OutputScreen(10, "atkDist has value between (%.3f and %.3f)", atkDist.minValue(), atkDist.maxValue());
				benchm->mark("start");
				//for (uint32_t i = 900; i < 1400; i+=10) {
				for (uint32_t i = 1100; i < 1200; i+=10) {
					float val = atkDist.chanceGreaterEqual((float)i, false);
					OutputScreen(10, "attack >= %d chance : %.4f", i, val);
				}
				benchm->mark("end");
				double timeElapsed = benchm->elapsedTime("start", "end");
				OutputScreen(10, "total time needed = %.6f", timeElapsed);

				//float v = 1157.5;
				//OutputScreen(10, "attack >= %.4f chance : %.4f", v, atkDist.chanceGreaterEqual(v));
			}
			break;
		case '2'://simplebutton
			void* tmp;
			tmp = aero::generic_fast_call<void*>(0x6F4D9830, 1);
			void* labels;
			labels = aero::generic_fast_call<void*>(0x6F30FFE0);
			aero::generic_fast_call<void>(0x6F4D8D60, tmp, Skin::getPathByName("MinimapWaypoint"), labels, 0, 0, 0);
			break;
		case 'a'://测试Ability相关
			SelectionGroup.clear();
			GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
			if (SelectionGroup.size()) {
				war3::CUnit* u = UnitGetObject(SelectionGroup.getUnit(0)->handleId());
				OutputScreen(10, "Unit: %s", SelectionGroup.getUnit(0)->name());
				war3::CAbility* ability = NULL;//(war3::CAbility*)AgentFromHash(&(u->abilityHash));
				while (ability) {
					float tmpfloat;
					if (ability->flag2 & 0x200)
						OutputDebug(RTTIHelper::className(ability));

					OutputDebug("0x%X AgentId: %s", ability, IntegerIdToChar(AgentTypeIdGet((war3::CAgent*)ability)));

					if (IsAbilitySpell(ability)) {
						OutputDebug("==================================================================================");
						OutputDebug("0x%X Name: %s, ManaCost: %.3f Cooldown: %.3f", ability, ObjectIdToNameChar(ability->id), AbilityManaCostGet(ability), AbilityCooldownGet(ability));
						Ability* aw = GetAbility(ability);
						OutputDebug("IntegerIdToChar(typeID()) = %s", IntegerIdToChar(aw->typeId()));
						OutputDebug("IntegerIdToChar(baseTypeID()) = %s", IntegerIdToChar(aw->baseTypeId()));
						OutputDebug("level() = 0x%X", aw->level());
						OutputDebug("cooldown() = %.2f", aw->cooldown());
						OutputDebug("cooldownRemain() = %.2f", aw->cooldownRemain());
						OutputDebug("isAvailable() = %s", aw->isAvailable() ? "Yes" : "No");
						OutputDebug("owner()->name = %s", aw->owner()->name());
						OutputDebug("iconPath() = %s", aw->iconPath());
					}
					ability = (war3::CAbility*)AgentFromHash(&(ability->nextAbilityHash));
				}
			}
			break;
		case 't'://simplefontstring
			sfs = SimpleFontString::create(GameUIObjectGet()->simpleConsole);
			SimpleFontString::initFont(sfs, Skin::getPathByName("MasterFont"), 0.115f, 1);
			SimpleFontString::initText(sfs);
			MultiByteToWideChar(936, 0, "a啊哈哈哈", -1, bufferW, 0x100);
			SimpleFontString::setText(sfs, (char*)bufferW);
			LayoutFrame::setAbsolutePosition(sfs, LayoutFrame::Position::BOTTOM_LEFT, 0.52f, 0.1f, 0);
			break;
		case 'r':
			SelectionGroup.clear();
			GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
			if (SelectionGroup.size()) {
				Unit* first = SelectionGroup.getUnit(0);
				war3::CUnit *u_obj = UnitGetObject(first->handleId());
				if (u_obj) {
					test = UnitGetObject(first->handleId());
					GetTimer(1, onTimer, true)->start();
				}
			}
			break;
		case 'x'://simpletexture
			st = SimpleTexture::create();
			LayoutFrame::setWidth(st, 0.04f);
			LayoutFrame::setHeight(st, 0.04f);
			SimpleTexture::setTexturePath(st, "UI\\Feedback\\BuildProgressBar\\human-buildprogressbar-fill.blp", 1);
			LayoutFrame::setRelativeFrame(st, GameUIObjectGet()->resourceBar);
			break;
		case 's'://simpleframe
			sf = SimpleFrame::create(GameUIObjectGet()->simpleConsole);	//TODO 与单位头上的自定义tip的层数关系？为什么显示bug
			settings = SimpleFrame::initTextureSettings(sf);
			RCString::setString(&(settings->RCS_bgTexturePath), Skin::getPathByName("EscMenuBackground"));//("ToolTipBackground")); 
			RCString::setString(&(settings->RCS_borderTexturePath), Skin::getPathByName("EscMenuBorder"));//("ToolTipBorder")); 
			settings->borderFlags = 0xFFu;
			settings->unk_30 = 1;
			settings->borderWidth = 0.048f;
			settings->paddingTop = settings->paddingBottom = settings->paddingLeft = settings->paddingRight = 0.01f;
			SimpleFrame::applyTextureSetting(sf);
			//LayoutFrame::setRelativePosition(sf, 0, GameUIObjectGet()->resourceBar, LayoutFrame::Position::BOTTOM_LEFT, 0, 0);
			LayoutFrame::setAbsolutePosition(sf, LayoutFrame::Position::BOTTOM_LEFT, 0.05f, 0.175f, 0);
			LayoutFrame::setWidth(sf, 0.7f);
			LayoutFrame::setHeight(sf, 0.4f);

			//导航
			sfNavigation = SimpleFrame::create(sf);
			LayoutFrame::setRelativePosition(sfNavigation, LayoutFrame::Position::TOP_LEFT, sf, LayoutFrame::Position::TOP_LEFT, 0, 0);
			LayoutFrame::setWidth(sfNavigation, 0.2f);
			LayoutFrame::setHeight(sfNavigation, 0.4f);

			UINaviItem1 = UISimpleButton::Create(&UISimpleFrame(sf));
			UINaviItem1->setStateTexture(UISimpleButton::STATE_DISABLED, Skin::getPathByName("EscMenuButtonDisabledBackground"));
			UINaviItem1->setStateTexture(UISimpleButton::STATE_ENABLED, Skin::getPathByName("EscMenuButtonDisabledBackground"));
			UINaviItem1->setStateTexture(UISimpleButton::STATE_PUSHED, Skin::getPathByName("EscMenuButtonPushedBackground"));
			//UINaviItem1->setBackground(Skin::getPathByName("EscMenuButtonDisabledBackground"));
			UINaviItem1->setBorder(Skin::getPathByName("ToolTipBorder")); 
			UINaviItem1->setBorderWidth(0.01f);
			UINaviItem1->setPadding(0.01f,0.01f,0.01f,0.01f);
			UINaviItem1->applyTextureSettings();
			UINaviItem1->setMouseButton(UISimpleButton::MOUSEBUTTON_LEFT);
			UINaviItem1->setRelativePosition(POS_UL, &UILayoutFrame(sfNavigation), POS_UL, 0.04f, -0.04f);
			UINaviItem1->setWidth(0.15f);
			UINaviItem1->setHeight(0.024f);
			UINaviItem1->setState(UISimpleButton::STATE_ENABLED);
			UINaviItem1sfs = UISimpleFontString::Create(UINaviItem1);
			UINaviItem1sfs->initFont(Skin::getPathByName("MasterFont"), 0.011f, 1);
			UINaviItem1sfs->setText("|cFFFFFFFFSOME CATEGORY MENU|R");
			UINaviItem1sfs->setRelativePosition(UILayoutFrame::POSITION_CENTER, UINaviItem1, UILayoutFrame::POSITION_CENTER, 0, 0);

			//内容
			sfContent = SimpleFrame::create(sf);
			LayoutFrame::setRelativePosition(sfContent, LayoutFrame::Position::TOP_LEFT, sfNavigation, LayoutFrame::Position::TOP_RIGHT, 0, 0);
			LayoutFrame::setWidth(sfContent, 0.5f);
			LayoutFrame::setHeight(sfContent, 0.4f);

			//默认checkbox 0.024
			//EscMenuCheckBoxBackground
			//EscMenuCheckBoxPushedBackground
			//EscMenuDisabledCheckBoxBackground
			//EscMenuCheckBoxCheckHighlight
			//EscMenuDisabledCheckHighlight	--纹理实际与上面一样？
			UIsb = UISimpleButton::Create(
				NULL,
				0.024f, 0.024f,
				Skin::getPathByName("EscMenuDisabledCheckBoxBackground"),
				Skin::getPathByName("EscMenuCheckBoxBackground"),
				Skin::getPathByName("EscMenuCheckBoxPushedBackground"),
				UISimpleButton::MOUSEBUTTON_LEFT,
				UISimpleButton::STATE_ENABLED
			);
			UIsb->setRelativePosition(
				POS_UL, 
				&UILayoutFrame(sfContent), 
				POS_UL, 
				0.04f, 
				-0.04f
			);

			//默认 0.012, 颜色0.99 0.827 0.0705 1 高亮颜色1,1,1,1 禁用颜色0.2 0.2 0.2 1
			//阴影颜色黑 阴影offset 0.002, -0.002
			//距离checkbox 0.003
			UIsfs = UISimpleFontString::Create(&UISimpleFrame(sf));
			UIsfs->initFont(Skin::getPathByName("MasterFont"), 0.012f, 1);
			UIsfs->setText("|cFFFCD312Some Option|R");
			UIsfs->setRelativePosition(POS_L, UIsb, POS_R, 0.003f, 0);
			

			break;
		case 'o'://observer
			//cob = CObserver::create((CObserver::EventProcessFunctionType)eventProcessFunc);
			//CObserver::addEventObserver((war3::CObserver*)GameUIObjectGet(), war3::EVENT_FOCUS, cob);

			ob = Observer::Create(ObserverHandler);
			Observer((war3::CObserver*)GameUIObjectGet()).addEventObserver(ob, war3::EVENT_FOCUS);
			break;
		case 'p':
			SelectionGroup.clear();
			GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
			if (SelectionGroup.size()) {
				
				Unit* first = SelectionGroup.getUnit(0);
				war3::CUnit *u_obj = UnitGetObject(first->handleId());
				if (u_obj) {
					war3::SmartPosition* sp = aero::generic_this_call<war3::SmartPosition*>(
						VTBL(u_obj)[0xB8 / 4],
						u_obj
					);
					OutputDebug("SmartPosition: 0x%X", sp);
					float xy[2];
					aero::generic_this_call<void>(
						0x6F476390,
						sp,
						xy
					);
					//OutputDebug("Unit 0x%X, %.3f, %.3f", u_obj, u_obj->x, u_obj->y);
				}
			}
			break;
		case 'h':
			SelectionGroup.clear();
			GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
			if (SelectionGroup.size()) {
				
				Unit* first = SelectionGroup.getUnit(0);
				war3::CUnit *u_obj = UnitGetObject(first->handleId());
				if (u_obj) {
					UnitStateTag* t = new UnitStateTag();
					t->setOwner(first->handleId());
					t->update();
				}
			}
			break;
		case 'm': //显示所有飞行中的missile
			SelectionGroup.clear();
			GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
			if (SelectionGroup.size()) {
				
				Unit* first = SelectionGroup.getUnit(0);
				war3::CUnit *u_obj = UnitGetObject(first->handleId());
				if (u_obj) {
					OutputScreen(10, "Unit obj = %X, ABnP = %X", u_obj, 
						AbilityObjGet(u_obj, 'ABnP') );
					const MissileInfo* info;
					while(NULL != (info = MissileManager_TargetUnitMissileFetch(u_obj))) {
						float timeNeed = info->timeNeeded();
						OutputScreen(10, "Missile: 0x%X Type: %d, attack: %.4f, damagefactor: %.4f", info->object, info->type, 
							((war3::CBulletBase *)(info->object))->attack.value,
							first->damageFactorAsTarget(((war3::CBulletBase *)(info->object))->attackType)
							);
					}
				}
			}
			break;
		case 'd':
			SelectionGroup.clear();
			GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
			if (SelectionGroup.size()) {
				Unit* first = SelectionGroup.getUnit(0);
				GetDebugPanel(first, panelUpdateFunction);
			}			
			break;

		case 'b':
			//test
			TestHeroBoard();
			break;
		case 'j':

			break;
		case 'c':
			const char* names[] = {"GetUpgradeGoldCost", "GetUpgradeWoodCost", "GetUnitGoldCost", "GetUnitWoodCost", "GetUnitBuildTime"};
			for (int iname = 0; iname < sizeof(names) / 4; ++iname) {
				OutputDebug("%s = 0x%08X\n", names[iname], GetNativeFuncNode(names[iname])->func);
			}
			SelectionGroup.clear();
			GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
			if (SelectionGroup.size()) {
				
				Unit* first = SelectionGroup.getUnit(0);
				war3::UnitDataNode* n = GetUnitDataNode(first->typeId());
				if (n) {
					BinaryDumper("UnitData.bin").dump(n, sizeof(war3::UnitDataNode));
					OutputDebug("gold cost = %d, wood cost = %d, build time = %d\n", n->goldCost, n->woodCost, n->buildTime);
					OutputDebug("%s\n%s\n%s\n%s", 
						RCString::getString(&(n->abilList)),
						RCString::getString(&(n->str_280)), 
						RCString::getString(&(n->str_29C)), 
						RCString::getString(&(n->str_2A8)));
				}

			}
			OutputDebug("%s\n", Jass::GetPlayerName(Jass::Player(1)));
			break;
		}
		
		
		//data->content[0] = 0;
		delete benchm;
	}
#endif
}



void panelUpdateFunction(DebugPanel* panel) {
	if (panel->parent()) {
		panel->set("Order", "0x%X", Jass::GetUnitCurrentOrder(panel->parent()->handleId()));
		panel->set("Position", "%.3f, %.3f", Jass::GetUnitX(panel->parent()->handleId()), Jass::GetUnitY(panel->parent()->handleId()));
	}
}

void onUnitCreated (const Event *evt) {
	UnitCreationEventData* data = evt->data<UnitCreationEventData>();
	war3::CUnit* obj = UnitGetObject(data->createdUnit);
	//OutputDebug("Unit created: type = %s, x = %.2f, y = %.2f", IntegerIdToChar(obj->typeId), obj->x, obj->y);
}

void onItemCreated (const Event *evt) {
	ItemCreationEventData* data = evt->data<ItemCreationEventData>();
	war3::CItem* obj = ItemGetObject(data->createdItem);
	//OutputDebug("Item created: type = %s, x = %.2f, y = %.2f", IntegerIdToChar(obj->typeId), Jass::GetWidgetX(data->createdItem), Jass::GetWidgetY(data->createdItem));
}

void onReceiveDamage (const Event *evt) {
	UnitDamagedEventData* data = evt->data<UnitDamagedEventData>();
	//OutputDebug("src:0x%X, dst:0x%X, damage:%.2f, raw:%.2f", data->source, data->target, data->damage, data->damageRaw);
}

void onKeyDown (const Event *evt) {
	//OutputScreen(10, "Game Mode = %d", ReplayState());	
}

void onTimerMissileTest (Timer *tm) {
	SelectionGroup.clear();
	GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
	if (SelectionGroup.size()) {
		Unit *u = SelectionGroup.getUnit(0);
		const MissileInfo* info;
		int i = 1;
		while(NULL != (info = MissileManager_TargetUnitMissileFetch(u))) {
			float timeNeed = info->timeNeeded();
			//OutputScreen(10, "Current Time : %.4f,  Missile #%d : type %d, time remain %.4f", Time(), i, info->type, timeNeed);
			i++;
		}
	}
}

void onAttackReleased(const Event *evt) {
	UnitAttackReleasedEventData* data = evt->data<UnitAttackReleasedEventData>();
	//OutputDebug("[%.3f]AttackReleased unit = 0x%X", Time(), data->attacker);
}

void onTick(Timer* tm) {
	DefaultDebugPanel->set("Game Time", "%.3f", Time());
}

void onUnitAttacked (const Event *evt) {
	//OutputScreen(10, "Attacked: Attacker:0x%X TriggerUnit:0x%X", Jass::GetAttacker(), Jass::GetTriggerUnit());
}

void onUnitDeath (const Event *evt) {
	SelectionGroup.clear();
	GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
	if (SelectionGroup.size()) {
		Unit* first = SelectionGroup.getUnit(0);
		//Jass::KillUnit(first->handleId());
	}
	MainDispatcher()->dispatch(evt);
}

void WalkerCallback(Unit* u) {

}

uint32_t CreateMultiboardHook() {
	handle m = Jass::CreateMultiboard();
	//OutputDebug("Multiboard created! handle = 0x%08X.", m);
	return m;
}

void DumpJassTm(Timer* tm) {
#ifndef _VMP
	//Dump jass func
	war3::NativeFuncAllocator* nfa;
	war3::NativeFuncAllocator::MemBlockType* block;
	nfa = (war3::NativeFuncAllocator*)Offset(AH_NATIVEFUNC);
	OutputDebug("NativeFuncNode size: 0x%X\n", nfa->dataSize);
	OutputDebug("NativeFuncNode count: 0x%X\n", nfa->dataCount);
	OutputDebug("NativeFuncNode mem blocks item count: 0x%X\n", nfa->memBlockDataNum);

	if (nfa->dataCount) {
		char dumpname[MAX_PATH];
		FILE *fp, *fp2;
		fp = fopen("JassNatives.txt", "w");
		sprintf(dumpname, "native_offsets_%d.inc", GetGameVersion());
		fp2 = fopen(dumpname, "w");
		block = nfa->memBlockListHead;
			
		while(block) {
			OutputDebug("NativeFuncNode block 0x%X:\n", block);
			for (int i = 0; i < war3::NativeFuncAllocator::MemBlockType::BLOCK_SIZE; ++i) {
				war3::NativeFuncAllocator::MemBlockType::NodeType& node = block->dataNodes[i];
				if (node.unusedNode.nextNode != 0 && node.unusedNode.nextNode != &(node) + 1) {
					fprintf(fp, "%s|%s\n", node.data.funcName, node.data.argsType);
					fprintf(fp2, "JASS_NATIVE_%s = (JASS_PROTOTYPE_%s)(base + 0x%08X);\n", node.data.funcName, node.data.funcName, (DWORD)node.data.func - (DWORD)GetModuleHandle("game.dll"));
				}
			}
			block = block->nextBlock;
		}

		fclose(fp);
		fclose(fp2);

	}

	OutputScreen(10, "%u Jass natives dumped.", nfa->dataCount);
#endif
}

void ModuleTest_Init() {
	AbilityTest_Init();
	CommandButtonTest_Init();
	UITest_Init();

	MainDispatcher()->listen(EVENT_LOCAL_CHAT, onLocalChat);
	//MainDispatcher()->listen(EVENT_UNIT_CREATED, onUnitCreated);
	//MainDispatcher()->listen(EVENT_ITEM_CREATED, onItemCreated);
	//MainDispatcher()->listen(EVENT_UNIT_RECEIVE_DAMAGE, onReceiveDamage);
	//MainDispatcher()->listen(Jass::EVENT_PLAYER_UNIT_ATTACKED, onUnitAttacked);
	//MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);
	//MainDispatcher()->listen(Jass::EVENT_PLAYER_UNIT_ISSUED_POINT_ORDER, onPointOrder);
	//GetTimer(0.03f, onTimerMissileTest, true)->start();
	//MainDispatcher()->listen(EVENT_UNIT_ATTACK_RELEASED, onAttackReleased);

	//DefaultDebugPanel->set("DefaultDebugPanel", "0x%X", DefaultDebugPanel);
	//GetTimer(0, onTick, true)->start();

	//MainDispatcher()->listen(Jass::EVENT_PLAYER_UNIT_DEATH, onUnitDeath);
	//GetUnitWalker(WalkerCallback);

	//GetTimer(0.1, DumpJassTm, false)->start();
}


void ModuleTest_Cleanup() {
	UITest_Cleanup();
	CommandButtonTest_Cleanup();
	AbilityTest_Cleanup();
}