#ifndef DETOURS_HOOK_H_INCLUDED
#define DETOURS_HOOK_H_INCLUDED

#include <windows.h>
#include <cstdio>
#include <detours.h>
#pragma comment(lib, "detours.lib")

bool detours_hook_apply(PVOID *, PVOID);
bool detours_hook_cancel(PVOID *, PVOID);


bool detours_hook_apply(PVOID * ppPointer, PVOID pDetour)
{
	LONG err;
	char buffer[16];
	DetourTransactionBegin();
	if ((err = DetourAttach(ppPointer, pDetour)) != NO_ERROR)
	{
		switch(err)
		{
		case ERROR_INVALID_BLOCK:
			OutputDebugString("DetoursAttach: ERROR_INVALID_BLOCK");
			break;
		case ERROR_INVALID_HANDLE:
			OutputDebugString("DetoursAttach: ERROR_INVALID_HANDLE");
			break;
		case ERROR_INVALID_OPERATION:
			OutputDebugString("DetoursAttach: ERROR_INVALID_OPERATION");
			break;
		case ERROR_NOT_ENOUGH_MEMORY:
			OutputDebugString("DetoursAttach: ERROR_NOT_ENOUGH_MEMORY");
			break;
		default:
			sprintf_s(buffer, 16, "DetoursAttach: ERROR %X", err);
			OutputDebugString(buffer);
		}
	}
	DetourTransactionCommit();

	return err == NO_ERROR;
}

bool detours_hook_cancel(PVOID * ppPointer, PVOID pDetour)
{
	LONG err;
	char buffer[16];
	DetourTransactionBegin();
	if ((err = DetourDetach(ppPointer, pDetour)) != NO_ERROR)
	{
		switch(err)
		{
		case ERROR_INVALID_BLOCK:
			OutputDebugString("DetourDetach: ERROR_INVALID_BLOCK");
			break;
		case ERROR_INVALID_HANDLE:
			OutputDebugString("DetourDetach: ERROR_INVALID_HANDLE");
			break;
		case ERROR_INVALID_OPERATION:
			OutputDebugString("DetourDetach: ERROR_INVALID_OPERATION");
			break;
		case ERROR_NOT_ENOUGH_MEMORY:
			OutputDebugString("DetourDetach: ERROR_NOT_ENOUGH_MEMORY");
			break;
		default:
			sprintf_s(buffer, 16, "DetourDetach: ERROR %X", err);
			OutputDebugString(buffer);
		}
	}
	DetourTransactionCommit();

	return err == NO_ERROR;
}

#endif