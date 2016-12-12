#ifndef UNITCREATION_H_INCLUDED_
#define UNITCREATION_H_INCLUDED_

void UnitCreation_Update(war3::CUnit *u);
void UnitDamaged_Update(war3::CUnit *eventUnit, war3::CUnit *damageSourceUnit, uint32_t type, float damage, float damageRaw);

#endif