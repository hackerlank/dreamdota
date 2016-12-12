#pragma once

#include <Windows.h>

namespace GameDef {
	struct VersionOffsetType {
		DWORD I;
		DWORD version;
		DWORD PVersionId;

		DWORD WndProc;
		DWORD PTLSIndex;
		DWORD PUnitInstanceGenerator;
		DWORD NativeFuncNodeGet;
	};
	
	static VersionOffsetType VersionOffsets[] = {
		{0, 6374, 0x3A21C0 + 0x20, 0xAE8454, 0xACEA4C, 0xACB0D4, 0x44D850},
		{1, 6378, 0x3A21C0 + 0x20, 0xAE8454, 0xACEA4C, 0xACB0D4, 0x44D7F0},
		{2, 6384, 0x3A2220 + 0x20, 0xAE8454, 0xACEA4C, 0xACB0D4, 0x44D850},
		{3, 6387, 0x3A2280 + 0x20, 0xAE8454, 0xACEA4C, 0xACB0D4, 0x44D8B0},
		{4, 6397, 0x3A1510 + 0x20, 0xAD15F4, 0xAB7BF4, 0xAB427C, 0x44CB70},
		{5, 6401, 0x3A1740 + 0x20, 0xAD15F4, 0xAB7BF4, 0xAB427C, 0x44CDA0}
	};

	#pragma pack(push, 1)

	struct NativeFunc {
		void**		vtable;			//0x0
		DWORD		hashFuncName;	//0x4
		BYTE		unk_8[0x10];	//0x8
		char*		funcName;		//0x18
		void*		func;			//0x1C
		BYTE		unk_20[0x4];	//0x20
		char*		argsType;		//0x24	
		BYTE		unk_28[0x14];	//0x28
	};//sizeof = 0x3C

	#pragma pack(pop)

	VersionOffsetType* IdentifyVersion();
	void* GameTlsDataGet(DWORD index);
	DWORD GetGameBase();
}