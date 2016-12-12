#ifndef STRING_MANAGER_H_INCLUDED
#define STRING_MANAGER_H_INCLUDED

#include <string>
#include "EncryptedData.h"
#include "LocaleStringId.inc"

namespace StringManager {
	typedef uint32_t (*DecryptorType)(uint32_t src);
	struct DecryptorsType {
		DecryptorType decryptors[32];
	};

	typedef EncryptedData<DecryptorsType> DecryptorsDataType;

	NOINLINE void Init(BYTE* data, uint32_t size);
	NOINLINE void Cleanup();
	NOINLINE void SetData(BYTE* data, uint32_t size);

	DecryptorsDataType* GetDecryptorsData();

	NOINLINE std::string StringUTF8(uint32_t id);
	NOINLINE std::wstring StringUnicode(uint32_t id);
	
	extern std::string GetStringCache;
	INLINE const char* GetString(uint32_t id) {
		GetStringCache = StringUTF8(id);
		return GetStringCache.c_str();
	}

}//namespace

#endif