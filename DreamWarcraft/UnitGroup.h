#include "stdafx.h"
#ifndef UNIT_GROUP_H_
#define UNIT_GROUP_H_

#include <cstdint>
#include <set>
#include "Point.h"
#include "GameStructs.h"
#include "Tools.h"
#include "Packet.h"

#include "Unit.h"
#include "Item.h"

struct unitgroupcomp {
  bool operator() (const Unit *lhs, const Unit *rhs) const;
};

typedef bool (*FilterUnitGroupFunction)(Unit* unit, void*);
typedef void (*ForUnitGroupFunction)(Unit* unit, void*);
typedef std::set<Unit*, unitgroupcomp> UnitGroupContainerType;
typedef std::set <war3::CUnit *> UnitObjectSetType;

class UnitGroup {
	UnitGroupContainerType* container_;
	DISALLOW_COPY_AND_ASSIGN(UnitGroup);
public:
	typedef UnitGroupContainerType::iterator iterator;
	iterator begin() {return this->container_->begin();}
	iterator end() {return this->container_->end();}

	UnitGroup( );
	UnitGroup( UnitGroupContainerType* container );
	~UnitGroup( );
	void fillUnitObjectSet ( UnitObjectSetType *set );

	UnitGroup*	clone();

	std::string toString ( );

	uint32_t	size	( );
	void		clear	( );
	void		copy	( UnitGroup *otherGroup );
	void		add		( Unit *unit );
	void		remove	( Unit *unit );
	void		remove	( UnitGroup *otherGroup );
	bool		has		( Unit *unit );
	bool		ident	( UnitGroup *otherGroup ) const;

	Unit	*getUnit	( uint32_t index ); //index´Ó0¿ªÊ¼
	Unit	*nearestUnit( Point p, float *distance = 0 );

	int		filterGroup	( FilterUnitGroupFunction func, void* arg = NULL );
	void	forGroup	( ForUnitGroupFunction func, void* arg = NULL );

	void sendAction ( uint32_t actionId, ActionType actionType, uint32_t actionFlag, Item *usingItem, Point targetPoint, Unit *targetUnit, Item *targetItem, bool flagReduceAPM, bool sendAsProgramm = true );

	void sendActionDropItem (
		uint32_t	actionFlag,
		Point		targetPoint,
		Unit		*targetUnit,
		item		dropItemHandle,
		bool		flagReduceAPM,
		bool		sendAsProgramm = true
	);

	uint32_t countUnitTypeId ();

	bool filterAllMatch (UnitFilter filter);
	bool filterExistsMatch (UnitFilter filter);
	bool testFlag (
		uint64_t	inFilterFlag, 
		int			inPlayerId = PLAYER_ANY
	);

};

void		GroupAddUnitAll (UnitGroup* group);

UnitGroup*	GroupUnitAll ();

void		GroupAddUnitsOfPlayerSelected (UnitGroup* group, int player_id, bool subgroupOnly);

UnitGroup*	GroupUnitsOfPlayerSelected (int player_id, bool subgroupOnly);

void		GroupAddUnitsInRange (UnitGroup* group, float x, float y, float r);

UnitGroup*	GroupUnitsInRange (float x, float y, float r);

void GroupAddUnits(
	UnitGroup*	group,
	UnitGroup*	fromGroup,				//NULL for all units
	int			inUnitTypeId,			//NULL for any
	PlayerGroup	Owners,					//PlayerGroup() or PlayerGroupAll() for any owner
	Region*		inRegion,				//Region() for no limit
	UnitFilter	inUnitFilter,			//UnitFilter() for no limit
	uint32_t	maxCount = 0			//0 or ignore for no limit
);

UnitGroup* GroupUnits(
	UnitGroup*	fromGroup,				//NULL for all units
	int			inUnitTypeId,			//NULL for any
	PlayerGroup	Owners,					//PlayerGroup() or PlayerGroupAll() for any owner
	Region*		inRegion,				//Region() for no limit
	UnitFilter	inUnitFilter,			//UnitFilter() for no limit
	uint32_t	maxCount = 0			//0 or ignore for no limit
);

void GroupDestroy(UnitGroup* group);

#define GroupForEachUnit(group, unitIdentifier, statements)\
for (UnitGroup::iterator iter = (group)->begin(); iter != (group)->end(); ++iter){\
	Unit *unitIdentifier = *iter;\
	statements\
}0\

#endif