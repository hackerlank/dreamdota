#include "stdafx.h"
#include "../DreamAuth2/StringManager.h"

namespace StringManager {
std::string GetStringCache;
DecryptorsDataType DecryptorsData;
CRITICAL_SECTION Cs;
struct StringDataType {
	BYTE* data;
	uint32_t size;
} StringData = {0};

template <uint32_t KEY>
uint32_t DecryptBlock(uint32_t src) {
	return src ^ KEY;
}

DecryptorsDataType* GetDecryptorsData() {
	return &DecryptorsData;
}

void Init(BYTE* data, uint32_t size) {
	VMProtectBeginVirtualization("StringManager::Init");
	InitializeCriticalSectionAndSpinCount(&Cs, 0x00000400); 

	StringData.data = new BYTE[size];
	StringData.size = size;
	memcpy_s(StringData.data, size, data, size);

	DecryptorsType decryptors;
#define REGISTER_DECRYPTOR(i, key) decryptors.decryptors[i] = DecryptBlock<key>
	REGISTER_DECRYPTOR(0, 0x4b2856e6);
	REGISTER_DECRYPTOR(1, 0x80ca16ad);
	REGISTER_DECRYPTOR(2, 0xa18c89d8);
	REGISTER_DECRYPTOR(3, 0x6788be03);
	REGISTER_DECRYPTOR(4, 0x9312beef);
	REGISTER_DECRYPTOR(5, 0x86187a8);
	REGISTER_DECRYPTOR(6, 0x121324ad);
	REGISTER_DECRYPTOR(7, 0x41715222);
	REGISTER_DECRYPTOR(8, 0xe9630c9b);
	REGISTER_DECRYPTOR(9, 0x125597a);
	REGISTER_DECRYPTOR(10, 0x4829944e);
	REGISTER_DECRYPTOR(11, 0x126de4e0);
	REGISTER_DECRYPTOR(12, 0xe0b11e);
	REGISTER_DECRYPTOR(13, 0x29438f94);
	REGISTER_DECRYPTOR(14, 0x9d576b4c);
	REGISTER_DECRYPTOR(15, 0xd65264d8);
	REGISTER_DECRYPTOR(16, 0x2b5f3316);
	REGISTER_DECRYPTOR(17, 0x26e810b0);
	REGISTER_DECRYPTOR(18, 0x1870979a);
	REGISTER_DECRYPTOR(19, 0xa2fb1b4b);
	REGISTER_DECRYPTOR(20, 0xc51d79f5);
	REGISTER_DECRYPTOR(21, 0x557a3f53);
	REGISTER_DECRYPTOR(22, 0x4a4e1286);
	REGISTER_DECRYPTOR(23, 0x15e742b5);
	REGISTER_DECRYPTOR(24, 0x7d238c72);
	REGISTER_DECRYPTOR(25, 0x27d13d7f);
	REGISTER_DECRYPTOR(26, 0x44ab904e);
	REGISTER_DECRYPTOR(27, 0xc9585bba);
	REGISTER_DECRYPTOR(28, 0x6442f916);
	REGISTER_DECRYPTOR(29, 0x9530d74b);
	REGISTER_DECRYPTOR(30, 0x8dc34e9a);
	REGISTER_DECRYPTOR(31, 0x559531d);
#undef REGISTER_DECRYPTOR
	DecryptorsData.SetData(&decryptors);
	memset(&decryptors, 0, sizeof(DecryptorsType));

	VMProtectEnd();
}

NOINLINE void SetData(BYTE* data, uint32_t size) {
	VMProtectBeginVirtualization("StringManager::SetData");
	EnterCriticalSection(&Cs); 
	if (StringData.data)
		delete [] StringData.data;
	StringData.data = new BYTE[size];
	StringData.size = size;
	memcpy_s(StringData.data, size, data, size);
	LeaveCriticalSection(&Cs); 
	VMProtectEnd();
}

void Cleanup() {
	VMProtectBeginVirtualization("StringManager::Cleanup");
	EnterCriticalSection(&Cs);
	delete [] StringData.data;
	StringData.size = 0;
	LeaveCriticalSection(&Cs); 
	DeleteCriticalSection(&Cs);
	VMProtectEnd();
}

INLINE uint32_t GetDword(DecryptorsType* decryptors, uint32_t index) {
	uint32_t d = index % 32;
	uint32_t* dword_data = (uint32_t*)StringData.data;
	return decryptors->decryptors[d](dword_data[index]);
}

INLINE void GetString(DecryptorsType* decryptors, uint32_t id, uint32_t size, char* buffer) {
	uint32_t count = GetDword(decryptors, 0);					//×Ö·û´®×ÜÊý
	uint32_t offset = GetDword(decryptors, 1 + id);				//Ä¿±ê×Ö·û´®Æ«ÒÆ
	uint32_t pos; 
	for (uint32_t i = 0; i < size / 4; ++i) {
		pos = (1 + count + 1 + (offset / 4)) + i;
		((uint32_t*)buffer)[i] =  GetDword(decryptors, pos);
	}	
}

INLINE uint32_t GetStringLength(DecryptorsType* decryptors, uint32_t id) {
	uint32_t count = GetDword(decryptors, 0);					//×Ö·û´®×ÜÊý
	uint32_t offset = GetDword(decryptors, 1 + id);				//Ä¿±ê×Ö·û´®Æ«ÒÆ
	uint32_t size = GetDword(decryptors, 1 + id + 1) - offset;	//Ä¿±ê×Ö·û´®´óÐ¡
	return size;
}

NOINLINE std::string StringUTF8(uint32_t id) {
	std::string rv;
	VMProtectBeginVirtualization("StringManager::StringUTF8");
	EnterCriticalSection(&Cs); 
	DecryptorsType decryptors;
	DecryptorsData.GetData(&decryptors);
	
	uint32_t size = GetStringLength(&decryptors, id);
	char* buffer = new char[size + 1];
	GetString(&decryptors, id, size, buffer);
	buffer[size] = '\0';
	rv.assign(buffer);
	delete [] buffer;
	
	memset(&decryptors, 0, sizeof(DecryptorsType));
	LeaveCriticalSection(&Cs); 
	VMProtectEnd();
	return rv;
}

NOINLINE std::wstring StringUnicode(uint32_t id) {
	std::wstring rv;
	VMProtectBeginVirtualization("StringManage::StringUnicode");
	EnterCriticalSection(&Cs); 
	DecryptorsType decryptors;
	DecryptorsData.GetData(&decryptors);

	uint32_t size = GetStringLength(&decryptors, id);
	char* buffer = new char[size + 1];
	GetString(&decryptors, id, size, buffer);
	buffer[size] = '\0';
	uint32_t req_size = MultiByteToWideChar(CP_UTF8, NULL, buffer, -1, NULL, 0); //any terminating null character included
	wchar_t* buffer_w = new wchar_t[req_size];
	MultiByteToWideChar(CP_UTF8, NULL, buffer, -1, buffer_w, req_size);
	buffer_w[req_size - 1] = '\0';
	rv.assign(buffer_w);

	delete [] buffer_w;
	delete [] buffer;
	memset(&decryptors, 0, sizeof(DecryptorsType));
	LeaveCriticalSection(&Cs);
	VMProtectEnd();
	return rv;
}

}//namespace