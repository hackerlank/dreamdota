#include "stdafx.h"
#include "Jass.h"
#include "JassTrigger.h"
#include "TriggerEventFilter.h"
#include "Game.h"
#include "Event.h"
#include "Tools.h"

static TriggerEventFilter Filter;
static Event JassTriggerEvent;

void JassTrigger_Filter(uint32_t id) {
	if (IsInGame()) {
		
		if (id > 0 && Filter.filter(id)) {
			JassTriggerEvent.setId(id);
			MainDispatcher()->dispatch(&JassTriggerEvent);
		}
		
	}
}

void JassTrigger_Init() {
	Filter.reset();
}

void JassTrigger_Cleanup() {

}