#include "stdafx.h"
#include "LocaleString.h"
#include "Locale.h"
#include "Exception.h"

namespace LocaleString {

bool Inited = false;

NOINLINE void Init() {
	VMProtectBeginVirtualization("LocaleString::Init");

	const Locale::LocaleInfo* info = Locale::CurrentLocaleInfo();
	if (!info)
		GLOBAL_LONGJMP(EXCEPTION_LOCALESTRING_INIT_FAILED);
	StringManager::Init(info->data, info->data_size);
	Inited = true;
	VMProtectEnd();
}

NOINLINE void Cleanup() {
	VMProtectBeginVirtualization("LocaleString::Cleanup");
	if (Inited) {
		StringManager::Cleanup();
	}
	VMProtectEnd();
}

void SetLocale(LCID lcid) {
	const Locale::LocaleInfo* info = Locale::CurrentLocaleInfo();
	if (info)
		StringManager::SetData(info->data, info->data_size);
	else
		Abort(EXCEPTION_LOCALESTRING_INIT_FAILED);
}

}//namespace