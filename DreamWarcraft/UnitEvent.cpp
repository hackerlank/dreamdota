#include "stdafx.h"
#include "GameStructs.h"
#include "Event.h"
#include "Tools.h"
#include "Game.h"

static Event UnitCreationEventObject;

void UnitCreation_Update(war3::CUnit *u){
	if (!u) return;
	UnitCreationEventObject.setId(EVENT_UNIT_CREATED);
	UnitCreationEventData data;

	data.createdUnit = ObjectToHandle(u);
	if (data.createdUnit) {
		UnitCreationEventObject.setData<UnitCreationEventData> (&data);
		MainDispatcher()->dispatch(&UnitCreationEventObject);
	}
}


static Event UnitDamagedEventObject;

void UnitDamaged_Update(war3::CUnit *eventUnit, war3::CUnit *damageSourceUnit, uint32_t type, float damage, float damageRaw){
	if (!eventUnit) return;
	UnitDamagedEventObject.setId(EVENT_UNIT_RECEIVE_DAMAGE);
	UnitDamagedEventData data;

	data.source = ObjectToHandle(damageSourceUnit);
	data.target = ObjectToHandle(eventUnit);
	if (data.target) {
		data.isSpell = (type==0);
		data.damage = damage;
		data.damageRaw = damageRaw;
	
		UnitDamagedEventObject.setData<UnitDamagedEventData> (&data);
		MainDispatcher()->dispatch(&UnitDamagedEventObject);
	}
}