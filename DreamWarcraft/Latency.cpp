#include "stdafx.h"
#include "Latency.h"
#include "GameTime.h"
#include "Tools.h"
#include "DebugPanel.h"

struct LatencyHistoryInfo {
	float timeGame;
	float latency;

	LatencyHistoryInfo(float _time, float _value) : timeGame(_time), latency(_value) { }
	float age() { return max(Time()-timeGame, 0); }
};

static std::deque<LatencyHistoryInfo> Latency;
static const int LATENCY_QUEUE_MAX_COUNT = 15;
static const float LATENCY_QUEUE_MAX_AGE = 10.0f;
static const float LATENCY_DEFAULT = 0.1f;
static float LatencyLastAverage;

static std::map<float, float, DistributionLess> LatencyNegDist;

void LatencyCalcNegDist() {
	LatencyNegDist.clear();
	if (Latency.size()){
		float chance = (float)(1.f/Latency.size());
		for (std::deque<LatencyHistoryInfo>::iterator iter = Latency.begin(); iter != Latency.end(); ++iter){
			LatencyNegDist[-(iter->latency)] += chance;
		}
	}
	else{//build default
		LatencyNegDist[-(LATENCY_DEFAULT)] = 1.f;
	}
	//DefaultDebugPanel->set("LatencyDistSize", "%d", LatencyNegDist.size());
}

std::map<float, float, DistributionLess> *LatencyGetNegDist() {
	return &LatencyNegDist;
}

void LatencyDistPrint() {
	for (std::map<float, float, DistributionLess>::iterator iter = LatencyNegDist.begin(); iter != LatencyNegDist.end(); ++iter) {
		OutputScreen(10, "LatencyNegDist[%.4f] = %.4f", iter->first, iter->second);
	}
}

void Latency_Refresh(){
	if (Latency.size() > LATENCY_QUEUE_MAX_COUNT) {
		for (uint32_t i = 0; i < Latency.size()-LATENCY_QUEUE_MAX_COUNT; i++){
			Latency.pop_front();
		}
	}
	while (Latency.size() && Latency.front().age() > LATENCY_QUEUE_MAX_AGE) {
		Latency.pop_front();
	}
	LatencyCalcNegDist();
}

static float LatencyLastUpdateTime;
static float LatencyCurrentUpdated;
void Latency_Update(float value){
	LatencyCurrentUpdated = value;
	float time = Time();
	if ( time - LatencyLastUpdateTime > LATENCY_UPDATE_COOLDOWN){
		Latency.push_back(LatencyHistoryInfo(Time(), value));//¾«È·
		Latency_Refresh();
		LatencyLastUpdateTime = time;
	}
}

float LatencyGetAverage() {
	if (Latency.size()){
		LatencyLastAverage = 0;
		for (std::deque<LatencyHistoryInfo>::iterator iter = Latency.begin(); iter != Latency.end(); ++iter){
			LatencyLastAverage += iter->latency;
		}
		LatencyLastAverage /= Latency.size();
	}
	return LatencyLastAverage;
}

float LatencyGetMax() {
	float rv = 0;
	if (Latency.size()){
		rv = Latency.begin()->latency;
		for (std::deque<LatencyHistoryInfo>::iterator iter = Latency.begin(); iter != Latency.end(); ++iter){
			if (rv < iter->latency) rv = iter->latency;
		}
	}
	else rv = LATENCY_DEFAULT;
	return rv;
}

float LatencyGetMin() {
	float rv = 0;
	if (Latency.size()){
		rv = Latency.begin()->latency;
		for (std::deque<LatencyHistoryInfo>::iterator iter = Latency.begin(); iter != Latency.end(); ++iter){
			if (rv > iter->latency) rv = iter->latency;
		}
	}
	else rv = LATENCY_DEFAULT;
	return rv;
}

void Latency_Init (){
	LatencyLastAverage = LATENCY_DEFAULT;
}

void Latency_Cleanup(){
	LatencyCurrentUpdated = 0;
	Latency.clear();
}

float LatencyGetCurrent()
{
	return LatencyCurrentUpdated;
}
