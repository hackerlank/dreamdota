#include "stdafx.h"
#include <sstream>
#include "UnitGroup.h"
#include "Action.h"
#include "Tools.h"

bool unitgroupcomp::operator() (const Unit *lhs, const Unit *rhs) const
{
	uint32_t handleL = lhs->handleId();
	uint32_t handleR = rhs->handleId();
	float prioDiff = UnitSelectionPrioGet(UnitGetObject(handleL)) - UnitSelectionPrioGet(UnitGetObject(handleR));
	return (prioDiff > 0) || (prioDiff == 0 && handleL < handleR);
}

UnitGroup::UnitGroup() {
	this->container_ = new UnitGroupContainerType();
}

UnitGroup::UnitGroup(UnitGroupContainerType* container) {
	this->container_ = container;
}

UnitGroup::~UnitGroup() {
	delete this->container_;
}

uint32_t	UnitGroup::size() {return this->container_->size();}
void		UnitGroup::clear() {this->container_->clear();}
void		UnitGroup::add(Unit* unit) {if (unit) this->container_->insert(unit);}
void		UnitGroup::remove(Unit* unit) {if (unit) this->container_->erase(unit);}
void		UnitGroup::remove( UnitGroup *otherGroup ) {
	for (UnitGroupContainerType::iterator iter = otherGroup->begin();
		iter != otherGroup->end(); ++iter)
	{
		this->remove(*iter);
	}
}
bool		UnitGroup::has(Unit* unit) { return unit? this->container_->count(unit) > 0 : false; }

Unit *UnitGroup::getUnit (uint32_t index) {//index从0开始, 排序按handle值
	uint32_t i = 0;
	if (index >= 0 && index < container_->size()){
		for (UnitGroupContainerType::iterator iter = container_->begin(); iter != container_->end();++i,++iter) {
			if (i == index) return *iter;
		}
	}
	return NULL;
}

Unit *UnitGroup::nearestUnit (Point p, float *distance){
	Unit *nearestUnit = NULL; float dsqr; float leastDsqr = 9999999.0f;
	for (UnitGroupContainerType::iterator iter = this->container_->begin(); iter != this->container_->end();) {
		dsqr = pow(((*iter)->x() - p.x), 2) + pow(((*iter)->y() - p.y), 2);
		if (leastDsqr > dsqr) {
			leastDsqr = dsqr;
			nearestUnit = *iter;
		}
		++iter;
	}
	if (distance) *distance = sqrt(leastDsqr);
	return nearestUnit;
}

int UnitGroup::filterGroup(FilterUnitGroupFunction func, void* arg) {
	int count = 0;
	for (UnitGroupContainerType::iterator iter = this->container_->begin(); iter != this->container_->end();) {
		if (!func(*iter, arg)) {
			this->container_->erase(iter++);
			count ++;
		} else
			++iter;
	}
	return count;
}

void UnitGroup::forGroup(ForUnitGroupFunction func, void* arg) {
	for (UnitGroupContainerType::iterator iter = this->container_->begin(); iter != this->container_->end(); ++iter) {
		func(*iter, arg);
	}
}

UnitGroup* UnitGroup::clone() {
	UnitGroup* rv = new UnitGroup();
	for (UnitGroup::iterator iter = this->begin(); iter != this->end(); ++iter)
		rv->add(*iter);
	return rv;
}

void UnitGroup::fillUnitObjectSet(UnitObjectSetType* set) {
	for (UnitGroupContainerType::iterator iter = this->container_->begin(); iter != this->container_->end(); ++iter) {
		war3::CUnit * unitObject;
		if (NULL != (unitObject = UnitGetObject((*iter)->handleId())))
			set->insert(unitObject);
	}
}

static war3::PacketAction ObjPacketAction;
static war3::PacketActionPoint ObjPacketActionPoint;
static war3::PacketActionTarget ObjPacketActionTarget;
static war3::PacketActionDropItem ObjPacketActionDropItem;

void UnitGroup::sendAction( uint32_t actionId, ActionType actionType, uint32_t actionFlag, Item *usingItem, Point targetPoint, Unit *targetUnit, Item *targetItem, bool flagReduceAPM, bool sendAsProgramm /*= true */ )
{
	if (!this->size()) return; //如果单位组为空，自然不可能实现任何操作。
	UnitObjectSetType set;
	this->fillUnitObjectSet(&set);

	switch(actionType){
	case TargetNone:
		ObjPacketAction.id = 0x10;
		ObjPacketAction.flag = actionFlag;
		ObjPacketAction.actionId = actionId;
		ObjPacketAction.hashUsedItem = 
		(usingItem && ItemGetObject(usingItem->handleId()))? 
			ItemGetObject(usingItem->handleId())->hash 
			: war3::HashGroup();
		PacketJustInTimeActionSend ( flagReduceAPM, &set, &ObjPacketAction, 15, sendAsProgramm );
		break;
	case TargetPoint:
		ObjPacketActionPoint.id = 0x11;
		ObjPacketActionPoint.flag = actionFlag;
		ObjPacketActionPoint.actionId = actionId;
		ObjPacketActionPoint.hashUsedItem = war3::HashGroup();//TODO
		ObjPacketActionPoint.targetX = targetPoint.x;
		ObjPacketActionPoint.targetY = targetPoint.y;
		PacketJustInTimeActionSend ( flagReduceAPM, &set, &ObjPacketActionPoint, 23, sendAsProgramm );
		break;
	case Target:
		ObjPacketActionTarget.id = 0x12;
		ObjPacketActionTarget.flag = actionFlag;
		ObjPacketActionTarget.actionId = actionId;
		ObjPacketActionTarget.hashUsedItem = war3::HashGroup();//TODO
		ObjPacketActionTarget.targetX = targetPoint.x;
		ObjPacketActionTarget.targetY = targetPoint.y;
		if (targetUnit)
		{
			ObjPacketActionTarget.hashWidgetTarget =
				(UnitGetObject(targetUnit->handleId()))? 
				UnitGetObject(targetUnit->handleId())->hash 
				: war3::HashGroup();
		}
		else if (targetItem)
		{
			ObjPacketActionTarget.hashWidgetTarget =
				(ItemGetObject(targetItem->handleId()))? 
				ItemGetObject(targetItem->handleId())->hash 
				: war3::HashGroup();
		}
		else
		{
			ObjPacketActionTarget.hashWidgetTarget = war3::HashGroup();
		}
		
		PacketJustInTimeActionSend ( flagReduceAPM, &set, &ObjPacketActionTarget, 31, sendAsProgramm );
		break;

	}
}

void UnitGroup::sendActionDropItem (
	uint32_t	actionFlag,
	Point		targetPoint,
	Unit		*targetUnit,
	item		dropItemHandle,
	bool		flagReduceAPM,
	bool		sendAsProgramm
){
	if (!this->size()) return; //如果单位组为空，自然不可能实现任何操作。
	UnitObjectSetType set;
	this->fillUnitObjectSet(&set);

	ObjPacketActionDropItem.id = 0x13;
	ObjPacketActionDropItem.flag = actionFlag;
	ObjPacketActionDropItem.actionId = ACTION_DROPITEM;
	ObjPacketActionDropItem.hashUsedItem = war3::HashGroup();
	ObjPacketActionDropItem.targetX = targetPoint.x;
	ObjPacketActionDropItem.targetY = targetPoint.y;
	ObjPacketActionDropItem.hashTarget = 
		(targetUnit && UnitGetObject(targetUnit->handleId())) ? 
			UnitGetObject(targetUnit->handleId())->hash 
			: war3::HashGroup();
	ObjPacketActionDropItem.hashItem = 
		(dropItemHandle && ItemGetObject(dropItemHandle)) ? 
			ItemGetObject(dropItemHandle)->hash 
			: war3::HashGroup();
	PacketJustInTimeActionSend ( flagReduceAPM, &set, &ObjPacketActionDropItem, 39, sendAsProgramm );
}
	

std::string UnitGroup::toString () {
	std::ostringstream s;
	for (UnitGroupContainerType::iterator iter = this->container_->begin(); iter != this->container_->end(); ++iter) {
		s << IntegerIdToChar((*iter)->typeId()) << "(" << (*iter)->handleId() << "," << 
			UnitSelectionPrioGet(UnitGetObject((*iter)->handleId()))
			<< ")  ";
	}
	s << "total count: " << this->container_->size();
	return s.str();
}

uint32_t UnitGroup::countUnitTypeId () {
	uint32_t typeId = 0, lastTypeId = 0, count = 0;
	for (UnitGroupContainerType::iterator iter = this->container_->begin(); iter != this->container_->end(); ++iter) {
		typeId = (*iter)->typeId();
		if (lastTypeId != typeId) ++count;
		lastTypeId = typeId;
	}
	return count;
}

bool UnitGroup::filterAllMatch (UnitFilter filter) {
	if (!this->container_->size()) return false;
	for (UnitGroupContainerType::iterator iter = this->container_->begin(); iter != this->container_->end(); ++iter) {
		if (!(*iter)->filterMatch(filter)) return false;
	}
	return true;
}

bool UnitGroup::filterExistsMatch (UnitFilter filter) {
	if (!this->container_->size()) return false;
	for (UnitGroupContainerType::iterator iter = this->container_->begin(); iter != this->container_->end(); ++iter) {
		if ((*iter)->filterMatch(filter)) return true;
	}
	return false;
}

bool UnitGroup::testFlag (uint64_t	inFilterFlag, int inPlayerId) {
	if (!this->container_->size()) return false;
	for (UnitGroupContainerType::iterator iter = this->container_->begin(); iter != this->container_->end(); ++iter) {
		if (!(*iter)->testFlag(inFilterFlag, inPlayerId)) return false;
	}
	return true;
}

bool UnitGroup::ident( UnitGroup *otherGroup ) const
{
	if (!this) return false;
	if (container_->size() != otherGroup->size()) return false;
	for (UnitGroupContainerType::iterator iter = container_->begin(); 
		iter != container_->end(); ++iter) 
	{
		if (!otherGroup->has(*iter)) return false;
	}
	return true;
}

void UnitGroup::copy( UnitGroup *otherGroup )
{
	clear();
	for (UnitGroupContainerType::iterator iter = otherGroup->begin();
		iter != otherGroup->end(); ++iter)
	{
		this->add(*iter);
	}
}


void GroupAddUnitAll(UnitGroup* group) {
    uint32_t size = NULL;
    void** arr = UnitGrabAll(size);
    for (uint32_t i = 0; i < size; ++i) {
        unit u = ObjectToHandle(arr[i]);
        group->add(GetUnit(u));
    }
}

UnitGroup* GroupUnitAll() {
	UnitGroup* rv = new UnitGroup();
	GroupAddUnitAll(rv);
	return rv;
}

void GroupAddUnitsOfPlayerSelected(UnitGroup* group, int player_id, bool subgroupOnly) {
	void* arr[12]; uint32_t size;
	if (subgroupOnly){	size = ActiveSubgroupGet(player_id, arr); }
	else {size = SelectedUnitGet(player_id, arr, false);}
	for (uint32_t i = 0; i < size; ++i) {
		unit u = ObjectToHandle(arr[i]);
		group->add(GetUnit(u));
	}
}

UnitGroup* GroupUnitsOfPlayerSelected(int player_id, bool subgroupOnly) {
	UnitGroup* rv = new UnitGroup();
	GroupAddUnitsOfPlayerSelected(rv, player_id, subgroupOnly);
	return rv;
}

void GroupAddUnitsInRange(UnitGroup* group, float x, float y, float r) {
	uint32_t size = NULL;
	void** arr = UnitGrabAll(size);
	for (uint32_t i = 0; i < size; ++i) {
		unit u = ObjectToHandle(arr[i]);
		if (Jass::IsUnitInRangeXY(u, x, y, r))
			group->add(GetUnit(u));
	}
}

UnitGroup* GroupUnitsInRange(float x, float y, float r) {
	UnitGroup* rv = new UnitGroup();
	GroupAddUnitsInRange(rv, x, y, r);
	return rv;
}

void GroupAddUnits(
	UnitGroup* group,
	UnitGroup* fromGroup,
	int inUnitTypeId,				//NULL for any
	PlayerGroup Owners,				//PlayerGroup() or PlayerGroupAll() for any owner
	Region* inRegion,				//Region() for no limit
	UnitFilter inUnitFilter,		//UnitFilter() for no limit
	uint32_t maxCount				//0 or ignore for no limit
)
{
	uint32_t size = NULL;
	bool playerMatched = false;
	bool typeIdMatched = false;
	bool filterMatched = false;
	bool regionMatched = false;
	void** arr;
	if (fromGroup == NULL){
		arr = UnitGrabAll(size);
	} else {
		size = fromGroup->size();
	}
	uint32_t count = 0;
	for (uint32_t i = 0; i < size; ++i) {
		unit u;
		if (fromGroup == NULL){
			u = ObjectToHandle(arr[i]);
		} else {
			u = fromGroup->getUnit(i)->handleId();//getUnit index从0开始
		}
		//条件
		typeIdMatched = 
			inUnitTypeId == NULL ||
			inUnitTypeId == Jass::GetUnitTypeId(u) ;

		playerMatched = 
			Owners == NULL ||
			Owners.has(Jass::GetPlayerId(Jass::GetOwningPlayer(u))) ;

		regionMatched = 
			inRegion == NULL ||
			inRegion->hasPoint(Point(Jass::GetUnitX(u), Jass::GetUnitY(u)));

		filterMatched =
			(inUnitFilter == NULL) ||
			(GetUnit(u)->filterMatch(inUnitFilter));

		if (	
			typeIdMatched &&
			playerMatched &&
			regionMatched &&
			filterMatched	)
		{
			if (!maxCount || count < maxCount){
				group->add(GetUnit(u)); 
				count+=1;
				if (maxCount && count >= maxCount) break;
			}
		}
	}	
}


UnitGroup* GroupUnits(
	UnitGroup*	fromGroup,
	int inUnitTypeId,						
	PlayerGroup Owners,
	Region* inRegion,
	UnitFilter inUnitFilter,
	uint32_t maxCount
)
{
	UnitGroup* rv = new UnitGroup();
	GroupAddUnits(rv, fromGroup, inUnitTypeId, Owners, inRegion, inUnitFilter, maxCount);
	return rv;
}

void GroupDestroy(UnitGroup* group) {
	if(group) delete group;
}