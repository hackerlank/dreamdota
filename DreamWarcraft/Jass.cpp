#include "stdafx.h"
#include "jass.h"

#include "native_offsets_6374.h"
#include "native_offsets_6378.h"
#include "native_offsets_6384.h"
#include "native_offsets_6387.h"
#include "native_offsets_6397.h"
#include "native_offsets_6401.h"

void Jass_Init(DWORD version, DWORD base) {
	switch (version) {
	case 6374:
		JassNativeAPI::Init_6374(base);
		break;
	case 6378:
		JassNativeAPI::Init_6378(base);
		break;
	case 6384:
		JassNativeAPI::Init_6384(base);
		break;
	case 6387:
		JassNativeAPI::Init_6387(base);
		break;
	case 6397:
		JassNativeAPI::Init_6397(base);
		break;
	case 6401:
		JassNativeAPI::Init_6401(base);
		break;
	}
}

std::list<war3::RCString*> RCStringArgs;

void Jass_Cleanup() {
	JASS_STR_CLEANUP();
}


#include "JassNativesImpl.inc"
#include "JassNativesWrapper.impl.inc"