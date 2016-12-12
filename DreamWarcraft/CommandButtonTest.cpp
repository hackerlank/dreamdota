#include "stdafx.h"
#include "CommandButtonTest.h"

#include "stdafx.h"
#include "AbilityTest.h"
#include "DebugPanel.h"
#include "Event.h"
#include "Game.h"
#include "Unit.h"
#include "Tools.h"
#include "Timer.h"
#include "Input.h"

static void onLocalChat (const Event *evt) {
	LocalChatEventData* data = evt->data<LocalChatEventData>();
	const char* text = data->content;
	if (text[0] == 'c') {
		war3::CCommandButton* btn = (war3::CCommandButton*)PositionGetButton(GetMousePosition());
		if (btn) {
			OutputScreen(10, "Data: 0x%X object id: %s, type: %s", 
				btn->commandButtonData,
				IntegerIdToChar(btn->commandButtonData->abilityId), 
				RTTIClassNameGet(btn->commandButtonData->ability)
			);
			OutputScreen(10, "Hotkey: %c", btn->commandButtonData->hotkey);
			OutputScreen(10, btn->commandButtonData->iconPath);
			OutputScreen(10, "ManaCost: %u", btn->commandButtonData->manaCost);
			OutputScreen(10, btn->commandButtonData->title);
			OutputScreen(10, btn->commandButtonData->tooltip);
		}
	}
}

void CommandButtonTest_Init() {
	MainDispatcher()->listen(EVENT_LOCAL_CHAT, onLocalChat);
}

void CommandButtonTest_Cleanup() {
	
}