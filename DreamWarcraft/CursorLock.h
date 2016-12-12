#include "stdafx.h"
#ifndef CURSOR_LOCK_H_INCLUDED_
#define CURSOR_LOCK_H_INCLUDED_

void CursorLock_Init();
void CursorLock_Update();
void CursorLock_Cleanup();
void LockCursor();
void UnlockCursor();

#endif