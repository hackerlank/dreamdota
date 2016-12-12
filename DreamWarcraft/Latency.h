#ifndef LATENCY_H_
#define LATENCY_H_

#include "Stochastic.h"

static const float LATENCY_UPDATE_COOLDOWN = 0.01f;

float LatencyGetAverage();
float LatencyGetMax();
float LatencyGetMin();
float LatencyGetCurrent();

std::map<float, float, DistributionLess> *LatencyGetNegDist();
void LatencyDistPrint();

void Latency_Update(float value);
void Latency_Init ();
void Latency_Cleanup();

#endif