#include "stdafx.h"
#include "UnitStateIcon.h"

#include "Texture.h"
#include "Bar.h"
#include "Tools.h"
#include "Unit.h"


UnitStateIcon::UnitStateIcon( IUIObject *parent, float width, float height, Unit *unit )
	: Frame(parent, width, height)
{
	this->unit = unit;
	this->typeId = unit->typeId();

	icon = new Texture(this, width, height);
	icon->setOwner(this);
	icon->setRelativePosition(POS_C, this, POS_C);
	icon->setTexture(GetIconFromFuncProfile(typeId, 0), NULL);

	barHP = new StateBar(this, width, width * 0.125f, unit, StateBarHP);
	barHP->setOwner(this);
	barMana = new StateBar(this, width, width * 0.125f, unit, StateBarMana);
	barMana->setOwner(this);

	barHP->setRelativePosition(POS_T, this, POS_B);
	barMana->setRelativePosition(POS_T, barHP, POS_B);
}

UnitStateIcon::~UnitStateIcon()
{
	delete barHP;
	delete barMana;
	delete icon;
}

void UnitStateIcon::tick()
{
	if (typeId != unit->typeId())
	{
		typeId = unit->typeId();
		icon->setTexture(GetIconFromFuncProfile(typeId, 0), NULL);
	}
	__super::tick();
}
