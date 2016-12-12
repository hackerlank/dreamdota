#pragma once

#include <Windows.h>
#include <map>

struct ObjectHookInfo {
	DWORD methodCount;
	void* mem;
	void** realVtable;
	void** fakeVtable;
	bool isDynamic;
	bool autoCleanup;
};

typedef std::map<void*, ObjectHookInfo> ObjectHookInfoMapType;

class ObjectHookManager {
public:
	ObjectHookManager();
	~ObjectHookManager();
	
	void** replace(void* object, DWORD vtableLength, bool dynamic = false);
	void** replace(void* object, void** vtable, DWORD vtableLength);
	void* apply(void* object, DWORD offset, void* detour);
	void cancel(void* object, DWORD offset);
	void restore(void* object);
	void clearAllDynamic();
	void* getOrignal(void* object, DWORD offset);
	ObjectHookInfo* getObjectHookInfo(void* object);
private:
	ObjectHookInfoMapType map_;
};

ObjectHookManager* GetObjectHookManager();
void ObjectHookManager_Init();
void ObjectHookManager_Cleanup();