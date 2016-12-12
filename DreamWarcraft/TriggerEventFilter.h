#include "stdafx.h"
#ifndef TRIGGER_EVENT_FILTER_H_
#define TRIGGER_EVENT_FILTER_H_

#include <cstdint>
#include <set>

typedef std::set<uint32_t> TriggerEventFilterHashSetType;

class TriggerEventFilter {
public:
	TriggerEventFilter();
	void reset();
	bool filter(uint32_t eid);
private:
	uint32_t hash_value(); 
	uint32_t last_event_id_;
	
	template<typename ValueType>
	void hash_combine(uint32_t* seed, ValueType value) {
		uint32_t t = *(reinterpret_cast<uint32_t*>((&value)));
		*seed =  (*seed) ^ (t + 0x9e3779b9 + ((*seed) << 6) + ((*seed) >> 2));
	}
	TriggerEventFilterHashSetType hash_set_;

	DISALLOW_COPY_AND_ASSIGN(TriggerEventFilter);
};


#endif