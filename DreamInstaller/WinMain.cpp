#include "stdafx.h"
#include <CommCtrl.h>
#pragma comment (lib, "comctl32.lib")
#pragma comment (linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "Exception.h"
#include "LocaleString.h"
#include "Main.h"

int CALLBACK WinMain(
  __in  HINSTANCE hInstance,
  __in  HINSTANCE hPrevInstance,
  __in  LPSTR lpCmdLine,
  __in  int nCmdShow
) 
{
	int rv = 0;
	try {
		LocaleString::Init();
		
		int argc;
		LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
		rv = Main(argc, argv);

		LocaleString::Cleanup();
	} catch(EEnum e) {
		MessageBox(NULL, EMsg(e), NULL, MB_ICONERROR);
		rv = e;
	}
	return rv;
}