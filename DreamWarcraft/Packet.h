#ifndef PACKET_H_INCLUDED_
#define PACKET_H_INCLUDED_
#include "GameStructs.h"
#include "Tools.h"
#include "Jass.h"

//发送packet
void PacketSend (void *pPacket, uint32_t size, bool sendAsProgramm);

//使一个packetSender无效化
void PacketSenderDestroy (void *pPacketSender);

//选择单位组
void PacketSelectionSend (std::set<war3::CUnit *> *set, bool select);

//操作
void PacketJustInTimeActionSend (
	bool useJIT,
	std::set<war3::CUnit *>	*unitSetToSelect,//单位set
	void					*pPacketAction,	//动作packet
	uint32_t				sizePacket,		//packet长度(不含sender)
	bool					sendAsProgramm
	);	

//对packet进行分析
void PacketAnalyze (void *pPacketSender);

//对返回的packet (CNetEvent)进行分析
void PacketNetEventAnalyze (war3::CEvent *evt);

//清理
void Packet_Cleanup();

//初始化
void Packet_Init();

#endif