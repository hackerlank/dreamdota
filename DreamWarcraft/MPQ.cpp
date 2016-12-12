#include "stdafx.h"
#include "MPQ.h"
#include "Foundation.h"

static HANDLE DreamDotaMPQHandle;
static char moduleName[MAX_PATH];

HANDLE DreamDotaMPQHandleGet() {
	return DreamDotaMPQHandle;
}

void MPQ_Init() {
	Storm::FileOpenArchive(GetPath(GetSelfFileName()), 10, 6, &DreamDotaMPQHandle);
}

void MPQ_Cleanup() {
	Storm::FileCloseArchive(DreamDotaMPQHandle);
}