#ifndef APM_H_
#define APM_H_

void APMUpdateAction( int playerId, int actionId );
float APMGetAverage( int playerId );
float APMGetPeak ( int playerId );

void APM_Init();
void APM_Cleanup();

#endif