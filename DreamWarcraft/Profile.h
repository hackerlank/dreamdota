#ifndef PROFILE_H_
#define PROFILE_H_

#define PROFILE_FILENAMEW L"DreamWarcraftConfig.txt"
#define PROFILE_FILENAMEA "DreamWarcraftConfig.txt"
#ifdef _UNICODE
#define PROFILE_FILENAME PROFILE_FILENAMEW
#else
#define PROFILE_FILENAME PROFILE_FILENAMEA
#endif

void ProfileSetInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int val);
int ProfileGetInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int defaultVal);
int ProfileFetchInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int defaultVal);

void ProfileSetBool(LPCTSTR lpAppName, LPCTSTR lpKeyName, bool val);
bool ProfileGetBool(LPCTSTR lpAppName, LPCTSTR lpKeyName, bool defaultVal);
bool ProfileFetchBool(LPCTSTR lpAppName, LPCTSTR lpKeyName, bool defaultVal);

void ProfileSetFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, float val);
float ProfileGetFloat (LPCTSTR lpAppName, LPCTSTR lpKeyName, float defaultVal);
float ProfileFetchFloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, float defaultVal);

void ProfileSetString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString);
const TCHAR *ProfileGetString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault);
const TCHAR *ProfileFetchString(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault);

void Profile_Init(LPCTSTR fileName);

#endif