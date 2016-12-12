#include "stdafx.h"
#include "War3Window.h"
#include "Event.h"
#include "Game.h"
#include "Tools.h"
#include "Input.h"
#include "Offsets.h"
#include "GameEventObserver.h"
#include "UI.h"
#include "ObjectHookManager.h"
#include "Version.h"
#include "Profile.h"
#include "Missile.h"
#include "IUIObject.h"
#include "Timer.h"
#include <VMP.h>

static const uint32_t MAX_WNDPROC = 32;
static uint32_t WndProcCount = 0;
static CustomWndProc WndProcs[MAX_WNDPROC] = {0};

static void CallWndProcs(HWND win, UINT message, WPARAM wParam, LPARAM lParam) {
	for (uint32_t i = 0; i < MAX_WNDPROC && WndProcs[i]; ++i) {
		if (WndProcs[i](win, message, wParam, lParam))
			break;
	}
}

void AddWindowProc(CustomWndProc proc) {
	if (WndProcCount < MAX_WNDPROC)
		WndProcs[WndProcCount++] = proc;
}

namespace DEVICE_TYPE {
	static const int D3D = 1;
	static const int OpenGL = 2;
}

static int DeviceType = 0;
static war3::CGxDevice *DeviceObject = NULL;

static bool Locked;
static RECT OldRect;
static RECT LockRect;
static RECT ClientAreaScreenRect;
static POINT Point;
static RECT OldWindowRect;
static RECT OldClientRect;
static LONG DefaultWindowStyle;
static LONG DefaultWindowExStyle;
static RECT TaskBarRect;

static bool EnableImprovedWindow;
static bool Fullscreen;
static float WidthRatio = 1.0f;
//static bool KeepRatio;
HWND Hwnd = NULL;

HWND GetWar3Window() {return Hwnd;}

typedef LRESULT (__fastcall *WAR3WNDPROC)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

WAR3WNDPROC OldWndProc;

bool UpdateClipCursor();
void UpdateFullscreen(WORD width = 0, WORD height = 0);
void HookReady();

void D3DSetStageSize(float width, float height) {
	war3::CGxDeviceD3d * device = reinterpret_cast<war3::CGxDeviceD3d*>(DeviceObject);
	device->unk_6C0 = 0.f;
	device->unk_6C4 = 0.f;
	device->windowWidth = static_cast<float>(width);
	device->windowHeight = static_cast<float>(height);
	device->unk_6D0 = 1;
	/*
	if (*reinterpret_cast<DWORD*>(0x6FA9E7A0))
		*reinterpret_cast<DWORD*>(Offset(GLOBAL_UPDATE_STAGE_SIZE)) = MAKELPARAM(static_cast<WORD>(width), static_cast<WORD>(height));
	*/
}

void RefreshUICallback(Timer *tm)
{
	UI_Refresh();
}

static POINTS LastMousePoint, MousePoint;
LRESULT __fastcall DetourWindowProc(
  HWND hwnd,
  UINT uMsg,
  WPARAM wParam,
  LPARAM lParam
) 
{
	static bool Inited = false;
	RECT orgRect;

	if (!Inited) {
		VMProtectBeginVirtualization("War3Window_DetourWindowProc");
		//Sleep(10000);
		if (TlsGetValue(GameTlsIndexGet())) {
			Inited = true;
			if (!Hwnd) {
				Hwnd = hwnd;
				HookReady();
			}
			if (hwnd != Hwnd) {
				Hwnd = hwnd;
				HookReady();
			}
		}
		VMProtectEnd();
	} else if (EnableImprovedWindow && Inited) {
		switch(uMsg) {
		case WM_SYSCOMMAND:
			if (wParam == SC_KEYMENU)
				return 0;
			break;
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			break;
		case WM_ACTIVATEAPP:
			if (wParam == TRUE) {
				if (Locked) {
					UpdateClipCursor();
				}	
				if (Fullscreen) {
					GetWindowRect(Hwnd, &orgRect);
					SetWindowPos(Hwnd, HWND_TOPMOST, orgRect.left, orgRect.top, orgRect.right - orgRect.left, orgRect.bottom - orgRect.top, SWP_SHOWWINDOW);
				}
			} else {
				ClipCursor(&OldRect);
				if (Fullscreen) {
					GetWindowRect(Hwnd, &orgRect);
					SetWindowPos(Hwnd, HWND_NOTOPMOST, orgRect.left, orgRect.top, orgRect.right - orgRect.left, orgRect.bottom - orgRect.top, SWP_NOACTIVATE);
				}
			}
			break;
		case WM_SIZING:
			break;
		case WM_SIZE:
			if (!Fullscreen && (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)) {
				ProfileSetInt("Misc", "WindowWidth", (int)LOWORD(lParam));
				ProfileSetInt("Misc", "WindowHeight", (int)HIWORD(lParam));
			}
			if (Locked) {
				UpdateClipCursor();
			}

			WidthRatio = ((float)LOWORD(lParam) / (float)HIWORD(lParam)) / (4.f/3.f);
			//OutputScreen(1, "widthratio = %.3f", WidthRatio);

			GetTimer(0.05, RefreshUICallback)->start();
			break;
		case WM_MOVE:
			if (!Fullscreen) {
				GetWindowRect(Hwnd, &orgRect);
				ProfileSetInt("Misc", "WindowX", (int)LOWORD(lParam));
				ProfileSetInt("Misc", "WindowY", (int)HIWORD(lParam));
			}
			if (Locked) {
				UpdateClipCursor();
			}
			break;
		case WM_DISPLAYCHANGE:
			if (Fullscreen)
				UpdateFullscreen();
			break;
		}
	}
	//TODO 把上面的switch换成不同的callback
	CallWndProcs(hwnd, uMsg, wParam, lParam);
	return OldWndProc(hwnd, uMsg, wParam, lParam);
}

__declspec(noinline) void War3Window_Init() {
	//检测设备类型
	DeviceObject = GxDeviceGet();
	DeviceType = RTTIClassNameGet(DeviceObject)[9] == 'D' ? DEVICE_TYPE::D3D : DEVICE_TYPE::OpenGL;
#ifdef _DEBUG
	OutputDebug("DeviceObject 0x%08X vtable = 0x%08X, window = 0x%08X\n", DeviceObject, VTBL(DeviceObject), aero::offset_element_get<void*>(DeviceObject, 0x57C));
	HWND win = aero::offset_element_get<HWND>(DeviceObject, 0x578);	
	//GetObjectHookManager()->analysis(DeviceObject, 45);
#endif
	memset(&OldRect, 0, sizeof(RECT));
	memset(&LockRect, 0, sizeof(RECT));
	memset(&ClientAreaScreenRect, 0, sizeof(RECT));
	memset(&Point, 0, sizeof(POINT));
	GetClipCursor(&OldRect);

	VMProtectBeginVirtualization("War3Window_Hook_WNDPROC_HOOK_GXDEVICED3D");
	Hwnd = DeviceObject->vtable->GetDeviceWindow();
	OldWndProc = reinterpret_cast<war3::CGxDeviceD3d*>(DeviceObject)->wndProc;
	reinterpret_cast<war3::CGxDeviceD3d*>(DeviceObject)->wndProc = &(DetourWindowProc);
	VMProtectEnd();
}

__declspec(noinline) void War3Window_Cleanup() {
	VMProtectBeginVirtualization("War3Window_Cleanup");
	if (!IsBadWritePtr(DeviceObject, 4))
		reinterpret_cast<war3::CGxDeviceD3d*>(DeviceObject)->wndProc = OldWndProc;
	Missile_Cleanup();
	GameEventObserver_Cleanup();
	VMProtectEnd();
}

uint32_t __fastcall MainMenuInitButtonHook(void* t, uint32_t dummy, uint32_t arg1, uint32_t arg2) {
	VMProtectBeginVirtualization("MainMenuInitButtonHook");
	uint32_t rv = aero::generic_this_call<uint32_t>(
		GetObjectHookManager()->getOrignal(t, 0xDC),
		t,
		arg1,
		arg2
	);
	war3::CTextFrame* versionFrame = aero::offset_element_get<war3::CTextFrame*>(t, 0x24C);
	if (versionFrame) {
		char buffer[65];
#ifdef _BETA
		sprintf_s(buffer, "%s|n|cFFFFCC00DreamWarcraft %u.%02u BETA %04u|r", versionFrame->text, VERSION.main, VERSION.release, VERSION.revision);
#else
		sprintf_s(buffer, "%s|n|cFFFFCC00DreamWarcraft %u.%02u.%u rev %04u|r", versionFrame->text, VERSION.main, VERSION.release, VERSION.build, VERSION.revision);
#endif
		TextFrame::setText(versionFrame, buffer);
	}
	GetObjectHookManager()->restore(t);
	VMProtectEnd();
	return rv;
}

void* OrgMainMenuInit;
void* __fastcall MainMenuInitHook(void* t, uint32_t dummy, uint32_t arg) {
	VMProtectBeginVirtualization("MainMenuInitHook");
	void* rv = aero::generic_this_call<void*>(
		OrgMainMenuInit,
		t,
		arg
	);
	if (rv) {
		GetObjectHookManager()->replace(rv, 57);
		GetObjectHookManager()->apply(rv, 0xDC, MainMenuInitButtonHook);
	}
	VMProtectEnd();
	return rv;
}

//当确保Hook成功时调用
void HookReady() {
	VMProtectBeginVirtualization("HookReady");
	GameEventObserver_Init();
	Missile_Init();

	EnableImprovedWindow = ProfileFetchInt("Misc", "EnableImprovedWindow", 1) >= 1;
	if (EnableImprovedWindow) {
		Locked = ProfileFetchInt("Misc", "LockMouse", 1) >= 1;
		Fullscreen = ProfileFetchInt("Misc", "WindowMaximized", 0) >= 1;
		//KeepRatio = ProfileFetchInt("Misc", "WindowKeepRatio", 0) >= 1;//true;

		DefaultWindowStyle = GetWindowLong(Hwnd, GWL_STYLE);
		DefaultWindowExStyle = GetWindowLong(Hwnd, GWL_EXSTYLE);

		//恢复大小
		HDC windowHDC = GetDC(Hwnd);
		WORD screenWidth  = GetDeviceCaps(windowHDC, HORZRES);
		WORD screenHeight = GetDeviceCaps(windowHDC, VERTRES);
		WORD windowWidth = ProfileFetchInt("Misc", "WindowWidth", 1024);
		WORD windowHeight = ProfileFetchInt("Misc", "WindowHeight", 768);

		windowHeight = min(windowHeight, screenHeight);
		windowWidth = min(windowWidth, screenWidth);

		WORD windowX = ProfileFetchInt("Misc", "WindowX", (screenWidth - windowWidth) / 2);
		WORD windowY = ProfileFetchInt("Misc", "WindowY", (screenHeight - windowHeight) / 2);

		windowX = max(0, min(windowX, screenWidth - windowWidth));
		windowY = max(0, min(windowY, screenHeight - windowHeight));
		//FIXME 修复bug
		/*
		if (windowWidth && windowHeight) {	
			if (DeviceType == DEVICE_TYPE::D3D)
				D3DSetStageSize(static_cast<float>(OldClientRect.right), static_cast<float>(OldClientRect.bottom));
			SetWindowLongPtr(Hwnd, GWL_EXSTYLE, DefaultWindowExStyle);
			SetWindowLongPtr(Hwnd, GWL_STYLE, DefaultWindowStyle);
			SetWindowPos(Hwnd, 0, windowX, windowY, windowWidth, windowHeight, 0);
		}
		*/

		if (Fullscreen) {
			GetWindowRect(Hwnd, &OldWindowRect);
			GetClientRect(Hwnd, &OldClientRect);
			UpdateFullscreen();
		}

		if (Locked) {
			UpdateClipCursor();
		}
	}

	//Hook 主菜单初始化函数
	war3::FrameNameHashNode* hashNode = FrameNameHashNodeGet("MainMenuFrame");
	if (hashNode) {
		OrgMainMenuInit = hashNode->initFunction;
		hashNode->initFunction = MainMenuInitHook;
		if (GlueMgrObjectGet()->currentFrame) {
			war3::CTextFrame* versionFrame = aero::offset_element_get<war3::CTextFrame*>(GlueMgrObjectGet()->currentFrame, 0x24C);
			const char* mode = ProfileFetchBool("Misc", "SafeMode", false) ? "(Safe Mode)" : "";
			if (versionFrame) {
				char buffer[100];
#ifdef _BETA
				sprintf_s(buffer, 100, "%s|n|cFFFFCC00DreamWarcraft%s %u.%02u BETA %04u|r", versionFrame->text, mode, VERSION.main, VERSION.release, VERSION.revision);
#else
				sprintf_s(buffer, 100, "%s|n|cFFFFCC00DreamWarcraft%s %u.%02u.%u rev %04u|r", versionFrame->text, mode, VERSION.main, VERSION.release, VERSION.build, VERSION.revision);
#endif
				TextFrame::setText(versionFrame, buffer);
			}
		}
	}

	VMProtectEnd();
}

void UpdateFullscreen(WORD width, WORD height) {
	HDC windowHDC = GetDC(Hwnd);
	WORD screenWidth  = width ? width : GetDeviceCaps(windowHDC, HORZRES);
	WORD screenHeight = height ? height : GetDeviceCaps(windowHDC, VERTRES);
	WORD windowWidth = screenWidth;
	WORD windowHeight = screenHeight;
	//0.8 x 0.6
	if (
		ProfileFetchInt("Misc", "WindowKeepRatio", 0) >= 1//KeepRatio
		) {
		if (windowWidth > windowHeight) {
			windowWidth = min (windowWidth, static_cast<WORD>(static_cast<double>(windowHeight) / .6 * .8));
			windowHeight = min (windowHeight, static_cast<WORD>(static_cast<double>(windowWidth) / .8 * .6));
		}
	}
	
	if (DeviceType == DEVICE_TYPE::D3D)
		D3DSetStageSize(static_cast<float>(screenWidth), static_cast<float>(screenHeight));
		
	SetWindowLongPtr(Hwnd, GWL_EXSTYLE, WS_EX_APPWINDOW);
	SetWindowLongPtr(Hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	SetWindowPos(Hwnd, HWND_TOPMOST, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2, windowWidth, windowHeight, SWP_SHOWWINDOW);
}

bool UpdateClipCursor() {
	Point.x = Point.y = 0;
	if (GetClientRect(Hwnd, &LockRect) && ClientToScreen(Hwnd, &Point)) {
		LockRect.left += Point.x;
		LockRect.right += Point.x;
		LockRect.top += Point.y;
		LockRect.bottom += Point.y;
		ClipCursor(&LockRect);
		return true;
	} else
		return false;
}

void LockCursor() {
	if (Locked)
		return;

	
	if (UpdateClipCursor()) {
		Locked = true;
	}
}

void UnlockCursor() {
	if (!Locked)
		return;

	ClipCursor(&OldRect);
	Locked = false;
}

bool ToggleCursorLock() {
	if (!Locked)
		LockCursor();
	else
		UnlockCursor();
	return Locked;
}

void EnableFullscreen() {
	if (!Fullscreen) {
		Fullscreen = true;
		GetWindowRect(Hwnd, &OldWindowRect);
		GetClientRect(Hwnd, &OldClientRect);
		UpdateFullscreen();
	}
}

void DisableFullscreen() {
	if (Fullscreen) {
		HDC windowHDC = GetDC(Hwnd);
		WORD screenWidth  = GetDeviceCaps(windowHDC, HORZRES);
		WORD screenHeight = GetDeviceCaps(windowHDC, VERTRES);
		WORD windowWidth = static_cast<WORD>(OldWindowRect.right - OldWindowRect.left);
		WORD windowHeight = static_cast<WORD>(OldWindowRect.bottom - OldWindowRect.top);
		windowWidth = static_cast<WORD>(OldWindowRect.right - OldWindowRect.left);
		windowHeight = static_cast<WORD>(OldWindowRect.bottom - OldWindowRect.top);
		if (DeviceType == DEVICE_TYPE::D3D)
			D3DSetStageSize(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
		SetWindowLongPtr(Hwnd, GWL_EXSTYLE, DefaultWindowExStyle);
		SetWindowLongPtr(Hwnd, GWL_STYLE, DefaultWindowStyle);
		if (ProfileGetBool("Misc", "WindowKeepRatio", true))
		{
			windowWidth = (windowWidth + windowHeight * 4.f / 3.f) / 2;
			windowHeight = windowWidth * 3.f / 4.f;
			SetWindowPos(Hwnd, HWND_NOTOPMOST, screenWidth/2 - windowWidth/2, screenHeight/2 - windowHeight/2, windowWidth, windowHeight, 0);
		}
		else
		{
			SetWindowPos(Hwnd, HWND_NOTOPMOST, OldWindowRect.left, OldWindowRect.top, windowWidth, windowHeight, 0);
		}
		Fullscreen = false;
	}
}

bool ToggleFullscreen() {
	if (Fullscreen) {
		DisableFullscreen();
	} else {
		EnableFullscreen();
	}
	return Fullscreen;
}

bool IsFullscreen() {
	return Fullscreen;
}

float War3WindowWidthRatio()
{
	//TODO
	return WidthRatio ? WidthRatio : 1.f;
}
