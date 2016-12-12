#ifndef VMP_H_INCLUDED
#define VMP_H_INCLUDED

#ifdef _VMP
#include <VMProtectSDK.h>
#else
#define VMProtectBeginVirtualization(tag)
#define VMProtectBeginMutation(tag)
#define VMProtectBeginUltra(tag)
#define VMProtectEnd()
#define VMProtectIsValidImageCRC()
#endif

#endif // VMP_INCLUDED
