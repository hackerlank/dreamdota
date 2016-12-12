#include "stdafx.h"
#include "TriggerEventFilter.h"
#include "Jass.h"
#include "GameTime.h"
#include "Tools.h"

TriggerEventFilter::TriggerEventFilter() {
	this->reset();
}

void TriggerEventFilter::reset() {
	this->last_event_id_ = 0;
	this->hash_set_.clear();
}

bool TriggerEventFilter::filter(uint32_t eid) {
	uint32_t hash = this->hash_value();
	if (eid != this->last_event_id_) {
		this->last_event_id_ = eid;
		this->hash_set_.clear();
		this->hash_set_.insert(hash);
		return true;
	}
	if (this->hash_set_.count(hash) == 0) {
		this->hash_set_.insert(hash);
		return true;
	}
	return false; 
}

uint32_t TriggerEventFilter::hash_value() {
	uint32_t result = 0;
	this->hash_combine(&result, Jass::GetTriggerPlayer());
	this->hash_combine(&result, Jass::GetTriggerUnit());
	this->hash_combine(&result, Jass::GetIssuedOrderId());
	this->hash_combine(&result, Jass::GetOrderTarget());
	this->hash_combine(&result, Jass::GetOrderPointX());
	this->hash_combine(&result, Jass::GetOrderPointY());
	this->hash_combine(&result, Jass::GetSpellAbilityId());
	this->hash_combine(&result, TimeRaw());
	return result;
}