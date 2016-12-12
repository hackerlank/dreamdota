#include "stdafx.h"
#include "AbilityTest.h"
#include "DebugPanel.h"
#include "Event.h"
#include "Game.h"
#include "Unit.h"
#include "Tools.h"
#include "Timer.h"
#include "Ability.h"

Unit* U = NULL;

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 

static void onTimer(Timer* tm) {
	if (U) {
		DebugPanel* d = DefaultDebugPanel;
		war3::CUnit* u = UnitGetObject(U->handleId());
		d->set("Unit", U->name());
		war3::CAbility* ability = NULL;//(war3::CAbility*)AgentFromHash(&(u->abilityHash));
		while (ability) {
			if (IsAbilitySpell(ability)) {
				//¼ÆÊ±Æ÷
				/*
				d->set(IntegerIdToChar(ability->id), "%.2f %.2f %.2f",
					AgentTimerRemainingTimeGet(&(ability->timer58)),
					AgentTimerRemainingTimeGet(&(((war3::CAbilitySpell*)ability)->timer_cooldown)),
					AgentTimerRemainingTimeGet(&(((war3::CAbilitySpell*)ability)->timer_last))
				);
				*/

				
				//FloatMini
				/*
				d->set(IntegerIdToChar(ability->id), "%.2f %.2f %.2f %.2f %.2f", 
					((war3::CAbilitySpell*)ability)->floatMini80.value,
					((war3::CAbilitySpell*)ability)->floatMini88.value,
					((war3::CAbilitySpell*)ability)->floatMini90.value,
					((war3::CAbilitySpell*)ability)->floatMini98.value,
					((war3::CAbilitySpell*)ability)->floatMiniB0.value
				);
				*/	
				
			}
			ability = (war3::CAbility*)AgentFromHash(&(ability->nextAbilityHash));
		}
	}
}

#ifndef _VMP
static void DumpAbilityUIDef(war3::CAbility* ability) {
	war3::AbilityUIDef* uiDef = AbilityUIDefGet(ability);
	uint32_t i;
	OutputDebug("Tooltip(%u):", uiDef->tooltip_levels);
	for (i = 0; i < uiDef->tooltip_levels; ++i) {
		if (uiDef->tooltip_items[i])
			OutputDebug("Level %u: %s", i + 1, uiDef->tooltip_items[i]);
	}

	OutputDebug("Tooltip2(%u):", uiDef->tooltip2_levels);
	for (i = 0; i < uiDef->tooltip2_levels; ++i) {
		if (uiDef->tooltip2_items[i])
			OutputDebug("Level %u: %s", i + 1, uiDef->tooltip2_items[i]);
	}

	OutputDebug("Description(%u):", uiDef->desc_levels);
	for (i = 0; i < uiDef->desc_levels; ++i) {
		OutputDebug("Level %u: %s", i + 1, uiDef->desc_items[i]);
	}

	OutputDebug("Description2(%u):", uiDef->desc2_levels);
	for (i = 0; i < uiDef->desc2_levels; ++i) {
		OutputDebug("Level %u: %s", i + 1, uiDef->desc2_items[i]);
	}

	OutputDebug("Hotkey(%u):", uiDef->hotkey_levels);
	for (i = 0; i < uiDef->hotkey_levels; ++i) {
		OutputDebug("Level %u: %c", i + 1, uiDef->hotkey_items[i]);
	}

	OutputDebug("Hotkey2(%u):", uiDef->hotkey2_levels);
	for (i = 0; i < uiDef->hotkey2_levels; ++i) {
		OutputDebug("Level %u: %c", i + 1, uiDef->hotkey2_items[i]);
	}
}
#endif

static void DumpUnitAbilities() {
	war3::CUnit* u = UnitGetObject(U->handleId());
	war3::CAbility* ability = (war3::CAbility*)AgentFromHash(u->unit_174.post_124d.abilityHash.toHashGroupPtr());
	while (ability) {
		/*
		if (IsAbilitySpell(ability))
			DumpAgentAncestors(AgentTypeIdGet((war3::CAgent*)ability));
		*/

		Ability* a = GetAbility(ability);
#ifndef _VMP
		OutputDebug("Ability: %s ===================================================================", IntegerIdToChar(ability->id));
		OutputDebug("Tooltip: %s", a->tooltip());
		OutputDebug("Description: %s", a->description());
		OutputDebug("Hotkey: %c", a->hotkey());
		OutputDebug("flag2 & 0x80: %u", ability->flag2 & 0x80 ? 1 : 0);
		OutputDebug("isSpell: %s", IsAbilitySpell(ability) ? "true" : "false");
		DumpAbilityUIDef(ability);
#endif


		ability = (war3::CAbility*)AgentFromHash(&(ability->nextAbilityHash));
	}
}

static void onLocalChat (const Event *evt) {
	LocalChatEventData* data = evt->data<LocalChatEventData>();
	const char* text = data->content;
	UnitGroup SelectionGroup;
	OutputScreen(10, text);
	if (text[0] == 'a') {
		OutputScreen(10, "AbilityTest");
		SelectionGroup.clear();
		GroupAddUnitsOfPlayerSelected(&SelectionGroup, PlayerLocal(), false);
		if (SelectionGroup.size()) {
			U = SelectionGroup.getUnit(0);
			DumpUnitAbilities();
		}
	}
}

void AbilityTest_Init() {
	MainDispatcher()->listen(EVENT_LOCAL_CHAT, onLocalChat);
	GetTimer(0.05, onTimer, true)->start();
}

void AbilityTest_Cleanup() {
	U = NULL;
}