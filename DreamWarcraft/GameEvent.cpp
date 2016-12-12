#include "stdafx.h"
#include "Game.h"
#include "BinaryDumper.h"
#include "Tools.h"

//static BinaryDumper Dumper("EventDump.txt");
static uint8_t DumpData[0x50];

void GameEventAnalyze (void *pEvent) {
	uint32_t size = TryDumpObject(pEvent, DumpData, 0x50);
	if (size) {
		//Dumper.dump(pEvent, size, RTTIClassNameGet(pEvent));
		//OutputScreen(10, RTTIClassNameGet(pEvent));
	}
}