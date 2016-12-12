#include "stdafx.h"
#include "Locale.h"
#include "../DreamWarcraft/Profile.h"

namespace Locale {

bool Inited = false;
LocaleMapType LocaleMap;
bool LocaleSelected = false;
volatile LCID LocaleId;

#define DEFINE_LOCALE(ID, LCID, NAME) \
	info = &(LocaleMap[LCID]); \
	info->data = (BYTE*)LOCALE_DATA_##ID; \
	info->data_size = sizeof(LOCALE_DATA_##ID); \
	info->name = L##NAME; \
	info->lcid = LCID; 
#include "LocaleData.inc"

void Init() {
	LocaleSelected = SavedLCID() > 0;
	LocaleInfo* info = NULL;
#include "Locale.inc"
	LCID saved = SavedLCID();
	LocaleId = saved ? saved : IdentifyLCID();
	Inited = true;
}

void Cleanup() {
	if (Inited) {

	}
}

const LocaleMapType& Map() {
	return LocaleMap;
}

LCID SavedLCID() {
	return ProfileGetInt(L"Language", L"LocaleID", 0);
}

void SaveLCID(LCID lcid) {
	LocaleId = lcid;
	ProfileSetInt(L"Language", L"LocaleID", lcid);
}

LCID IdentifyLCID() {
	LCID defaultLCID = GetSystemDefaultLCID();
	WORD default_lang = LANGIDFROMLCID(defaultLCID);
	for (LocaleMapType::iterator iter = LocaleMap.begin(); iter != LocaleMap.end(); ++iter) {
		WORD lang_id = LANGIDFROMLCID(iter->second.lcid);
		if (lang_id == default_lang) {
			return iter->second.lcid;
		}
	}
	return DEFAULT_LOCALE;
}

LCID GetPreferedLCID() {
	return LocaleId;
}

bool IsLocaleSelected() {
	return SavedLCID() > 0;
}

const LocaleInfo* CurrentLocaleInfo() {
	return LocaleMap.count(LocaleId) ? &(LocaleMap[LocaleId]) : NULL;
}

}// namespace