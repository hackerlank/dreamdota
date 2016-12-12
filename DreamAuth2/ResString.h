#include "stdafx.h"
#ifndef RESSTRING_H_
#define RESSTRING_H_

namespace ResString {
#include "ResStringId.inc"

	void Init();
	void Cleanup();

	const wchar_t* GetString(int id, LCID locale_id = 0);

} //namespace

#endif