#include "stdafx.h"
#include "StatePanel.h"
#include "Texture.h"
#include "Label.h"
#include "UnitStateIcon.h"
#include "Unit.h"
#include "Item.h"

typedef std::map<void *, StatePanel *> statepanelmap;
static statepanelmap InstanceList;

StatePanelRefreshObject::StatePanelRefreshObject()
	: RefreshObject(true)
{

}

void StatePanelRefreshObject::refresh()
{
	//refresh all objects here
	for (statepanelmap::iterator iter = InstanceList.begin(); iter != InstanceList.end(); ) 
	{
		if (!(iter->second)->update()) 
		{
			delete iter->second;
			InstanceList.erase(iter++);
			continue;
		}
		iter++;
	}
}

bool StatePanelRefreshObject::isCompleted()
{
	return false;
}

void StatePanelInit()
{
	RefreshManager_AddObject(new StatePanelRefreshObject());
	InstanceList.clear();
}

void StatePanelCleanup()
{
	InstanceList.clear();
}

StatePanel::StatePanel(void *obj)
	: Frame(UI_NULL, 0.01f, 0.01f),
	object(obj)
{
	setParent(UIObject::GetGameSimpleConsole());
	if (InstanceList.count(object))
	{
		delete InstanceList[object];
	}
	InstanceList[object] = this;
	point.x = 0;
	point.y = 0;
	bShow = true;
	bDeleteme = false;
}

StatePanel::~StatePanel()
{

}

bool StatePanel::update()
{
	if (!bDeleteme)
	{
		this->show(bShow);
		if (bShow)
		{
			this->setAbsolutePosition(POS_B, point.x, point.y);
		}
		return true;
	}
	else
	{
		return false;
	}
}

StatePanelUnit::StatePanelUnit(Unit *bindUnit):
	StatePanel(bindUnit),
	icon()
{
	typeId = bindUnit->typeId();
	icon = new Texture(this, 0.02f, 0.02f, GetIconFromFuncProfile(bindUnit->typeId(), 0));
	icon->setOwner(this);
	icon->setRelativePosition(POS_B, this, POS_B);
}

StatePanelUnit::~StatePanelUnit()
{
	if ( icon )
	{
		delete icon;
	}
}

bool StatePanelUnit::update()
{
	if (!bDeleteme)
	{
		Unit *unit = (Unit *)object;
		if (UnitGetObject(unit->handleId()))
		{
			if ( bShow = 
				enabled &&
				unit->life() > 0 &&
				!unit->testFlag(UnitFilter::HIDDEN) &&
				!unit->testFlag(UnitFilter::VISIBLE, PlayerLocal())
			)
			{
				if (typeId != unit->typeId())
				{
					typeId = unit->typeId();
					icon->setTexture(GetIconFromFuncProfile(typeId));
				}
				unit->framepointGet(&point);
			}
			else
			{
				bShow = false;
			}
		}
		else
		{
			bDeleteme = true;
		}
		return __super::update();
	}
	return false;
}

bool StatePanelUnit::enabled;

StatePanelItem::StatePanelItem(Item *bindItem)
	: StatePanel(bindItem),
	icon(),
	name()
{
	icon = new Texture(this, 0.02f, 0.02f, GetIconFromFuncProfile(bindItem->typeId(), 0));
	icon->setOwner(this);
	icon->setRelativePosition(POS_B, this, POS_B);

	name = new Label (this, bindItem->name(), 0.009f, Color::WHITE);
	name->setOwner(this);
	name->setRelativePosition(POS_T, icon, POS_B);
}

StatePanelItem::~StatePanelItem()
{
	if ( icon )
	{
		delete icon;
	}
	if ( name )
	{
		delete name;
	}
}

bool StatePanelItem::update()
{
	if (!bDeleteme)
	{
		Item *item = (Item *)object;
		war3::CItem *pItem = ItemGetObject(item->handleId());
		if ( pItem )
		{
			if ( bShow = 
				enabled &&
				item->life() > 0 &&
				!item->isOwned() &&
				!item->position().isVisible(PlayerLocal())
			)
			{
				GetUnitFramePoint((war3::CUnit *)pItem, &point);
			}
		}
		else
		{
			bDeleteme = true;
		}
		return __super::update();
	}
	return false;
}

bool StatePanelItem::enabled;

StatePanelHero::StatePanelHero(Unit *bindHero)
	: StatePanel(bindHero),
	icon(),
	name(),
	level()
{
	level = -1;

	icon = new UnitStateIcon(this, 0.03f, 0.03f, bindHero);
	icon->setOwner(this);
	icon->setRelativePosition(POS_B, this, POS_B);

	name = new Label(this, "", 0.009f, Color::WHITE);
	name->setOwner(this);
	name->setRelativePosition(POS_T, icon, POS_B, 0, -0.01f);
}

StatePanelHero::~StatePanelHero()
{
	if ( icon )
	{
		delete icon;
	}
	if ( name )
	{
		delete name;
	}
}

bool StatePanelHero::update()
{
	if (!bDeleteme)
	{
		Unit *hero = (Unit *)object;
		if (UnitGetObject(hero->handleId()))
		{
			if (hero->life() > 0)
			{
				hero->framepointGet(&point);
				bShow = enabled && !hero->testFlag(UnitFilter::VISIBLE, PlayerLocal());
				if (bShow)
				{
					if (needUpdate())
					{
						bool bIllusion = hero->testFlag(UnitFilter::ILLUSION);
						if (bIllusion)
						{
							name->setText(
								"%s%s (%s)%s",
								"cff808080",
								hero->name(),
								Jass::GetObjectName('BIil'),
								"|r" 
							);
						}
						else
						{
							name->setText(
								"%sLv %d%s %s%s%s",
								"|cffffcc00",
								level,
								"|r", 
								GetPlayerColorString(hero->owner()),
								hero->name(),
								"|r" 
							);
						}
						
					}
				}
			}
			else
			{
				bShow = false;
			}
		}
		else
		{
			bDeleteme = true;
		}
		return __super::update();
	}
	return false;
}

bool StatePanelHero::needUpdate()
{
	Unit *hero = (Unit *)object;
	if (level != hero->level(true))
	{
		level = hero->level(true);
		return true;
	}
	return false;
}

bool StatePanelHero::enabled;

StatePanelBoss::StatePanelBoss( Unit *boss ) : StatePanelHero(boss){}

StatePanelBoss::~StatePanelBoss(){}

bool StatePanelBoss::needUpdate()
{
	Unit *boss = (Unit *)object;
	if (level != boss->level(false))
	{
		level = boss->level(false);
		return true;
	}
	return false;
}

bool StatePanelBoss::enabled;

StatePanelWard::StatePanelWard( Unit *bindWard ) : StatePanelUnit(bindWard)
{

}

StatePanelWard::~StatePanelWard()
{

}

bool StatePanelWard::update()
{
	return __super::update();
}
