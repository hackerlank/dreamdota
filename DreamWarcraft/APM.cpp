#include "stdafx.h"
#include "GameTime.h"

const float APM_LATEST_TIME = 3.0f;

static std::map<int, uint32_t> PlayerActionCountTotal;

typedef std::list<float> TimeSig;
static std::map<int, TimeSig> PlayerLatestActionTimeSig;

static float TimeBegin;
static bool TimeBeginInited;

void APMCleanLatest()
{
	for (int p = 0; p < 16; p++)
	{
		while (PlayerLatestActionTimeSig[p].size() && (Time() - PlayerLatestActionTimeSig[p].front()) > APM_LATEST_TIME )
		{
			PlayerLatestActionTimeSig[p].pop_front();
		}
	}
}

float APMGetAge(int playerId)
{
	if (PlayerLatestActionTimeSig[playerId].size())
	{
		return Time() - PlayerLatestActionTimeSig[playerId].front();
	}
	return 0;
}
#include "Tools.h"
static bool APMLastActionWasSelection;
//APM+: 0x10, 0x11, 0x12, 0x13, 0x14, 0x17, 0x18, 0x1C, 0x1D, 0x1E, 0x61(?), 0x66(?), 0x67(?)
//APM?: 0x16, 0x19
void APMUpdateAction( int playerId, int actionId )
{
	float lastActionTime;

	if ( !TimeBeginInited )
	{
		TimeBegin = Time();
		TimeBeginInited = true;
	}

	switch(actionId)
	{
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x13:
	case 0x14:
	case 0x17:
	case 0x18:
	case 0x1C:
	case 0x1D:
	case 0x1E:
	case 0x61:
	case 0x66:
	case 0x67:
		APMLastActionWasSelection = false;
		PlayerActionCountTotal[playerId] += 1;
		PlayerLatestActionTimeSig[playerId].push_back(Time());
		APMCleanLatest();
		break;

	case 0x16:
	//case 0x19:
		lastActionTime = PlayerLatestActionTimeSig[playerId].size()? PlayerLatestActionTimeSig[playerId].back() : TimeBegin;
		if ( !APMLastActionWasSelection 
			|| (Time() - lastActionTime > 0.001f) )
		{
			APMLastActionWasSelection = true;
			PlayerActionCountTotal[playerId] += 1;//TODO
			PlayerLatestActionTimeSig[playerId].push_back(Time());//TODO
			APMCleanLatest();
		}
		break;

	default:
		APMLastActionWasSelection = false;
		break;
	}
}

float APMGetAverage( int playerId )
{
	return 60.f * (float)PlayerActionCountTotal[playerId] / (Time() - TimeBegin);
}

float APMGetPeak( int playerId )
{
	APMCleanLatest();
	return 60.f * (float)PlayerLatestActionTimeSig[playerId].size() / 
		max( APMGetAge(playerId), APM_LATEST_TIME * 0.6f );
}

void APM_Init()
{
	TimeBegin = 0;
	TimeBeginInited = false;
}

void APM_Cleanup()
{
	APMLastActionWasSelection = false;
	PlayerActionCountTotal.clear();
	PlayerLatestActionTimeSig.clear();
}