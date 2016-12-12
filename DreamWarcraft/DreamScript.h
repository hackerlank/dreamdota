#include "stdafx.h"
#ifndef DREAM_SCRIPT_H_INCLUDED_
#define DREAM_SCRIPT_H_INCLUDED_

#include "ScriptProcess.h"

void DreamScript_Init();
void DreamScript_Tick(uint32_t time);
void DreamScript_Cleanup();

ScriptProcess* GetScriptProcess();

#endif