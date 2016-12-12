#include "stdafx.h"
#include "ResString.h"
#include "Exception.h"
#include "Locale.h"

namespace ResString {
	typedef std::map<int, const wchar_t*> ResStringMapType;
	typedef std::map<LCID, ResStringMapType> LocaleResStringMapType;

	bool Inited = false;
	LocaleResStringMapType StringMap;

	void Init() {
#include "ResString.inc"
		Inited = true;
	}

	const wchar_t* GetString(int id, LCID locale_id) {
		const wchar_t* rv = L"<null>";
		if (!locale_id)
			locale_id = Locale::GetPreferedLCID();
		if (StringMap.count(locale_id) && StringMap[locale_id].count(id)) {
			rv = StringMap[locale_id][id];
		}
		return rv;
	}

	void Cleanup() {
		if (Inited) {

		}
	}

} //namespace