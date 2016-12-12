// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT _WIN32_WINNT_WINXP
       
#define STRICT 1
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN 
#define WIN32_EXTRA_LEAN
#define VC_EXTRALEAN
// Windows Header Files:
#include <windows.h>


// TODO: reference additional headers your program requires here
#include <map>
#include <deque>
#include <set>
#include <list>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <assert.h>
#include <VMP.h>
#include <Shellapi.h>
#include <WindowsX.h>

// Macros
#define INLINE __forceinline
#define NOINLINE __declspec(noinline)

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

int OutputDebug(const wchar_t *format, ...);
int OutputDebug(const char *format, ...);

#define GETSET(type, var) \
private: \
	type var##_; \
public: \
   type var() {\
   return var##_; \
   }\
   void set_##var(type val) {\
   var##_ = val; \
   }