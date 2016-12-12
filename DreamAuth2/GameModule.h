#include "stdafx.h"
#ifndef GAMEMODULE_H_
#define GAMEMODULE_H_

#include <SimpleUI\Delegate.h>

namespace GameModule {

enum InjectMethodEnum {
	INJECT_METHOD_AUTO,
	INJECT_METHOD_PASSIVE
};

struct SearchResultType {
	uint32_t version;
	uint32_t game_base;
	DWORD process_id;
	HANDLE process_handle;
	DWORD thread_id;
	void* cgx_device;
	void* cgx_device_vtable;
	HWND win;
	HWND msg_win;
};

extern SimpleUI::Delegate<bool> onActionComplete;

void Start();
void Stop();
void Change(InjectMethodEnum m);
InjectMethodEnum GetCurrentMethod();
const wchar_t* GetLastErrorMessage();
const SearchResultType* GetLastSearchResult();

void Init();
void Cleanup();

} //namespace

#endif