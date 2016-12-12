#include <Windows.h>
#include <VMP.h>
#include <list>
#include <fp_call.h>
#include "MH.h"
#include "GameDef.h"
#include "ObjectHookManager.h"

#include <cstdio>
int OutputDebug(const char *format, ...) {
		char buffer[256];
		int rv;
		va_list args;
		va_start(args, format);
		rv = vsprintf_s(buffer, 256, format, args);
		va_end(args);

		OutputDebugStringA(buffer);
		return rv;
}

namespace MH {
	static GameDef::VersionOffsetType* GameInfo;
	static std::list<void*> FreeList;

	inline void** VTBL(void* obj) {
		return *reinterpret_cast<void***>(obj);
	}

	static bool MapHack_MainMapShowUnit = true;
	static bool MapHack_MainMapRemoveFog = true;
	static bool MapHack_MiniMapShowUnit = true;

	static void* OrgUnitGenerate;
	static void** OrgUnitVtable;
	static void* FakeUnitVtableData[1 + 118];
	static void** FakeUnitVtable = &(FakeUnitVtableData[1]);
	static void *VisStateCheckCall;
	void __declspec(naked) Game_Fake_0x3A1520 (){
		__asm{
			SUB ESP,0x8
			MOV EAX,DWORD PTR SS:[ESP+0x10]
			PUSH EBX
			PUSH EBP
			MOV WORD PTR DS:[EAX],0
			MOV EBP,DWORD PTR SS:[ESP+0x20]
			PUSH ESI
			MOV ESI,DWORD PTR SS:[ESP+0x18]
			PUSH EDI
			MOV EDI,ECX
			MOV ECX,DWORD PTR SS:[ESP+0x24]
			MOV WORD PTR DS:[ECX],0
			MOV EDX,DWORD PTR DS:[EDI+0x34]
			MOV ECX,DWORD PTR DS:[EDX+0x68]
			MOV EAX,DWORD PTR DS:[ESI+0x4]
			SHL EAX,CL
			MOV ECX,DWORD PTR DS:[EDX+0x30]
			MOV EDX,DWORD PTR DS:[EDX+0x2C]
			MOV EBX,1
			ADD EAX,DWORD PTR DS:[ESI]
			MOV DWORD PTR SS:[ESP+0x1C],0xC
			MOV CX,WORD PTR DS:[ECX+EAX*2]
			MOV AX,WORD PTR DS:[EDX+EAX*2]
			OR CX,0x0F000
			MOVZX ECX,CX
			AND AX,0x0FFF
			MOV DWORD PTR SS:[ESP+0x14],ECX
			MOVZX ECX,AX
			MOV DWORD PTR SS:[ESP+0x10],ECX
			ADD EBP,0x4
	L030:
			MOVZX EAX,WORD PTR SS:[EBP]
			TEST AX,AX
			JE L060
			MOV EDX,DWORD PTR SS:[ESP+0x20]
			MOVZX ESI,WORD PTR DS:[EDX]
			MOVZX ECX,SI
			MOVZX EDX,AX
			/* 这里为去除的语句 AND ECX,EDX */
			JNZ L057
			MOV ECX,DWORD PTR SS:[ESP+0x14]
			PUSH EAX
			MOV EAX,DWORD PTR SS:[ESP+0x14]
			PUSH EAX
			PUSH ECX
			MOV ECX,DWORD PTR DS:[EDI+0x34]
			CALL VisStateCheckCall
			MOV EDX,EAX
			SHR EDX,2
			AND EDX,1
			JNZ L057
			CMP DWORD PTR DS:[EDI+0x3C0],EDX
			JNZ L054
			TEST AL,2
			JE L060
	L054:
			MOV EAX,DWORD PTR SS:[ESP+0x24]
			OR WORD PTR DS:[EAX],BX
			JMP L060
	L057:
			MOV EAX,DWORD PTR SS:[ESP+0x20]
			OR ESI,EBX
			MOV WORD PTR DS:[EAX],SI
	L060:
			ADD EBP,2
			ADD EBX,EBX
			SUB DWORD PTR SS:[ESP+0x1C],1
			JNZ L030
			POP EDI
			POP ESI
			POP EBP
			POP EBX
			ADD ESP,0x8
			RETN 0x10
		}
	}


	void *UnitVtable0xF0;
	void *GameVisionCheckCallerRetn, *GameVisionCheckHookRetn;
	void __declspec(naked) HookUnitVtable0xF0() {
		__asm {
			cmp MapHack_MainMapShowUnit, 1;
			jnz quit;
			mov eax, GameVisionCheckCallerRetn;
			cmp [esp], eax;
			jnz quit;
	//0x6F26DE50 content
			mov eax, [ecx+0x5C];
			test eax, 0x10000;
			je result1;
			cmp [esp+4], 0;
			je result2;
			test al, al;
			jns result2;
			test eax, 0x8000000;
			je result1;
	result2:
			mov eax, 1;
			//retn 4
			jmp hook;
	result1:
			xor eax, eax
			//retn 4
			jmp hook;
	hook:
			add esp, 8;

			lea ecx, [edi + 0x1F8];
			push ecx;
			lea edx, [esp + 0x14];
			mov [esp + 0x48], eax;
			push edx;
			lea eax, [esp + 0x20];
			push eax;
			lea ecx, [esp + 0x38];
			push ecx;
			mov ecx, [edi + 0x178];
			mov [esp + 0x20], ebp;
			mov [esp + 0x2C], ebp;
	//call 0x6F3A1520
			push GameVisionCheckHookRetn;//fake retn in stack
			jmp Game_Fake_0x3A1520;
	quit:
			jmp UnitVtable0xF0;
		}
	}

	void *MinimapShowUnitCallerRetn, *MHShowUnitCallerRetn2, *MHSomeStateCheck;
	void __declspec(naked) HookUnitVtable0xB8() {
		__asm {
			push eax;
			mov eax, [esp+0x4];
			cmp eax, MinimapShowUnitCallerRetn;
			pop eax;
			jnz trynext1;
			cmp MapHack_MiniMapShowUnit, 1;
			jnz orig;
			mov [esp + 0x38], 0x00000000;		//0为全显示
			jmp orig;

	trynext1:
			push eax;
			mov eax, [esp+0x4];
			cmp eax, MHShowUnitCallerRetn2;//TODO 
			pop eax;
			jnz trynext2;
			cmp MapHack_MainMapShowUnit, 1;
			jnz orig;
			LEA EAX,DWORD PTR DS:[ECX+0x164];//原操作
			add esp, 4;//伪retn
			//6F392BCE开始的内容
			MOV ECX,EAX
			CALL MHSomeStateCheck//TODO 
			SAR DWORD PTR SS:[ESP+0x18],2
			SAR DWORD PTR SS:[ESP+0x1C],2
			LEA ECX,DWORD PTR DS:[ESI+0x1F8]
			PUSH ECX
			LEA EDX,DWORD PTR SS:[ESP+0x14]
			PUSH EDX
			LEA EAX,DWORD PTR SS:[ESP+0x1C]
			PUSH EAX
			LEA ECX,DWORD PTR SS:[ESP+0x24]
			PUSH ECX
			MOV ECX,DWORD PTR DS:[ESI+0x178]
			//call 0x6F3A1520
			mov eax, MHShowUnitCallerRetn2;
			add eax, 0x32;
			push eax;//push 6F392C00; fake retn in stack
			jmp Game_Fake_0x3A1520;

	trynext2:

	orig:
			LEA EAX,DWORD PTR DS:[ECX+0x164];
			RETN;
		}
	}

	void* __fastcall UnitGenerateHook(void* generator) {
		static bool inited = false;
		void* rv = aero::generic_this_call<void*>(
			OrgUnitGenerate,
			generator
		);

		if (!rv) return NULL;

		if (!inited) {
			inited = true;
			OrgUnitVtable = VTBL(rv);
			
			DWORD base = GameDef::GetGameBase();

			//MH
			DWORD VISION_CHECK_CALLER_RETN[] =			{0x39A3D9, 0x39A3D9, 0x39A439, 0x39A499, 0x399729, 0x399959};
			DWORD VISION_MAINMAP_FOG[] =				{0xAB7E6D, 0xAB7E6D, 0xAB7E6D, 0xAB7E6D, 0xAA1E4D, 0xAA1E4D};
			DWORD VISION_MINIMAP_UNIT_CALLER_RETN[] =	{0x362245, 0x362245, 0x3622A5, 0x362305, 0x361595, 0x3617C5};
			DWORD VISION_VISIBLESTATECHECK_CALL[] =		{0x00F4E0, 0x00F4E0, 0x00F4E0, 0x00F4E0, 0x00E7A0, 0x00E7A0};
			DWORD VISION_CHECK_CALLER_RETN_2[] =		{0x39364E, 0x39364E, 0x3936AE, 0x39370E, 0x39299E, 0x392BCE};
			DWORD VISION_SOME_STATE_CHECK[] =			{0x474EF0, 0x474EB0, 0x474F10, 0x474F70, 0x474230, 0x474460};
			//MH
			GameVisionCheckCallerRetn = (void*)(VISION_CHECK_CALLER_RETN[GameInfo->I] + base);
			GameVisionCheckHookRetn = reinterpret_cast<void *>((BYTE *)GameVisionCheckCallerRetn + 0x2D);
			MinimapShowUnitCallerRetn = (void*)(VISION_MINIMAP_UNIT_CALLER_RETN[GameInfo->I] + base);
			VisStateCheckCall = (void*)(VISION_VISIBLESTATECHECK_CALL[GameInfo->I] + base);
			MHShowUnitCallerRetn2 = (void*)(VISION_CHECK_CALLER_RETN_2[GameInfo->I] + base);
			MHSomeStateCheck = (void*)(VISION_SOME_STATE_CHECK[GameInfo->I] + base);

			*(BYTE *)(VISION_MAINMAP_FOG[GameInfo->I] + base) = MapHack_MainMapRemoveFog ? 0 : 0xFF ;//为迷雾浓度

			UnitVtable0xF0 = OrgUnitVtable[0xF0 / sizeof(void*)];
		
			memcpy_s(FakeUnitVtableData, sizeof(FakeUnitVtableData), aero::pointer_calc<void*>(OrgUnitVtable, -4), sizeof(FakeUnitVtableData));
		
			FakeUnitVtable[0xF0 / sizeof(void*)] = HookUnitVtable0xF0; //Maphack 大地图显示单位
			FakeUnitVtable[0xB8 / sizeof(void*)] = HookUnitVtable0xB8; //Maphack 小地图显示单位
		}
		*((void**)(rv)) = FakeUnitVtable;
		return rv;
	}

	#pragma optimize( "", off ) 
	BOOL CALLBACK EnumWindowsProc(
	  __in  HWND hwnd,
	  __in  LPARAM lParam
	) {
		BOOL rv = TRUE;
		VMProtectBeginMutation("EnumWindowsProc");
		char title[6];
		GetWindowTextA(hwnd, title, 6);
		if (title[3] == '-' && title[4] == '[') {
			title[3] = 0;
			if (atoi(title) / 90 == 6) {
				GameInfo = GameDef::IdentifyVersion();
				rv = FALSE;
			}
		}
		VMProtectEnd();
		return rv;
	}

	void Init() {
		VMProtectBeginVirtualization("MH::Init");
		
		EnumWindows(EnumWindowsProc, NULL);

		if (GameInfo) {
			void* War3UnitInstanceGenerator = (void*)(GameDef::GetGameBase() + GameInfo->PUnitInstanceGenerator);
			ObjectHookManager* HookManager = GetObjectHookManager();
			HookManager->replace(War3UnitInstanceGenerator, 3);
			OrgUnitGenerate = HookManager->apply(War3UnitInstanceGenerator, 0x0, UnitGenerateHook);			
		}
		VMProtectEnd();
	}

	void Cleanup() {
		VMProtectBeginVirtualization("MH::Cleanup");

		if (GameInfo) {

		}

		VMProtectEnd();
	}
	#pragma optimize( "", on ) 
}