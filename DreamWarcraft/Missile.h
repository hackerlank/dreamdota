#include "stdafx.h"
#ifndef MISSILE_H_INCLUDED
#define MISSILE_H_INCLUDED
#include "FunctionTemplate.h"
#include "MissileManager.h"
#include "Tools.h"
#include "Offsets.h"
#include "ObjectHookManager.h"

//按照TYPE_ID保存MissileHookInfo struct
extern void* MissileHookInfoArray[10];

//用来获取特定类型Missile的静态信息
template <typename MissileType>
struct MISSILE_TYPE_INFO {
	enum {IS_DEFINED = false};

	enum {TYPE_ID = NULL};
	enum {GENERATOR_OFFSET_ID = NULL};
	enum {TARGET_HASH_OFFSET = 0};
	enum {VTABLE_LENGTH = 0};
	
	typedef void* GENERATOR_TYPE;
};

//存储Hook数据
template <typename MissileType>
struct MissileHookInfo {
	void** OrgVtable;
	void* OrgGenerate;
	void* fakeVtablePreInitData[1 + MISSILE_TYPE_INFO<MissileType>::VTABLE_LENGTH];
	void** fakeVtablePreInit;
	void* fakeVtableData[1 + MISSILE_TYPE_INFO<MissileType>::VTABLE_LENGTH];
	void** fakeVtable;
};

//用来定义要Hook的Missile类型的静态信息
#define DECLARE_MISSILE_TYPE(generator_type, type, type_id, offset_id, target_hash_offset, vtableLength) \
template <> \
struct MISSILE_TYPE_INFO<type> { \
	enum {IS_DEFINED = true}; \
	\
	enum {TYPE_ID = type_id}; \
	enum {GENERATOR_OFFSET_ID = offset_id}; \
	enum {TARGET_HASH_OFFSET = target_hash_offset}; \
	enum {VTABLE_LENGTH = vtableLength}; \
	\
	typedef generator_type GENERATOR_TYPE;\
	\
}

extern std::map<uint32_t, uint32_t> MissileStatsMap; //debug

//Generator Hook Function
template <typename MissileType>
MissileType* MissileGeneratorHookFunc(void* t) {
	static bool inited = false;
	MissileHookInfo<MissileType>* info = (MissileHookInfo<MissileType>*)(MissileHookInfoArray[MISSILE_TYPE_INFO<MissileType>::TYPE_ID]);
	MissileType* rv = aero::generic_this_call<MissileType*>(info->OrgGenerate, t);
	if (!inited) {
		inited = true;
		uint32_t vtableSize = sizeof(info->fakeVtableData);
		info->OrgVtable = VTBL(rv);
		memcpy_s(info->fakeVtableData, 1 + vtableSize, aero::pointer_calc<void*>(info->OrgVtable, -4), 1 + vtableSize);
		info->fakeVtable = &(info->fakeVtableData[1]);
		memcpy_s(info->fakeVtablePreInitData, 1 + vtableSize, aero::pointer_calc<void*>(info->OrgVtable, -4), 1 + vtableSize);
		info->fakeVtablePreInit = &(info->fakeVtablePreInitData[1]);

		info->fakeVtable[0xC / sizeof(void*)] = MissileHookFunc0xC<MissileType>;
		info->fakeVtablePreInit[0x8 / sizeof(void*)] = MissileHookFunc0x8<MissileType>;
	}
	*((void***)rv) = info->fakeVtablePreInit;
	//GetObjectHookManager()->analysis(rv, 200);

	if (MissileStatsMap.count(MISSILE_TYPE_INFO<MissileType>::TYPE_ID) == 0) {
		MissileStatsMap[MISSILE_TYPE_INFO<MissileType>::TYPE_ID] = 1;
	} else
		MissileStatsMap[MISSILE_TYPE_INFO<MissileType>::TYPE_ID]++;
	//OutputDebug("Missile Type %u #%u", MISSILE_TYPE_INFO<MissileType>::TYPE_ID, MissileStatsMap[MISSILE_TYPE_INFO<MissileType>::TYPE_ID]);
	return rv;
} 

template <typename MissileType>
uint32_t __fastcall MissileHookFunc0xC(void* t, uint32_t dummy, war3::CEvent* evt);

template <typename MissileType>
uint32_t __fastcall MissileHookFunc0x8(void* t, uint32_t dummy, uint32_t id1, uint32_t id2, war3::CObserver* ob);

//初始化Hook
template <typename MissileType>
void MissileGeneratorHookInit() {
	void* generator = (Offset(MISSILE_TYPE_INFO<MissileType>::GENERATOR_OFFSET_ID));
	ObjectHookManager* hookMgr = GetObjectHookManager();

	MissileHookInfo<MissileType>* info = new MissileHookInfo<MissileType>;
	MissileHookInfoArray[MISSILE_TYPE_INFO<MissileType>::TYPE_ID] = info;
	hookMgr->replace(generator, 3);
	info->OrgGenerate = hookMgr->apply(generator, 0x0, (void(*)())MissileGeneratorHookFunc<MissileType>);
}

//0xC Hook Function
template <typename MissileType>
uint32_t __fastcall MissileHookFunc0xC(void* t, uint32_t dummy, war3::CEvent* evt) {
	MissileHookInfo<MissileType>* info = (MissileHookInfo<MissileType>*)(MissileHookInfoArray[MISSILE_TYPE_INFO<MissileType>::TYPE_ID]);
	if (evt->id == 0xD019Cu) {
		war3::CMissile* missile = (war3::CMissile*)t;
		MissileManager_RemoveMissile(missile);
	}
	uint32_t rv = aero::generic_this_call<uint32_t>(
		info->OrgVtable[0xC / sizeof(void*)],
		t,
		evt
	);

	return rv;
}

//0x8 Hook Function
template <typename MissileType>
uint32_t __fastcall MissileHookFunc0x8(void* t, uint32_t dummy, uint32_t id1, uint32_t id2, war3::CObserver* ob) {
	MissileHookInfo<MissileType>* info = (MissileHookInfo<MissileType>*)(MissileHookInfoArray[MISSILE_TYPE_INFO<MissileType>::TYPE_ID]);
	*((void***)t) = info->fakeVtable;

	MissileManager_AddMissile(
		(Unit::WeaponTypeEnum)MISSILE_TYPE_INFO<MissileType>::TYPE_ID, 
		t, 
		aero::pointer_calc<war3::HashGroup*>(t, MISSILE_TYPE_INFO<MissileType>::TARGET_HASH_OFFSET)
	);
	return aero::generic_this_call<uint32_t>(
		info->OrgVtable[0x8 / sizeof(void*)],
		t,
		id1,
		id2,
		ob
	);
}

void Missile_Init();

void Missile_Cleanup();

#endif