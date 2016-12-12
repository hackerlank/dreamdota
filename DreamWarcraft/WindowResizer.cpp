#include "stdafx.h"
#include "WindowResizer.h"
#include "War3Window.h"
#include "Input.h"
#include "KeyCode.h"
#include "Profile.h"

namespace WindowResizer {
	static bool Inited = false;
	
	static uint32_t HANDLE_SIZE = 100;

	static bool Active = false;
	static HWND War3Win = NULL;
	static bool InDragArea = false;
	static POINT StartPt;
	static POINT CursorPt;
	static RECT WindowRect;
	static RECT CRect;
	
	enum HotAreaEnum {
		NONE,
		MOVE,
		RESIZE
	} Area = NONE;

	static HotAreaEnum CheckHotArea() {
		RECT& r = WindowRect;
		POINT& p = CursorPt;

		if (p.x >= r.right - HANDLE_SIZE && p.x <= r.right && p.y >= r.bottom - HANDLE_SIZE && p.y <= r.bottom) {
			Area = RESIZE;
		} else if (p.x >= r.left && p.x <= r.right && p.y >= r.top && p.y <= r.top + HANDLE_SIZE) {
			Area = MOVE;
		} else
			Area = NONE;

		return Area;
	}

	static bool WantAction(WPARAM w) {
		return (w & MK_CONTROL) > 0;
	}

	static void StartDrag() {
		RECT& r = WindowRect;
		POINT& p = CursorPt;
		StartPt.x = r.right - p.x;
		StartPt.y = r.bottom - p.y;
		LockCursor();
		Active = true;
	}

	static void StopDrag() {
		Active = false;
		if (ProfileFetchInt("Misc", "LockMouse", 1) < 1) 
			UnlockCursor();
	}

	static void Update() {
		if (Active) {
			RECT& r = WindowRect;
			POINT& p = CursorPt;
			if (Area == RESIZE) {
				if (KeyIsDown(KEYCODE::KEY_SHIFT)) {
					float f = ((float)(r.bottom - r.top) / (float)(r.right - r.left));
					float w = (float)((p.x - r.left) + StartPt.x);
					float h = w * f;
					SetWindowPos(War3Win, NULL, r.left, r.top, (int)w, (int)h, NULL);
				} else
					SetWindowPos(War3Win, NULL, r.left, r.top, (p.x - r.left) + StartPt.x, (p.y - r.top) + StartPt.y, NULL);
			} else if (Area == MOVE) {
				SetWindowPos(War3Win, NULL, p.x - ((r.right - r.left) - StartPt.x), p.y - ((r.bottom - r.top) - StartPt.y), r.right - r.left, r.bottom - r.top, NULL);
			}
		}
	}

	static bool WndProc(HWND win, UINT message, WPARAM wParam, LPARAM lParam) {
		if (!War3Win)
			War3Win = win;
		switch (message) {
		case WM_LBUTTONDOWN:
			if (WantAction(wParam) && Area != NONE)
				StartDrag();
			break;
		case WM_LBUTTONUP:
			StopDrag();
			break;
		case WM_ACTIVATEAPP:
			if (wParam == FALSE)
				StopDrag();
			break;
		case WM_MOUSEMOVE:
			GetWindowRect(War3Win, &WindowRect);
			GetCursorPos(&CursorPt);
			if (Active) {
				Update();
			} else
				CheckHotArea();
			break;
		}
		return false;
	}

	void Init() {
		VMProtectBeginVirtualization("WindowResizer::Init");
		AddWindowProc(WndProc);
		Inited = true;
		VMProtectEnd();
	}

	void Cleanup() {
		Inited = false;
	}
}