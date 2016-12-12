#include "stdafx.h"
#include "UnitWalker.h"
#include <algorithm>
#include "Timer.h"
#include "UnitGroup.h"

typedef std::list<UnitWalker*> UnitWalkerListType;

class UnitWalker {
public:
	UnitWalker(UnitWalkerCallbackType callback);
	~UnitWalker();
	UnitWalkerCallbackType callback() {return this->callback_;}
private:
	UnitWalkerCallbackType callback_;
};

UnitWalkerListType UnitWalkerList;

UnitWalker::UnitWalker(UnitWalkerCallbackType callback) {
	this->callback_ = callback;
}

UnitWalker::~UnitWalker() {

}

UnitWalker* GetUnitWalker(UnitWalkerCallbackType callback) {
	UnitWalker* rv = new UnitWalker(callback);
	UnitWalkerList.push_back(rv);
	return rv;
}

void DestroyUnitWalker(UnitWalker* walker) {
	UnitWalkerListType::iterator iter = std::find(UnitWalkerList.begin(), UnitWalkerList.end(), walker);
	if (iter != UnitWalkerList.end()) {
		delete *iter;
		UnitWalkerList.erase(iter);
	}
}

UnitGroup UnitWalkerUnits;
void onUnitWalkerTimer (Timer *tm) {
	if (UnitWalkerList.size()) {
		UnitWalkerUnits.clear();
		GroupAddUnitAll(&UnitWalkerUnits);
		GroupForEachUnit(&UnitWalkerUnits, unit, 
			for (UnitWalkerListType::iterator iter = UnitWalkerList.begin();
				iter != UnitWalkerList.end();
				++iter)
			{
				(*iter)->callback()(unit);
			}
		);
	}
}

void UnitWalker_Init() {
	GetTimer(UNIT_WALKER_INTERVAL, onUnitWalkerTimer, true)->start();
}

void UnitWalker_Cleanup() {
	for (UnitWalkerListType::iterator iter = UnitWalkerList.begin();
		iter != UnitWalkerList.end();
		++iter)
	{
		delete *iter;
	}
	UnitWalkerList.clear();
}