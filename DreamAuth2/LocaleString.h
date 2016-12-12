#include "stdafx.h"
#ifndef LOCALE_STRING_H_
#define LOCALE_STRING_H_

#include "EncryptedData.h"
#include "StringManager.h"

namespace LocaleString {
	NOINLINE void Init();
	NOINLINE void Cleanup();
	void SetLocale(LCID lcid);
}//namespace

#endif