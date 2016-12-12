#include "stdafx.h"
#include "DreamWar3Main.h"
#include "Table.h"
#include "MultiIcon.h"

namespace GLeagueDota
{
	const float PANEL_POS_X = 0.0125f;//FIXME
	const float PANEL_POS_Y = 0.525f;

	const float HERO_ICON_SIZE = 0.06f;
	const float HERO_ITEM_SIZE = 0.045f;

	static Table	*PanelSentinel;
	static Table	*PanelScourge;



	void RefreshPlayer(Table *panel, uint32_t row, uint32_t player)
	{

		UnitGroup *playerHeros = GroupUnits(NULL, NULL, PlayerGroupSingle(player), NULL, 
			UnitFilter(
			UnitFilter::HERO, 
			UnitFilter::ILLUSION
			),
			1
		);

		//TODO 改进unitgroup（重载+=, -=）

		Unit *hero = playerHeros->getUnit(0);
		if (hero)
		{
			bool bIsDead = (hero->life() <= 0);
			int column = 0;

			//头像
			MultiIcon *heroIcon = panel->getElement<MultiIcon*>(row, column);
			if (!heroIcon)
			{
				heroIcon = new MultiIcon(UI_NULL, HERO_ICON_SIZE, HERO_ICON_SIZE);
				heroIcon->showBottom(TypeNone);
				heroIcon->showCorner(true, Color::GOLD);
				panel->setElement(row, column, heroIcon);
			}
			if (heroIcon->getId() != hero->typeId())
			{
				heroIcon->setTextureById(hero->typeId());
			}
			heroIcon->setCorner("Lv %d", hero->level(true));
			if ( heroIcon->isActive() != !bIsDead )
			{
				heroIcon->activate(!bIsDead);
			}

			column++;
			//物品
			if (!hero->testFlag(UnitFilter::ILLUSION)) {
				for (uint32_t i = 0; i < 6; i++)
				{
					Item *it = GetItem(Jass::UnitItemInSlot(hero->handleId(), i));
					if (!it)
					{
						continue;
					}
					else
					{
						MultiIcon *itemIcon = panel->getElement<MultiIcon*>(row, column);
						if (!itemIcon)
						{
							itemIcon = new MultiIcon(UI_NULL, HERO_ITEM_SIZE, HERO_ITEM_SIZE);
							panel->setElement(row, column, itemIcon);
						}
						if (itemIcon->getId() != it->typeId())
						{
							itemIcon->setTextureById(it->typeId());
						}

						int charge = it->charges();
						if (!charge)
						{
							itemIcon->showCorner(false);
						}
						else
						{
							itemIcon->showCorner(true);
							itemIcon->setCorner("%d", it->charges()); //TODO 判断物品类别
						}

						if ( itemIcon->isActive() != !bIsDead )
						{
							itemIcon->activate(!bIsDead);
						}
						
						//TODO 处理英雄死亡判断
						column++;
					}
				}
			}

			for (uint32_t i = column; i < panel->sizeColumn(); ++i)
				panel->setElement(row, i, NULL);
		}
		GroupDestroy(playerHeros);
	}

	void Refresh(Timer *tm)
	{
		uint32_t player;
		if (PanelSentinel)
		{
			for (uint32_t row = 0; row < 5; row++)
			{
				player = row + 1; //玩家1~5对应行0~4
				RefreshPlayer(PanelSentinel, row, player);
			}
		}
		if (PanelScourge)
		{
			for (uint32_t row = 0; row < 5; row++)
			{
				player = row + 7; //玩家7~11对应行0~4
				RefreshPlayer(PanelScourge, row, player);
			}
		}
	}

	void onKeyDown(const Event *evt){
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (data->code == KEYCODE::KEY_TAB)
		{
			if(PanelSentinel)
			{
				PanelSentinel->show(true);
			}
			if(PanelScourge)
			{
				PanelScourge->show(true);
			}
		}
	}

	void onKeyUp(const Event *evt){
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (data->code == KEYCODE::KEY_TAB)
		{
			if(PanelSentinel)
			{
				PanelSentinel->show(false);
			}
			if(PanelScourge)	
			{
				PanelScourge->show(false);
			}
		}
	}

	void Init()
	{
		if (true ||ReplayState() == REPLAY_STATE_STREAMINGOUT
			|| Jass::IsPlayerObserver(Jass::Player(PlayerLocal())) )
		{
			PanelSentinel = new Table(UI_NULL, 5, 7, false, 0, true);
			PanelSentinel->setParent(UISimpleFrame::GetGameSimpleConsole());
			PanelSentinel->setColumnMinWidth(0, 0.035f);
			PanelSentinel->setElementPadding(0.005f, 0);
			PanelSentinel->showRowFrame(false);
			PanelSentinel->setAbsolutePosition(POS_UL, PANEL_POS_X, PANEL_POS_Y);
			PanelSentinel->show(false);

			PanelScourge = new Table(UI_NULL, 5, 7, false, 0, true);
			PanelScourge->setParent(UISimpleFrame::GetGameSimpleConsole());
			PanelScourge->setColumnMinWidth(0, 0.035f);
			PanelScourge->setElementPadding(0.005f, 0);
			PanelScourge->showRowFrame(false);
			PanelScourge->setInverse(true);
			PanelScourge->setAbsolutePosition(POS_UR, 0.8f - PANEL_POS_X, PANEL_POS_Y);
			PanelScourge->show(false);

			MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);
			MainDispatcher()->listen(EVENT_KEY_UP, onKeyUp);

			GetTimer(0.5, Refresh, true)->startImmediate();
		}
	}

	void Cleanup()
	{
		if (PanelSentinel)
		{
			delete PanelSentinel;
			PanelSentinel = NULL;
		}
		if (PanelScourge)
		{
			delete PanelScourge;
			PanelScourge = NULL;
		}
	}
}