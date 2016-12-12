#include "stdafx.h"
#include <CommCtrl.h>
#pragma comment (lib, "comctl32.lib")
#pragma comment (linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "Exception.h"
#include "DialogLogin.h"
#include "SharedMemory.h"

//Modules
#include "../DreamWarcraft/Profile.h"
#include "Utils.h"
#include "Locale.h"
#include "ResString.h"
#include "LocaleString.h"
#include "Connection.h"
#include "Auth.h"
#include "NTDLL.h"
#include "SystemTools.h"
#include "Injection.h"


#include "DialogInit.h"
#include "Main.h"

#include "HTTP.h"

int DreamMain() {
	VMProtectBeginVirtualization("DreamMain");

	//基本模块初始化 
	SharedMemory::Init();
	Utils::Init();
	Profile_Init(Utils::GetPath(PROFILE_FILENAME));
	Locale::Init();
	ResString::Init();

	int rv;
	bool module_init_success = true;
	srand((DWORD)time(NULL));
	InitCommonControls();

	//初始化模块
	int e = GLOBAL_SETJMP();
	if (e == 0) {
		Connection::Init();
		LocaleString::Init();

		std::wstring classname = StringManager::StringUnicode(STR::WIN_CLASS_NAME);
		CreateMutex(NULL, NULL, classname.c_str());
		if (GetLastError() == ERROR_ALREADY_EXISTS)
			GLOBAL_LONGJMP(EXCEPTION_MULTI_INSTANCE);

		NTDLL::Init();
		SystemTools::Init();
		Auth::Init();
	} else {
		module_init_success = false;
		if (e == EXCEPTION_MULTI_INSTANCE)
			MessageBox(NULL, StringManager::StringUnicode(STR::MULTI_INSTANCE).c_str(), L"", MB_ICONINFORMATION);
		else
			Utils::MessageBoxFormat(NULL, NULL, MB_ICONERROR, L"Initialization failed, error code 0x%08X.", e);
	}

	if (module_init_success)
		rv = Main();

	//模块清理
	Connection::Term();

	Auth::Cleanup();
	SystemTools::Cleanup();
	NTDLL::Cleanup();
	LocaleString::Cleanup();
	Connection::Cleanup();

	//基本模块清理
	ResString::Cleanup();
	Locale::Cleanup();
	Utils::Cleanup();
	SharedMemory::Cleanup();

	VMProtectEnd();
	return rv;
}

int CALLBACK WinMain(
  __in  HINSTANCE hInstance,
  __in  HINSTANCE hPrevInstance,
  __in  LPSTR lpCmdLine,
  __in  int nCmdShow
) 
{
	return DreamMain();
}