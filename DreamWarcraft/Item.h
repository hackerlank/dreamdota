#ifndef ITEM_H_
#define ITEM_H_

#include "Point.h"

class Item {
	uint32_t handleId_;
	DISALLOW_COPY_AND_ASSIGN(Item);
public:
	Item (uint32_t handleId);
	~Item ();

	uint32_t handleId() const;
	const char *name() const;
	const char *debugName(bool showHandleId = true, bool showObject = false) const;
	float x () const;
	float y () const;
	float life () const;
	Point position () const;
	uint32_t typeId () const;
	const char *typeIdChar() const;
	uint32_t owner () const;
	uint32_t level () const;
	uint32_t charges () const;
	uint32_t itemType () const;

	bool isInvulnerable () const;
	bool isVisible () const;
	bool isOwned () const;
	bool isPowerup () const;
	bool isSellable () const;
	bool isPawnable () const;

	float cooldownRemain ( ) const;

};

Item* GetItem(uint32_t handle);

void ItemManager_Init();
void ItemManager_Cleanup();


#endif