//仅限于ObjectHookManager.cpp使用

#include "stdafx.h"
#include "Tools.h"

void* __fastcall VtableCallAnalysis(void* obj, uint32_t index);

#define VTABLE_FAKE_MATHOD(NAME, INDEX) \
	void __declspec(naked) NAME##INDEX() { \
		__asm { \
			push edx; \
			mov edx, INDEX; \
			call VtableCallAnalysis; \
			pop edx; \
			jmp eax; \
		} \
	} \