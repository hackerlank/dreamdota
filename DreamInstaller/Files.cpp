#include "stdafx.h"
#include "Files.h"

namespace Files {
	const FileInfo Files[] = {
#include "Files.inc"
		{NULL, 0}
	};

	const FileInfo* GetFileList() {
		return Files;
	}

	size_t GetFileCount() {
		return sizeof(Files) / sizeof(FileInfo) - 1;
	}
}