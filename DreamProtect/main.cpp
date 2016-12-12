#include "stdafx.h"
#include "main.h"
#include <Windows.h>
#include <stdio.h>
#include <VMP.h>
HANDLE hXpHandle;
DWORD FakeGameBase;
#define OPTHDROFFSET(a) ((LPVOID)((BYTE *)a + \
                        ((PIMAGE_DOS_HEADER)a)->e_lfanew + \
                        sizeof(DWORD) + \
                        sizeof(IMAGE_FILE_HEADER)))

DWORD WINAPI GetSizeOfFile(LPVOID lpFile)
{
  PIMAGE_OPTIONAL_HEADER poh;
  poh = (PIMAGE_OPTIONAL_HEADER)OPTHDROFFSET(lpFile);
  if (poh != NULL)
	  return poh->SizeOfImage;
  else
	  
    return 0;
}


unsigned int   CRC32[256];

//≥ı ºªØ±Ì
void init_table()
{
	int   i,j;
	unsigned int   crc;
	for(i = 0;i < 256;i++)
	{
		crc = i;
		for(j = 0;j < 8;j++)
		{
			if(crc & 1)
			{
				crc = (crc >> 1) ^ 0xEDB88320;
			}
			else
			{
				crc = crc >> 1;
			}
		}
		CRC32[i] = crc;
	}
}
//crc32
unsigned int  crc32( unsigned char *buf, int len)
{
	unsigned int ret = 0xFFFFFFFF;
	int   i;
	static int init = 0;
	if(!init)
	{
		init_table();
		init = 1;
	}
	for(i = 0; i < len;i++)
	{
		ret = CRC32[((ret & 0xFF) ^ buf[i])] ^ (ret >> 8);
	}
	ret = ~ret;
	return ret;
}

bool XpShell()
{
	VMProtectBeginVirtualization("XpShell");

	bool rv = true;
	DWORD addrGame;
	hXpHandle = GetModuleHandle("11xp.dll");
	if (hXpHandle == NULL) return false;
	char filename[MAX_PATH] = {0};
	GetModuleFileName((HMODULE)hXpHandle,filename,MAX_PATH);
	FILE * f11xp = fopen(filename,"rb");
	fseek(f11xp,0L,SEEK_END);
	DWORD xplen = ftell(f11xp);
	rewind(f11xp);
	char * buffxp = new char[xplen];
	fread(buffxp,1,xplen,f11xp);
	fclose(f11xp);
	DWORD xpcrc = crc32((unsigned char*)buffxp,xplen);
	delete [] buffxp;

	if (xpcrc == 0x8EBCCD64)
	{
		addrGame = 0x93088;

	}
	else if (xpcrc == 0x1a8aed60)
	{
		addrGame = 0x93088;
	}
	else 
		rv = false;
	*(DWORD*)((DWORD)hXpHandle + addrGame) = FakeGameBase;

	VMProtectEnd();

	return rv;
}
void InitDreamProtect()
{
	VMProtectBeginVirtualization("InitDreamProtect");

	char szGame[MAX_PATH]= {0};
	HMODULE GameBase = GetModuleHandle("game.dll");
	GetModuleFileName(GameBase,szGame,MAX_PATH);

	DWORD GameLen = GetSizeOfFile((LPVOID)GameBase);
	FakeGameBase = (DWORD)VirtualAlloc(NULL,GameLen,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE);
	memcpy((LPVOID)FakeGameBase,(LPVOID)GameBase,GameLen);
	memset((LPVOID)FakeGameBase,0,0x1000);
	XpShell();

	VMProtectEnd();
}