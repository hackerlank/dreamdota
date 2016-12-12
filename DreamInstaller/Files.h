#pragma once

namespace Files {
	struct FileInfo {
		const wchar_t* name;
		int rcid;
	};

	const FileInfo* GetFileList();
	size_t GetFileCount();
}