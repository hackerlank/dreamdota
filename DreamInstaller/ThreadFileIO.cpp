#include "stdafx.h"
#include "LocaleString.h"
#include "ThreadFileIO.h"
#include "Files.h"
#include "Main.h"
#include <string.h>

enum IOState {
	STATE_ERROR		= -1,
	STATE_NONE		= 0,
	STATE_OK		= 1,
	STATE_CANCELED	= 2
};

void ThreadFileIO::Work() {
	wchar_t buffer_fn[MAX_PATH];
	wchar_t buffer[MAX_PATH + 30];
	const wchar_t* InstallPath = GetInstallPath();
	HWND dialog = (HWND)this->arg();
	HMODULE module = GetModuleHandle(NULL);
	const Files::FileInfo* info = Files::GetFileList();
	size_t count = Files::GetFileCount();

	ProgressInfo pi;
	pi.total = count;

	HRSRC src;
	uint32_t size;
	HGLOBAL global;
	void* ptr;
	FILE* fp;
	for (size_t i = 0; i < count; ++i) {
		swprintf_s(buffer_fn, sizeof(buffer_fn) / sizeof(wchar_t), L"%s\\%s", InstallPath, info[i].name);
		this->onFileChange.Invoke(info[i].name);
		src = FindResource(module, MAKEINTRESOURCE(i + 1), MAKEINTRESOURCE(10));
		if (!src)
			Abort(dialog, _(LocaleString::READ_RES_ERR));
		size = SizeofResource(module, src);
		if (!size)	
			Abort(dialog, _(LocaleString::READ_RES_ERR));
		global = LoadResource(module, src);
		if (!global)
			Abort(dialog, _(LocaleString::READ_RES_ERR));
		ptr = LockResource(global);
		if (!ptr)
			Abort(dialog, _(LocaleString::READ_RES_ERR));
		
		IOState state = STATE_NONE;
		while (state <= STATE_NONE) {
			const wchar_t *token = info[i].name, *pos = info[i].name;
			wchar_t dirpath[MAX_PATH];
			wcscpy_s(dirpath, InstallPath);
			wcscat_s(dirpath, L"/");
			while(NULL != (token = wcsstr(pos, L"/"))) {
				wcsncat_s(dirpath, pos, token - pos + 1);
				pos = token + 1;
				_wmkdir(dirpath);
			}

			fp = NULL;
			if (0 == _wfopen_s(&fp, buffer_fn, L"wb") && fwrite(ptr, size, 1, fp) == 1) {
				fclose(fp);
				state = STATE_OK;
			} else {
				if (fp) {
					fclose(fp);
					fp = NULL;
				}
				swprintf_s(buffer, sizeof(buffer) / sizeof(wchar_t), _(LocaleString::WRITE_ERR), buffer_fn);
				if (IDCANCEL == MessageBox(dialog, buffer, NULL, MB_ICONERROR | MB_RETRYCANCEL)) {
					state = STATE_CANCELED;
					this->set_result(false);
				}
			}
		}

		UnlockResource(global);
		FreeResource(src);

		pi.now = i + 1;
		this->onProgress.Invoke(&pi);
	}
	this->set_result(true);
}