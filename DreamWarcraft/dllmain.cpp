#include "stdafx.h"
#include "Foundation.h"
#include <process.h>
#include "SystemTools.h"

static HFONT LoadingFont = NULL;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (!SystemTools::Init()) {
			return FALSE;
		}
		HWND win;

		win = FindWindowEx(NULL, NULL, "Warcraft III", NULL);
		HDC dc;
		RECT rect;
		if (win && (dc = GetDC(win)) != NULL && TRUE == GetClientRect(win, &rect)) {
			LoadingFont = CreateFont(
				14, //__in  int nHeight,
				0, //__in  int nWidth,
				0, //__in  int nEscapement,
				0, //  int nOrientation,
				FW_BOLD, //__in  int fnWeight,
				false, //__in  DWORD fdwItalic,
				false, //__in  DWORD fdwUnderline,
				false, //__in  DWORD fdwStrikeOut,
				ANSI_CHARSET, //__in  DWORD fdwCharSet,
				OUT_OUTLINE_PRECIS, //__in  DWORD fdwOutputPrecision,
				CLIP_DEFAULT_PRECIS, //__in  DWORD fdwClipPrecision,
				CLEARTYPE_QUALITY, //__in  DWORD fdwQuality,
				VARIABLE_PITCH, //__in  DWORD fdwPitchAndFamily,
				"Verdana"
			);	
			UINT align = GetTextAlign(dc);
			HFONT font = (HFONT)GetCurrentObject(dc, OBJ_FONT);
			COLORREF color = SetTextColor(dc, RGB(0x2E,0xB0,0xDF));
			int bkmode = SetBkMode(dc, TRANSPARENT);

			SetTextAlign(dc, TA_CENTER | VTA_CENTER);
			SelectObject(dc, LoadingFont);
			
			
			TextOut(dc, (rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2, "Loading DreamWarcraft...", strlen("Loading DreamWarcraft..."));
			
			RedrawWindow(win, NULL, NULL, RDW_UPDATENOW);

			SetBkMode(dc, bkmode);
			SetTextColor(dc, color);
			SetTextAlign(dc, align);
			SelectObject(dc, font);
		}
		Init(hModule);
		break;
	case DLL_THREAD_ATTACH:
		/*
		SystemTools::ThreadInfo ti1;
		if (SystemTools::GetThreadInfo(GetCurrentThreadId(), &ti1)) {
			OutputDebug("[11]Thread Attach. Start Address: 0x%08X\n", ti1.start_address);
		} else 
			OutputDebug("[11]Attach: Unable to get thread info.\n");
		*/
		break;
	case DLL_THREAD_DETACH:
		/*
		SystemTools::ThreadInfo ti2;
		if (SystemTools::GetThreadInfo(GetCurrentThreadId(), &ti2)) {
			OutputDebug("[11]Thread Detach. Start Address: 0x%08X\n", ti2.start_address);
		} else 
			OutputDebug("[11]Detach: Unable to get thread info.\n");
		*/
		break;
	case DLL_PROCESS_DETACH:
		Cleanup();
		if (LoadingFont) {
			DeleteObject(LoadingFont);
			LoadingFont = NULL;
		}
		SystemTools::Cleanup();
		break;
	}
	return TRUE;
}