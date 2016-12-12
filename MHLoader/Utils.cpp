#include "stdafx.h"
#include "Utils.h"

namespace Utils {
	static wchar_t ModulePath[MAX_PATH];
	static char ModulePathA[MAX_PATH];
	static wchar_t ModuleFileName[MAX_PATH];
	static wchar_t PathBuffer[MAX_PATH];
	static char PathBufferA[MAX_PATH];

	int MessageBoxFormat(HWND hwnd, const wchar_t* title, UINT type, const wchar_t* format, ...) {
		wchar_t buffer[256];
		va_list args;
		va_start(args, format);
		vswprintf_s(buffer, 256, format, args);
		va_end(args);
		return MessageBox(hwnd, buffer, title, type);
	}

	void SetSelfFullPath(const wchar_t* path) {
		wcscpy_s(PathBuffer, MAX_PATH, path);
		wchar_t *filename = wcsrchr(PathBuffer, '\\');
		wcscpy_s(ModuleFileName, MAX_PATH, filename + 1);
		*filename = '\0';
		wcscpy_s(ModulePath, MAX_PATH, PathBuffer);
		WideCharToMultiByte(CP_ACP, NULL, ModulePath, -1, ModulePathA, sizeof(PathBufferA), NULL, NULL);
	}

	const wchar_t* GetSelfPath() {return ModulePath;}
	const char* GetSelfPathA() {return ModulePathA;}
	const wchar_t* GetSelfFileName() {return ModuleFileName;}
	const wchar_t* GetPath(const wchar_t* filename) {swprintf_s(PathBuffer, MAX_PATH, L"%s\\%s", ModulePath, filename);return PathBuffer;}
	const char* GetPathA(const char* filename) {sprintf_s(PathBufferA, MAX_PATH, "%s\\%s", ModulePathA, filename);return PathBufferA;}

	void Init() {
		wchar_t buff[MAX_PATH];
		GetModuleFileName(GetModuleHandle(NULL), buff, MAX_PATH);
		SetSelfFullPath(buff);
	}

	void Cleanup() {

	}
}