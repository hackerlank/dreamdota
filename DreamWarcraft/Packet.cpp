#include "stdafx.h"
#include "Game.h"
#include "Offsets.h"
#include "Packet.h"
#include "Event.h"
#include "Action.h"
#include "Timer.h"
#include "GameTime.h"
#include "Latency.h"
#include "APM.h"


const float JITSelectBackChanceInit = 0.01f;
const float JITSelectBackChanceFactor = 1.5f;
static float JITSelectBackChanceCurrent = 0.0f;
static Timer* JITSelectBackTimer = NULL;

static bool ActionSentByScript = false;
static bool ActionProcessing = false;

#define ACTION_PROGRAMM_BEGIN ActionSentByScript = true;
#define ACTION_PROGRAMM_END   ActionSentByScript = false;
#define ACTION_PROGRAMM (ActionSentByScript!=false)

#define ACTION_PROCESS_BEGIN ActionProcessing = true;
#define ACTION_PROCESS_END   ActionProcessing = false;
#define ACTION_PROCESS (ActionProcessing!=false)

void PacketSend (void *pPacket, uint32_t size, bool sendAsProgramm) {
	void *funcPacketSend = Offset(PACKET_SEND);
	war3::PacketSender sender;
	sender.vtable = (void **)Offset(DATASTORECACHE1460_VTABLE);
	sender.packet = pPacket;
	sender.unk_8 = 0;
	sender.unk_C = 0x5B4;
	sender.sizePacket = size;
	sender.unk_14 = -1;
	if(sendAsProgramm)ACTION_PROGRAMM_BEGIN	//宣告动作包为本程序所发
	__asm {
		lea ecx, sender;
		xor edx, edx;
		call funcPacketSend;
	}
	if(sendAsProgramm)ACTION_PROGRAMM_END	//结束
}

void PacketSenderDestroy (void *pPacketSender) {
	if ( pPacketSender ) {
		((war3::PacketSender *)pPacketSender)->sizePacket = 0;
		//war3::PacketGeneral *packet = (war3::PacketGeneral *)((war3::PacketSender *)pPacketSender)->packet;
		//packet->id = 0xFF;
	}
}

void PacketSelectionSend (std::set<war3::CUnit *> *set, bool select) {
	war3::CUnit *lpUnit = NULL;
	if (set->size() > 0) {
		war3::PacketSelection packet;
		packet.id = 0x16;
		packet.mode = select ? 1 : 2;
		packet.count = set->size();
		std::set<war3::CUnit *>::iterator iter; uint32_t i = 0;
		for (iter = set->begin(); iter != set->end(); ++iter) {
			lpUnit = *iter;
			if (lpUnit) { 
				packet.objects[i] = lpUnit->hash; 
				++i;
			}
		}
		PacketSend(&packet, (4 + i * 8), true);//TODO 验证用i取代set->size是否会bug
	}
}

bool UnitSetCheckIdent (std::set<war3::CUnit *> *set1, std::set<war3::CUnit *> *set2) {
	std::set<war3::CUnit *>::iterator iter1, iter2;
	if (set1->size() == set2->size()) {
		iter1 = set1->begin(); iter2 = set2->begin();
		while( iter1 != set1->end()) {
			if (*iter1 != *iter2) {
				//OutputScreen(0,0,10,"check ident: element inequal 0x%X = *iter1 != *iter2 = 0x%X", *iter1, *iter2);
				return false;
			}
			++iter1; ++iter2;
		}
		return true;
	}
	//OutputScreen(0,0,10,"check ident: size inequal %d != %d", set1->size(), set2->size());
	return false;
}

void UnitSetCopyFromArr (std::set<war3::CUnit *> *set, war3::CUnit *arr[], uint32_t & count){
	for (uint32_t i = 0; i < count; ++i) set->insert(arr[i]);
}

void UnitSetCopyToArr (std::set<war3::CUnit *> *set, war3::CUnit *arr[], uint32_t & count){
	std::set<war3::CUnit *>::iterator iter; uint32_t i = 0;
	for (iter = set->begin(); iter != set->end(); ++iter){
		arr[i] = *iter;	i++;
	}
	count = i;
}

//current selections used in JIT selection
static std::set<war3::CUnit *> JustInTimeSelection;

void PacketJustInTimeActionSelectBack ();

void PacketJustInTimeActionSend (
	bool useJIT,
	std::set<war3::CUnit *>	*unitSetToSelect,
	void					*pPacketAction,
	uint32_t				sizePacket,
	bool					sendAsProgramm
)	
{
	JITSelectBackChanceCurrent = JITSelectBackChanceInit;

//	1. 如果 !processing, 
//	current <- 本地选择(UI); processing <- true;
	if (!ACTION_PROCESS) {
		ACTION_PROCESS_BEGIN
		//OutputScreen(0,0,10,"step 1");
		war3::CUnit *arr[12] = {0};
		uint32_t arr_count = SelectedUnitGet(PlayerLocal(), (void **)arr, false);
		if (arr_count)
			UnitSetCopyFromArr(&JustInTimeSelection, arr, arr_count);
	}

//	[ 仅当 current != toSelect
//		2. 移除current
//		3. 添加toSelect; current <- toSelect
//		   刷新(0x1A); 切换子组toSelect[0] (0x19)
//	]
	if (!UnitSetCheckIdent(&JustInTimeSelection, unitSetToSelect)){
		PacketSelectionSend(&JustInTimeSelection, false);
		PacketSelectionSend(unitSetToSelect, true);

		war3::CUnit *unitSetToSelectBegin;;
		if (unitSetToSelect->size() && (unitSetToSelectBegin = *(unitSetToSelect->begin()))){
			war3::PacketPreSubSelection preSubSel; preSubSel.id = 0x1A;
			PacketSend(&preSubSel, 1, true);
		
			uint32_t typeId = unitSetToSelectBegin->typeId;
			war3::PacketSubgroup subg; subg.id = 0x19;
			subg.typeId = typeId;
			subg.object = unitSetToSelectBegin->hash;
			PacketSend(&subg, 13, true);
		}

		JustInTimeSelection = *unitSetToSelect;
		
		//OutputScreen(0,0,10,"step 2, 3");
	}

//	4. action
	PacketSend(pPacketAction, sizePacket, sendAsProgramm);
	//OutputScreen(0,0,10,"step 4");

	if (!useJIT){
		PacketJustInTimeActionSelectBack();
	}
}

//	7. current <- 空; processing <- false
void PacketJustInTimeActionClear () {
	JITSelectBackChanceCurrent = JITSelectBackChanceInit;
	JustInTimeSelection.clear();
	ACTION_PROCESS_END
	//OutputScreen(0,0,10,"step 7");
}

//	[ 仅当 current != 本地选择(UI)
//		5. 移除current
//		6. 添加 本地选择(UI)
//         刷新(0x1A); 切换子组 本地高亮子组(0x19)
//	]
void PacketJustInTimeActionSelectBack () {
	war3::CUnit *arr[12] = {0};	war3::CUnit *arrSubgroup[12] = {0};
	uint32_t arr_count = SelectedUnitGet(PlayerLocal(), (void **)arr, false);
	uint32_t arrSubgroup_count = ActiveSubgroupGet(PlayerLocal(), (void **)arrSubgroup);

	std::set<war3::CUnit *> setCurrentSelection, setCurrentSubgroup;
	if (arr_count)
		UnitSetCopyFromArr(&setCurrentSelection, arr, arr_count);
	if (arrSubgroup_count)
		UnitSetCopyFromArr(&setCurrentSubgroup, arrSubgroup, arrSubgroup_count);

	if (!UnitSetCheckIdent(&JustInTimeSelection, &setCurrentSelection)){
		//OutputScreen(0,0,10,"step 5, 6");
		PacketSelectionSend(&JustInTimeSelection, false);//BUG，结束游戏需要清理
		PacketSelectionSend(&setCurrentSelection, true);
		if (setCurrentSubgroup.size()){
			war3::CUnit *setCurrentSubgroupBegin = *(setCurrentSubgroup.begin());
			if (setCurrentSubgroupBegin){
				war3::PacketPreSubSelection preSubSel; preSubSel.id = 0x1A;
				PacketSend(&preSubSel, 1, true);
				uint32_t typeId = setCurrentSubgroupBegin->typeId;
				war3::PacketSubgroup subg; subg.id = 0x19;
				subg.typeId = typeId; subg.object = setCurrentSubgroupBegin->hash;
				PacketSend(&subg, 13, true);
			}
		}
	}
	PacketJustInTimeActionClear();
}

void JITSelectBackTimerFunc (Timer *tm) {
	if (ACTION_PROCESS){
		tm->setTimeout(RandomFloat(0.06f, 0.14f));
		JITSelectBackChanceCurrent *= JITSelectBackChanceFactor;
		if (RandomFloat(0.0f, 1.0f) <= JITSelectBackChanceCurrent){
			PacketJustInTimeActionSelectBack();
		}
	}
}


static Event PacketEventObject;
void PacketEventDispatch (war3::PacketSender *pPacketSender, void *pPacket, uint32_t packetId) {
	if (!IsInGame())
		return;

	//OutputScreen(10, "PacketEventDispatch, packetId = 0x%X", packetId);

	PacketEventObject.setId(EVENT_LOCAL_ACTION);
	ActionEventData data;

	data.packetSender = pPacketSender;
	data.type = TargetNone;
	data.x = 0;
	data.y = 0;
	data.target = NULL;

	//通用部分
	data.byProgramm = ACTION_PROGRAMM;
	data.id		= ((war3::PacketAction *)pPacket)->actionId;
	data.flag	= ((war3::PacketAction *)pPacket)->flag;
	data.usingItem = ObjectToHandle(CItemFromHash(	&(((war3::PacketAction *)pPacket)->hashUsedItem)	));

	//point
	if (packetId == 0x11){
		data.type = TargetPoint;
		data.x = ((war3::PacketActionPoint *)pPacket)->targetX;
		data.y = ((war3::PacketActionPoint *)pPacket)->targetY;
	}

	//target
	if (packetId == 0x12){
		data.type = Target;
		data.x = ((war3::PacketActionTarget *)pPacket)->targetX;
		data.y = ((war3::PacketActionTarget *)pPacket)->targetY;
		data.target = ObjectToHandle(AgentFromHash(	&(((war3::PacketActionTarget *)pPacket)->hashWidgetTarget)	));
	}

	//drop item
	if (packetId == 0x13){
		data.type = DropItem;
		data.x = ((war3::PacketActionDropItem *)pPacket)->targetX;
		data.y = ((war3::PacketActionDropItem *)pPacket)->targetY;
		data.target = ObjectToHandle(AgentFromHash(	&(((war3::PacketActionDropItem *)pPacket)->hashTarget)	));
		data.transferItem = ObjectToHandle(CItemFromHash(	&(((war3::PacketActionDropItem *)pPacket)->hashItem)	));
	}
	
	//to add

	//send
	PacketEventObject.setData<ActionEventData> (&data);
	MainDispatcher()->dispatch(&PacketEventObject);
}

static Event ControlGroupEventObj;
void ControlGroupAssignEventDispatch ( war3::PacketControlGroupAssign *pPacket ) {
	ControlGroupEventData data;
	ControlGroupEventObj.setId(EVENT_CONTROL_GROUP_ASSIGN);
	data.reason = ControlGroupEventData::REASON_ASSIGN;
	data.numGroup = pPacket->numGroup;
	ControlGroupEventObj.setData<ControlGroupEventData>(&data);
	MainDispatcher()->dispatch(&ControlGroupEventObj);
}

struct PacketHistoryInfo {
	float timeGame;
	uint32_t id;
	PacketHistoryInfo (float _time, uint32_t _id) : timeGame(_time), id(_id) { }
};
static std::list<PacketHistoryInfo> LocalPacketQueue, LocalActionPacketQueue;
void PacketQueueRefresh(std::list<PacketHistoryInfo> *queue){
	if (queue->size() > 0x100) {
		OutputScreen(10, "Local packet queue overrun: id = 0x%X", queue->rbegin()->id);
		while(queue->size() > 0x100){
			queue->pop_front();//防止过长
		}
	}
}

static Event packetEvtObj;
void PacketAnalyze (void *pPacketSender) {
	war3::PacketSender *sender = (war3::PacketSender *)pPacketSender;
	uint8_t packetId = *(uint8_t *)(sender->packet);

//	当processing状态时：检测【非本程序所发的】封包：（即玩家操作和war3自动产生的操作）
//	只考虑下列封包 动作(0x10 ~ 0x14)，选择单位(0x16)，选择编队(0x18)，切换子组(0x19)，刷新(0x1A)
//	5.a. 遇到封包为 动作(0x10 ~ 0x14, 0x1D, 0x1E)，加插5, 6, 7后继续
//	5.b. 遇到封包为 选择编队(0x18)，加插7后继续
//	5.c. 遇到封包为 选择单位(0x16)，刷新(0x1A)，切换子组(0x19)，选择物品(0x1C)：拦截封包使之无效化
	if (ACTION_PROCESS && !ACTION_PROGRAMM){
		switch (packetId) {
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x1D:
		case 0x1E:
		case 0x61: //按下ESC
		case 0x66: //进入选择技能子菜单
		case 0x67: //进入建造子菜单
			PacketJustInTimeActionSelectBack(); break;
		case 0x18:
			PacketJustInTimeActionClear(); break;
		case 0x16:
		case 0x1A:
		case 0x19:
		case 0x1C:
			//OutputScreen(0,0,10,"destroy packet!");
			PacketSenderDestroy(sender); return;//break;
		}
	}

//	any packet sent event
	if (IsInGame()){//MUSTDO 竟然会崩溃
		packetEvtObj.setId(EVENT_PACKET);
		MainDispatcher()->dispatch(&packetEvtObj);
	}


//	local action sent event
//	0x10 ~ 0x14
	switch (packetId) {
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x13:
	case 0x14:
		PacketEventDispatch(sender, sender->packet, packetId); break;
	}

//	local control group assign event
//	0x17
	switch (packetId) {
	case 0x17:
		ControlGroupAssignEventDispatch((war3::PacketControlGroupAssign *)sender->packet);
	}

//	本地系统
	//LocalPacketQueue.push_back(PacketHistoryInfo(Time(), packetId));
	//PacketQueueRefresh(&LocalPacketQueue);
	if (packetId >= 0x10 && packetId <= 0x14){
		LocalActionPacketQueue.push_back(PacketHistoryInfo(Time(), packetId));
		PacketQueueRefresh(&LocalActionPacketQueue);
	}
}

void PacketNetEventAnalyze (war3::CEvent *evt) {
	if (!evt) return;
	uint32_t id = evt->id;
	//if (id < 0x40000000) OutputScreen(10, "event id = 0x%X", id);
	if (id >= 0xA0000 && id < 0x40000000) //范围内
	{
		uint8_t playerId = ((uint8_t *)evt)[0x15];

		//任意玩家：计算APM
		APMUpdateAction(playerId, (id-0xA0000));

		//本地玩家：发布任意本地netevent事件
		if (playerId == PlayerLocal())
		{	
			if (IsInGame()){
				Event localNetEvt;
				localNetEvt.setId(EVENT_LOCAL_NETEVENT);
				MainDispatcher()->dispatch(&localNetEvt);
			}

			id -= 0xA0000;
			std::list<PacketHistoryInfo>::iterator iter;
			bool found = false;
			/*
			for (iter = LocalPacketQueue.begin(); iter != LocalPacketQueue.end(); ++iter){
				if (iter->id == id) { found = true; break; }
			}
			if (found) {
				while (LocalPacketQueue.front().id != id) {
					LocalPacketQueue.pop_front();
				}
				LocalPacketQueue.pop_front();
			}
			*/

			if (id >= 0x10 && id <= 0x14) {
				found = false;
				for (iter = LocalActionPacketQueue.begin(); iter != LocalActionPacketQueue.end(); ++iter){
					if (iter->id == id) { found = true; break; }
				}
				if (found) {
					while (LocalActionPacketQueue.front().id != id) {
						LocalActionPacketQueue.pop_front();
					}
					float lag = Time() - LocalActionPacketQueue.front().timeGame;
					if (lag > 0 && lag < 2.5f){//设置阈值防止bug
						Latency_Update(lag);
					}
					while (LocalActionPacketQueue.size() && LocalActionPacketQueue.front().id == id) {//如果有连续多个相同的记录，可认为是相同操作而一并消除
						LocalActionPacketQueue.pop_front();
					}
				}
			}

		}
	}
}

/*
计划
Just-in-time selection

用到函数
SelectedUnitGet		获取本地选择(UI)
ActiveSubgroupGet	获取本地高亮子组(UI)

对单位数组toSelect发布动作action：

1. 如果 !processing, 
   current <- 本地选择(UI); processing <- true;

[ 仅当 current != toSelect
  2. 移除current
  3. 添加toSelect; current <- toSelect
     刷新(0x1A); 切换子组toSelect[0] (0x19)
]

4. action

[ 5, 6, 7的执行见下文

  [ 仅当 current != 本地选择(UI)
    5. 移除current
    6. 添加 本地选择(UI)
       刷新(0x1A); 切换子组 本地高亮子组(0x19)
  ]
  7. current <- 空; processing <- false
]

当processing状态时：检测【非本程序所发的】封包：（即玩家操作和war3自动产生的操作）
只考虑下列封包 动作(0x10 ~ 0x14)，选择单位(0x16)，选择编队(0x18)，切换子组(0x19)，刷新(0x1A)

5.a. 遇到封包为 动作(0x10 ~ 0x14, 0x1D, 0x1E)，加插5, 6, 7后继续
5.b. 遇到封包为 选择编队(0x18)，加插7后继续
5.c. 遇到封包为 选择单位(0x16)，刷新(0x1A)，切换子组(0x19)，选择物品(0x1C)：拦截封包使之无效化

一个随机的倒计时，按概率随时间增大恢复概率：例如0.5秒后有x%概率恢复选择，1秒后有2x%概率，1.5秒有4x%概率。。。

原理：本地选择(UI)与本地高亮子组(UI)总是对应所显示的单位选择状态，因此完全符合玩家设想
选择编队事件与选择单位包都会影响到本地选择(UI)，切换子组会影响到本地高亮子组(UI)
由于选择编队事件总是载入整个编队覆盖原本所选，因此可以直接允许
选择单位及切换高亮如果不拦截封包，可能导致同步选择bug，因为所发的封包不对应“真正”本地选择
在本地选择(UI)与真实本地选择异步的过程中，单位数组current记录了真实本地选择。
在一个玩家动作到来时，拦截并加插选择包，使得本地选择恢复UI所选。

*/

void Packet_Cleanup() {
	APM_Cleanup();
	ACTION_PROGRAMM_END
	PacketJustInTimeActionClear();
	JITSelectBackTimer->destroy();
	LocalPacketQueue.clear();
	LocalActionPacketQueue.clear();
}

void Packet_Init() {
	JITSelectBackTimer = GetTimer(0.1, JITSelectBackTimerFunc, true);
	JITSelectBackTimer->start();
	APM_Init();
}