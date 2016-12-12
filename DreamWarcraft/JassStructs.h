#include "stdafx.h"
#ifndef JASS_STRUCT_H_INCLUDED
#define JASS_STRUCT_H_INCLUDED

#include "BaseStructs.h"

namespace war3 {

	#ifdef _MSC_VER
	#pragma pack(push, 1)
	#endif // _MSC_VER

	struct NativeFunc {
		void**		vtable;			//0x0
		uint32_t	hashFuncName;	//0x4
		uint8_t		unk_8[0x10];	//0x8
		char*		funcName;		//0x18
		void*		func;			//0x1C
		uint8_t		unk_20[0x4];	//0x20
		char*		argsType;		//0x24	
		uint8_t		unk_28[0x14];	//0x28
	};//sizeof = 0x3C

	struct Script2HandleReg {
		void**		vtable;			//0x0
		uint8_t		unk_4[0x18];	//0x4
	};//sizeof = 0x1C

	typedef TSHashTable<Script2HandleReg, HASHKEY_NONE> Script2HandleRegHashTable;

	typedef TAllocatorHashTable<NativeFunc, HASHKEY_STR, 0x100> NativeFuncAllocatorHashTable;

	struct JassThreadLocal {
		void**							vtable;														//0x0
		uint32_t						unk_4;														//0x4
		uint32_t						unk_8;														//0x8
		uint32_t						unk_C;														//0xC
		uint32_t						unk_10;														//0x10
		uint32_t						unk_14;														//0x14
		NativeFuncAllocatorHashTable	hashtableNativeFunc;										//0x18
		uint32_t						unk_40;														//0x40
		uint32_t						unk_44;														//0x44
		uint32_t						unk_48;														//0x48
		uint32_t						unk_4C;														//0x4C
		uint32_t						unk_50;														//0x50
		uint32_t						unk_54;														//0x54
		uint32_t						unk_58;														//0x58
		uint32_t						unk_5C;														//0x5C
		Script2HandleRegHashTable		hashtableScript2HandleReg;									//0x60
		uint32_t						unk_88;														//0x88
		uint32_t						unk_8C;														//0x8C
		void**							stringArr;													//0x90							
		//...
	};

	#ifdef _MSC_VER
	#pragma pack(pop)
	#endif // _MSC_VER

}//namespace war3
#endif