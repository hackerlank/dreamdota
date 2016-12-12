#include "GameDef.h"
#include <VMP.h>
#include <fp_call.h>

namespace GameDef {

static DWORD VI;
static DWORD GameBase;

DWORD GetGameBase() {return GameBase;}

#pragma optimize( "", off )

VersionOffsetType* IdentifyVersion() {
	VersionOffsetType* rv = NULL;
	VMProtectBeginVirtualization("IdentifyVersion");
	DWORD game = GameBase = (DWORD)GetModuleHandle(L"game.dll");
	if (game) {
		for (int i = 0; i < sizeof(VersionOffsets) / sizeof(VersionOffsetType); ++i) {
			VersionOffsetType& node = VersionOffsets[i];
			if (!IsBadReadPtr((void*)(game + node.PVersionId), 4)) {
				if (*(DWORD*)(game + node.PVersionId) == node.version) {
					VI = i;
					rv = &node;
				}
			}
		}
	}
	VMProtectEnd();
	return rv;
}


#pragma optimize( "", on ) 

void* GameTlsDataGet(DWORD index) {
	DWORD tlsIndex = *(DWORD*)(VersionOffsets[VI].PTLSIndex + GameBase);
	void* tlsValue = TlsGetValue(tlsIndex);
	if (tlsValue)
		return aero::offset_element_get<void*>(tlsValue, index * 4);
	else
		return NULL;
}

}