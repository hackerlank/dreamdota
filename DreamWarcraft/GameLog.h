#ifndef GAME_LOG_H_INCLUDED_
#define GAME_LOG_H_INCLUDED_

void GameLog_Init();
void GameLog_Cleanup();
void WriteGameLog(const char *format, ...);

#endif