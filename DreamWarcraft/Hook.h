#ifndef HOOK_H_INCLUDED_
#define HOOK_H_INCLUDED_

#include "GameStructs.h"

void StatBarCallVtable0x34(war3::CStatBar *obj, float param);
void StatBarCallVtable0x64(war3::CStatBar *obj);
void StatBarCallVtable0x74(war3::CStatBar *obj, war3::CUnit *u);

void Hook_Init ();

#endif