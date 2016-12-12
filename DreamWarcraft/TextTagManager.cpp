#include "stdafx.h"
#include "TextTagManager.h"
#include "GameStructs.h"
#include "Offsets.h"
#include "Tools.h"
#include <set>

war3::CTextTagManager* GetJassTTM() {
	return &(GameStateObjectGet()->textTagManager);
}

war3::CTextTagManager* GetMapTTM() {
	return MapInfoGet()->textTagManager;
}

war3::CTextTagData* TTMGetOccupiedTagData(war3::CTextTagManager* m, uint32_t tagId);

typedef std::set<war3::CTextTagManager*> ManagerSetType;
ManagerSetType ManagerSet;

war3::CTextTagManager tmp;

typedef float (__fastcall *PROTOTYPE_ZConv)(int a0, int a1, float x, float y, int a5);
PROTOTYPE_ZConv ZConv;

typedef uint32_t (__thiscall *PROTOTYPE_TextTagManager_SetTagText)(war3::CTextTagManager* m, uint32_t tagId, const char* text, float size);
PROTOTYPE_TextTagManager_SetTagText TextTagManager_SetTagText;

typedef uint32_t (__fastcall *PROTOTYPE_TextTagManager_ShowTag)(void* ttm_84, war3::CTextTagTextData* data_2C);
PROTOTYPE_TextTagManager_ShowTag TextTagManager_ShowTag;

void TextTagManager_Init() {
	ZConv = (PROTOTYPE_ZConv)Offset(Z_CONV);
	TextTagManager_SetTagText = (PROTOTYPE_TextTagManager_SetTagText)Offset(TEXTTAG_MANAGER_SETTAGTEXT);
	TextTagManager_ShowTag = (PROTOTYPE_TextTagManager_ShowTag)Offset(TEXTTAG_MANAGER_SHOWTEXTTAG);
}

void TTMSetTagPos(war3::CTextTagManager* m, uint32_t tagId, float x, float y, float heightOffset) {
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (data) {
		data->x = x;
		data->y = y;
		data->z = ZConv(-2, 0, x, y, 0) + heightOffset;
	}
}

void TTMSetTagPos3D(war3::CTextTagManager* m, uint32_t tagId, float x, float y, float z) {
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (data) {
		data->x = x;
		data->y = y;
		data->z = z;
	}
}

void TTMSetTagText(war3::CTextTagManager* m, uint32_t tagId, const char* text, float size) {
	TextTagManager_SetTagText(m, tagId, text, size); //这里有0x64的限制
}

void TTMSetTagColor(war3::CTextTagManager* m, uint32_t tagId, uint32_t color) {
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (data) {
		data->color = color;
	}
}

void TTMSetTagVelocity(war3::CTextTagManager* m, uint32_t tagId, float x, float y) {
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (data) {
		data->velocityX = x;
		data->velocityY = y;
		data->velocityZ = 0.00; //似乎不起作用
	}
}

void __declspec(naked) TextTagManager_HideTag() {
	__asm {
			test    ecx, ecx
			jnz     short loc_6F7B9C57
			xor     eax, eax
			retn
		loc_6F7B9C57:
			lea     eax, [ecx+10h]
			push    esi
			mov     esi, [eax]
			test    esi, esi
			jz      short loc_6F7B9C8A
			mov     edx, [eax+4]
			test    edx, edx
			jg      short loc_6F7B9C6C
			not     edx
			jmp     short loc_6F7B9C73
		loc_6F7B9C6C:   
			mov     ecx, eax
			sub     ecx, [esi+4]
			add     edx, ecx
		loc_6F7B9C73:                        
			mov     [edx], esi
			mov     ecx, [eax]
			mov     edx, [eax+4]
			mov     [ecx+4], edx
			mov     dword ptr [eax], 0
			mov     dword ptr [eax+4], 0
		loc_6F7B9C8A: 
			mov     eax, 1
			pop     esi
			retn
	}
}

void TTMSetTagVisibility(war3::CTextTagManager* m, uint32_t tagId, bool v) {
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (data) {
		if (v) {
			data->flags &= 0xFFFFFFFBu;
			if (data->textData) 
				TextTagManager_ShowTag(m->unk_84, data->textData);
		} else {
			data->flags |= 4u;
			if (data->textData) {
				war3::CTextTagTextData* textData = data->textData;
				__asm {
					mov ecx, textData;
					call TextTagManager_HideTag;
				}
			}
		}
	}	
}

void TTMSetTagSuspended(war3::CTextTagManager* m, uint32_t tagId, bool v) {
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (data) {
		if (v) {
			data->flags |= 0x2u;
		} else {
			data->flags &= 0xFFFFFFFDu;
		}
	}	
}

void TTMSetTagPermanent(war3::CTextTagManager* m, uint32_t tagId, bool v) {
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (data) {
		if (v) {
			data->flags |= 0x8u;
		} else {
			data->flags &= 0xFFFFFFF7u;
		}
	}	
}

void TTMSetTagAge(war3::CTextTagManager* m, uint32_t tagId, float v) {
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (data) {
		data->age = v;
	}	
}

void TTMSetTagLifespan(war3::CTextTagManager* m, uint32_t tagId, float v) {
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (data) {
		data->lifespan = v;
	}	
}

void TTMSetTagFadepoint(war3::CTextTagManager* m, uint32_t tagId, float v) {
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (data) {
		data->fadepoint = v;
	}	
}

void TextTagManager_Update() {
	war3::CTextTagManager* cur;
	void* curdata;
	war3::CGameState* state = GameStateObjectGet();
	for (ManagerSetType::iterator iter = ManagerSet.begin(); iter != ManagerSet.end(); ++iter) {
		cur = *iter;
		curdata = cur->unk_84;
		uint32_t test1 = 0x6F4E50C0;
		uint32_t test2 = 0x6F7B8CF0;
		uint32_t test3 = 0x6F016BA0;	
		__asm {
			push 0;
			mov ecx, cur;
			call test1;
			mov ecx, curdata
			call test2;
		}
	}
}

typedef int (__thiscall *PROTOTYPE_TextTagManager_construct)(war3::CTextTagManager* t, const char* fontName, float size);
PROTOTYPE_TextTagManager_construct TextTagManager_construct = NULL;

typedef int (__thiscall *PROTOTYPE_TextTagManager_CreateTag)(
	war3::CTextTagManager* t, 
	int* a2, 
	const char* text, 
	uint32_t* real1, 
	float size, 
	uint32_t* real2, 
	float a7, 
	float a8, 
	uint32_t *tag_id, 
	int a10, 
	int a11, 
	int toPos);

PROTOTYPE_TextTagManager_CreateTag TextTagManager_CreateTag = NULL;

war3::CTextTagManager* CreateTextTagManager(const char* fontName, double size) {
	war3::CTextTagManager* rv = new war3::CTextTagManager;
	memset(rv, 0, sizeof(war3::CTextTagManager));
	if (!TextTagManager_construct) {
		TextTagManager_construct = reinterpret_cast<PROTOTYPE_TextTagManager_construct>(Offset(TEXTTAG_MANAGER_CONSTRUCT));
	}
	TextTagManager_construct(rv, fontName, static_cast<float>(size));
	ManagerSet.insert(rv);
	return rv;
}

void DestroyTextTagManager(war3::CTextTagManager* m) {
	if (!m) return;
	void* destruct_func = m->vtable[0];
	__asm {
		mov ecx, m;
		call destruct_func;
	}
	delete m;
}

uint32_t TTMCreateTag(war3::CTextTagManager* m, const char* text, double size) {
	if (!m || !text) return 0;
	if (!TextTagManager_CreateTag)
		TextTagManager_CreateTag = reinterpret_cast<PROTOTYPE_TextTagManager_CreateTag>(Offset(TEXTTAG_MANAGER_CREATETEXT));
	int intValue = -1;
	uint32_t realValue = 0;
	uint32_t tagId;

	uint32_t rv = TextTagManager_CreateTag(
		m,
		&intValue,
		text,
		&realValue,
		static_cast<float>(size),
		&realValue,
		static_cast<float>(0.0f),
		static_cast<float>(0.0f),
		&tagId,
		1,
		1,
		-1);
	//Set suspended
	//m->dataArray[tagId].flags |= 0x2;
	return tagId;
}


war3::CTextTagData* TTMGetOccupiedTagData(war3::CTextTagManager* m, uint32_t tagId) {
	if (tagId < m->size) {
		return *(reinterpret_cast<uint8_t*>(&m->dataArray[tagId].flags)) & 0x10 ? NULL : &(m->dataArray[tagId]);
	}
	return NULL;
}

uint32_t TTMDestroyTag(war3::CTextTagManager* m, uint32_t tagId) {
	if (!m) return 0;
	war3::CTextTagData* data = TTMGetOccupiedTagData(m, tagId);
	if (!data)
		return NULL;

	void* vtable_4 = m->vtable[1];
	__asm {
		mov ecx, m;
		push data;
		call vtable_4;
	}
	data->flags |= 0x10;

	uint32_t currentRemain = m->slotData.remainCount;
	++ m->slotData.remainCount;
	m->slotData.emptyIdArray[currentRemain] = tagId;

	-- m->count;
}



