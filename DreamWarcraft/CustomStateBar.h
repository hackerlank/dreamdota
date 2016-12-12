#ifndef CUSTOMSTATEBAR_H_
#define CUSTOMSTATEBAR_H_
#include "GameStructs.h"

void TimedUpdateUnitStatBarReport (war3::CStatBar *hpBar, float param);
void UpdateUnitStatBarReport (war3::CUnit *u);
void ShowUnitStatBarReport (war3::CStatBar *hpBar, bool show);

void CustomStatBar_Init();
void CustomStatBar_Cleanup();

#endif