#include "stdafx.h"
#ifndef CURSOR_LOCK_H_INCLUDED_
#define CURSOR_LOCK_H_INCLUDED_

typedef bool (*CustomWndProc)(HWND win, UINT message, WPARAM wParam, LPARAM lParam);

void AddWindowProc(CustomWndProc proc);
HWND GetWar3Window();
void War3Window_Init();
void War3Window_Cleanup();
void LockCursor();
void UnlockCursor();
bool ToggleCursorLock();
void EnableFullscreen();
void DisableFullscreen();
bool ToggleFullscreen();
bool IsFullscreen();
bool KeyIsDown(const uint32_t keyCode);

float War3WindowWidthRatio();
#endif