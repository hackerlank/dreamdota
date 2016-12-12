#include "Exception.h"
#include "LocaleString.h"

int EMsgMap[] = {
	-1,
	LocaleString::INIT_FAILED
};

const wchar_t* EMsg(EEnum e) {
	return _(EMsgMap[e]);
}