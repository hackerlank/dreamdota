#ifndef SHAREDMEMORY_H_
#define SHAREDMEMORY_H_

namespace SharedMemory {
	const int SMEM_SIZE = 1024;

	void Init();
	void Cleanup();
	DWORD GetId();
	void* Create();
	void* Open();
	void Close();

} //namespace

#endif