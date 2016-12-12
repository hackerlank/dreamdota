#include "stdafx.h"
#include "CursorLock.h"
#include "Event.h"
#include "Game.h"
#include "Tools.h"

static bool Enable;
static RECT OldRect;
static RECT LockRect;
static POINT Point;

typedef LRESULT (__fastcall *WAR3WNDPROC)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

WAR3WNDPROC OldWndProc;

LRESULT __fastcall DetourWindowProc(
  HWND hwnd,
  UINT uMsg,
  WPARAM wParam,
  LPARAM lParam
) 
{
	return OldWndProc(hwnd, uMsg, wParam, lParam);
}

void CursorLock_Init() {
	Enable = false;
	OldWndProc = GxDeviceGet()->wndProc;
	GxDeviceGet()->wndProc = &(DetourWindowProc);
	memset(&OldRect, 0, sizeof(RECT));
	memset(&LockRect, 0, sizeof(RECT));
	memset(&Point, 0, sizeof(POINT));
}

void CursorLock_Update() {

}

void CursorLock_Cleanup() {
	GxDeviceGet()->wndProc = OldWndProc;
}

void LockCursor() {
	HWND hwnd = GxDeviceGet()->hwnd;
	if (GetClipCursor(&OldRect) && GetClientRect(hwnd, &LockRect) && ClientToScreen(hwnd, &Point)) {
		LockRect.left += Point.x;
		LockRect.right += Point.x;
		LockRect.top += Point.y;
		LockRect.bottom += Point.y;
		ClipCursor(&LockRect);
	}
}

void UnlockCursor() {
	if (OldRect.right > 0) {
		ClipCursor(&OldRect);
	} else {
		OldRect.left = OldRect.right = 0;
	}
}