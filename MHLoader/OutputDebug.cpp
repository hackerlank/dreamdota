#include "stdafx.h"

int OutputDebug(const wchar_t *format, ...) {
#if defined(_DEBUG) || !defined(_VMP)
	wchar_t buffer[256];
	va_list args;
	va_start(args, format);
	int rv = vswprintf_s(buffer, 256, format, args);
	va_end(args);
	OutputDebugStringW(buffer);
	return rv;
#else
	format;
	return 0;
#endif
}

int OutputDebug(const char *format, ...) {
#if defined(_DEBUG) || !defined(_VMP)
		char buffer[256];
		int rv;
		va_list args;
		va_start(args, format);
		rv = vsprintf_s(buffer, 256, format, args);
		va_end(args);

		OutputDebugStringA(buffer);
		return rv;
#else
		format;
		return 0;
#endif
}