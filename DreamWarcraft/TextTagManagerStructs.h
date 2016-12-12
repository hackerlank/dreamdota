#ifndef TEXTTAGMANAGER_STRUCTS_INCLUDED
#define TEXTTAGMANAGER_STRUCTS_INCLUDED

#include "stdafx.h"

namespace war3 {
	#ifdef _MSC_VER
	#pragma pack(push, 1)
	#endif // _MSC_VER

	struct CTextTagTextData {
		uint32_t	unk_0;		//0x0
		uint32_t	unk_4;		//0x4
		uint32_t	unk_8;		//0x8
		uint32_t	unk_C;		//0xC
		uint32_t	unk_10;		//0x10
		uint32_t	unk_14;		//0x14
		//...
	};

	//size 0x34
	struct CTextTagData {
		float						x;				//0x0
		float						y;				//0x4
		float						z;				//0x8

		float						velocityX;		//0xC
		float						velocityY;		//0x10
		float						velocityZ;		//0x14 似乎不灵
	
		float						age;			//0x18 defalut = 0.0
		float						lifespan;		//0x1C default = 100.0
		float						fadepoint;		//0x20 default = 90.000

		uint32_t					color;			//0x24	= a2
		uint8_t						unk_0x28;		//0x28	= *(BYTE*)(a2 + 3)
		uint8_t						unk_0x29[3];	//0x29
		CTextTagTextData*			textData;		//0x2C
		uint32_t					flags;			//0x30	= a11 != 0 ? 8 : 0
														//如果 & 0x10 == 0 说明被占用
	};

	struct CTextTagManagerSlotData {
		uint32_t			unk_18;			//0x0 = 0x64?
		uint32_t			unk_1C;			//0x4 = 0x64?
		uint32_t*			emptyIdArray;	//0x8
		int					remainCount;	//0xC
	};

	struct CTextTagManager {
		void**						vtable;				//0x0
		uint32_t					unk_4;				//0x4
		uint32_t					size;				//0x8  = 0x64?
		CTextTagData*				dataArray;			//0xC
		uint32_t					unk_10;				//0x10 = 8?
		int							count;				//0x14
		CTextTagManagerSlotData		slotData;			//0x18
		uint32_t					unk_28;				//0x28	default 0
		uint32_t					unk_2C;				//0x2C	default 0
		uint32_t					unk_30;				//0x30	font?
		float						unk_34;				//0x34	default 1.0
		float						unk_38;				//0x38	
		float						unk_3C;				//0x3C
		float						unk_40;				//0x40
		float						unk_44;				//0x44
		float						unk_48;				//0x48	default 1.0
		float						unk_4C;				//0x4C
		float						unk_50;				//0x50
		float						unk_54;				//0x54
		float						unk_58;				//0x58
		float						unk_5C;				//0x5C	default 1.0
		float						unk_60;				//0x60
		float						unk_64;				//0x64
		float						unk_68;				//0x68
		float						unk_6C;				//0x6C
		float						unk_70;				//0x70	default 1.0
		uint8_t						unk_74[0x10];		//0x74
		void*						unk_84;				//0x84
	};

	#ifdef _MSC_VER
	#pragma pack(pop)
	#endif // _MSC_VER

}

#endif

