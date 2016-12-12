#include "stdafx.h"
#ifndef _VMP
int OutputDebug(const wchar_t *format, ...) {
	wchar_t buffer[256];
	va_list args;
	va_start(args, format);
	int rv = vswprintf_s(buffer, 256, format, args);
	va_end(args);
	OutputDebugStringW(buffer);
	return rv;
}

int OutputDebug(const char *format, ...) {
	char buffer[256];
	int rv;
	va_list args;
	va_start(args, format);
	rv = vsprintf_s(buffer, 256, format, args);
	va_end(args);

	OutputDebugStringA(buffer);
	return rv;
}
#endif