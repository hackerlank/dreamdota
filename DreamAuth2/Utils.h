#include "stdafx.h"
#ifndef UTILS_H_
#define UTILS_H_

namespace Utils {
	void Init();
	void Cleanup();

	int MessageBoxFormat(HWND hwnd, const wchar_t* title, UINT type, const wchar_t* text_format, ...);

	void SetSelfFullPath(const wchar_t* path);
	const wchar_t* GetSelfPath();
	const char* GetSelfPathA();
	const wchar_t* GetSelfFileName();
	const wchar_t* GetPath(const wchar_t* filename);
	const char* GetPathA(const char* filename);
} //namespace

#define SETCONTROLTEXT(var, string_id) \
	this->##var##->SetWindowText(ResString::GetString(ResString::##string_id))

#endif