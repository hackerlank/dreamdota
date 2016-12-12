#include "stdafx.h"
#ifndef UNIT_WALKER_H_INCLUDED
#define UNIT_WALKER_H_INCLUDED

const double UNIT_WALKER_INTERVAL = 0.05;

class Unit;
class UnitWalker;
typedef void (*UnitWalkerCallbackType)(Unit* unit);

UnitWalker* GetUnitWalker(UnitWalkerCallbackType callback);
void DestroyUnitWalker(UnitWalker* walker);

void UnitWalker_Init();
void UnitWalker_Cleanup();

#endif