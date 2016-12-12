#include "stdafx.h"
#include "GameLog.h"
#include <ctime>
#include "Foundation.h"

static FILE* FpLog;

void GameLog_Init() {
#if defined(_BETA) || defined(_DEBUG)
	char filename[MAX_PATH];
	time_t rawtime;
	struct tm timeinfo;
	time ( &rawtime );
	localtime_s(&timeinfo, &rawtime );
	strftime(filename, MAX_PATH - 1, "Errors\\%Y-%m-%d %H.%M.%S DreamDota.txt", &timeinfo);
	if (0 != fopen_s(&FpLog, filename, "w"))
		FpLog = NULL;
	WriteGameLog("Game started, base 0x%08X.", GetSelfModule());
#endif
}

void WriteGameLog(const char *format, ...) {
#if defined(_BETA) || defined(_DEBUG)
	if (FpLog) {
		char timebuff[32];
		time_t rawtime;
		struct tm timeinfo;
		time ( &rawtime );
		localtime_s(&timeinfo, &rawtime );
		strftime(timebuff, sizeof(timebuff) - 1, "%Y-%m-%d %H.%M.%S ", &timeinfo);
		fprintf(FpLog, timebuff);
		va_list args;
		va_start(args, format);
		vfprintf_s(FpLog, format, args);
		va_end(args);
		fprintf(FpLog, "\n");
		fflush(FpLog);
	}
#endif
}

void GameLog_Cleanup() {
#if defined(_BETA) || defined(_DEBUG)
	WriteGameLog("Game ended.");
	if (FpLog) {
		fclose(FpLog);
		FpLog = NULL;
	}
#endif
}