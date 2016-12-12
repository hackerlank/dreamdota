#pragma once


const wchar_t* _(int id);

namespace LocaleString {
	enum LocaleIdEnum {
		EN_US,
		ZH_CN,
		MAX_LOCALE_ID
	};

	enum StringIdEnum {
		INIT_FAILED,
		SELECT_DIR,
		TITLE,
		READ_RES_ERR,
		WRITE_ERR,
		SUCCESS,
		FAILURE,
		COPYING,
		WAIT_EXIT,
		MAX_STRING_ID
	};

	void Init();
	void Cleanup();
}