#include "stdafx.h"
#include "LanguageSelect.h"
#include "DialogLanguageSelect.h"
#include "Locale.h"
#include "LocaleString.h"

static void OnLanguageSelectHandler(LCID selected) {
	Locale::SaveLCID(selected);
	LocaleString::SetLocale(selected);
}

void LanguageSelect(bool force_reselect) {
	if (Locale::IsLocaleSelected() && !force_reselect)
		return;

	const Locale::LocaleMapType& map = Locale::Map();
	LCID select = Locale::GetPreferedLCID();
	DialogLanguageSelect dlg;
	
	const wchar_t* select_name = NULL;
	for (Locale::LocaleMapType::const_iterator iter = map.begin(); iter != map.end(); ++iter) {
		dlg.AddLocale(iter->second.name, iter->second.lcid);
		if (iter->second.lcid == select)
			select_name = iter->second.name;
	}

	dlg.SelectString(select_name);

	dlg.onLanguageSelect += OnLanguageSelectHandler;
	dlg.Show(true);
	dlg.WaitClose();
}