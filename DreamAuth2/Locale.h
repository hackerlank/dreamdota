#include "stdafx.h"
#ifndef LOCALE_H_
#define LOCALE_H_

#include <map>

namespace Locale {

struct LocaleInfo {
	const wchar_t* name;
	LCID lcid;
	BYTE* data;
	int data_size;
};

typedef std::map<volatile LCID, LocaleInfo> LocaleMapType;

static const LCID DEFAULT_LOCALE = 0x00000409; //en-us

void Init();
void Cleanup();

LCID SavedLCID();
LCID GetPreferedLCID();
LCID IdentifyLCID();
void SaveLCID(LCID lcid);
bool IsLocaleSelected();

const LocaleMapType& Map();
const LocaleInfo* CurrentLocaleInfo();

}// namespace

#endif