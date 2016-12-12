#include "stdafx.h"
#ifndef FOUNDATION_H_INCLUDED
#define FOUNDATION_H_INCLUDED

//#ifdef _VMP
//#pragma comment(lib, "../Release/DreamProtect.lib")
//#else
//#pragma comment(lib, "../Debug/DreamProtect.lib")
//#endif

#include "../DreamAuth2/RSA.h"

extern uint8_t PUBLIC_ENCRYPTED_KEY[RSA_SIZE];
extern char RootPath[MAX_PATH];

void Init (HMODULE selfModule);
void Cleanup();

HMODULE GetSelfModule();
const char* GetSelfPath();
const char* GetSelfFileName();
const char* GetPath(const char* filename);
int GetGameVersion();

#endif