#include "stdafx.h"
#include "DreamWar3Main.h"

namespace DynamicHotkey {
	static bool DynamicHotkeyEnabled, DynamicHotkeyShowOnButton;

	int UnitItemTypeSlotGet(Unit *u, uint32_t itemTypeId);

	//获取鼠标所指的格子(0~5, 没有返回-1)
	int MousePointingItemSlot () {
		MousePosition* pos = GetMousePosition();
		float x = pos->x;
		float y = pos->y;

		if (x > 0.516 && x < 0.548) {
			if (y > 0.081 && y < 0.112) return 0;
			if (y > 0.043 && y < 0.074) return 2;
			if (y > 0.004 && y < 0.036) return 4;
		}
		else if (x > 0.556 && x < 0.587) {
			if (y > 0.081 && y < 0.112) return 1;
			if (y > 0.043 && y < 0.074) return 3;
			if (y > 0.004 && y < 0.036) return 5;
		}
		return -1;
	}

	//获得格子对应坐标
	MousePosition ItemSlotPositionGet(int slot){
		switch(slot){
		case 0: return MousePosition(0.532f, 0.096f);
		case 1: return MousePosition(0.572f, 0.096f);
		case 2: return MousePosition(0.532f, 0.059f);
		case 3: return MousePosition(0.572f, 0.059f);
		case 4: return MousePosition(0.532f, 0.02f);
		case 5: return MousePosition(0.572f, 0.02f);
		default: return MousePosition(0,0);
		}
	}

	typedef std::map<uint32_t, uint32_t> hotkeyMapType;//<keyCode, itemTypeId>
	static  hotkeyMapType HotkeyMap;
	static  hotkeyMapType HotkeyMapItemType;

	static	std::map<void*, Label *> HotkeyLabels;

	void RefreshHotkeyShow() {
		std::set<Label *> displayingLabels;

		if (!DynamicHotkeyShowOnButton) return;
		//轮询当前单位所有格子
		UnitGroup *group = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
		if (group->size() > 0){
			Unit *hero = group->getUnit(0);
			if (!Jass::IsUnitIllusion(hero->handleId())) {
				item i; int itemType;
				for (int slot = 0; slot < 6; slot++) {
					i = Jass::UnitItemInSlot(hero->handleId(),slot);
					itemType = Jass::GetItemTypeId(i);
					if (i && HotkeyMapItemType.count(itemType)){
						//获得物品类型对应当前动态热键并显示
						void* frame = PositionGetButton(&ItemSlotPositionGet(UnitItemTypeSlotGet(hero, itemType)));
						if (frame){
							Label *lb;
							if (HotkeyLabels.count(frame))
							{
								lb = HotkeyLabels[frame];
							}
							else
							{
								UISimpleFrame *btn = &UISimpleFrame(frame);//TODO 这样泄露么
								lb = new Label(btn, "", 0.011f);
								lb->showBackground(false);
								lb->setRelativePosition(POS_UL, btn, POS_UL, 0.002f, -0.002f);
								HotkeyLabels[frame] = lb;
							}
							lb->setText(KEYCODE::getStr(HotkeyMapItemType[itemType]));
							lb->show(true);
							displayingLabels.insert(lb);
						}
					}
				}
			}
		}

		Label *lb;
		for (std::map<void*, Label *>::iterator iter = HotkeyLabels.begin(); iter != HotkeyLabels.end(); ++iter)
		{
			lb = iter->second;
			if (!displayingLabels.count(lb))
			{
				lb->show(false);
			}
			else
			{
				displayingLabels.erase(lb);
			}
		}

		GroupDestroy(group);
	}

	//TODO: 更好的映射
	int UnitItemTypeSlotGet(Unit *u, uint32_t itemTypeId) {
		if (!Jass::IsUnitIllusion(u->handleId())) {
			item i;
			for (int slot = 0; slot < 6; slot++) {
				i = Jass::UnitItemInSlot(u->handleId(),slot);
				if (i){
					if (Jass::GetItemTypeId(i)==itemTypeId){
						return slot;
					}
				}
			}
		}
		return -1;
	}


	//TODO: 使用class Item
	void RegisterHotkey(item whichItem, uint32_t keyCode) {
		uint32_t itemTypeId = Jass::GetItemTypeId(whichItem);
		//1. 脱钩itemtypeid与任何热键，脱钩热键与任何typeid
		if (HotkeyMapItemType.count(itemTypeId)){//存在原有热键
			HotkeyMap.erase(HotkeyMapItemType[itemTypeId]);//删除原热键到物品类型映射
			HotkeyMapItemType.erase(itemTypeId);
		}
		if (HotkeyMap.count(keyCode)){//存在热键-->原有物品类型映射
			HotkeyMapItemType.erase(HotkeyMap[keyCode]);//删除原物品类型到热键映射
			HotkeyMap.erase(keyCode);
		}

		//2. 双向记录
		HotkeyMap[keyCode] = itemTypeId;
		HotkeyMapItemType[itemTypeId] = keyCode;
		//OutputScreen(10, "Bind hotkey %c for item type %s", keyCode, IntegerIdToChar(itemTypeId));
		SoundPlay("ScoreScreenTabClick", NULL, 0);

		//3. 刷新热键显示
		RefreshHotkeyShow();
	}

	uint32_t SlotToKeyCode (int slot) {
		switch (slot) {
		case 0: return KEYCODE::KEY_NUMPAD7;
		case 1: return KEYCODE::KEY_NUMPAD8;
		case 2: return KEYCODE::KEY_NUMPAD4;
		case 3: return KEYCODE::KEY_NUMPAD5;
		case 4: return KEYCODE::KEY_NUMPAD1;
		case 5: return KEYCODE::KEY_NUMPAD2;
		}
		return 0;
	}

	void UseSlotItem(KeyboardEventData *data, int slot) {
		//OutputScreen(10, "Slot %d item used.", slot);
		int keyCode = SlotToKeyCode(slot);
		if (keyCode)
			data->resetCode(keyCode);
			//data->discard();
	}

	bool keyModifierAllowedForRegisterHotkey (bool ctrl, bool alt, bool shift) {
		//if (!ctrl && alt && !shift) return true;//允许 alt + 热键
		if (ctrl && !alt && !shift) return true;//允许 ctrl + 热键
		return false;
	}

	bool keyAllowedForHotkey(uint32_t keyCode) {
		if (	keyCode >= 'A' && keyCode <= 'Z'
			||	keyCode >= '0' && keyCode <= '9'	) 
			return true; //仅允许字母与数字按键
		return false;
	}

	void onKeyDown (const Event *evt) {
		if (!DynamicHotkeyEnabled) return;
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (keyAllowedForHotkey(data->code)){
			if (keyModifierAllowedForRegisterHotkey(data->ctrl, data->alt, data->shift)){
				int slot = MousePointingItemSlot();
				war3::CSimpleButton *btn = (war3::CSimpleButton*)PositionGetButton(&ItemSlotPositionGet(slot));

				//MousePosition* pos = GetMousePosition();
				//war3::CCommandButton *btncmd = (war3::CCommandButton *)PositionGetButton(pos);
				//OutputScreen(10, "mouse (%.3f, %.3f) pointing at button 0x%X", pos->x, pos->y, btncmd);
				//OutputScreen(10, "Button: 0x%X, 0x%X", 
				//	btncmd->commandButtonData->orderId_8,
				//	btncmd->commandButtonData->orderId_C
				//);


				//OutputScreen(10, "Current CSelectionWar3 obj = 0x%X", 
				//	(*(war3::CGameWar3 **)(Offset(GLOBAL_WARCRAFT_GAME)))->players[PlayerLocal()]->selection
				//);
				//if (data->code == KEYCODE::KEY_A)
				//{
				//	UnitGroup *group = GroupUnitsOfPlayerSelected(PlayerLocal(), false);
				//	if (group->size() > 1)
				//	{
				//		Unit *secondUnit = group->getUnit(1);
				//		if (secondUnit)
				//		{
				//			SetLocalSubgroup(secondUnit);
				//			OutputScreen(1, "subgroup set to %s", secondUnit->debugName());
				//		}
				//	}
				//	GroupDestroy(group);
				//}
				
				//TODO 不要跨层使用
				if (slot != -1 && btn && (btn->mouseButtonFlags & UISimpleButton::MOUSEBUTTON_LEFT) ) {
					UnitGroup *group = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
					if (group->size() > 0){
						Unit *hero = group->getUnit(0);
						if (!Jass::IsUnitIllusion(hero->handleId())) {
							item it = Jass::UnitItemInSlot(hero->handleId(),slot);
							if (it){
								data->discard();
								RegisterHotkey(it, data->code);
							}
						}
					}
					GroupDestroy(group);
				}
			}
			else if (	!data->ctrl && !data->alt 
				//&& !data->shift //允许shift使用
				){
				uint32_t code = data->code;
				if (HotkeyMap.count(code)){
					UnitGroup *group = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
					if (group->size() > 0){
						Unit *hero = group->getUnit(0);
						int slot = UnitItemTypeSlotGet(hero, HotkeyMap[code]);
						if (slot != -1) {
							UseSlotItem(data, slot);
						}
					}
					GroupDestroy(group);
				}
			}
		}
	}

	//void onAnyPacketWaited(Timer *tm){
	//	RefreshHotkeyShow();
	//}

	//void onAnyPacket(const Event *evt){
	//	GetTimer(0.01, onAnyPacketWaited);
	//	RefreshHotkeyShow();
	//}

	//void onAnyLocalNetEventWaited(Timer *tm){
	//	RefreshHotkeyShow();
	//}

	//void onAnyLocalNetEvent(const Event *evt) {
	//	GetTimer(0.01, onAnyLocalNetEventWaited);
	//	RefreshHotkeyShow();
	//}

	void onTimerRefresh (Timer *tm)
	{
		RefreshHotkeyShow();
	}

	//---------------
	//UI
	static CheckBox *CbEnableDynamicHotkey, *CbButtonShowHotkey;
	static Label *LbEnableDynamicHotkey, *LbButtonShowHotkey;

	void CallbackEnableDynamicHotkey(CheckBox *cb, bool flag){
		CbButtonShowHotkey->activate(flag);
		LbButtonShowHotkey->activate(flag);
		RefreshHotkeyShow();
	}

	void CallbackButtonShowHotkey(CheckBox *cb, bool flag){
		RefreshHotkeyShow();
	}

	void CreateMenuContent() {
		VMProtectBeginVirtualization("DynamicHotkey_MenuContent");

		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::HOTKEY_CATEGORYNAME), NULL);
		CbEnableDynamicHotkey = new CheckBox(
			Panel, 0.024f, CallbackEnableDynamicHotkey, &DynamicHotkeyEnabled, 
			"DynamicHotkey", "Enable", false );
		CbEnableDynamicHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.21f);
		LbEnableDynamicHotkey = new Label(Panel, StringManager::GetString(STR::HOTKEY_ENABLE_DYNAMIC), 0.013f);
		LbEnableDynamicHotkey->setRelativePosition(	POS_L, CbEnableDynamicHotkey, POS_R, 0.01f, 0);

		CbButtonShowHotkey = new CheckBox(
			Panel, 0.024f, CallbackButtonShowHotkey, &DynamicHotkeyShowOnButton,
			"DynamicHotkey", "ShowHotkeyOnButton", true );
		CbButtonShowHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.237f);
		LbButtonShowHotkey = new Label(Panel, StringManager::GetString(STR::HOTKEY_SHOW_DYNAMIC), 0.013f);
		LbButtonShowHotkey->setRelativePosition(	POS_L, CbButtonShowHotkey, POS_R, 0.01f, 0);

		CallbackEnableDynamicHotkey(CbEnableDynamicHotkey, DynamicHotkeyEnabled);

		VMProtectEnd();
	}

	void Init () {
		VMProtectBeginVirtualization("DynamicHotkey_Init");

		CreateMenuContent();

		HotkeyMap.clear();
		HotkeyMapItemType.clear();
		HotkeyLabels.clear();
		MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);
		//MainDispatcher()->listen(EVENT_PACKET, onAnyPacket);
		//MainDispatcher()->listen(EVENT_LOCAL_NETEVENT, onAnyLocalNetEvent);
		GetTimer(0.01f, onTimerRefresh, true)->startImmediate();

		VMProtectEnd();
	}

	void Cleanup() {
		for (std::map<void*, Label *>::iterator iter = HotkeyLabels.begin(); iter != HotkeyLabels.end(); ++iter)
		{
			if (iter->second) delete (iter->second);
		}
		HotkeyLabels.clear();
	}
}