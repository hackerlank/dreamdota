#include "stdafx.h"
#include "Item.h"
#include "Jass.h"
#include "Tools.h"
#include "Ability.h"

Item::Item (uint32_t handleId) : handleId_(handleId) { }
Item::~Item () { }

uint32_t Item::handleId() const { return handleId_; }
const char * Item::name() const { return ObjectIdToNameChar(typeId()); }

float Item::x () const { return Jass::GetItemX(handleId_); }
float Item::y () const { return Jass::GetItemY(handleId_); }
Point Item::position () const { return Point(this->x(), this->y()); }
uint32_t Item::typeId () const { return Jass::GetItemTypeId(handleId_); }
const char * Item::typeIdChar () const { return IntegerIdToChar(typeId()); }
uint32_t Item::owner () const { return Jass::GetPlayerId(Jass::GetItemPlayer(handleId_)); }
uint32_t Item::level () const { return Jass::GetItemLevel(handleId_); }
uint32_t Item::charges () const { return Jass::GetItemCharges(handleId_); }
uint32_t Item::itemType () const { return Jass::GetItemType(handleId_); }

bool Item::isInvulnerable () const { return Jass::IsItemInvulnerable(handleId_); }
bool Item::isVisible () const { return Jass::IsItemVisible(handleId_); }
bool Item::isOwned () const { return Jass::IsItemOwned(handleId_); }
bool Item::isPowerup () const { return Jass::IsItemPowerup(handleId_); }
bool Item::isSellable () const { return Jass::IsItemSellable(handleId_); }
bool Item::isPawnable () const { return Jass::IsItemPawnable(handleId_); }

float Item::cooldownRemain() const
{
	float rv = 0;
	war3::CItem *objItem = ItemGetObject(handleId_);
	war3::CAbility *objAbil;
	for (int i = 0; i < 4; i++)
	{
		objAbil = (war3::CAbility *)AgentFromHash(&objItem->hashAbility[i].hash);
		if (objAbil)
		{
			rv = max(rv, GetAbility(objAbil)->cooldownRemain());
		}
	}
	return rv;
}

static char ItemDebugNameBuffer[0x30];
const char * Item::debugName( bool showHandleId, bool showObject ) const
{
	if (showHandleId && showObject){
		sprintf_s(ItemDebugNameBuffer, 0x30, "%s (%d, 0x%X)", ObjectIdToNameChar(typeId()), handleId_, ItemGetObject(handleId_));
	}
	else if (showHandleId && !showObject){
		sprintf_s(ItemDebugNameBuffer, 0x30, "%s (%d)", ObjectIdToNameChar(typeId()), handleId_);
	}
	else if (!showHandleId && showObject){
		sprintf_s(ItemDebugNameBuffer, 0x30, "%s (0x%X)", ObjectIdToNameChar(typeId()), ItemGetObject(handleId_));
	}
	else {
		sprintf_s(ItemDebugNameBuffer, 0x30, "%s", ObjectIdToNameChar(typeId()));
	}
	return ItemDebugNameBuffer;
}

float Item::life() const
{
	return Jass::GetWidgetLife(handleId_);
}

typedef std::map<item, Item*> ItemMapType;

static ItemMapType ItemMap;

void ItemManager_Init() {
}

void ItemManager_Cleanup(){ 
	for (ItemMapType::iterator iter = ItemMap.begin(); iter != ItemMap.end(); ++iter) {
		delete iter->second;
	}
	ItemMap.clear();
}

Item* GetItem(uint32_t handle) {
	if (!handle) return NULL;
	Item* rv;
	if (ItemMap.count(handle) == 0)
	{
		//验证是否物品
		war3::CItem *i_obj = ItemGetObject(handle);
		if (i_obj)
		{
			if (AgentTypeIdGet((war3::CAgent *)i_obj) == 'item')
			{
				rv = ItemMap[handle] = new Item(handle);
			}
		}
	}
	else
		rv = ItemMap[handle];
	return rv;
}
