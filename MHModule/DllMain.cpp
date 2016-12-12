#pragma once

#include <Windows.h>
#include <VMP.h>
#include "ObjectHookManager.h"
#include "MH.h"
#include "../DreamWarcraft/HideModule.h"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
			VMProtectBeginMutation("DLL_PROCESS_ATTACH");
			HideModule(hinstDLL);
			ObjectHookManager_Init();
			MH::Init();
			VMProtectEnd();
            break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            break;

        case DLL_PROCESS_DETACH:
			VMProtectBeginMutation("DLL_PROCESS_DETACH");
			MH::Cleanup();
			ObjectHookManager_Cleanup();
			VMProtectEnd();
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}