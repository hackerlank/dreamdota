#include "stdafx.h"
#include "DreamWar3Main.h"

namespace SlotHotkey {

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

	static UISimpleTexture *BackgroundInventory, *BackgroundCommandCard;

	static SlotHotkeyButton 
		*InventorySlotHotkeyButton0, 
		*InventorySlotHotkeyButton1, 
		*InventorySlotHotkeyButton2, 
		*InventorySlotHotkeyButton3, 
		*InventorySlotHotkeyButton4, 
		*InventorySlotHotkeyButton5;

	static SlotHotkeyButton 
		*CmdSlotHotkeyButton0, 
		*CmdSlotHotkeyButton1, 
		*CmdSlotHotkeyButton2, 
		*CmdSlotHotkeyButton3, 
		*CmdSlotHotkeyButton4, 
		*CmdSlotHotkeyButton5, 
		*CmdSlotHotkeyButton6, 
		*CmdSlotHotkeyButton7, 
		*CmdSlotHotkeyButton8, 
		*CmdSlotHotkeyButton9, 
		*CmdSlotHotkeyButton10, 
		*CmdSlotHotkeyButton11; 

	static bool SlotHotkeyEnabled;
	static CheckBox *CbEnableSlotHotkey;
	static Label *LbEnableSlotHotkey;

	void CallbackSlotHotkeyCheckBox(CheckBox *cb, bool flag){
		InventorySlotHotkeyButton0->enable(flag);InventorySlotHotkeyButton1->enable(flag);InventorySlotHotkeyButton2->enable(flag);
		InventorySlotHotkeyButton3->enable(flag);InventorySlotHotkeyButton4->enable(flag);InventorySlotHotkeyButton5->enable(flag);
		CmdSlotHotkeyButton0->enable(flag);CmdSlotHotkeyButton1->enable(flag);CmdSlotHotkeyButton2->enable(flag);
		CmdSlotHotkeyButton3->enable(flag);CmdSlotHotkeyButton4->enable(flag);CmdSlotHotkeyButton5->enable(flag);
		CmdSlotHotkeyButton6->enable(flag);CmdSlotHotkeyButton7->enable(flag);CmdSlotHotkeyButton8->enable(flag);
		CmdSlotHotkeyButton9->enable(flag);CmdSlotHotkeyButton10->enable(flag);CmdSlotHotkeyButton11->enable(flag);
		if (!flag) {
			BackgroundInventory->setColorFloat(0.5f, 0.5f, 0.5f, 1);
			BackgroundCommandCard->setColorFloat(0.5f, 0.5f, 0.5f, 1);
		} else {
			BackgroundInventory->setColorFloat(1,1,1,1);
			BackgroundCommandCard->setColorFloat(1,1,1,1);
		}
	}
		

	bool keyModifierAllowed (bool ctrl, bool alt, bool shift) {
		if (!ctrl && !alt) return true;
		return false;
	}

	void onKeyDown(const Event *evt){
		VMProtectBeginVirtualization("SlotHotkey_onKeyDown");

		if (!SlotHotkeyEnabled) return;
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (!keyModifierAllowed(data->ctrl, data->alt, data->shift)) return;
		if (ProfileGetInt("SlotHotkey", "SlotInventory0Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotInventory0", -1) == data->code){
			GameUIButtonClick(PositionGetButton(&ItemSlotPositionGet(0)), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotInventory1Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotInventory1", -1) == data->code){
			GameUIButtonClick(PositionGetButton(&ItemSlotPositionGet(1)), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotInventory2Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotInventory2", -1) == data->code){
			GameUIButtonClick(PositionGetButton(&ItemSlotPositionGet(2)), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotInventory3Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotInventory3", -1) == data->code){
			GameUIButtonClick(PositionGetButton(&ItemSlotPositionGet(3)), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotInventory4Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotInventory4", -1) == data->code){
			GameUIButtonClick(PositionGetButton(&ItemSlotPositionGet(4)), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotInventory5Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotInventory5", -1) == data->code){
			GameUIButtonClick(PositionGetButton(&ItemSlotPositionGet(5)), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}

		if (ProfileGetInt("SlotHotkey", "SlotCommand0Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand0", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.63713f, 0.112f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand1Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand1", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.68075f, 0.112f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand2Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand2", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.72438f, 0.112f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand3Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand3", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.768f, 0.112f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand4Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand4", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.63713f, 0.069f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand5Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand5", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.68075f, 0.069f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand6Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand6", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.72438f, 0.069f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand7Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand7", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.768f, 0.069f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand8Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand8", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.63713f, 0.026f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand9Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand9", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.68075f, 0.026f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand10Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand10", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.72438f, 0.026f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}
		if (ProfileGetInt("SlotHotkey", "SlotCommand11Enabled", 0) > 0 && ProfileGetInt("SlotHotkey", "SlotCommand11", -1) == data->code){
			GameUIButtonClick(PositionGetButton(0.768f, 0.026f), MOUSECODE::MOUSE_LEFT, true); data->discard();	 DiscardCurrentEvent();
		}

		VMProtectEnd();
	}

	void CreateMenuContent(){
		VMProtectBeginVirtualization("SlotHotkey_MenuContent");

		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::HOTKEY_CATEGORYNAME), NULL);

		CbEnableSlotHotkey = new CheckBox(
			Panel, 0.024f, CallbackSlotHotkeyCheckBox, &SlotHotkeyEnabled, 
			"SlotHotkey", "Enable", false );
		CbEnableSlotHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.03f);
		LbEnableSlotHotkey = new Label(Panel, StringManager::GetString(STR::HOTKEY_ENABLE_GRID), 0.013f);
		LbEnableSlotHotkey->setRelativePosition(	POS_L, CbEnableSlotHotkey, POS_R, 0.01f, 0);

		BackgroundInventory = UISimpleTexture::Create(Panel);
		BackgroundInventory->setWidth(0.128f); BackgroundInventory->setHeight(0.128f);
		BackgroundInventory->fillBitmap("DreamDota3\\Textures\\InventoryHuman.tga");
		BackgroundInventory->setRelativePosition(POS_L, Panel, POS_L, 0.03f, 0.02f);

		InventorySlotHotkeyButton0 = new SlotHotkeyButton(Panel, 0.032f, 0.032f, NULL, -1, "SlotHotkey", "SlotInventory0", "SlotInventory0Enabled"	);
		InventorySlotHotkeyButton0->setRelativePosition(POS_UL, BackgroundInventory, POS_UL, 
			0.029f, -0.0085f);

		InventorySlotHotkeyButton1 = new SlotHotkeyButton(Panel, 0.032f, 0.032f, NULL, -1, "SlotHotkey", "SlotInventory1", "SlotInventory1Enabled"	);
		InventorySlotHotkeyButton1->setRelativePosition(POS_UL, BackgroundInventory, POS_UL, 
			0.069f, -0.0085f);

		InventorySlotHotkeyButton2 = new SlotHotkeyButton(Panel, 0.032f, 0.032f, NULL, -1, "SlotHotkey", "SlotInventory2", "SlotInventory2Enabled"	);
		InventorySlotHotkeyButton2->setRelativePosition(POS_UL, BackgroundInventory, POS_UL, 
			0.029f, -0.0465f);

		InventorySlotHotkeyButton3 = new SlotHotkeyButton(Panel, 0.032f, 0.032f, NULL, -1, "SlotHotkey", "SlotInventory3", "SlotInventory3Enabled"	);
		InventorySlotHotkeyButton3->setRelativePosition(POS_UL, BackgroundInventory, POS_UL, 
			0.069f, -0.0465f);

		InventorySlotHotkeyButton4 = new SlotHotkeyButton(Panel, 0.032f, 0.032f, NULL, -1, "SlotHotkey", "SlotInventory4", "SlotInventory4Enabled"	);
		InventorySlotHotkeyButton4->setRelativePosition(POS_UL, BackgroundInventory, POS_UL, 
			0.029f, -0.0845f);

		InventorySlotHotkeyButton5 = new SlotHotkeyButton(Panel, 0.032f, 0.032f, NULL, -1, "SlotHotkey", "SlotInventory5", "SlotInventory5Enabled"	);
		InventorySlotHotkeyButton5->setRelativePosition(POS_UL, BackgroundInventory, POS_UL, 
			0.069f, -0.0845f);

		BackgroundCommandCard = UISimpleTexture::Create(Panel);
		BackgroundCommandCard->setWidth(0.256f); BackgroundCommandCard->setHeight(0.256f);
		BackgroundCommandCard->fillBitmap("DreamDota3\\Textures\\CommandCardHuman.tga");
		BackgroundCommandCard->setRelativePosition(POS_L, Panel, POS_L, 0.15f, 0.02f);

		CmdSlotHotkeyButton0 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand0", "SlotCommand0Enabled"	);
		CmdSlotHotkeyButton0->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.045f, -0.064f);

		CmdSlotHotkeyButton1 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand1", "SlotCommand1Enabled"	);
		CmdSlotHotkeyButton1->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.08862f, -0.064f);

		CmdSlotHotkeyButton2 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand2", "SlotCommand2Enabled"	);
		CmdSlotHotkeyButton2->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.13224f, -0.064f);

		CmdSlotHotkeyButton3 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand3", "SlotCommand3Enabled"	);
		CmdSlotHotkeyButton3->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.17586f, -0.064f);

		CmdSlotHotkeyButton4 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand4", "SlotCommand4Enabled"	);
		CmdSlotHotkeyButton4->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.045f, -0.107f);

		CmdSlotHotkeyButton5 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand5", "SlotCommand5Enabled"	);
		CmdSlotHotkeyButton5->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.08862f, -0.107f);

		CmdSlotHotkeyButton6 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand6", "SlotCommand6Enabled"	);
		CmdSlotHotkeyButton6->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.13224f, -0.107f);

		CmdSlotHotkeyButton7 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand7", "SlotCommand7Enabled"	);
		CmdSlotHotkeyButton7->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.17586f, -0.107f);

		CmdSlotHotkeyButton8 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand8", "SlotCommand8Enabled"	);
		CmdSlotHotkeyButton8->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.045f, -0.15f);

		CmdSlotHotkeyButton9 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand9", "SlotCommand9Enabled"	);
		CmdSlotHotkeyButton9->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.08862f, -0.15f);

		CmdSlotHotkeyButton10 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand10", "SlotCommand10Enabled"	);
		CmdSlotHotkeyButton10->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.13224f, -0.15f);

		CmdSlotHotkeyButton11 = new SlotHotkeyButton(Panel, 0.038f, 0.038f, NULL, -1, "SlotHotkey", "SlotCommand11", "SlotCommand11Enabled"	);
		CmdSlotHotkeyButton11->setRelativePosition(POS_UL, BackgroundCommandCard, POS_UL, 
			0.17586f, -0.15f);

		//运行一次callback
		CallbackSlotHotkeyCheckBox(CbEnableSlotHotkey, SlotHotkeyEnabled);

		VMProtectEnd();
	}

	void Init(){
		CreateMenuContent();
		MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);
	}

	void Cleanup(){
	}
}