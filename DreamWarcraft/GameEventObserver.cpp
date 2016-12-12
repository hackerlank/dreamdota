#include "stdafx.h"
#include <TlHelp32.h>
#include "GameEventObserver.h"
#include "FunctionTemplate.h"

#include "Foundation.h"
#include "Tools.h"
#include "BaseStructs.h"
#include "GameStructs.h"
#include "Observer.h"
#include "SystemTools.h"
#include "Profile.h"

#include "Game.h"
#include "GameTime.h"
#include "Timer.h"
#include "Player.h"
#include "Input.h"
#include "Offsets.h"
#include "ObjectHookManager.h"
#include "Event.h"
#include "JassTrigger.h"
#include "UnitEvent.h"
#include "RefreshManager.h"
#include "BinaryDumper.h"
#include "MissileManager.h"

#include <VMP.h>
ObjectHookManager* HookManager;

static war3::CObserver* War3NetEventObserver;
static war3::CNetData* War3NetData;
static war3::CNetObserver* War3NetObserver;
static war3::CObserver* War3InputObserver;

war3::UnitInstanceGenerator* War3UnitInstanceGenerator;
war3::ItemInstanceGenerator* War3ItemInstanceGenerator;
war3::TriggerInstanceGenerator* War3TriggerInstanceGenerator;
war3::AbilityAttackInstanceGenerator* War3AbilityAttackInstanceGenerator;
war3::AbilitySpellInstanceGenerator* War3AbilitySpellInstanceGenerator;

war3::MissileInstanceGenerator* War3MissileInstanceGenerator;
war3::MissileSplashInstanceGenerator* War3MissileSplashInstanceGenerator;
war3::MissileBounceInstanceGenerator* War3MissileBounceInstanceGenerator;
war3::MissileLineInstanceGenerator* War3MissileLineInstanceGenerator;
war3::ArtilleryInstanceGenerator* War3ArtilleryInstanceGenerator;
war3::ArtilleryLineInstanceGenerator* War3ArtilleryLineInstanceGenerator;

war3::CGameUI* War3GameUI;

Event CustomEvent;

static bool SafeMode;


//处理游戏还没正式开始前发生的事件
static std::list<Event*> PreGameEventList;
void GameEventObserver_ProcessPreGameEvents() {
	for (std::list<Event*>::iterator iter = PreGameEventList.begin();
		iter != PreGameEventList.end();
		++iter)
	{
		MainDispatcher()->dispatch(*iter);
		delete *iter;
	}
	PreGameEventList.clear();
}

void* OrgWorldFrame0x30;
uint32_t __fastcall WorldFrame0x30Hook(war3::CWorldFrameWar3* object) {
	uint32_t rv = aero::generic_this_call<uint32_t>(
		OrgWorldFrame0x30,
		object
	);

	RefreshManager_Update();

	return rv;
}

void* OrgGameUIEventHandler;
OBSERVER_EVENT_HANDLER(GameUIEventHook) {
	//OutputDebug("0x%X", EVENT->id);
	switch(EVENT->id) {
	case war3::EVENT_ITEM_CLICK:
		ItemClick_Report(EVENT);
		break;
	}
	
	return aero::generic_this_call<uint32_t>(
		OrgGameUIEventHandler,
		OBSERVER,
		EVENT
	);
}

static BinaryDumper* Dumper = NULL; //使用console debug

void* OrgNetEventHandler;
OBSERVER_EVENT_HANDLER(NetEventHook) {
	/*
	//if (EVENT->id != war3::EVENT_GAMETICK && EVENT->id != war3::EVENT_GAMEIDLETICK && EVENT->id != war3::EVENT_GAMEASYNCIDLETICK)
	if (EVENT->id >= 0xA0010 && EVENT->id <= 0xA0015){
		//OutputDebug("[%u]NetEvent ID = 0x%X, Name = %s", TimeRaw(), EVENT->id, RTTIClassNameGet(EVENT));
		uint8_t DumpData[0x50];
		uint32_t size = TryDumpObject(EVENT, DumpData, 0x50);
		if (!Dumper)
			Dumper = new BinaryDumper(NULL); //临时，没清理
		Dumper->dump(EVENT, size, RTTIClassNameGet(EVENT));
	}
	*/
	
	uint32_t time;
	war3::CWorldFrameWar3* worldFrame;
	switch (EVENT->id) {
	case war3::EVENT_GAMESTART:
		break;
	case war3::EVENT_GAMEREADY:

		HookManager->clearAllDynamic(); //清理上一次游戏的遗留
		Game_Init();
		
		War3GameUI = GameUIObjectGet();
		HookManager->replace(War3GameUI, 57, true);
		OrgGameUIEventHandler = HookManager->apply(War3GameUI, 0xC, GameUIEventHook);
		
		worldFrame = War3GameUI->world;
		HookManager->replace(worldFrame, 57, true);
		OrgWorldFrame0x30 = HookManager->apply(worldFrame, 0x30, WorldFrame0x30Hook);

		//HookManager->analysis(War3GameUI->world, 57);

		break;
	case war3::EVENT_GAMETICK:
		time = War3NetData->time;
		GameTime_Update(time);
		Timer_Update(time);
		break;
	case war3::EVENT_GAMELEAVE:
		Game_Cleanup();
		break;
	}

	PacketNetEventAnalyze(EVENT);

	return aero::generic_this_call<uint32_t>(
		OrgNetEventHandler,
		OBSERVER,
		EVENT
	);
}

void* OrgInputEventHandler;
OBSERVER_EVENT_HANDLER(InputEventHook) {
	//OutputDebug("InputEvent ID = 0x%X, Name = %s", EVENT->id, RTTIClassNameGet(EVENT));
	Input_Update(EVENT);
	return aero::generic_this_call<uint32_t>(
		OrgInputEventHandler,
		OBSERVER,
		EVENT
	);
}

OBSERVER_EVENT_HANDLER(TestEventHandler) {
#ifndef _VMP
	OutputDebug("Test ID = 0x%X, Name = %s", EVENT->id, RTTIClassNameGet(EVENT));
#endif
	return 0;
}


//--------------------------------------------------------------------------------
// Unit Hook
//--------------------------------------------------------------------------------
void* OrgUnitGenerate;
void** OrgUnitVtable;
void* FakeUnitVtableData[1 + 118];
void** FakeUnitVtable = &(FakeUnitVtableData[1]);

void DetourUnitDamageEventProcess(uint32_t type, war3::CUnit *sourceUnit, war3::CUnit *damageTarget, float damage, float damageRawNeg) {
	if (damage > 0){
		UnitDamaged_Update(damageTarget, sourceUnit, type, damage, -damageRawNeg);
	}
}

//伤害事件
static uint32_t HookUnitVtable0x120_DamageTarget;
static uint32_t HookUnitVtable0x120_DamageType;
static float HookUnitVtable0x120_DamageRawNeg;
void *UnitVtable0x120;
void __declspec(naked) HookUnitVtable0x120() {
	__asm {

		mov HookUnitVtable0x120_DamageTarget, ecx;
		mov eax, [esp+0xC];
		mov HookUnitVtable0x120_DamageType, eax;

		//调用原函数
		mov eax, [esp+0x10];
		push eax;
		mov eax, [esp+0x10];
		push eax;
		mov eax, [esp+0x10];
		push eax;
		mov eax, [esp+0x10];
		push eax;
		call UnitVtable0x120;

		push eax;//保护eax
		mov eax, [esp-0x8];//获取overhit damage
		mov HookUnitVtable0x120_DamageRawNeg, eax;

		push ecx;//保护ecx

		push HookUnitVtable0x120_DamageRawNeg;//neg overhit damage
		push ecx;//damage

		push HookUnitVtable0x120_DamageTarget;//damage target
		mov ecx, [esp+0x1C];
		mov eax, [ecx];
		push eax;//source unit
		push HookUnitVtable0x120_DamageType;//type
		call DetourUnitDamageEventProcess;
		add esp, 0x14;

		pop ecx;//恢复ecx
		pop eax;//恢复eax

		retn 0x10;
	}
}

void UnitReportAttackMiss(war3::CUnit *eventUnit) {
	if (!eventUnit) return;
	if (IsInGame()) {
		UnitAttackMissedEventData data;
		data.attacker = ObjectToHandle(eventUnit);
		if (data.attacker) {
			CustomEvent.setId(EVENT_UNIT_ATTACK_MISS);
			CustomEvent.setData<UnitAttackMissedEventData>(&data);
			MainDispatcher()->dispatch(&CustomEvent);
		}
	}
}

uint32_t MissTextTag0x2E;
void *UnitVtable0x100;
void __declspec(naked) HookUnitVtable0x100() {
	__asm {
		push esi
		lea esi, [esp+4]
		mov eax, [esi]
		push ebp
		mov ebp, MissTextTag0x2E
		cmp eax, ebp
		jne quit

		pushad
		pushfd
		push ecx//攻击者
		call UnitReportAttackMiss	//汇报miss事件
		add esp, 4
		popfd
		popad
	quit:
		pop ebp
		pop esi
		jmp UnitVtable0x100
	}
}

//Maphack
static bool MapHack_MainMapShowUnit;
static bool MapHack_MainMapRemoveFog;
static bool MapHack_MiniMapShowUnit;
static bool MapHack_BypassAH;

void MapHackSet (
	bool mainMapRemoveFog,
	bool mainMapShowUnit,
	bool miniMapShowUnit,
	bool bypassAH
	//...
	)
{
	//移除大地图迷雾
	MapHack_MainMapRemoveFog = mainMapRemoveFog;
	*(uint8_t *)Offset(VISION_MAINMAP_FOG) = MapHack_MainMapRemoveFog ? 0 : 0xFF ;//为迷雾浓度
	//大地图可见单位
	MapHack_MainMapShowUnit = mainMapShowUnit;
	//小地图可见单位
	MapHack_MiniMapShowUnit = miniMapShowUnit;
	//强制单位不透明
	MapHack_BypassAH = bypassAH;
}

void GetCurrentMapHackOptions(MapHackOptions* options) {
	options->BypassAH = MapHack_BypassAH;
	options->MainMapRemoveFog = MapHack_MainMapRemoveFog;
	options->MainMapShowUnit = MapHack_MainMapShowUnit;
	options->MiniMapShowUnit = MapHack_MiniMapShowUnit;
}

/*
6F3A159B -> nop nop	需要捕捉更多调用者
6F3A1520的本地调用来自 
6F38C647(destructable), 
6F392BFB,(完成)
6F392D60, 
6F399981, (完成)
6F39B1C7, 
6F3A5E1D
*/
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

void BypassVertexColorSet(war3::CUnit *u){
	if (u && MapHack_BypassAH) {//TODO 如何处理不同版本的CUnit结构差异
		uint32_t offset = (GetGameVersion() <= 6378) ? 0x2D0/4 : 0x2D4/4;//究竟是什么时候改的
		war3::ColorARGB *unitVertexColor =  (war3::ColorARGB *)(((uint32_t *)u)+offset);
		unitVertexColor->a = 0xFF;
	}
}

void *UnitVtable0xB4;
void __declspec(naked) HookUnitVtable0xB4() {
	__asm{
		pushad;
		pushfd;
		push ecx;
		call BypassVertexColorSet;
		add esp, 4;
		popfd;
		popad;
		jmp UnitVtable0xB4;
	}
}

void UnitCreateNotify(Timer* tm) {
	war3::CUnit* unit = *tm->data<war3::CUnit*>();
	UnitCreationEventData data;
	data.createdUnit = ObjectToHandle(unit);
	if (data.createdUnit) {
		CustomEvent.setId(EVENT_UNIT_CREATED);
		CustomEvent.setData<UnitCreationEventData>(&data);
		MainDispatcher()->dispatch(&CustomEvent);
	}
}

war3::CUnit* __fastcall UnitGenerateHook(war3::UnitInstanceGenerator* generator) {
	static bool inited = false;
	war3::CUnit* rv = aero::generic_this_call<war3::CUnit*>(
		OrgUnitGenerate,
		generator
	);

	if (!rv) return NULL;

	//禁止vtable的替换
	if (!inited) {
		inited = true;

		//Temp disabled part due to 11game detection.
		//TODO use choice

		OrgUnitVtable = VTBL(rv);
		
		//Miss
		MissTextTag0x2E = (uint32_t)Offset(MISS_TEXT_TAG_DISPLAY) + 0x2E;
		//MH
		GameVisionCheckCallerRetn = Offset(VISION_CHECK_CALLER_RETN);
		GameVisionCheckHookRetn = reinterpret_cast<void *>((uint8_t *)GameVisionCheckCallerRetn + 0x2D);
		MinimapShowUnitCallerRetn = Offset(VISION_MINIMAP_UNIT_CALLER_RETN);
		VisStateCheckCall = Offset(VISION_VISIBLESTATECHECK_CALL);
		MHShowUnitCallerRetn2 = Offset(VISION_CHECK_CALLER_RETN_2);
		MHSomeStateCheck = Offset(VISION_SOME_STATE_CHECK);

		UnitVtable0xF0 = OrgUnitVtable[0xF0 / sizeof(void*)];
		UnitVtable0xB4 = OrgUnitVtable[0xB4 / sizeof(void*)];
		
		memcpy_s(FakeUnitVtableData, sizeof(FakeUnitVtableData), aero::pointer_calc<void*>(OrgUnitVtable, -4), sizeof(FakeUnitVtableData));
		
		UnitVtable0x120 = FakeUnitVtable[0x120 / sizeof(void*)];
		UnitVtable0x100 = FakeUnitVtable[0x100 / sizeof(void*)];
		FakeUnitVtable[0x120 / sizeof(void*)] = HookUnitVtable0x120; //伤害
		FakeUnitVtable[0x100 / sizeof(void*)] = HookUnitVtable0x100; //Miss
		FakeUnitVtable[0xF0 / sizeof(void*)] = HookUnitVtable0xF0; //Maphack 大地图显示单位
		FakeUnitVtable[0xB8 / sizeof(void*)] = HookUnitVtable0xB8; //Maphack 小地图显示单位
		FakeUnitVtable[0xB4 / sizeof(void*)] = HookUnitVtable0xB4; //Maphack bypass -ah
	}
	
	rv->vtable = FakeUnitVtable;

	//TODO 更好的判断方式？
	if (GameObjectGet()) {
		Timer* tm = GetTimer(0, UnitCreateNotify);
		tm->setData<war3::CUnit*>(&rv);
		tm->start();
	}
	//HookManager->analysis(rv, 118);
	return rv;
}

//--------------------------------------------------------------------------------
// Item Hook
//--------------------------------------------------------------------------------
void* OrgItemGenerate;
void** OrgItemVtable;
void* FakeItemVtableData[1 + 110];
void** FakeItemVtable = &(FakeItemVtableData[1]);

void ItemCreateNotify(Timer* tm) {
	war3::CItem* item = *tm->data<war3::CItem*>();
	ItemCreationEventData data;
	data.createdItem = ObjectToHandle(item);
	if (data.createdItem) {
		CustomEvent.setId(EVENT_ITEM_CREATED);
		CustomEvent.setData<ItemCreationEventData>(&data);
		MainDispatcher()->dispatch(&CustomEvent);
	}
}

war3::CItem* __fastcall ItemGenerateHook(war3::ItemInstanceGenerator* generator) {
	static bool inited = false;
	war3::CItem* rv = aero::generic_this_call<war3::CItem*>(
		OrgItemGenerate,
		generator
	);

	if (!rv) return NULL;

	if (!inited) {
		inited = true;
		OrgItemVtable = VTBL(rv);
		
		memcpy_s(FakeItemVtableData, sizeof(FakeItemVtableData), aero::pointer_calc<void*>(VTBL(rv), -4), sizeof(FakeItemVtableData));
	}
	rv->vtable = FakeItemVtable;
	//HookManager->analysis(rv, 110);

	//TODO 更好的判断方式？ IsInGame太晚，捕捉不到地图初始化时的创建
	if (GameObjectGet()) {
		Timer* tm = GetTimer(0, ItemCreateNotify);
		tm->setData<war3::CItem*>(&rv);
		tm->start();
	}
	return rv;
}

//--------------------------------------------------------------------------------
// Trigger Hook
//--------------------------------------------------------------------------------
void* OrgTriggerGenerate;
void** OrgTriggerVtable;
void* FakeTriggerVtableData[1 + 30];
void** FakeTriggerVtable = &(FakeTriggerVtableData[1]);

void *TriggerVtable0xC;
void *TriggerVtable0xC_ObjFromHash;
void *TriggerVtable0xC_GameObj;
void *TriggerVtable0xC_GameState;
void *TriggerVtable0xC_Call_1;
void *TriggerVtable0xC_Call_2;
void *TriggerVtable0xC_Call_3;
void *TriggerVtable0xC_JmpBack;

void DetourTriggerExec() {
	JassTrigger_Filter(Jass::GetTriggerEventId());
}

void __declspec(naked) HookTriggerVtable0xC() {
        __asm {
                PUSH EDI                                // = trigger method 0xC
                MOV EDI,ECX
                MOV EDX,DWORD PTR DS:[EDI+0x10]
                MOV ECX,DWORD PTR DS:[EDI+0xC]
                CALL TriggerVtable0xC_ObjFromHash       //offset
                TEST EAX,EAX
                JE quit
                XOR ECX,ECX
                CMP DWORD PTR DS:[EAX+0xC],0x2B61676C   //const value
                SETNE CL
                SUB ECX,0x1
                AND ECX,EAX
                MOV EAX,ECX
                JE quit
                CMP DWORD PTR DS:[EAX+0x20],0
                JE somebranch0

        quit:
                XOR EAX,EAX
                POP EDI
                RETN 0x4

        somebranch0:
                MOV EAX,DWORD PTR SS:[ESP+0x8]
                CMP DWORD PTR DS:[EAX+0x8],0x80274
                JNZ noquit2
                ADD DWORD PTR DS:[EDI+0x60],-1
                MOV EAX,DWORD PTR DS:[EDI+0x60]
                XOR EDX,EDX
                TEST EAX,EAX
                SETLE DL
                SUB EDX,0x1
                AND EAX,EDX
                MOV DWORD PTR DS:[EDI+0x60],EAX
                MOV EAX,0x1
                POP EDI
                RETN 0x4

        noquit2:
                PUSH EBX
                PUSH EBP
                MOV EBP,DWORD PTR DS:[EAX+0xC]
                TEST EBP,EBP
                PUSH ESI
                JE somebranch2
                MOV EAX,DWORD PTR SS:[EBP+0x28]
                AND EAX,DWORD PTR SS:[EBP+0x24]
                LEA ECX,DWORD PTR SS:[EBP+0x24]
                CMP EAX,-1
                JNZ somebranch1
                XOR EAX,EAX
                MOV EBX,EAX
                JMP somebranch3

        somebranch1:
                CALL TriggerVtable0xC_Call_1
                MOV EBX,EAX
                JMP somebranch3

        somebranch2:
                XOR EBX,EBX

        somebranch3:
                MOV ECX,TriggerVtable0xC_GameObj
                MOV ECX,[ECX]
                CALL TriggerVtable0xC_GameState
                PUSH 0
                MOV ESI,EAX
                PUSH EDI
                PUSH 0x2
                MOV ECX,ESI
                CALL TriggerVtable0xC_Call_2
                PUSH 0x1
                PUSH EBP
                PUSH 0x4
                MOV ECX,ESI
                CALL TriggerVtable0xC_Call_2
                PUSH 0x1
                PUSH EBX
                PUSH 0x5
                MOV ECX,ESI
                CALL TriggerVtable0xC_Call_2
                MOV ECX,DWORD PTR SS:[ESP+0x14]
                MOV EAX,DWORD PTR DS:[ECX+0x8]
                ADD EAX,0xFFF7FE00
                PUSH EAX
                PUSH 0x6
                MOV ECX,ESI
                CALL TriggerVtable0xC_Call_3
                MOV ECX,EDI

                //my codes
                pushad
                pushfd
                call DetourTriggerExec
                popfd
                popad
                //my codes

                JMP TriggerVtable0xC_JmpBack
        }
}

war3::CTriggerWar3* __fastcall TriggerGenerateHook(war3::TriggerInstanceGenerator* generator) {
	static bool inited = false;
	war3::CTriggerWar3* rv = aero::generic_this_call<war3::CTriggerWar3*>(
		OrgTriggerGenerate,
		generator
	);

	if (!rv) return NULL;

	if (!inited) {
		inited = true;
		void ** vtbl = VTBL(rv);
		OrgTriggerVtable = vtbl;
		TriggerVtable0xC = vtbl[0xC / sizeof(void*)];
		TriggerVtable0xC_ObjFromHash    = Offset(OBJECT_FROM_HASH);
		TriggerVtable0xC_GameObj        = Offset(GLOBAL_WARCRAFT_GAME);
		TriggerVtable0xC_GameState      = Offset(STATE_GET);
		TriggerVtable0xC_Call_1         = Offset(TRIGGER_CALL_1);
		TriggerVtable0xC_Call_2         = Offset(TRIGGER_CALL_2);
		TriggerVtable0xC_Call_3         = Offset(TRIGGER_CALL_3);
		TriggerVtable0xC_JmpBack        = reinterpret_cast<void*>(*(DWORD *)((uint8_t *)OrgTriggerVtable + 0xC) + 0xD1);
		
		memcpy_s(FakeTriggerVtableData, sizeof(FakeTriggerVtableData), aero::pointer_calc<void*>(vtbl, -4), sizeof(FakeTriggerVtableData));
		//FakeTriggerVtable[0xC / sizeof(void*)] = TriggerEventHook;
		FakeTriggerVtable[0xC / sizeof(void*)] = HookTriggerVtable0xC;
	}
	rv->vtable = FakeTriggerVtable;
	//HookManager->analysis(rv, 110);

	return rv;
}

//--------------------------------------------------------------------------------
// AbilityAttack Hook
//--------------------------------------------------------------------------------
void* OrgAbilityAttackGenerate;
void** OrgAbilityAttackVtable;
void* FakeAbilityAttackVtableData[1 + 195];
void** FakeAbilityAttackVtable = &(FakeAbilityAttackVtableData[1]);
void* OrgAbilityAttackEventHandler;


static UnitAttackReleasedEventData	EvtData_AtkReleased;
static UnitAcquireEventData			EvtData_Acquire;
static std::map<war3::CAbilityAttack*, war3::CUnit *> EvtLastAcquired;
static war3::CUnit *EvtCurrentAcquired;

OBSERVER_EVENT_HANDLER(AbilityAttackEventHook) {
	/*
	if (EVENT->id != 0xD01C1){
		OutputScreen(10, "Event id = 0x%X", EVENT->id);
		if (EVENT->id == 0xD01B1) {
			uint8_t DumpData[0x50];
			uint32_t size = TryDumpObject(EVENT, DumpData, 0x50);
			if (!Dumper)
				Dumper = new BinaryDumper(NULL); //临时，没清理
			Dumper->dump(EVENT, size, RTTIClassNameGet(EVENT));
		}
	}
	*/
	if (IsInGame()) {
		switch(EVENT->id) {
		case war3::EVENT_UNIT_ATTACK_RELEASED://前摇结束
			EvtData_AtkReleased.attacker = ObjectToHandle(((war3::CAbilityAttack*)OBSERVER)->baseAbility.abilityOwner);
			if (EvtData_AtkReleased.attacker) {
				CustomEvent.setId(EVENT_UNIT_ATTACK_RELEASED);
				CustomEvent.setData<UnitAttackReleasedEventData>(&EvtData_AtkReleased);
				MainDispatcher()->dispatch(&CustomEvent);
			}
			break;
		case war3::EVENT_UNIT_ACQUIRE_START://开始注意到一个目标
			EvtCurrentAcquired = CUnitFromHash(&((war3::CAbilityAttack*)OBSERVER)->hashAcquired);
			if (EvtCurrentAcquired) {
				EvtData_Acquire.eventUnit = ObjectToHandle(((war3::CAbilityAttack*)OBSERVER)->baseAbility.abilityOwner);
				EvtData_Acquire.target = ObjectToHandle(EvtCurrentAcquired);
				if (EvtData_Acquire.eventUnit && EvtData_Acquire.target) {
					CustomEvent.setId(EVENT_UNIT_ACQUIRE_START);
					CustomEvent.setData<UnitAcquireEventData>(&EvtData_Acquire);
					MainDispatcher()->dispatch(&CustomEvent);
				}
			}
			break;
		case war3::EVENT_UNIT_ACQUIRE_READY://反应延迟完毕(TODO 是否与转身/推进有关系？)
			EvtCurrentAcquired = CUnitFromHash(&((war3::CAbilityAttack*)OBSERVER)->hashAcquired);
			if (EvtCurrentAcquired) {
				EvtData_Acquire.eventUnit = ObjectToHandle(((war3::CAbilityAttack*)OBSERVER)->baseAbility.abilityOwner);
				EvtData_Acquire.target = ObjectToHandle(EvtCurrentAcquired);
				if (EvtData_Acquire.eventUnit && EvtData_Acquire.target) {
					CustomEvent.setId(EVENT_UNIT_ACQUIRE_READY);
					CustomEvent.setData<UnitAcquireEventData>(&EvtData_Acquire);
					MainDispatcher()->dispatch(&CustomEvent);
				}
			}
			break;
		case war3::EVENT_UNIT_ACQUIRE_REFRESH://当acquire由有效变为无效时，单位停止注意目标
			EvtCurrentAcquired = CUnitFromHash(&((war3::CAbilityAttack*)OBSERVER)->hashAcquired);
			if (EvtCurrentAcquired != EvtLastAcquired[(war3::CAbilityAttack*)OBSERVER]){
				if (EvtCurrentAcquired == NULL){
					EvtData_Acquire.eventUnit = ObjectToHandle(((war3::CAbilityAttack*)OBSERVER)->baseAbility.abilityOwner);
					EvtData_Acquire.target = ObjectToHandle(EvtLastAcquired[(war3::CAbilityAttack*)OBSERVER]);
					if (EvtData_Acquire.eventUnit && EvtData_Acquire.target) {
						CustomEvent.setId(EVENT_UNIT_ACQUIRE_STOP);
						CustomEvent.setData<UnitAcquireEventData>(&EvtData_Acquire);
						MainDispatcher()->dispatch(&CustomEvent);
					}
				}
				EvtLastAcquired[(war3::CAbilityAttack*)OBSERVER] = EvtCurrentAcquired;
			}
			break;
		}
	}

	return aero::generic_this_call<uint32_t>(
		OrgAbilityAttackEventHandler,
		OBSERVER,
		EVENT
	);
}

war3::CAbilityAttack* __fastcall AbilityAttackGenerateHook(war3::AbilityAttackInstanceGenerator* generator) {
	static bool inited = false;
	war3::CAbilityAttack* rv = aero::generic_this_call<war3::CAbilityAttack*>(
		OrgAbilityAttackGenerate,
		generator
	);

	if (!rv) return NULL;

	if (!inited) {
		inited = true;
		OrgAbilityAttackVtable = VTBL(rv);
		
		memcpy_s(FakeAbilityAttackVtableData, sizeof(FakeAbilityAttackVtableData), aero::pointer_calc<void*>(VTBL(rv), -4), sizeof(FakeAbilityAttackVtableData));
		OrgAbilityAttackEventHandler = OrgAbilityAttackVtable[0xC / sizeof(void*)];
		FakeAbilityAttackVtable[0xC / sizeof(void*)] = AbilityAttackEventHook;
	}
	rv->baseAbility.vtable = FakeAbilityAttackVtable;
	return rv;
}

//--------------------------------------------------------------------------------
// SimpleButton Hook TODO 自动hook每个simplebutton
//--------------------------------------------------------------------------------
static void* FakeSimpleButtonVtableData[1 + 0x1D];
static void** FakeSimpleButtonVtable = &(FakeSimpleButtonVtableData[1]);

static void* SimpleButtonVtable0x50;
static void* SimpleButtonVtable0x54;
static Event MouseEventObject;
static MouseEventData MouseEventObjectData;
void __cdecl SimpleButtonMouseEventHandler(war3::CSimpleButton* button, war3::CMouseEvent *evt){
	//OutputScreen(10, "event: button 0x%X has event 0x%X", button, evt->baseEvent.id);
	switch(evt->baseEvent.id){
	case war3::EVENT_MOUSE_DOWN:
		if (IsInGame()) {
			MouseEventObject.setId(EVENT_MOUSE_DOWN);
			MouseEventObjectData.mouseCode = reinterpret_cast<war3::CMouseEvent*>(evt)->keyCurrent;
			MouseEventObjectData.x = reinterpret_cast<war3::CMouseEvent*>(evt)->x;
			MouseEventObjectData.y = reinterpret_cast<war3::CMouseEvent*>(evt)->y;
			MouseEventObjectData.buttonPushed = button;
			MouseEventObject.setData<MouseEventData>(&MouseEventObjectData);
			MainDispatcher()->dispatch(&MouseEventObject);
		}
		break;
	case war3::EVENT_MOUSE_UP:
		if (IsInGame()) {
			MouseEventObject.setId(EVENT_MOUSE_UP);
			MouseEventObjectData.mouseCode = reinterpret_cast<war3::CMouseEvent*>(evt)->keyCurrent;
			MouseEventObjectData.x = reinterpret_cast<war3::CMouseEvent*>(evt)->x;
			MouseEventObjectData.y = reinterpret_cast<war3::CMouseEvent*>(evt)->y;
			MouseEventObjectData.buttonPushed = button;
			MouseEventObject.setData<MouseEventData>(&MouseEventObjectData);
			MainDispatcher()->dispatch(&MouseEventObject);
		}
		break;
	default:
		break;
	}
	
}

void __declspec(naked) SimpleButtonMouseDownEventHook (){
	__asm{
		push ecx;//保护
		mov eax, [esp+8];
		push eax;
		mov eax, ecx;
		push eax;
		call SimpleButtonMouseEventHandler;
		add esp, 8;
		pop ecx;//恢复
		jmp SimpleButtonVtable0x50;
	}
}

void __declspec(naked) SimpleButtonMouseUpEventHook (){
	__asm{
		push ecx;//保护
		mov eax, [esp+8];
		push eax;
		mov eax, ecx;
		push eax;
		call SimpleButtonMouseEventHandler;
		add esp, 8;
		pop ecx;//恢复
		jmp SimpleButtonVtable0x54;
	}
}

void SimpleButtonHook (war3::CSimpleButton *button) {
	memcpy_s(FakeSimpleButtonVtableData, sizeof(FakeSimpleButtonVtableData), aero::pointer_calc<void*>(VTBL(button), -4), sizeof(FakeSimpleButtonVtableData));
	button->baseSimpleFrame.baseLayoutFrame.vtable = FakeSimpleButtonVtable;

	SimpleButtonVtable0x50 = FakeSimpleButtonVtable[0x50 / sizeof(void*)];
	FakeSimpleButtonVtable[0x50 / sizeof(void*)] = SimpleButtonMouseDownEventHook;

	SimpleButtonVtable0x54 = FakeSimpleButtonVtable[0x54 / sizeof(void*)];
	FakeSimpleButtonVtable[0x54 / sizeof(void*)] = SimpleButtonMouseUpEventHook;
}

void GameEventObserver_Init() {
	VMProtectBeginUltra("GameEventObserver_Init");

	SafeMode = ProfileFetchBool("Misc", "SafeMode", false);

	HookManager = GetObjectHookManager();
	void* data = aero::offset_element_get<void*>(GameTlsDataGet(0xD), 0x10);
	War3NetData = aero::offset_element_get<war3::CNetData*>(data, 0x8);
	War3NetObserver = aero::pointer_calc<war3::CNetObserver*>(War3NetData, 0x8);
	War3NetEventObserver = &(War3NetObserver->observer_4);

	War3InputObserver = InputObserverGet();
	//Hook InputObserver
	HookManager->replace(War3InputObserver, 6);
	OrgInputEventHandler = HookManager->apply(War3InputObserver, 0x10, InputEventHook);

	//Hook NetEventObserver
	HookManager->replace(War3NetEventObserver, 6);
	OrgNetEventHandler = HookManager->apply(War3NetEventObserver, 0x10, NetEventHook);

	//Hook Unit InstanceGenerator
	War3UnitInstanceGenerator = (war3::UnitInstanceGenerator*)Offset(IG_UNIT);
	HookManager->replace(War3UnitInstanceGenerator, 3);
	OrgUnitGenerate = HookManager->apply(War3UnitInstanceGenerator, 0x0, UnitGenerateHook);

	//Hook Item InstanceGenerator
	War3ItemInstanceGenerator = (war3::ItemInstanceGenerator*)Offset(IG_ITEM);
	HookManager->replace(War3ItemInstanceGenerator, 3); 
	OrgItemGenerate = HookManager->apply(War3ItemInstanceGenerator, 0x0, ItemGenerateHook);

	//Hook Trigger InstanceGenerator
	War3TriggerInstanceGenerator = (war3::TriggerInstanceGenerator*)Offset(IG_TRIGGER);
	HookManager->replace(War3TriggerInstanceGenerator, 3); 
	OrgTriggerGenerate = HookManager->apply(War3TriggerInstanceGenerator, 0x0, TriggerGenerateHook);

	//Hook AbilityAttack InstanceGenerator 
	War3AbilityAttackInstanceGenerator = (war3::AbilityAttackInstanceGenerator*)Offset(IG_ABILITYATTACK);
	HookManager->replace(War3AbilityAttackInstanceGenerator, 3); 
	OrgAbilityAttackGenerate = HookManager->apply(War3AbilityAttackInstanceGenerator, 0x0, AbilityAttackGenerateHook);

	VMProtectEnd();
}

void GameEventObserver_Cleanup() {
	VMProtectBeginVirtualization("GameEventObserver_Cleanup");
	//遍历所有被修改的对象并把vtable复原？
	//否则如果被强行卸载会出错

	if (IsInGame()) { //说明在游戏内被强行退出
		HookManager->clearAllDynamic();
		Game_Cleanup();
	}

	EvtLastAcquired.clear();
	VMProtectEnd();
}