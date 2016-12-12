#include "ObjectHookManager.h"
#include <VMP.h>

static ObjectHookManager* Manager = NULL;

ObjectHookManager::ObjectHookManager() {

}

void WriteVtable(void* obj, void** orginal) {
	__try {
		*(void***)(obj) = orginal;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
#ifdef _DEBUG
		void* dummy = orginal;
		OutputDebug("WriteVtable : Bad write ptr.(ObjectName: %s)", RTTIClassNameGet(&dummy));
#endif
	}	
}

ObjectHookManager::~ObjectHookManager() {
	ObjectHookInfoMapType::iterator iter;
	for (iter = this->map_.begin(); iter != this->map_.end(); ++iter) {
		if (iter->second.autoCleanup) {
			(void*)((DWORD)iter->second.fakeVtable - 4);
		}
		WriteVtable(iter->first, iter->second.realVtable);
	}
}

ObjectHookInfo* ObjectHookManager::getObjectHookInfo(void* object) {
	ObjectHookInfo* rv = NULL;
	if (this->map_.count(object)) {
		rv = &(this->map_[object]);
	}
	return rv;	
}

void** ObjectHookManager::replace(void* object, DWORD vtableLength, bool dynamic) {
	ObjectHookInfo* info = &(this->map_[object]);
	info->realVtable = *(void***)object;
	info->mem = new void*[vtableLength + 1]; //+1 for RTTI;
	info->fakeVtable = (void**)((DWORD)info->mem + 4);
	info->isDynamic = dynamic;
	info->methodCount = vtableLength;
	info->autoCleanup = true;
	memcpy_s(info->mem, sizeof(void*) * (vtableLength + 1), (void*)((DWORD)info->realVtable - 4), sizeof(void*) * (vtableLength + 1));
	*(void***)object = info->fakeVtable;
	return info->realVtable;
}

/*
void** ObjectHookManager::replace(void* object, void** vtable, DWORD vtableLength) {
	ObjectHookInfo* info = &(this->map_[object]);
	info->realVtable = *(void***)object;
	info->fakeVtable = vtable;
	info->isDynamic = false;
	info->methodCount = vtableLength;
	info->autoCleanup = true;
	*(void***)object = info->fakeVtable;
	return info->realVtable;
}
*/

void* ObjectHookManager::apply(void* object, DWORD offset, void* detour) {
	VMProtectBeginVirtualization("ObjectHookApply");
	if (this->map_.count(object)) {
		ObjectHookInfo* info = &(this->map_[object]);
		info->fakeVtable[offset / sizeof(void*)] = detour;
		return info->realVtable[offset / sizeof(void*)];
	}
	VMProtectEnd();
	return NULL;
}

void ObjectHookManager::cancel(void* object, DWORD offset) {
	VMProtectBeginVirtualization("ObjectHookCancel");
	if (this->map_.count(object)) {
		ObjectHookInfo* info = &(this->map_[object]);
		info->fakeVtable[offset / sizeof(void*)] = this->getOrignal(object, offset);
	}
	VMProtectEnd();
}

void ObjectHookManager::restore(void* object) {
	VMProtectBeginVirtualization("ObjectHookRestore");
	if (this->map_.count(object)) {
		ObjectHookInfo* info = &(this->map_[object]);
		WriteVtable(object, info->realVtable);
		this->map_.erase(object);
	}
	VMProtectEnd();
}

void* ObjectHookManager::getOrignal(void* object, DWORD offset) {
	void* rv = NULL;
	if (this->map_.count(object)) {
		rv = this->map_[object].realVtable[offset / sizeof(void*)];
	}
	return rv;
}

void ObjectHookManager::clearAllDynamic() {
	ObjectHookInfoMapType::iterator iter;
	for (iter = this->map_.begin(); iter != this->map_.end(); ) {
		ObjectHookInfo* info = &(iter->second);
		if (info->isDynamic) {
			delete [] iter->second.mem;
			iter = this->map_.erase(iter);
		} else
			++ iter;
	}
}

ObjectHookManager* GetObjectHookManager() {
	return Manager;
}

void ObjectHookManager_Init() {
	Manager = new ObjectHookManager();
}

void ObjectHookManager_Cleanup() {
	delete Manager;
}