#include "stdafx.h"
#ifndef GAME_VERSION_H_
#define GAME_VERSION_H_

#include "RemoteMemory.h"

namespace GameVersion {

	struct VersionOffsetType {
		uint32_t version;
		uint32_t version_offset;
		uint32_t cgx_device_vtable_offset;
		uint32_t cgx_device_vtable_0;
	};
	
	static VersionOffsetType VersionOffsets[] = {
		{6374, 0x3A21C0 + 0x20, 0x967A3C, 0x52E190},
		{6378, 0x3A21C0 + 0x20, 0x967A54, 0x52E150},
		{6384, 0x3A2220 + 0x20, 0x967A54, 0x52E1B0},
		{6387, 0x3A2280 + 0x20, 0x967A54, 0x52E210},
		{6397, 0x3A1510 + 0x20, 0x9558FC, 0x52D4E0},
		{6401, 0x3A1740 + 0x20, 0x9558FC, 0x52D710}
	};

	struct GameInfo {
		uint32_t version;
		uint32_t base;
		void* cgx_device;
		void* cgx_device_vtable;
	};

	static const uint32_t VersionCount = sizeof(VersionOffsets) / sizeof(VersionOffsetType);

	//TODO 整理！
	INLINE bool GetGameInfo(HWND win, HANDLE process, GameInfo* result) {
		bool rv = false;
		void* device_ptr = (void*)GetWindowLongPtr(win, GWL_USERDATA);
		uint32_t device_vtable;
		ULONG bytes_read;
		if (ReadRemoteMemory<uint32_t>(process, device_ptr, &device_vtable, &bytes_read) && bytes_read == 4) {
			uint32_t base = 0;
			char mz[2] = {0};
			uint32_t version = 0;
			for (uint32_t i = 0; i < VersionCount; ++i) {
				/*
				base = device_vtable - VersionOffsets[i].cgx_device_vtable_offset;
				if (ReadRemoteMemory(process, (void*)base, mz, 2, &bytes_read) && 
						bytes_read == 2 && 
						mz[0] == 'M' && mz[1] == 'Z') {
					
					if (ReadRemoteMemory(process, (void*)(base + VersionOffsets[i].version_offset), &version, 4, &bytes_read) && 
							bytes_read == 4 && 
							version == VersionOffsets[i].version) {

						result->base = base;
						result->cgx_device = device_ptr;
						result->cgx_device_vtable = (void*)device_vtable;
						result->version = version;

						rv = true;

#ifdef _DEBUG
						OutputDebug("Found base (1).\n");
#endif
						break;
					}
				}
				*/

				//vtable可能被替换，对比第一个虚函数
				void* v0 = NULL;
				if (ReadRemoteMemory(process, (void*)device_vtable, &v0, 4, &bytes_read) && bytes_read == 4) {
					base = (uint32_t)v0 - VersionOffsets[i].cgx_device_vtable_0;
					if (ReadRemoteMemory(process, (void*)base, mz, 2, &bytes_read) && 
							bytes_read == 2 && 
							mz[0] == 'M' && mz[1] == 'Z') {
					
						if (ReadRemoteMemory(process, (void*)(base + VersionOffsets[i].version_offset), &version, 4, &bytes_read) && 
								bytes_read == 4 && 
								version == VersionOffsets[i].version) {

							result->base = base;
							result->cgx_device = device_ptr;
							result->cgx_device_vtable = (void*)device_vtable;
							result->version = version;

							rv = true;
#ifdef _DEBUG
							OutputDebug("Found base (2).\n");
#endif
							break;
						}
					}
				}
			}
		}
		return rv;
	}

}//namespace

#endif