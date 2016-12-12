#include "stdafx.h"
#include "LocaleString.h"

namespace LocaleString {
	LocaleIdEnum LocaleId;

	struct StringDataType {
		const wchar_t* string[MAX_LOCALE_ID];
	};

	StringDataType StringData[MAX_STRING_ID] = {
		{L"Initialize installer failed", L"初始化安装程序失败。"},
		{L"Select install directory", L"选择安装目录"},
		{L"DreamDota Installer %u.%02u.%u.%04u", L"DreamDota 安装程序 %u.%02u.%u.%04u"},
		{L"Error reading resource.", L"读取资源错误。"},
		{L"Unable to write:\n%s", L"无法写入文件:\n%s"},
		{L"Installation completed, starting DreamDota...", L"安装完成，正在启动DreamDota..."},
		{L"Installation interupted.", L"安装中断。"},
		{L"Copying %s...", L"正在复制 %s..."},
		{L"Waiting process for exit...", L"正在等待进程退出..."}
	};

	void Init() {
		LocaleId = GetSystemDefaultLCID() == 2052 ? ZH_CN : EN_US;
	}

	void Cleanup() {

	}
}

const wchar_t* _(int id) {
	return LocaleString::StringData[id].string[LocaleString::LocaleId];
}