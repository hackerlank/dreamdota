#include "stdafx.h"
//#include "Includes.h"
//#include "ManaBar.h"

#pragma comment(linker, "/MERGE:.rdata=.text") 
#pragma comment(linker, "/MERGE:.data=.text") 
#pragma comment(linker, "/MERGE:code=.text") 
#pragma comment(linker,"/SECTION:.text,RWE")
#pragma optimize("gsy", on)

//////////////////////////////////////////////////////////////////////////
#define ADDRESS LPVOID
#define GADDRESS LPVOID
 
GADDRESS g16FF24;
GADDRESS g16FF68;
GADDRESS a16FF64;
GADDRESS a16FF5C;
GADDRESS a16FF58;
GADDRESS a16FF20;
ADDRESS storm401;
GADDRESS a2C7F10;

ADDRESS lpTempVar1; 
ADDRESS lpTempVar2;
ADDRESS gameDllBase;
ADDRESS CStatBarVTable;
ADDRESS a16F06C;
ADDRESS a16F070;
ADDRESS FeatureEnabled;
ADDRESS StatBarRemembered;

BYTE Copy_StatBarVTable[0x80];

char* a164684 = "scaleFactor";

double ScaleConvertConst = 72;
double ScaleConvertConst2 = 0.0005000000237487257;
double ManaBarYOffset = 0.006000000052154064;
double a1649D4 = 0.03000000;
double a1649D0 = 0.004000000;
double a1649CC = 0.3000000;

void __declspec(naked) InitCStatBar()
{
    __asm
    {
		push    ebx
		mov     ebx, a16FF64					// 0x6061B0
		push    edi
		mov     edi, a16FF5C					// 0x605CC0
		push    0
		push    0
		push    0
		xor     edx, edx
		mov     ecx, esi
		call    a16FF58							// 0x359CC0 fastcall (lpObj, 0, 0, 0, 0), Init vtable and so on
		fld     a1649D4
		push    0
		fstp    dword ptr [esi+0x58]			// lpObj->unk58 = 0.03	//sizeX?
		xor     edx, edx
		mov     ecx, esi
		call    edi								// 0x605CC0 fastcall (lpObj, 0, 0)
		fld     a1649D0
		push    0
		fstp    dword ptr [esi+0x5C]			// lpObj->unk5C = 0.004	//sizeY?
		xor     edx, edx
		mov     ecx, esi
		call    edi								// 0x605CC0 fastcall (lpObj, 0, 0)
		fld     a1649CC
		push    1
		sub     esp, 0x8
		fst     dword ptr [esp+0x4]
		xor     edx, edx
		fstp    dword ptr [esp]
		push    1
		mov     ecx, esi
		call    ebx								// 0x6061B0 fastcall (lpObj, 0, 1, 0.3, 0.3, 1)
		mov     eax, dword ptr [esi]
		mov     eax, dword ptr [eax+0x64]
		pop     edi
		xor     edx, edx
		mov     ecx, esi
		pop     ebx
		jmp     eax								// jmp CStatBar vtable 0x64
    }
}

void __declspec(naked) Hook_MallocCStatBar()
{
    __asm
	{
        pop     lpTempVar1			//save call retn address
        pop     eax
        add     eax, eax			//malloc sizeof(CStatBar)*2 (sizeof = 0x158)
        push    eax
        call    storm401			//malloc
        pushad
        mov     lpTempVar2, eax
        mov     esi, lpTempVar2
        add     esi, 0x158			//second CStatBar object
        call    InitCStatBar		//init CStatBar object
        popad
        push    lpTempVar1			//restore call retn address
        retn
    }
}

void __declspec(naked) Hook_Copy_StatBarVTable_0x64()
{
    __asm
	{
        mov     eax, CStatBarVTable
        mov     eax, dword ptr [eax+0x64]
        push    esi
        push    edi
        mov     esi, edx
        mov     edi, ecx
        call    eax
        mov     eax, CStatBarVTable
        mov     eax, dword ptr [eax+0x64]
        lea     ecx, dword ptr [edi+0x158]
        pop     edi
        mov     edx, esi
        pop     esi
        jmp     eax
    }
}
void __declspec(naked) Hook_Copy_StatBarVTable_0x68()
{
    __asm
	{
		mov     eax, CStatBarVTable
		mov     eax, dword ptr [eax+0x68]
		jmp     eax
    }
}

void __declspec(naked) myInitFunc()
{
    __asm
	{
        mov     CStatBarVTable, ecx
        xor     eax, eax
        jmp		L004
        lea     ebx, dword ptr [ebx]
L004:
        mov     dl, byte ptr [eax+ecx]
        mov     byte ptr [eax+Copy_StatBarVTable], dl
        inc     eax
        cmp     eax, 0x80
        jb		L004							//copy all functions (0x80 bytes) of vtable
        push	eax
        push	ebx
        lea     eax, Copy_StatBarVTable
        add     eax, 0x64
        lea     ebx, Hook_Copy_StatBarVTable_0x64
        mov     dword ptr [eax], ebx			//hook Copy_StatBarVTable 0x64
        lea     eax, Copy_StatBarVTable
        add     eax, 0x68
        lea     ebx, Hook_Copy_StatBarVTable_0x68
        mov     dword ptr [eax], ebx			//hook Copy_StatBarVTable 0x68
        pop		ebx
        pop		eax
        retn
    }
}


void __declspec(naked) f001527F0()
{
    __asm
	{
        sub     esp, 0x10
        cmp     FeatureEnabled, 0
        push    edi
        mov     edi, lpTempVar2					//lpUnit
        je		quit							//if (!Enabled) return
        mov     eax, dword ptr [edi+0x50]
        test    eax, eax
        je		quit							//if (!lpUnit->preselectUI(0x50)) return
        cmp     StatBarRemembered, 0
        push    ebx
        mov     ebx, dword ptr [eax+0xC]		// lpUnit->preselectUI(0x50)->statBar(0xC)
        push    esi
        lea     esi, dword ptr [ebx+0x158]		// statBarMana: lpUnit->preselectUI(0x50)->statBar(0xC) + 0x158
        jnz		L017
        mov     ecx, dword ptr [ebx]			// if (!StatBarRemembered) {
        call    myInitFunc						//   myInitFunc (statBar->vTable)
        mov     StatBarRemembered, 1			//   StatBarRemembered = true; }
L017:
        push    0
        lea     eax, dword ptr [esp+0x10]
        push    eax
        xor     edx, edx
        mov     ecx, edi						//ecx = lpUnit
        push	eax
        lea		eax, Copy_StatBarVTable
        mov     dword ptr [ebx], eax			//statBar->vtable = Copy_StatBarVTable
        pop		eax
        call    g16FF24		//0x27AE90 fastcall (lpUnit, 0, &hp, 0)	//UnitGetState
        fldz
        fcomp   dword ptr [esp+0xC]
        fstsw   ax
        test    ah, 1
        je		quit2							//if (hp==0) goto quit2
        push    3
        lea     ecx, dword ptr [esp+0x10]
        push    ecx
        xor     edx, edx
        mov     ecx, edi
        call    g16FF24		//0x27AE90 fastcall (lpUnit, 0, &maxMana, 3)	//UnitGetState
        fldz
        fcomp   dword ptr [esp+0xC]
        fstsw   ax
        test    ah, 5
        jpe		quit2							//if (maxMana==0) goto quit2
        mov     eax, dword ptr [esi]
        mov     eax, dword ptr [eax+0x74]
        push    ebp
        push    edi
        xor     edx, edx
        mov     ecx, esi
        call    eax								//statBar vtable 0x74 (statBarMana, 0, lpUnit)	//OUR HOOK IS HERE ?
        mov     ebx, a16FF64					// 0x6061B0
        mov     ebp, a16FF5C					// 0x605CC0
        lea     ecx, dword ptr [esp+0x1C]
        push    ecx
        lea     edx, dword ptr [esp+0x18]
        mov     ecx, edi
        call    g16FF68		// 0x334180 fastcall (lpUnit, &XYPos, &rv2) //XYPos = 2 floats
        mov     ecx, dword ptr [edi+0x30]		//lpUnit->typeId
        mov     eax, a16FF20
        lea     edx, a164684					//&str_scaleFactor, str_scaleFactor = "scaleFactor"
        call    eax								//0x32C880 fastcall (typeId, &str_scaleFactor) returns UnitUIDef lpUnitUIDef
        test    eax, eax
        jnz		L062
        fld1
        jmp		L063
L062:
        fld     dword ptr [eax+0x54]
L063:
        fstp    dword ptr [esp+0x10]			// scale = lpUnitUIDef ? lpUnitUIDef->scaleFactor(0x54) : 1.0
        push    0
        fld     dword ptr [esp+0x14]
        xor     edx, edx
        fmul    qword ptr [ScaleConvertConst]	// scale *= 72.0
        mov     ecx, esi
        fmul    qword ptr [ScaleConvertConst2]	// scale *= 0.0005000000237487257
        fstp    dword ptr [esi+0x58]			// statBarMana->scale(0x58) = scale
        call    ebp								// 0x605CC0 fastcall (statBarMana, 0, 0)
        fld     dword ptr [esp+0x18]
        push    1
        fsub    qword ptr [ManaBarYOffset]
        sub     esp, 8
        xor     edx, edx
        mov     ecx, esi//statBarMana
        fstp    dword ptr [esp+0x24]			// XYPos.y -= 0.006000000052154064;	//show mana bar below hp bar
        fld     dword ptr [esp+0x24]
        fstp    dword ptr [esp+0x4]
        fld     dword ptr [esp+0x20]
        fstp    dword ptr [esp]
        push    1
        call    ebx								// 0x6061B0 fastcall (statBarMana, 0, 1, XYPos.x, XYPos.y, 1)
        mov     eax, dword ptr [esi]
        mov     eax, dword ptr [eax+0x68]
        xor     edx, edx
        mov     ecx, esi
        call    eax								// statBar vtable 0x68 fastcall (statBarMana, 0)
        pop     ebp
quit2:
        pop     esi
        pop     ebx
quit:
        pop     edi
        add     esp, 0x10
        retn
	}
	//statBar + 0x130 = valuePercent
}
void __declspec(naked) Hook_Refresh()
{
    __asm
	{
        pushad
        mov     lpTempVar2, ecx			//lpTempVar2 = lpUnit
        call    f001527F0
        popad
        mov     eax, a2C7F10
        jmp     eax						//jmp 0x2C74B0 (original call)
    }
}


ADDRESS MallocCStatBar;
ADDRESS a6F37A968;
void Hook(ADDRESS lpBase)
{
    DWORD old;
    VirtualProtect(MallocCStatBar, 5, PAGE_EXECUTE_READWRITE, &old);
    VirtualProtect(a6F37A968, 5, PAGE_EXECUTE_READWRITE, &old);
    
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(MallocCStatBar);
        *p = 0xe8;
        p += 5;
        int X = (int)Hook_MallocCStatBar - (int)p;
        p -= 5;
        *reinterpret_cast<DWORD*>(p+1) = X;
    }
    {
        unsigned char* p = reinterpret_cast<unsigned char*>(a6F37A968);
        *p = 0xe8;
        p += 5;
        int X = (int)Hook_Refresh - (int)p;
        p -= 5;
        *reinterpret_cast<DWORD*>(p+1) = X;
    }
}

BOOL WINAPI InjectManabar(DWORD gameBase)
{
    *(int*)&FeatureEnabled = 1;
    HMODULE hMod = GetModuleHandle("storm.dll");
    storm401 = (ADDRESS)GetProcAddress(hMod, (LPCSTR)0x191);//storm 401 SMemAlloc
    gameDllBase = (void*) gameBase;//game.dll base

										//1.26		//1.25
    *(int*)&g16FF24 = (int)gameDllBase + 0x27AE90;//0x27AC60;
    *(int*)&g16FF68 = (int)gameDllBase + 0x334180;//0x333F50;
    *(int*)&a16FF64 = (int)gameDllBase + 0x6061B0;//0x605F80;
    *(int*)&a16FF5C = (int)gameDllBase + 0x605CC0;//0x605A90;
    *(int*)&a16FF58 = (int)gameDllBase + 0x359CC0;//0x359A90;
    *(int*)&a16FF20 = (int)gameDllBase + 0x32C880;//0x32C650;
    *(int*)&a2C7F10 = (int)gameDllBase + 0x2C74B0;//0x2C7280;

    *(int*)&MallocCStatBar = (int)gameDllBase + 0x379AE3;//0x3798B3;
    *(int*)&a6F37A968 = (int)gameDllBase + 0x379EE8;//0x379CB8;

    Hook(gameDllBase);
    return TRUE;
}