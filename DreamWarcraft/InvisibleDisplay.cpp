#include "stdafx.h"
#include "DreamDotaMain.h"
#include "StatePanel.h"

namespace InvisibleDisplay
{
	static int MaxUnitLevel;
	const float BossLevelThreshold = 0.8f;

	void onUnitCreated (const Event *evt) 
	{
		Unit *u = GetUnit(evt->data<UnitCreationEventData>()->createdUnit);
		if (u->testFlag(UnitFilter::HERO))
		{
			new StatePanelHero(u);
		}
		else if (//boss
			u->owner() == Jass::PLAYER_NEUTRAL_AGGRESSIVE &&
			//Jass::UnitInventorySize(u->handleId()) > 0)
			u->level(false) >=  BossLevelThreshold * MaxUnitLevel
		)
		{
			new StatePanelBoss(u);
		}
		else
		{
			if (u->abilityLevel('Aloc') == 0)
			{
				if (u->testFlag(UnitFilter::WARD))
				{
					new StatePanelWard(u);
				}
				else
				{
					new StatePanelUnit(u);
				}
			}
		}
		
	}

	void onItemCreated (const Event *evt) 
	{
		ItemCreationEventData *data = evt->data<ItemCreationEventData>();
		Item *createdItem = GetItem(data->createdItem);
		new StatePanelItem(createdItem);
	}

	void CreateMenuContent()
	{
		CheckBox *cb; Label *lb;
		UISimpleFrame* Panel = DefaultOptionMenuGet()->
			category(StringManager::GetString(STR::INVISIBLEDISPLAY));

		float offsetY = -0.03f;

		cb = new CheckBox(Panel);
		cb->bindProfile("InvisibleDisplay", "ShowHero", true);
		cb->bindVariable(&(StatePanelHero::enabled));
		cb->setRelativePosition(	POS_UL,	Panel, POS_UL, 0.03f, offsetY);
		lb = new Label(Panel, StringManager::GetString(STR::INVISIBLEDISPLAY_SHOWHERO), 0.013f);
		lb->setRelativePosition(POS_L, cb, POS_R, 0.01f, 0);

		offsetY -= 0.027f;

		cb = new CheckBox(Panel);
		cb->bindProfile("InvisibleDisplay", "ShowBoss", true);
		cb->bindVariable(&(StatePanelBoss::enabled));
		cb->setRelativePosition(	POS_UL,	Panel, POS_UL, 0.03f, offsetY);
		lb = new Label(Panel, StringManager::GetString(STR::INVISIBLEDISPLAY_SHOWBOSS), 0.013f);
		lb->setRelativePosition(POS_L, cb, POS_R, 0.01f, 0);

		offsetY -= 0.027f;

		cb = new CheckBox(Panel);
		cb->bindProfile("InvisibleDisplay", "ShowUnit", true);
		cb->bindVariable(&(StatePanelUnit::enabled));
		cb->setRelativePosition(	POS_UL,	Panel, POS_UL, 0.03f, offsetY);
		lb = new Label(Panel, StringManager::GetString(STR::INVISIBLEDISPLAY_SHOWUNIT), 0.013f);
		lb->setRelativePosition(POS_L, cb, POS_R, 0.01f, 0);

		offsetY -= 0.027f;

		cb = new CheckBox(Panel);
		cb->bindProfile("InvisibleDisplay", "ShowItem", true);
		cb->bindVariable(&(StatePanelItem::enabled));
		cb->setRelativePosition(	POS_UL,	Panel, POS_UL, 0.03f, offsetY);
		lb = new Label(Panel, StringManager::GetString(STR::INVISIBLEDISPLAY_SHOWITEM), 0.013f);
		lb->setRelativePosition(POS_L, cb, POS_R, 0.01f, 0);
	}
	


	void Init()
	{
		CreateMenuContent();

		MaxUnitLevel = GameDataProfileGetInt("Misc", "MaxUnitLevel", 0);

		//测试：对所有单位显示statepanel
		MainDispatcher()->listen(EVENT_UNIT_CREATED, onUnitCreated);

		MainDispatcher()->listen(EVENT_ITEM_CREATED, onItemCreated);
	}

	void Cleanup()
	{

	}
}
