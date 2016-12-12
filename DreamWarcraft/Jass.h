#ifndef API_JASS_H_
#define API_JASS_H_

#include <cstdint>
#include "jass_types.h"
#include "jass_constants.h"
#include "jass_natives.h"
#include "RCString.h"
#include "Tools.h"
#include <fp_call.h>

void Jass_Init(DWORD version, DWORD base);
void Jass_Cleanup();

inline float JASS_FLOAT_CAST(real v) {
	return *(reinterpret_cast<float*>(&v));
}

inline const char* JASSSTR_TO_STR(DWORD string_id) {
	return GetJassReturedString((uint32_t)string_id);
}

extern std::list<war3::RCString*> RCStringArgs;
inline DWORD STR_TO_JASSSTR(const char* str) {
	war3::RCString* rv = RCString::create(str);
	RCStringArgs.push_back(rv);
	return (DWORD)rv;
}

inline void JASS_STR_CLEANUP() {
	for (std::list<war3::RCString*>::iterator iter = RCStringArgs.begin();
		iter != RCStringArgs.end();
		++iter) 
	{
		RCString::destroy(*iter);
	}
	RCStringArgs.clear();
}

namespace JassNativeAPI {
	void Init(int version, uint32_t base);
}


#include "JassNativesWrapper.h.inc"

namespace Jass {
#include "JassNativesBridge.inc"
}
#endif //API_JASS_NATIVE_API_H_