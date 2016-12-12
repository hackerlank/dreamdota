#include "stdafx.h"
#include "DreamWar3Main.h"
#include "Table.h"
#include "RaceIcon.h"
#include "MultiIcon.h"
#include "Bar.h"
#include "APM.h"
#include "HeroBar.h"
#include "MinimapRadar.h"

namespace InformationPanel {
	static bool Enabled;

	static PlayerGroup ValidPlayers = PlayerGroup();
	static bool bSoloTeam = false;

	const float PANEL_POS_X = 0.002f;
	const float PANEL_POS_X_WITHHERO = 0.048f;
	const float PANEL_POS_Y = 0.557f;
	static float PanelPosXCalculated;

	const int HERO_PANEL_ABILITY_COUNT_MAX = 6;
	const int DOTA_PANEL_ABILITY_COUNT_MAX = 9;
	
	static bool bIsReplayOrObs;

	static const uint32_t PullDownItemTotal = 9;
	static InfoPanel::PullDown *PullDown;
	static IUIObject *DropDownPanels[PullDownItemTotal];
	static std::string PullDownItemNames[PullDownItemTotal];

	static UISimpleFrame *frameLevelDropDown;

	static Table *ResourcePanel;
	static Table *UnitPanel;
	static Table *DotaPanel;
	static Table *HeroPanel;
	static Table *APMPanel;
	static Table *ProductionPanel;
	static Table *ArmyPanel;
	static MinimapRadar *RadarPanel;
	static int DotaPanelLastHitCount[16];
	static int DotaPanelDenyCount[16];
	static std::string PanelPlayerTeamStr;

	void DetectHeroButtonExists ( Timer *tm )
	{
		if ( HeroButtonExists() )
		{
			PanelPosXCalculated = PANEL_POS_X_WITHHERO;
		}
		else
		{
			PanelPosXCalculated = PANEL_POS_X;
		}
		for (uint32_t i = 0; i < PullDownItemTotal; i++)
		{
			if ( PullDown != NULL )
			{
				PullDown->setAbsolutePosition(POS_BL, PanelPosXCalculated, PANEL_POS_Y);
			}
			if ( DropDownPanels[i] != NULL )
			{
				DropDownPanels[i]->setAbsolutePosition(POS_UL, PanelPosXCalculated, PANEL_POS_Y);
			}
		}
	}

	static char TagStr[100];
	const char *GetPlayerTag(int player, int team)
	{
		if (bSoloTeam)
		{
			sprintf_s(TagStr, 100, "%s%s%s", GetPlayerColorString(player, true), PlayerName(player), "|r");
		}
		else
		{
			sprintf_s(TagStr, 100, "%s %d", PanelPlayerTeamStr.c_str(), team+1);
		}
		return TagStr;
	}

	void RefreshResourcePlayer(int team, int indexInTeam, int indexTotal, int player)
	{
		int row = indexTotal;
		if (row > -1)
		{
			if (indexInTeam == 0)
			{	
				ResourcePanel->setTag( row, GetPlayerTag(player, team) );
			}

			RaceIcon *ri = ResourcePanel->getElement<RaceIcon*>(row, 0);
			if (!ri || ri->player() != player)
			{
				ri = new RaceIcon(UI_NULL, 0.03f, 0.03f, player);
				ResourcePanel->setElement(row, 0, ri, true);
			}

			Label *lb;
			lb = ResourcePanel->getElement<Label*>(row, 1);
			if (!lb) {
				lb = new Label(UI_NULL, "", 0.015f, Color::WHITE);
				ResourcePanel->setElement(row, 1, lb);
			}
			lb->setText( "%d", Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_RESOURCE_GOLD) );

			lb = ResourcePanel->getElement<Label*>(row, 2);
			if (!lb) {
				lb = new Label(UI_NULL, "", 0.015f, Color::WHITE);
				ResourcePanel->setElement(row, 2, lb);
			}
			lb->setText( "%d", Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_RESOURCE_LUMBER) );


			lb = ResourcePanel->getElement<Label*>(row, 3);
			if (!lb) {
				lb = new Label(UI_NULL, "", 0.015f, Color::WHITE);
				ResourcePanel->setElement(row, 3, lb);
			}
			int cap = Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_RESOURCE_FOOD_CAP);
			cap = min(cap, Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_FOOD_CAP_CEILING));
			lb->setText( cap > 0 ? "%d/%d" : "%d", 
				Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_RESOURCE_FOOD_USED),
				cap );
			int upkeep = Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_GOLD_UPKEEP_RATE);
			if (upkeep < 30)
			{
				lb->setTextColor(Color::GREEN);
			}
			else if (upkeep < 60)
			{
				lb->setTextColor(Color::YELLOW);
			}
			else
			{
				lb->setTextColor(Color::RED);
			}
			
		}
	}

	void RefreshResource(Timer *tm)
	{
		if (ResourcePanel && ResourcePanel->isShown())
		{
			if ( ValidPlayers.count() != ResourcePanel->sizeRow() )
			{
				ResourcePanel->setRowColumnCount(ValidPlayers.count(), ResourcePanel->sizeColumn());
			}
			ValidPlayers.forEachTeam(RefreshResourcePlayer);
		}
	}

	static UnitGroup *UnitPanelUnits;
	static UnitGroup *UnitPanelPlayerUnits[16];
	void RefreshUnitsContent(int team, int indexInTeam, int indexTotal, int player)
	{
	 	if (UnitPanel)
	 	{
			int row = indexTotal;
			int column = 0;

			if (indexInTeam == 0)
			{
				UnitPanel->setTag( row, GetPlayerTag(player, team) );
			}
	 		
			UnitGroup *playerUnits = UnitPanelPlayerUnits[player];

			std::map<uint32_t, std::set<Unit*>> unitMap;
			std::map<uint32_t, bool> unitEtherealMap;
			GroupForEachUnit(playerUnits, u,
				if (u->abilityLevel('Aloc') > 0)//蝗虫
				{
					continue;
				}
				unitMap[u->typeId()].insert(u);
				unitEtherealMap[u->typeId()] = u->testFlag(UnitFilter::ETHEREAL);
			);

			uint32_t size = unitMap.size();
			UnitPanel->setRowColumnCount(UnitPanel->sizeRow(), max(UnitPanel->sizeColumn(), size + 1));

			RaceIcon *raceIcon = UnitPanel->getElement<RaceIcon*>(row, 0);
			if (!raceIcon || raceIcon->player() != player)
			{
				raceIcon = new RaceIcon(UI_NULL, 0.03f, 0.03f, player);
				UnitPanel->setElement(row, 0, raceIcon, true);
			}			

			uint32_t i = 1; //第0列预留给玩家图标
			for (std::map<uint32_t, std::set<Unit*>>::iterator iter = unitMap.begin();
				iter != unitMap.end(); ++iter, ++i)
			{
				uint32_t typeId = iter->first;
				uint32_t number = iter->second.size();
				MultiIcon *mi;
				mi = UnitPanel->getElement<MultiIcon*>(row, i);
				if (!mi)
				{
					mi = new MultiIcon(UI_NULL, 0.025f, 0.025f, NULL, NULL, true);
					mi->showBottom(TypeNone);
					mi->showCorner(true);
					UnitPanel->setElement(row, i, mi);
				}
				mi->setTextureById(typeId);
				mi->clickerJumpGroup->clear();
				for (std::set<Unit*>::iterator iterinner = iter->second.begin();
					iterinner != iter->second.end(); ++iterinner)
				{
					mi->clickerJumpGroup->add(*iterinner);
				}
				
				//处理虚无状态
				if (unitEtherealMap[typeId])
				{
					mi->setColor(Color(0.75f, 1, 0.5f));
				}
				else mi->setColor(Color(1.f, 1.f, 1.f));

				if (Jass::IsHeroUnitId(typeId))
				{
					//TODO 处理死亡等情况
					mi->showCorner(true, Color::GOLD);
					mi->setCorner("Lv %d", (*iter->second.begin())->level(true));
				}
				else
				{
					mi->showCorner(true, Color::WHITE);
					mi->setCorner("%d", number);	//数量
				}
				mi->show(true);
			}
			while(i < UnitPanel->sizeColumn())
			{
				UnitPanel->setElement(row, i, NULL);
				++i;
			}
	 	}
	}

 	void RefreshUnits(Timer *tm)
 	{
 		if (UnitPanel && UnitPanel->isShown())
 		{
			if (UnitPanelUnits)
			{
				GroupDestroy(UnitPanelUnits);
			}
			UnitPanelUnits = GroupUnits(
				NULL,
				NULL,
				ValidPlayers,
				NULL,
				UnitFilter(
					NULL,
					UnitFilter::STRUCTURE | UnitFilter::WARD | UnitFilter::DEAD | UnitFilter::ILLUSION
				)
			);
			for (int i = 0; i < 16; i++)
			{
				if (UnitPanelPlayerUnits[i])
				{
					UnitPanelPlayerUnits[i]->clear();
				}
				else
				{
					UnitPanelPlayerUnits[i] = new UnitGroup();
				}
			}
			int owner;
			for (UnitGroup::iterator iter = UnitPanelUnits->begin();
				iter != UnitPanelUnits->end(); ++iter)
			{
				owner = (*iter)->owner();
				if (owner >= 0 && owner < 16)
				{
					UnitPanelPlayerUnits[owner]->add(*iter);
				}
			}

			UnitPanel->setRowColumnCount(ValidPlayers.count(), UnitPanel->sizeColumn());
			ValidPlayers.forEachTeam(RefreshUnitsContent);
 		}
 	}

	void RefreshDotaPlayerIcon(int team, int indexInTeam, int indexTotal, int player)
	{
		int row = indexTotal;
		if (row > -1 && (uint32_t)row < DotaPanel->sizeRow())
		{
			MultiIcon *mi = new MultiIcon(UI_NULL, 0.03f, 0.03f);
			mi->showBottom(TypeNone);
			mi->showCorner(true, Color::GOLD);
			mi->show(true);
			DotaPanel->setElement(row, 0, mi);
		}
	}

	struct AbilityPositionLess {
		bool operator() (const Ability* lhs, const Ability *rhs) const
		{
			int posValueDiff = lhs->iconPositionValue() - rhs->iconPositionValue();
			if (posValueDiff < 0) 
				return true;
			else if (posValueDiff == 0)
			{
				int typeIdDiff = lhs->typeId() - rhs->typeId();
				if (typeIdDiff < 0) 
					return true;
				else if (typeIdDiff == 0)
				{
					return lhs < rhs;
				}
			}
			return false;
		}
	};

	void RefreshDotaContent(int team, int indexInTeam, int indexTotal, int player)
	{
		int column = 0;

		//0: 玩家英雄 
		//1~DOTA_PANEL_ABILITY_COUNT_MAX: 技能 
		//DOTA_PANEL_ABILITY_COUNT_MAX+1~DOTA_PANEL_ABILITY_COUNT_MAX+6: 物品 
		//DOTA_PANEL_ABILITY_COUNT_MAX+7: 金钱
		UnitGroup *playerHeros = GroupUnits(NULL, NULL, PlayerGroupSingle(player), NULL, 
			UnitFilter(
				UnitFilter::HERO, 
				UnitFilter::ILLUSION
			),
			1
		);

		Unit *hero = playerHeros->getUnit(0);
		if (hero)
		{
			int row = indexTotal;//g.position(player);
			if (indexInTeam == 0)
			{
				std::string teamName;
				switch(team)
				{
				case 0:
					teamName = "|cffff0000";
					teamName += ObjectIdToNameChar('n03N');
					teamName += "|r";
					DotaPanel->setTag( indexTotal,  teamName.c_str());	 //TODO改为动态获取
					break;
				case 1:
					teamName = "|cff00ff00";
					teamName += ObjectIdToNameChar('n03O');
					teamName += "|r";
					DotaPanel->setTag( indexTotal,  teamName.c_str());
					break;
				default:
					break;
				}
			}
			


			bool bIsDead = (hero->life() <= 0);

			//头像
			MultiIcon *heroIcon = DotaPanel->getElement<MultiIcon*>(row, column);//column = 0
			if (heroIcon)
			{
				
				heroIcon->setTextureById(hero->typeId());
				heroIcon->setClickUnit(hero);
				heroIcon->showCorner(true, bIsDead ? Color::GREY : Color::GOLD);
				heroIcon->setCorner("Lv %d", hero->level(true));
				heroIcon->activate(!bIsDead);
				heroIcon->show(true);
			}
			column++;			

			//技能
			std::set<Ability*, AbilityPositionLess> AbilityPositionRankedSet;
			std::set<uint32_t> AbilityExceptions;
			std::set<uint32_t> AbilitySpellBookSpells;
			Ability *abil = hero->AbilityListHead();
			
			bool bHasIcon = true;
			bool bIsNotBuff = true;
			bool bNotHiddenAbil = true;
			bool bNotItem = true;
			//bool bTechAvailable = true;

			while (abil)
			{
				//DefaultDebugPanel->set(abil->name(), "UIDef: 0x%X", ((war3::CAbility*)abil)->defData->uiDefAvailable);

				uint32_t flag = abil->flag();

				if (abil->getSpellBookSpells(&AbilitySpellBookSpells) > 0)
				{
					for(std::set<uint32_t>::iterator iter = AbilitySpellBookSpells.begin();
						iter != AbilitySpellBookSpells.end(); ++iter)
					{
						AbilityExceptions.insert(*iter);
					}
				}

				bHasIcon = abil->iconPath() != NULL;//TODO 实际上少判断了一层图标，应当使用排除标准技能的方式
				bIsNotBuff = !IsAbilityBuff((war3::CAbility*)abil);	//TODO 包装
				bNotHiddenAbil = ( !(flag & 0x80000000) || ((flag & 0x10000000) && (flag & 0x10)) );//不是光环以外隐藏技能(buff)
				bNotItem = !(flag & 0x20);//不是物品
				//bTechAvailable = IsTechtreeAvailable(player, abil->typeId());
				//MUSTDO 掉线bug

				if (	
					bHasIcon
					&&	bIsNotBuff
					&&	bNotHiddenAbil
					&&	bNotItem
					//&&	bTechAvailable
				)
				{
					AbilityPositionRankedSet.insert(abil);
				}
				
				abil = abil->nextNode();
			}

			for (std::set<Ability*, AbilityPositionLess>::iterator iter = AbilityPositionRankedSet.begin();
				iter != AbilityPositionRankedSet.end(); ++iter)
			{
				abil = *iter;
				uint32_t typeId = abil->typeId();
				uint32_t baseTypeId = abil->baseTypeId();

				if (AbilityExceptions.count(typeId))		//魔法书
				{
					continue;
				}

				MultiIcon *abilIcon = DotaPanel->getElement<MultiIcon*>(row, column);
				if (!abilIcon)
				{
					abilIcon = new MultiIcon(UI_NULL, 0.03f, 0.03f, NULL, NULL, true, true);
					DotaPanel->setElement(row, column, abilIcon);
				}
				abilIcon->setTextureById(typeId);
				abilIcon->setClickUnit(NULL);
				
				//英雄死亡时显示为不可用
				//技能由于其他原因不可用时显示为不可用
				bool bDisabled = false;//(abil->flag() & 0x100) != 0;		//TODO bug 会影响疾风步判定
				bool bWantActivate = !(bIsDead || bDisabled);

				if ( abilIcon->isActive() != bWantActivate )
				{
					abilIcon->activate(bWantActivate);
				}

				bool bInsufficientMana = AbilityManaCostGet((war3::CAbility*)abil) > hero->mana();
				Color c = (!bIsDead && bInsufficientMana) ? 
					Color((uint8_t)0x0, 0x40, 0xFF) : 
 					Color((uint8_t)0xFF, 0xFF, 0xFF);
				if(abilIcon->getColor() != c )
				{
					abilIcon->setColor(c);
				}
					
				//abilIcon->showCorner( true, bIsDead ? Color::GREY : Color::GOLD );
				abilIcon->setCorner("%d", abil->level()+1);
				float cdRemain = abil->cooldownRemain();
				if (!bIsDead && cdRemain > 0)
				{
					abilIcon->showBottom(TypeText);
					abilIcon->setBottomLabel("%d", (int)ceil(cdRemain));
				}
				else 
				{
					abilIcon->showBottom(TypeNone);
				}
				abilIcon->show(true);
				column++;
				if(column - 1 >= DOTA_PANEL_ABILITY_COUNT_MAX) break;
			}
			//清理 暂时用
			for (uint32_t i = column; i < 1 + DOTA_PANEL_ABILITY_COUNT_MAX; ++i)
				DotaPanel->setElement(row, i, NULL);

			

			column = 1 + DOTA_PANEL_ABILITY_COUNT_MAX + 1;
			for (uint32_t i = 0; i < 6; i++)
			{
				Item *it = GetItem(Jass::UnitItemInSlot(hero->handleId(), i));
				if (!it)
				{
					continue;
				}
				else
				{
					MultiIcon *itemIcon = DotaPanel->getElement<MultiIcon*>(row, column);
					if (!itemIcon)
					{
						itemIcon = new MultiIcon(UI_NULL, 0.03f, 0.03f, NULL, NULL, true, true);
						itemIcon->showBottom(TypeNone);
						DotaPanel->setElement(row, column, itemIcon);
					}
					itemIcon->setTextureById(it->typeId());
					itemIcon->setClickUnit(NULL);

					int charge = it->charges();
					if (!charge)
					{
						itemIcon->showCorner(false);
					}
					else
					{
						itemIcon->showCorner(true);
						itemIcon->setCorner("%d", it->charges());
					}
					//TODO 处理英雄死亡判断
					if ( itemIcon->isActive() != !bIsDead )
					{
						itemIcon->activate(!bIsDead);
					}

					float cdRemain = it->cooldownRemain();
					if (!bIsDead && cdRemain > 0)
					{
						itemIcon->showBottom(TypeText);
						itemIcon->setBottomLabel("%d", (int)ceil(cdRemain));
					}
					else 
					{
						itemIcon->showBottom(TypeNone);
					}
					itemIcon->show(true);
					column++;
				}
			}
			//清理
			for (uint32_t i = column; i < 1 + DOTA_PANEL_ABILITY_COUNT_MAX + 1 + 6 + 1; ++i)
				DotaPanel->setElement(row, i, NULL);

			column = 1 + DOTA_PANEL_ABILITY_COUNT_MAX + 1 + 6 + 1;
			//金钱
			Label *lbGold = DotaPanel->getElement<Label*>(row, column);
			if (!lbGold) {
				lbGold = new Label(UI_NULL, "", 0.013f, Color::WHITE);
				DotaPanel->setElement(row, column, lbGold);
			}
			lbGold->setText( "%d", Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_RESOURCE_GOLD) );

			column++;
			//补刀值
			Label *lbLasthit = DotaPanel->getElement<Label*>(row, column);
			if (!lbLasthit) {
				lbLasthit = new Label(UI_NULL, "", 0.013f, Color::WHITE);
				DotaPanel->setElement(row, column, lbLasthit);
			}
			lbLasthit->setText("%d/%d", DotaPanelLastHitCount[player], DotaPanelDenyCount[player]);

		}

		GroupDestroy(playerHeros);
	}

	void RefreshDota(Timer *tm)
	{
		if (DotaPanel && DotaPanel->isShown())
		{
			if ( ValidPlayers.count() != DotaPanel->sizeRow() )
			{
				DotaPanel->setRowColumnCount(ValidPlayers.count(), DotaPanel->sizeColumn());
				ValidPlayers.forEachTeam(RefreshDotaPlayerIcon);
			}
			ValidPlayers.forEachTeam(RefreshDotaContent);
		}
	}

	void CalcLastHitScore( const Event *evt )
	{
		Unit *dyingUnit = GetUnit(Jass::GetDyingUnit());
		Unit *killer = GetUnit(Jass::GetKillingUnit());
		int killerOwner, dyingOwner;

		if (NULL != dyingUnit && NULL != killer)
		{
			dyingOwner = dyingUnit->owner();
			killerOwner = killer->owner();
			if (
					PlayerFilterMatch(
						dyingOwner,
						PlayerFilter(
							NULL,
							PlayerFilter::CONTROL_USER | PlayerFilter::CONTROL_CREEP | PlayerFilter::CONTROL_COMPUTER
						)
					)
				&&	!dyingUnit->testFlag(UnitFilter::STRUCTURE)
			)
			{
				if (
					PlayerFilterMatch(
						killerOwner,
						PlayerFilter(
							PlayerFilter::ALLIANCE_PASSIVE,
							NULL,
							dyingOwner
						)
					)
				)
				{
					DotaPanelDenyCount[killerOwner] += 1;
				}
				else
				{
					DotaPanelLastHitCount[killerOwner] += 1;
				}
			}
		}
	}

	static int RefreshHeroRowCurrent;
	static UnitGroup *HeroPanelHeroes;

	void RefreshHeroContent(int team, int indexInTeam, int indexTotal, int player)
	{

		Table *panel = HeroPanel;
		int row = RefreshHeroRowCurrent;
		int column = 0;

		if (indexInTeam == 0)
		{
			panel->setTag( row, GetPlayerTag(player, team) );
		}

		UnitGroup *playerHeroes = GroupUnits(
			HeroPanelHeroes,
			NULL,
			PlayerGroupSingle(player),
			NULL,
			UnitFilter()
		);

		Unit *hero;
		for (UnitGroup::iterator iter = playerHeroes->begin();
			iter != playerHeroes->end(); ++iter, ++row)
		{
			hero = *iter;
			if (hero)
			{
				bool bIsDead = (hero->life() <= 0);
				//0: 头像
				column = 0;
				MultiIcon *heroIcon = panel->getElement<MultiIcon*>(row, column);
				if (!heroIcon)
				{
					heroIcon = new MultiIcon(UI_NULL, 0.03f, 0.03f);
					heroIcon->showBottom(TypeNone);
					panel->setElement(row, column, heroIcon);
				}
				heroIcon->setTextureById(hero->typeId());
				heroIcon->setClickUnit(hero);
				heroIcon->showCorner(true, bIsDead ? Color::GREY : Color::GOLD);
				heroIcon->setCorner("Lv %d", hero->level(true));
				heroIcon->show(true);
				heroIcon->activate(!bIsDead);

				//1 ~ HERO_PANEL_ABILITY_COUNT_MAX: 技能
				column = 1;
				std::set<Ability*, AbilityPositionLess> AbilityPositionRankedSet;
				std::set<uint32_t> AbilityExceptions;
				std::set<uint32_t> AbilitySpellBookSpells;
				Ability *abil = hero->AbilityListHead();
				bool bHasIcon = true;
				bool bIsNotBuff = true;
				bool bNotHiddenAbil = true;
				bool bNotItem = true;
				//bool bTechAvailable = true;
				while (abil)
				{
					uint32_t flag = abil->flag();
					if (abil->getSpellBookSpells(&AbilitySpellBookSpells) > 0)
					{
						for(std::set<uint32_t>::iterator iter = AbilitySpellBookSpells.begin();
							iter != AbilitySpellBookSpells.end(); ++iter)
						{
							AbilityExceptions.insert(*iter);
						}
					}
					bHasIcon = abil->iconPath() != NULL;//TODO 实际上少判断了一层图标，应当使用排除标准技能的方式
					bIsNotBuff = !IsAbilityBuff((war3::CAbility*)abil);	//TODO 包装
					bNotHiddenAbil = ( !(flag & 0x80000000) || ((flag & 0x10000000) && (flag & 0x10)) );//不是光环以外隐藏技能(buff)
					bNotItem = !(flag & 0x20);//不是物品
					//bTechAvailable = IsTechtreeAvailable(player, abil->typeId());
					//MUSTDO 掉线bug

					if (	
						bHasIcon
						&&	bIsNotBuff
						&&	bNotHiddenAbil
						&&	bNotItem
						//&&	bTechAvailable
						)
					{
						AbilityPositionRankedSet.insert(abil);
					}
					abil = abil->nextNode();
				}

				for (std::set<Ability*, AbilityPositionLess>::iterator iter = AbilityPositionRankedSet.begin();
					iter != AbilityPositionRankedSet.end(); ++iter)
				{
					abil = *iter;
					uint32_t typeId = abil->typeId();
					uint32_t baseTypeId = abil->baseTypeId();

					if (AbilityExceptions.count(typeId))		//魔法书
					{
						continue;
					}

					MultiIcon *abilIcon = panel->getElement<MultiIcon*>(row, column);
					if (!abilIcon)
					{
						abilIcon = new MultiIcon(UI_NULL, 0.03f, 0.03f, NULL, NULL, true, true);
						panel->setElement(row, column, abilIcon);
					}
					abilIcon->setTextureById(typeId);
					abilIcon->setClickUnit(NULL);

					//英雄死亡时显示为不可用
					//技能由于其他原因不可用时显示为不可用
					bool bWantActivate = !(bIsDead);
					abilIcon->activate(bWantActivate);
					bool bInsufficientMana = AbilityManaCostGet((war3::CAbility*)abil) > hero->mana();
					Color c = (!bIsDead && bInsufficientMana) ? 
						Color((uint8_t)0x0, 0x40, 0xFF) : 
					Color((uint8_t)0xFF, 0xFF, 0xFF);
					if(abilIcon->getColor() != c )
					{
						abilIcon->setColor(c);
					}
					abilIcon->setCorner("%d", abil->level()+1);
					float cdRemain = abil->cooldownRemain();
					if (!bIsDead && cdRemain > 0)
					{
						abilIcon->showBottom(TypeText);
						abilIcon->setBottomLabel("%d", (int)ceil(cdRemain));
						//abilIcon->showBottom(TypeBar);
						//abilIcon->setBottomBar(cdRemain / abil->cooldown());
					}
					else 
					{
						abilIcon->showBottom(TypeNone);
					}
					abilIcon->show(true);
					column++;
					if(column - 1 >= HERO_PANEL_ABILITY_COUNT_MAX) break;
				}
				//清理 暂时用
				for (uint32_t i = column; i < 1 + HERO_PANEL_ABILITY_COUNT_MAX; ++i)
					panel->setElement(row, i, NULL);

				//物品
				column = 1 + HERO_PANEL_ABILITY_COUNT_MAX + 1;
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
							itemIcon = new MultiIcon(UI_NULL, 0.03f, 0.03f, NULL, NULL, true, true);
							itemIcon->showBottom(TypeNone);
							panel->setElement(row, column, itemIcon);
						}
						itemIcon->setTextureById(it->typeId());
						itemIcon->setClickUnit(NULL);

						int charge = it->charges();
						if (!charge)
						{
							itemIcon->showCorner(false);
						}
						else
						{
							itemIcon->showCorner(true);
							itemIcon->setCorner("%d", it->charges());
						}
						itemIcon->activate(!bIsDead);

						float cdRemain = it->cooldownRemain();
						if (!bIsDead && cdRemain > 0)
						{
							itemIcon->showBottom(TypeText);
							itemIcon->setBottomLabel("%d", (int)ceil(cdRemain));
						}
						else 
						{
							itemIcon->showBottom(TypeNone);
						}
						itemIcon->show(true);
						column++;
					}
				}
				//清理
				for (uint32_t i = column; i < 1 + HERO_PANEL_ABILITY_COUNT_MAX + 1 + 6 + 1; ++i)
					panel->setElement(row, i, NULL);

			}
		}


		GroupDestroy(playerHeroes);
		RefreshHeroRowCurrent = row;
	}

	

	void RefreshHero(Timer *tm)
	{
		if (HeroPanel && HeroPanel->isShown())
		{
			if (HeroPanelHeroes)
			{
				GroupDestroy(HeroPanelHeroes);
			}
			HeroPanelHeroes = GroupUnits(
				NULL,
				NULL,
				ValidPlayers,
				NULL,
				UnitFilter(
					UnitFilter::HERO,
					UnitFilter::ILLUSION
				)
			);
			HeroPanel->setRowColumnCount(HeroPanelHeroes->size(), HeroPanel->sizeColumn());

			RefreshHeroRowCurrent = 0;
			ValidPlayers.forEachTeam(RefreshHeroContent);
		}
	}

	void RefreshAPMPlayer(int team, int indexInTeam, int indexTotal, int player)
	{
		Table *panel = APMPanel;
		int row = indexTotal;
		if (row > -1)
		{
			if (indexInTeam == 0)
			{	
				panel->setTag( row, GetPlayerTag(player, team) );
			}

			RaceIcon *ri = panel->getElement<RaceIcon*>(row, 0);
			if (!ri || ri->player() != player)
			{
				ri = new RaceIcon(UI_NULL, 0.03f, 0.03f, player);
				panel->setElement(row, 0, ri, true);
			}

			BarIndicator *bar;
			bar = panel->getElement<BarIndicator *>(row, 1);
			if ( bar == NULL )
			{
				panel->setElement(row, 1, 
					bar = new BarIndicator (
					UI_NULL, 0.065f, 0.02f,
					"UI\\Widgets\\EscMenu\\Human\\editbox-border.blp",
					0.005f,
					0.002f,
					"UI\\Feedback\\HPBarConsoleSmall\\human-statbar-color.blp",
					0.015f
					)
				);
				bar->setColor(Color::GREY);
			}
			bar->setValue((int)floor(APMGetPeak(player)), 500);
		}
	}

	void RefreshAPMPlayerAverage(int team, int indexInTeam, int indexTotal, int player)
	{
		Table *panel = APMPanel;
		int row = indexTotal;
		if (row > -1)
		{
			BarIndicator *bar;
			bar = panel->getElement<BarIndicator *>(row, 2);
			if ( bar == NULL )
			{
				panel->setElement(row, 2, 
					bar = new BarIndicator (
					UI_NULL, 0.065f, 0.02f,
					"UI\\Widgets\\EscMenu\\Human\\editbox-border.blp",
					0.005f,
					0.002f,
					"UI\\Feedback\\HPBarConsoleSmall\\human-statbar-color.blp",
					0.015f
					)
				);
				bar->setColor(Color::GREY);
			}
			bar->setValue((int)floor(APMGetAverage(player)), 350);
		}
	}

	void RefreshAPM(Timer *tm)
	{
		if (APMPanel && APMPanel->isShown())
		{
			APMPanel->setRowColumnCount(ValidPlayers.count(), APMPanel->sizeColumn());
			ValidPlayers.forEachTeam(RefreshAPMPlayer);
		}
	}

	void RefreshAPMAverage(Timer *tm)
	{
		if (APMPanel && APMPanel->isShown())
		{
			APMPanel->setRowColumnCount(ValidPlayers.count(), APMPanel->sizeColumn());
			ValidPlayers.forEachTeam(RefreshAPMPlayer);
			ValidPlayers.forEachTeam(RefreshAPMPlayerAverage);
		}
	}


	static UnitGroup *ProductionPanelUnits;
	static UnitGroup *ProductionPanelPlayerUnits[16];
	void RefreshProductionContent(int team, int indexInTeam, int indexTotal, int player)
	{
		Table *panel = ProductionPanel;
		int row = indexTotal;
		int column = 0;
		float iconSize = 0.032f;

		if (indexInTeam == 0)
		{
			panel->setTag( row, GetPlayerTag(player, team) );
		}

		RaceIcon *raceIcon = panel->getElement<RaceIcon*>(row, column);
		if (!raceIcon || raceIcon->player() != player)
		{
			raceIcon = new RaceIcon(UI_NULL, 0.03f, 0.03f, player);
			panel->setElement(row, 0, raceIcon, true);
		}
		column++;

		UnitGroup *playerConstructions = GroupUnits(
			ProductionPanelPlayerUnits[player],
			NULL,
			PlayerGroupAll(),
			NULL,
			UnitFilter(
				UnitFilter::UNDER_CONSTRUCTION,
				NULL
			)
		);

		UnitGroup *playerUpgrades = GroupUnits(
			ProductionPanelPlayerUnits[player],
			NULL,
			PlayerGroupAll(),
			NULL,
			UnitFilter(
				UnitFilter::UNDER_UPGRADE,
				NULL
			)
		);

		UnitGroup *playerQueues = GroupUnits(
			ProductionPanelPlayerUnits[player],
			NULL,
			PlayerGroupAll(),
			NULL,
			UnitFilter(
				UnitFilter::UNDER_QUEUE,
				NULL
			)
		);

		panel->setRowColumnCount( panel->sizeRow(), max(panel->sizeColumn(), 
			1 + playerConstructions->size() + playerUpgrades->size() + playerQueues->size()
		) );


		//建造中的建筑
		while (playerConstructions->size() > 0)
		{
			UnitGroup *g = GroupUnits(playerConstructions, playerConstructions->getUnit(0)->typeId(), PlayerGroupAll(), NULL, UnitFilter() );
			playerConstructions->remove(g);

			ProgressIcon *icon;
			icon = panel->getElement<ProgressIcon*>(row, column);
			if ( !icon )
			{
				icon = new ProgressIcon(UI_NULL, iconSize, iconSize);
				panel->setElement(row, column, icon);
			}
			icon->refreshType = TypeConstruction;
			icon->units->copy(g);
			icon->clickerJumpGroup->copy(g);
			icon->setTextureById(g->getUnit(0)->typeId());

			GroupDestroy(g);
			column++;
		}

		//升级
		while (playerUpgrades->size() > 0)
		{
			uint32_t desiredTypeId = playerUpgrades->getUnit(0)->upgradeType();

			UnitGroup *g = new UnitGroup();
			for (UnitGroup::iterator iter = playerUpgrades->begin(); iter != playerUpgrades->end(); ++iter)
			{
				Unit *u = *iter;
				uint32_t typeId = u->upgradeType();

				if (iter == playerUpgrades->begin())
				{
					desiredTypeId = typeId;
					g->add(u);
				}
				else
				{
					if (typeId == desiredTypeId)
					{
						g->add(u);
					}
				}
			}
			playerUpgrades->remove(g);

			ProgressIcon *icon;
			icon = panel->getElement<ProgressIcon*>(row, column);
			if ( !icon )
			{
				icon = new ProgressIcon(UI_NULL, iconSize, iconSize);
				panel->setElement(row, column, icon);
			}
			icon->refreshType = TypeUpgrade;
			icon->units->copy(g);
			icon->clickerJumpGroup->copy(g);
			icon->setTextureById(desiredTypeId);

			GroupDestroy(g);
			column++;
		}

		//生产/研究
		while (playerQueues->size() > 0)
		{
			UnitGroup *g = new UnitGroup();
			uint32_t desiredQueueTypeId;
			for (UnitGroup::iterator iter = playerQueues->begin(); iter != playerQueues->end(); ++iter)
			{
				Unit *u = *iter;
				uint32_t queueTypeId = u->queueType();

				if (iter == playerQueues->begin())
				{
					desiredQueueTypeId = queueTypeId;
					g->add(u);
				}
				else
				{
					if (queueTypeId == desiredQueueTypeId)
					{
						g->add(u);
					}
				}
			}

			playerQueues->remove(g);
			if (desiredQueueTypeId != NULL)
			{
				ProgressIcon *icon;
				icon = panel->getElement<ProgressIcon*>(row, column);
				if ( !icon )
				{
					icon = new ProgressIcon(UI_NULL, iconSize, iconSize);
					panel->setElement(row, column, icon);
				}
				icon->refreshType = TypeQueue;
				icon->units->copy(g);
				icon->clickerJumpGroup->copy(g);
				icon->setTextureById(desiredQueueTypeId,
					Jass::GetPlayerTechCount(Jass::Player(player), desiredQueueTypeId, true)
				);
				column++;
			}
			GroupDestroy(g);
		}

		for (uint32_t i = column; i < panel->sizeColumn(); ++i)
		{
			panel->setElement(row, i, NULL);
		}




		GroupDestroy(playerConstructions);
		GroupDestroy(playerUpgrades);
		GroupDestroy(playerQueues);
	}

	void RefreshProduction ( Timer *tm )
	{
		if (ProductionPanel && ProductionPanel->isShown())
		{

			if (ProductionPanelUnits)
			{
				GroupDestroy(ProductionPanelUnits);
			}
			ProductionPanelUnits = GroupUnits(
				NULL,
				NULL,
				ValidPlayers,
				NULL,
				UnitFilter(
					UnitFilter::STRUCTURE,
					UnitFilter::WARD | UnitFilter::DEAD | UnitFilter::ILLUSION
				)
			);
			for (int i = 0; i < 16; i++)
			{
				if (ProductionPanelPlayerUnits[i])
				{
					ProductionPanelPlayerUnits[i]->clear();
				}
				else
				{
					ProductionPanelPlayerUnits[i] = new UnitGroup();
				}
			}
			int owner;
			for (UnitGroup::iterator iter = ProductionPanelUnits->begin();
				iter != ProductionPanelUnits->end(); ++iter)
			{
				owner = (*iter)->owner();
				if (owner >= 0 && owner < 16)
				{
					ProductionPanelPlayerUnits[owner]->add(*iter);
				}
			}

			ProductionPanel->setRowColumnCount(ValidPlayers.count(), ProductionPanel->sizeColumn());
			ValidPlayers.forEachTeam(RefreshProductionContent);

			////test 显示当前所选单位的技能
			//UnitGroup *g = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
			//DefaultDebugPanel->clear();
			//if (g->size())
			//{
			//	Unit *u = g->getUnit(0);
			//	Ability *abil = u->AbilityListHead();
			//	while (abil)
			//	{
			//		DefaultDebugPanel->set(abil->typeIdChar(), "%s, 0x%X", abil->name(), abil
			//			);
			//		abil = abil->nextNode();
			//	}
			//	
			//}
			
		}
	}

	std::map<int, std::map<const char*, int>> ArmyMap;
	void CalcArmyPlayer(int team, int indexInTeam, int indexTotal, int player)
	{
		int playerArmyGold = 0;
		int playerArmyLumber = 0;
		int playerArmyFood = Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_RESOURCE_FOOD_USED);
		//统计所有作战单位的资源：非建筑，非工人
		//统计所有英雄身上拥有的宝物价值
		UnitGroup *g = GroupUnits(NULL, NULL, PlayerGroupSingle(player), NULL,
			UnitFilter(
			NULL,
			UnitFilter::DEAD | UnitFilter::PEON | UnitFilter::STRUCTURE | UnitFilter::ILLUSION | UnitFilter::WARD
			)
			);

		for (UnitGroup::iterator iter = g->begin(); iter != g->end(); ++iter)
		{
			Unit *u = *iter;
			playerArmyGold += u->costGold();
			playerArmyLumber += u->costLumber();
		}
		ArmyMap[player]["Gold"] = playerArmyGold;
		ArmyMap[player]["Lumber"] = playerArmyLumber;
		ArmyMap[player]["Food"] = playerArmyFood;
		ArmyMap[-1]["Gold"] = max( playerArmyGold, ArmyMap[-1]["Gold"]);
		ArmyMap[-1]["Lumber"] = max ( playerArmyLumber, ArmyMap[-1]["Lumber"] );
		ArmyMap[-1]["Food"] = max ( playerArmyFood, ArmyMap[-1]["Food"] );
	}

	void RefreshArmyPlayer(int team, int indexInTeam, int indexTotal, int player)
	{
		Table *panel = ArmyPanel;
		int row = indexTotal;
		if (row > -1)
		{
			int gold = ArmyMap[player]["Gold"];
			int lumber = ArmyMap[player]["Lumber"];
			int food = ArmyMap[player]["Food"];
			int maxGold = ArmyMap[-1]["Gold"];
			int maxLumber = ArmyMap[-1]["Lumber"];
			int maxFood = ArmyMap[-1]["Food"];
			if (maxFood < 50) maxFood = 50;
			else if (maxFood < 80) maxFood = 80;
			else maxFood = max(maxFood, 100);

			if (indexInTeam == 0)
			{	
				panel->setTag( row, GetPlayerTag(player, team) );
			}

			RaceIcon *ri = panel->getElement<RaceIcon*>(row, 0);
			if (!ri || ri->player() != player)
			{
				ri = new RaceIcon(UI_NULL, 0.03f, 0.03f, player);
				panel->setElement(row, 0, ri, true);
			}

			BarIndicator *bar;
			bar = panel->getElement<BarIndicator *>(row, 1);
			if ( bar == NULL )
			{
				panel->setElement(row, 1, 
					bar = new BarIndicator (
					UI_NULL, 0.065f, 0.02f,
					"UI\\Widgets\\EscMenu\\Human\\editbox-border.blp",
					0.005f,
					0.002f,
					"UI\\Feedback\\HPBarConsoleSmall\\human-statbar-color.blp",
					0.015f
					)
				);
				bar->setColor(Color::GREY);
			}
			bar->setValue(gold, maxGold);

			bar = panel->getElement<BarIndicator *>(row, 2);
			if ( bar == NULL )
			{
				panel->setElement(row, 2, 
					bar = new BarIndicator (
					UI_NULL, 0.065f, 0.02f,
					"UI\\Widgets\\EscMenu\\Human\\editbox-border.blp",
					0.005f,
					0.002f,
					"UI\\Feedback\\HPBarConsoleSmall\\human-statbar-color.blp",
					0.015f
					)
					);
				bar->setColor(Color::GREY);
			}
			bar->setValue(lumber, maxLumber);

			bar = panel->getElement<BarIndicator *>(row, 3);
			if ( bar == NULL )
			{
				panel->setElement(row, 3, 
					bar = new BarIndicator (
					UI_NULL, 0.065f, 0.02f,
					"UI\\Widgets\\EscMenu\\Human\\editbox-border.blp",
					0.005f,
					0.002f,
					"UI\\Feedback\\HPBarConsoleSmall\\human-statbar-color.blp",
					0.015f
					)
					);
				bar->setColor(Color::GREY);
			}
			bar->setValue(food, maxFood);
		}
	}

	void RefreshArmy(Timer *tm)
	{
		if (ArmyPanel && ArmyPanel->isShown())
		{
			if ( ValidPlayers.count() != ArmyPanel->sizeRow() )
			{
				ArmyPanel->setRowColumnCount(ValidPlayers.count(), ArmyPanel->sizeColumn());
			}
			ArmyMap[-1]["Gold"] = 0;
			ArmyMap[-1]["Lumber"] = 0;
			ArmyMap[-1]["Food"] = 0;
			ValidPlayers.forEachTeam(CalcArmyPlayer);
			ValidPlayers.forEachTeam(RefreshArmyPlayer);
		}
	}

	void RefreshRadar(Timer *tm)
	{
		if (RadarPanel && RadarPanel->isShown())
		{
			RadarPanel->RefreshData();
		}
	}

	void RefreshPlayer(Timer *tm)
	{
		ValidPlayers = PlayerGroup(
			PlayerFilter::STATE_PLAYING, 
			PlayerFilter::CONTROL_CREEP | PlayerFilter::CONTROL_NEUTRAL 
		);
		bSoloTeam = (ValidPlayers.countTeam() == ValidPlayers.count());
	}

	void PdCallback(InfoPanel::PullDown *pd, uint32_t index)
	{
		for (uint32_t i = 0; i < PullDownItemTotal; i++){
			if (i != index && DropDownPanels[i]) DropDownPanels[i]->show(false);
		}
		if (DropDownPanels[index]) 
		{
			DropDownPanels[index]->show(true);
			switch (index)
			{
			case 0:
				break;
			case 1:
				RefreshResource(NULL); break;
			case 2:
				RefreshUnits(NULL); break;
			case 3:
				RefreshHero(NULL); break;
			case 4:
				RefreshAPMAverage(NULL); break;
			case 5:
				RefreshDota(NULL); break;
			case 6:
				RefreshProduction(NULL); break;
			case 7:
				RefreshArmy(NULL); break;
			case 8:
				RefreshRadar(NULL); break;
			default:
				break;
			}
		}
	}

	static int ResourcePanelHotkey;
	static bool ResourcePanelHotkeyCtrl;
	static bool ResourcePanelHotkeyAlt;
	static bool ResourcePanelHotkeyShift;

	static int UnitPanelHotkey;
	static bool UnitPanelHotkeyCtrl;
	static bool UnitPanelHotkeyAlt;
	static bool UnitPanelHotkeyShift;

	static int HeroPanelHotkey;
	static bool HeroPanelHotkeyCtrl;
	static bool HeroPanelHotkeyAlt;
	static bool HeroPanelHotkeyShift;

	static int APMPanelHotkey;
	static bool APMPanelHotkeyCtrl;
	static bool APMPanelHotkeyAlt;
	static bool APMPanelHotkeyShift;

	static int DotaPanelHotkey;
	static bool DotaPanelHotkeyCtrl;
	static bool DotaPanelHotkeyAlt;
	static bool DotaPanelHotkeyShift;

	static int ProductionPanelHotkey;
	static bool ProductionPanelHotkeyCtrl;
	static bool ProductionPanelHotkeyAlt;
	static bool ProductionPanelHotkeyShift;

	static int ArmyPanelHotkey;
	static bool ArmyPanelHotkeyCtrl;
	static bool ArmyPanelHotkeyAlt;
	static bool ArmyPanelHotkeyShift;

	static int RadarPanelHotkey;
	static bool RadarPanelHotkeyCtrl;
	static bool RadarPanelHotkeyAlt;
	static bool RadarPanelHotkeyShift;

	void InitNames () {
		char tmp[30];
		PullDownItemNames[0].assign(StringManager::GetString(STR::PANEL_NONE));

		PullDownItemNames[1].assign(StringManager::GetString(STR::PANEL_RESOURCE));
		sprintf_s(tmp, 30, " (%s)", KEYCODE::getStr(ResourcePanelHotkey));
		PullDownItemNames[1]+=tmp;

		PullDownItemNames[2].assign(StringManager::GetString(STR::PANEL_UNIT));
		sprintf_s(tmp, 30, " (%s)", KEYCODE::getStr(UnitPanelHotkey));
		PullDownItemNames[2]+=tmp;

		PullDownItemNames[3].assign(StringManager::GetString(STR::PANEL_HERO));
		sprintf_s(tmp, 30, " (%s)", KEYCODE::getStr(HeroPanelHotkey));
		PullDownItemNames[3]+=tmp;

		PullDownItemNames[4].assign(StringManager::GetString(STR::PANEL_APM));
		sprintf_s(tmp, 30, " (%s)", KEYCODE::getStr(APMPanelHotkey));
		PullDownItemNames[4]+=tmp;

		PullDownItemNames[5].assign(StringManager::GetString(STR::PANEL_DOTA));
		sprintf_s(tmp, 30, " (%s)", KEYCODE::getStr(DotaPanelHotkey));
		PullDownItemNames[5]+=tmp;

		PullDownItemNames[6].assign(StringManager::GetString(STR::PANEL_PRODUCTION));
		sprintf_s(tmp, 30, " (%s)", KEYCODE::getStr(ProductionPanelHotkey));
		PullDownItemNames[6]+=tmp;

		PullDownItemNames[7].assign(StringManager::GetString(STR::PANEL_ARMY));
		sprintf_s(tmp, 30, " (%s)", KEYCODE::getStr(ArmyPanelHotkey));
		PullDownItemNames[7]+=tmp;

		PullDownItemNames[8].assign(StringManager::GetString(STR::PANEL_RADAR));
		sprintf_s(tmp, 30, " (%s)", KEYCODE::getStr(RadarPanelHotkey));
		PullDownItemNames[8]+=tmp;

		for (uint32_t i = 0; i < PullDownItemTotal; i++)
		{
			PullDown->setText(i, "%s", PullDownItemNames[i].c_str());
		}
	}

	void PanelChangeHotkey ( Button *btn )
	{
		InitNames();
	}

	void InitOnGameStart(Timer *tm)
	{
		VMProtectBeginVirtualization("InformationPanel");

		GetTimer(2, DetectHeroButtonExists, true)->startImmediate();

		frameLevelDropDown = UISimpleFrame::Create(UISimpleFrame::GetGameSimpleConsole());

		//下拉框
		PullDown = new InfoPanel::PullDown(frameLevelDropDown, 0.1f, 0.013f, PullDownItemTotal, PdCallback);
		InitNames();

		PullDown->setAbsolutePosition(UILayoutFrame::POSITION_BOTTOM_LEFT, PANEL_POS_X, PANEL_POS_Y);
		PullDown->setIndex(0);
		PullDown->show(Enabled);

		//计算玩家
		GetTimer(0.5, RefreshPlayer, true)->startImmediate();

		//资源面板
		DropDownPanels[1] = ResourcePanel = new Table( );
		//ResourcePanel->setParent(UISimpleFrame::GetGameSimpleConsole());
		ResourcePanel->setRowColumnCount(0, 4);
		ResourcePanel->setColumnMinWidth(1, 0.05f);
		ResourcePanel->setColumnMinWidth(2, 0.05f);
		ResourcePanel->setColumnMinWidth(3, 0.05f);
		ResourcePanel->setTitle(1, new Texture(UI_NULL, 0.015f, 0.015f, 
			Skin::getPathByName("GoldIcon")
		));
		ResourcePanel->setTitle(2, new Texture(UI_NULL, 0.015f, 0.015f, 
			Skin::getPathByName("LumberIcon")
		));
		ResourcePanel->setTitle(3, new Texture(UI_NULL, 0.015f, 0.015f, 
			Skin::getPathByName("SupplyIcon")
		));
		ResourcePanel->setAbsolutePosition( POS_UL, PANEL_POS_X, PANEL_POS_Y );
		ResourcePanel->show(false);
		GetTimer(0.5, RefreshResource, true)->startImmediate();

		//单位面板
 		DropDownPanels[2] = UnitPanel = new Table(NULL, 0, 2, false, 0, true);
 		//UnitPanel->setParent(UISimpleFrame::GetGameSimpleConsole());
 		UnitPanel->setAbsolutePosition( POS_UL, PANEL_POS_X, PANEL_POS_Y );
		UnitPanel->setColumnMinWidth(0, 0.034f);
		UnitPanel->setElementPadding(0.005f, 0);
 		UnitPanel->show(false);
 		GetTimer(0.5, RefreshUnits, true)->startImmediate();

		//英雄面板
		DropDownPanels[3] = HeroPanel = new Table( NULL, 1, 1, false, 0, true );
		//HeroPanel->setParent(UISimpleFrame::GetGameSimpleConsole());
		HeroPanel->setRowColumnCount(0, 
			1 + HERO_PANEL_ABILITY_COUNT_MAX + 1 + 6);
		HeroPanel->setColumnMinWidth(0, 0.035f);
		HeroPanel->setColumnMinWidth(1 + HERO_PANEL_ABILITY_COUNT_MAX, 0.01f);//隔开技能和物品的最小间隔
		HeroPanel->setAbsolutePosition( POS_UL, PANEL_POS_X, PANEL_POS_Y );
		HeroPanel->setElementPadding(0.005f, 0);
		HeroPanel->show(false);
		GetTimer(0.5, RefreshHero, true)->startImmediate();

		//APM面板
		DropDownPanels[4] = APMPanel = new Table( );
		APMPanel->setRowColumnCount(0, 3);
		APMPanel->setColumnMinWidth(0, 0.034f);
		APMPanel->setTitle(1, new Label(UI_NULL, StringManager::GetString(STR::PANEL_APM_CURRENT), 0.011f));
		APMPanel->setTitle(2, new Label(UI_NULL, StringManager::GetString(STR::PANEL_APM_AVERAGE), 0.011f));
		APMPanel->setAbsolutePosition( POS_UL, PANEL_POS_X, PANEL_POS_Y );
		APMPanel->setElementPadding(0.005f, 0);
		APMPanel->show(false);
		GetTimer(0.5, RefreshAPM, true)->startImmediate();
		GetTimer(2.0, RefreshAPMAverage, true)->startImmediate();

		//Dota面板
		DropDownPanels[5] = DotaPanel = new Table( );
		//DotaPanel->setParent(UISimpleFrame::GetGameSimpleConsole());
		DotaPanel->setRowColumnCount(0, 1 + DOTA_PANEL_ABILITY_COUNT_MAX + 1 + 6 + 1 + 1 + 1);
		DotaPanel->setColumnMinWidth(0, 0.035f);
		DotaPanel->setColumnMinWidth(1 + DOTA_PANEL_ABILITY_COUNT_MAX, 0.01f);//隔开技能和物品的最小间隔
		DotaPanel->setColumnMinWidth(1 + DOTA_PANEL_ABILITY_COUNT_MAX + 1 + 6, 0.01f);//隔开物品和金钱的最小间隔
		DotaPanel->setColumnMinWidth(1 + DOTA_PANEL_ABILITY_COUNT_MAX + 1 + 6 + 1, 0.03f);//金钱标签
		DotaPanel->setTitle(1 + DOTA_PANEL_ABILITY_COUNT_MAX + 1 + 6 + 1, new Texture(UI_NULL, 0.015f, 0.015f,
			Skin::getPathByName("GoldIcon")
		));

		DotaPanel->setColumnMinWidth(1 + DOTA_PANEL_ABILITY_COUNT_MAX + 1 + 6 + 1 + 1, 0.03f);//补刀
		DotaPanel->setTitle(1 + DOTA_PANEL_ABILITY_COUNT_MAX + 1 + 6 + 1 + 1, new Label(UI_NULL, StringManager::GetString(STR::PANEL_DOTA_CREEP), 0.011f));

		DotaPanel->setAbsolutePosition( POS_UL, PANEL_POS_X, PANEL_POS_Y );
		DotaPanel->setElementPadding(0.005f, 0);
		
		DotaPanel->show(false);
		
		GetTimer(0.5, RefreshDota, true)->startImmediate();

		//生产面板
		DropDownPanels[6] = ProductionPanel = new Table ( NULL, 0, 2, false, 0, true );
		ProductionPanel->setAbsolutePosition( POS_UL, PANEL_POS_X, PANEL_POS_Y );
		ProductionPanel->setColumnMinWidth(0, 0.034f);
		ProductionPanel->setElementPadding(0.005f, 0);
		ProductionPanel->show(false);
		GetTimer(0.5, RefreshProduction, true)->startImmediate();

		//军队面板
		DropDownPanels[7] = ArmyPanel = new Table ( );
		ArmyPanel->setRowColumnCount(0, 4);
		ArmyPanel->setColumnMinWidth(0, 0.034f);
		//ArmyPanel->setColumnMinWidth(1, 0.05f);
		//ArmyPanel->setColumnMinWidth(2, 0.05f);
		//ArmyPanel->setColumnMinWidth(3, 0.05f);
		ArmyPanel->setTitle(1, new Texture(UI_NULL, 0.015f, 0.015f, 	Skin::getPathByName("GoldIcon")));
		ArmyPanel->setTitle(2, new Texture(UI_NULL, 0.015f, 0.015f, 	Skin::getPathByName("LumberIcon")));
		ArmyPanel->setTitle(3, new Texture(UI_NULL, 0.015f, 0.015f, 	Skin::getPathByName("SupplyIcon")));
		ArmyPanel->setAbsolutePosition( POS_UL, PANEL_POS_X, PANEL_POS_Y );
		ArmyPanel->setElementPadding(0.005f, 0);
		ArmyPanel->show(false);
		GetTimer(1, RefreshArmy, true)->startImmediate();

		//小地图面板
		DropDownPanels[8] = RadarPanel = new MinimapRadar();
		RadarPanel->show(false);
		GetTimer(0.2, RefreshRadar, true)->startImmediate();

		VMProtectEnd();
	}

	void onKeyDown(const Event *evt){
		if (!PullDown) return;
		if (!Enabled) return;
		KeyboardEventData *data = evt->data<KeyboardEventData>();

		bool bModifierAllow = false;

		if (	data->code == ResourcePanelHotkey )
		{
			bModifierAllow = bIsReplayOrObs ? true : 
			(	(data->ctrl == ResourcePanelHotkeyCtrl)
			&&	(data->alt == ResourcePanelHotkeyAlt)
			&&	(data->shift == ResourcePanelHotkeyShift)
			);
			if (bModifierAllow)
			{
				data->discard();
				PullDown->toggleIndex(1);
			}
		}

		if (	data->code == UnitPanelHotkey )
		{
			bModifierAllow = bIsReplayOrObs ? true : 
			(	(data->ctrl == UnitPanelHotkeyCtrl)
			&&	(data->alt == UnitPanelHotkeyAlt)
			&&	(data->shift == UnitPanelHotkeyShift)
			);
			if (bModifierAllow)
			{
				data->discard();
				PullDown->toggleIndex(2);
			}
		}

		if (	data->code == HeroPanelHotkey )
		{
			bModifierAllow = bIsReplayOrObs ? true : 
			(	(data->ctrl == HeroPanelHotkeyCtrl)
			&&	(data->alt == HeroPanelHotkeyAlt)
			&&	(data->shift == HeroPanelHotkeyShift)
			);
			if(bModifierAllow)
			{
				data->discard();
				PullDown->toggleIndex(3);
			}
		}

		if (	data->code == APMPanelHotkey )
		{
			bModifierAllow = bIsReplayOrObs ? true : 
				(	(data->ctrl == APMPanelHotkeyCtrl)
				&&	(data->alt == APMPanelHotkeyAlt)
				&&	(data->shift == APMPanelHotkeyShift)
				);
			if(bModifierAllow)
			{
				data->discard();
				PullDown->toggleIndex(4);
			}
		}

		if (	data->code == DotaPanelHotkey )
		{
			bModifierAllow = bIsReplayOrObs ? true : 
				(	(data->ctrl == DotaPanelHotkeyCtrl)
				&&	(data->alt == DotaPanelHotkeyAlt)
				&&	(data->shift == DotaPanelHotkeyShift)
				);
		if(bModifierAllow)
		{
			data->discard();
			PullDown->toggleIndex(5);
		}
		}

		if (	data->code == ProductionPanelHotkey )
		{
			bModifierAllow = bIsReplayOrObs ? true : 
				(	(data->ctrl == ProductionPanelHotkeyCtrl)
				&&	(data->alt == ProductionPanelHotkeyAlt)
				&&	(data->shift == ProductionPanelHotkeyShift)
				);
			if(bModifierAllow)
			{
				data->discard();
				PullDown->toggleIndex(6);
			}
		}

		if (	data->code == ArmyPanelHotkey )
		{
			bModifierAllow = bIsReplayOrObs ? true : 
				(	(data->ctrl == ArmyPanelHotkeyCtrl)
				&&	(data->alt == ArmyPanelHotkeyAlt)
				&&	(data->shift == ArmyPanelHotkeyShift)
				);
			if(bModifierAllow)
			{
				data->discard();
				PullDown->toggleIndex(7);
			}
		}

		if (	data->code == RadarPanelHotkey )
		{
			bModifierAllow = bIsReplayOrObs ? true : 
				(	(data->ctrl == RadarPanelHotkeyCtrl)
				&&	(data->alt == RadarPanelHotkeyAlt)
				&&	(data->shift == RadarPanelHotkeyShift)
				);
			if(bModifierAllow)
			{
				data->discard();
				PullDown->toggleIndex(8);
			}
		}

		
	}

	void InfoPanelEnable(CheckBox *cb, bool flag)
	{
		if (PullDown)
		{
			PullDown->show(flag);
			if (!flag)
			{
				PullDown->toggleIndex(0);
			}
		}
	}

	static CheckBox *CbEnabled;
	static Label *LbEnabled;

	static Label		*LbResourcePanelHotkey;
	static HotkeyButton	*BtnResourcePanelHotkey;
	static CheckBox		*CbResourcePanelHotkeyCtrl;
	static Label		*LbResourcePanelHotkeyCtrl;
	static CheckBox		*CbResourcePanelHotkeyAlt;
	static Label		*LbResourcePanelHotkeyAlt;
	static CheckBox		*CbResourcePanelHotkeyShift;
	static Label		*LbResourcePanelHotkeyShift;

	static Label		*LbUnitPanelHotkey;
	static HotkeyButton	*BtnUnitPanelHotkey;
	static CheckBox		*CbUnitPanelHotkeyCtrl;
	static Label		*LbUnitPanelHotkeyCtrl;
	static CheckBox		*CbUnitPanelHotkeyAlt;
	static Label		*LbUnitPanelHotkeyAlt;
	static CheckBox		*CbUnitPanelHotkeyShift;
	static Label		*LbUnitPanelHotkeyShift;

	static Label		*LbHeroPanelHotkey;
	static HotkeyButton	*BtnHeroPanelHotkey;
	static CheckBox		*CbHeroPanelHotkeyCtrl;
	static Label		*LbHeroPanelHotkeyCtrl;
	static CheckBox		*CbHeroPanelHotkeyAlt;
	static Label		*LbHeroPanelHotkeyAlt;
	static CheckBox		*CbHeroPanelHotkeyShift;
	static Label		*LbHeroPanelHotkeyShift;

	static Label		*LbAPMPanelHotkey;
	static HotkeyButton	*BtnAPMPanelHotkey;
	static CheckBox		*CbAPMPanelHotkeyCtrl;
	static Label		*LbAPMPanelHotkeyCtrl;
	static CheckBox		*CbAPMPanelHotkeyAlt;
	static Label		*LbAPMPanelHotkeyAlt;
	static CheckBox		*CbAPMPanelHotkeyShift;
	static Label		*LbAPMPanelHotkeyShift;

	static Label		*LbProductionPanelHotkey;
	static HotkeyButton	*BtnProductionPanelHotkey;
	static CheckBox		*CbProductionPanelHotkeyCtrl;
	static Label		*LbProductionPanelHotkeyCtrl;
	static CheckBox		*CbProductionPanelHotkeyAlt;
	static Label		*LbProductionPanelHotkeyAlt;
	static CheckBox		*CbProductionPanelHotkeyShift;
	static Label		*LbProductionPanelHotkeyShift;

	static Label		*LbArmyPanelHotkey;
	static HotkeyButton	*BtnArmyPanelHotkey;
	static CheckBox		*CbArmyPanelHotkeyCtrl;
	static Label		*LbArmyPanelHotkeyCtrl;
	static CheckBox		*CbArmyPanelHotkeyAlt;
	static Label		*LbArmyPanelHotkeyAlt;
	static CheckBox		*CbArmyPanelHotkeyShift;
	static Label		*LbArmyPanelHotkeyShift;

	static Label		*LbDotaPanelHotkey;
	static HotkeyButton	*BtnDotaPanelHotkey;
	static CheckBox		*CbDotaPanelHotkeyCtrl;
	static Label		*LbDotaPanelHotkeyCtrl;
	static CheckBox		*CbDotaPanelHotkeyAlt;
	static Label		*LbDotaPanelHotkeyAlt;
	static CheckBox		*CbDotaPanelHotkeyShift;
	static Label		*LbDotaPanelHotkeyShift;

	static Label		*LbRadarPanelHotkey;
	static HotkeyButton	*BtnRadarPanelHotkey;
	static CheckBox		*CbRadarPanelHotkeyCtrl;
	static Label		*LbRadarPanelHotkeyCtrl;
	static CheckBox		*CbRadarPanelHotkeyAlt;
	static Label		*LbRadarPanelHotkeyAlt;
	static CheckBox		*CbRadarPanelHotkeyShift;
	static Label		*LbRadarPanelHotkeyShift;

	void CreateMenuContent(){
		VMProtectBeginVirtualization("InformationPanelMenuContent");

		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::INFOPANEL), NULL);
		CbEnabled = new CheckBox(Panel, 0.024f, InfoPanelEnable, &Enabled, "InfoPanel", "Enable", true);
		CbEnabled->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.03f);
		LbEnabled = new Label(Panel, StringManager::GetString(STR::INFOPANEL_ENABLE), 0.013f);
		LbEnabled->setRelativePosition(POS_L, CbEnabled, POS_R, 0.01f, 0);

		//资源面板热键
		LbResourcePanelHotkey = new Label(Panel, StringManager::GetString(STR::PANEL_RESOURCE), 0.013f);
		LbResourcePanelHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.060f);
		BtnResourcePanelHotkey = new HotkeyButton(Panel, 0.09f, 0.03f, 
			&ResourcePanelHotkey, KEYCODE::KEY_R, "InfoPanel", "HotkeyResourceKey",
			PanelChangeHotkey );
		BtnResourcePanelHotkey->setRelativePosition(
			POS_L, LbResourcePanelHotkey->getFrame(), POS_L, 0.15f, 0);
		//Ctrl
		CbResourcePanelHotkeyCtrl = new CheckBox(Panel, 0.020f, NULL, &ResourcePanelHotkeyCtrl, 
			"InfoPanel", "HotkeyResourceCtrl", true);
		CbResourcePanelHotkeyCtrl->setRelativePosition(POS_L, BtnResourcePanelHotkey->getFrame(), POS_R, 0.01f, 0);
		LbResourcePanelHotkeyCtrl = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_CONTROL), 0.011f);
		LbResourcePanelHotkeyCtrl->setRelativePosition(POS_L, CbResourcePanelHotkeyCtrl->getFrame(), POS_R, 0.003f, 0);
		//Alt
		CbResourcePanelHotkeyAlt = new CheckBox(Panel, 0.020f, NULL, &ResourcePanelHotkeyAlt, 
			"InfoPanel", "HotkeyResourceAlt", true);
		CbResourcePanelHotkeyAlt->setRelativePosition(POS_L, BtnResourcePanelHotkey->getFrame(), POS_R, 0.06f, 0);
		LbResourcePanelHotkeyAlt = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_ALT), 0.011f);
		LbResourcePanelHotkeyAlt->setRelativePosition(POS_L, CbResourcePanelHotkeyAlt->getFrame(), POS_R, 0.003f, 0);
		//Shift
		CbResourcePanelHotkeyShift = new CheckBox(Panel, 0.020f, NULL, &ResourcePanelHotkeyShift, 
			"InfoPanel", "HotkeyResourceShift", false);
		CbResourcePanelHotkeyShift->setRelativePosition(POS_L, BtnResourcePanelHotkey->getFrame(), POS_R, 0.11f, 0);
		LbResourcePanelHotkeyShift = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_SHIFT), 0.011f);
		LbResourcePanelHotkeyShift->setRelativePosition(POS_L, CbResourcePanelHotkeyShift->getFrame(), POS_R, 0.003f, 0);

		//单位面板热键
		LbUnitPanelHotkey = new Label(Panel, StringManager::GetString(STR::PANEL_UNIT), 0.013f);
		LbUnitPanelHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.087f);
		BtnUnitPanelHotkey = new HotkeyButton(Panel, 0.09f, 0.03f, 
			&UnitPanelHotkey, KEYCODE::KEY_U, "InfoPanel", "HotkeyUnitKey",
			PanelChangeHotkey );
		BtnUnitPanelHotkey->setRelativePosition(
			POS_L, LbUnitPanelHotkey->getFrame(), POS_L, 0.15f, 0);
		//Ctrl
		CbUnitPanelHotkeyCtrl = new CheckBox(Panel, 0.020f, NULL, &UnitPanelHotkeyCtrl, 
			"InfoPanel", "HotkeyUnitCtrl", true);
		CbUnitPanelHotkeyCtrl->setRelativePosition(POS_L, BtnUnitPanelHotkey->getFrame(), POS_R, 0.01f, 0);
		LbUnitPanelHotkeyCtrl = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_CONTROL), 0.011f);
		LbUnitPanelHotkeyCtrl->setRelativePosition(POS_L, CbUnitPanelHotkeyCtrl->getFrame(), POS_R, 0.003f, 0);
		//Alt
		CbUnitPanelHotkeyAlt = new CheckBox(Panel, 0.020f, NULL, &UnitPanelHotkeyAlt, 
			"InfoPanel", "HotkeyUnitAlt", true);
		CbUnitPanelHotkeyAlt->setRelativePosition(POS_L, BtnUnitPanelHotkey->getFrame(), POS_R, 0.06f, 0);
		LbUnitPanelHotkeyAlt = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_ALT), 0.011f);
		LbUnitPanelHotkeyAlt->setRelativePosition(POS_L, CbUnitPanelHotkeyAlt->getFrame(), POS_R, 0.003f, 0);
		//Shift
		CbUnitPanelHotkeyShift = new CheckBox(Panel, 0.020f, NULL, &UnitPanelHotkeyShift, 
			"InfoPanel", "HotkeyUnitShift", false);
		CbUnitPanelHotkeyShift->setRelativePosition(POS_L, BtnUnitPanelHotkey->getFrame(), POS_R, 0.11f, 0);
		LbUnitPanelHotkeyShift = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_SHIFT), 0.011f);
		LbUnitPanelHotkeyShift->setRelativePosition(POS_L, CbUnitPanelHotkeyShift->getFrame(), POS_R, 0.003f, 0);

		//英雄面板热键
		LbHeroPanelHotkey = new Label(Panel, StringManager::GetString(STR::PANEL_HERO), 0.013f);
		LbHeroPanelHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.114f);
		BtnHeroPanelHotkey = new HotkeyButton(Panel, 0.09f, 0.03f, 
			&HeroPanelHotkey, KEYCODE::KEY_H, "InfoPanel", "HotkeyHeroKey",
			PanelChangeHotkey );
		BtnHeroPanelHotkey->setRelativePosition(
			POS_L, LbHeroPanelHotkey->getFrame(), POS_L, 0.15f, 0);
		//Ctrl
		CbHeroPanelHotkeyCtrl = new CheckBox(Panel, 0.020f, NULL, &HeroPanelHotkeyCtrl, 
			"InfoPanel", "HotkeyHeroCtrl", true);
		CbHeroPanelHotkeyCtrl->setRelativePosition(POS_L, BtnHeroPanelHotkey->getFrame(), POS_R, 0.01f, 0);
		LbHeroPanelHotkeyCtrl = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_CONTROL), 0.011f);
		LbHeroPanelHotkeyCtrl->setRelativePosition(POS_L, CbHeroPanelHotkeyCtrl->getFrame(), POS_R, 0.003f, 0);
		//Alt
		CbHeroPanelHotkeyAlt = new CheckBox(Panel, 0.020f, NULL, &HeroPanelHotkeyAlt, 
			"InfoPanel", "HotkeyHeroAlt", true);
		CbHeroPanelHotkeyAlt->setRelativePosition(POS_L, BtnHeroPanelHotkey->getFrame(), POS_R, 0.06f, 0);
		LbHeroPanelHotkeyAlt = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_ALT), 0.011f);
		LbHeroPanelHotkeyAlt->setRelativePosition(POS_L, CbHeroPanelHotkeyAlt->getFrame(), POS_R, 0.003f, 0);
		//Shift
		CbHeroPanelHotkeyShift = new CheckBox(Panel, 0.020f, NULL, &HeroPanelHotkeyShift, 
			"InfoPanel", "HotkeyHeroShift", false);
		CbHeroPanelHotkeyShift->setRelativePosition(POS_L, BtnHeroPanelHotkey->getFrame(), POS_R, 0.11f, 0);
		LbHeroPanelHotkeyShift = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_SHIFT), 0.011f);
		LbHeroPanelHotkeyShift->setRelativePosition(POS_L, CbHeroPanelHotkeyShift->getFrame(), POS_R, 0.003f, 0);

		//APM面板热键
		LbAPMPanelHotkey = new Label(Panel, StringManager::GetString(STR::PANEL_APM), 0.013f);
		LbAPMPanelHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.141f);
		BtnAPMPanelHotkey = new HotkeyButton(Panel, 0.09f, 0.03f, 
			&APMPanelHotkey, KEYCODE::KEY_M, "InfoPanel", "HotkeyAPMKey",
			PanelChangeHotkey );
		BtnAPMPanelHotkey->setRelativePosition(
			POS_L, LbAPMPanelHotkey->getFrame(), POS_L, 0.15f, 0);
		//Ctrl
		CbAPMPanelHotkeyCtrl = new CheckBox(Panel, 0.020f, NULL, &APMPanelHotkeyCtrl, 
			"InfoPanel", "HotkeyAPMCtrl", true);
		CbAPMPanelHotkeyCtrl->setRelativePosition(POS_L, BtnAPMPanelHotkey->getFrame(), POS_R, 0.01f, 0);
		LbAPMPanelHotkeyCtrl = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_CONTROL), 0.011f);
		LbAPMPanelHotkeyCtrl->setRelativePosition(POS_L, CbAPMPanelHotkeyCtrl->getFrame(), POS_R, 0.003f, 0);
		//Alt
		CbAPMPanelHotkeyAlt = new CheckBox(Panel, 0.020f, NULL, &APMPanelHotkeyAlt, 
			"InfoPanel", "HotkeyAPMAlt", true);
		CbAPMPanelHotkeyAlt->setRelativePosition(POS_L, BtnAPMPanelHotkey->getFrame(), POS_R, 0.06f, 0);
		LbAPMPanelHotkeyAlt = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_ALT), 0.011f);
		LbAPMPanelHotkeyAlt->setRelativePosition(POS_L, CbAPMPanelHotkeyAlt->getFrame(), POS_R, 0.003f, 0);
		//Shift
		CbAPMPanelHotkeyShift = new CheckBox(Panel, 0.020f, NULL, &APMPanelHotkeyShift, 
			"InfoPanel", "HotkeyAPMShift", false);
		CbAPMPanelHotkeyShift->setRelativePosition(POS_L, BtnAPMPanelHotkey->getFrame(), POS_R, 0.11f, 0);
		LbAPMPanelHotkeyShift = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_SHIFT), 0.011f);
		LbAPMPanelHotkeyShift->setRelativePosition(POS_L, CbAPMPanelHotkeyShift->getFrame(), POS_R, 0.003f, 0);

		//生产面板热键
		LbProductionPanelHotkey = new Label(Panel, StringManager::GetString(STR::PANEL_PRODUCTION), 0.013f);
		LbProductionPanelHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.168f);
		BtnProductionPanelHotkey = new HotkeyButton(Panel, 0.09f, 0.03f, 
			&ProductionPanelHotkey, KEYCODE::KEY_P, "InfoPanel", "HotkeyProductionKey",
			PanelChangeHotkey );
		BtnProductionPanelHotkey->setRelativePosition(
			POS_L, LbProductionPanelHotkey->getFrame(), POS_L, 0.15f, 0);
		//Ctrl
		CbProductionPanelHotkeyCtrl = new CheckBox(Panel, 0.020f, NULL, &ProductionPanelHotkeyCtrl, 
			"InfoPanel", "HotkeyProductionCtrl", true);
		CbProductionPanelHotkeyCtrl->setRelativePosition(POS_L, BtnProductionPanelHotkey->getFrame(), POS_R, 0.01f, 0);
		LbProductionPanelHotkeyCtrl = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_CONTROL), 0.011f);
		LbProductionPanelHotkeyCtrl->setRelativePosition(POS_L, CbProductionPanelHotkeyCtrl->getFrame(), POS_R, 0.003f, 0);
		//Alt
		CbProductionPanelHotkeyAlt = new CheckBox(Panel, 0.020f, NULL, &ProductionPanelHotkeyAlt, 
			"InfoPanel", "HotkeyProductionAlt", true);
		CbProductionPanelHotkeyAlt->setRelativePosition(POS_L, BtnProductionPanelHotkey->getFrame(), POS_R, 0.06f, 0);
		LbProductionPanelHotkeyAlt = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_ALT), 0.011f);
		LbProductionPanelHotkeyAlt->setRelativePosition(POS_L, CbProductionPanelHotkeyAlt->getFrame(), POS_R, 0.003f, 0);
		//Shift
		CbProductionPanelHotkeyShift = new CheckBox(Panel, 0.020f, NULL, &ProductionPanelHotkeyShift, 
			"InfoPanel", "HotkeyProductionShift", false);
		CbProductionPanelHotkeyShift->setRelativePosition(POS_L, BtnProductionPanelHotkey->getFrame(), POS_R, 0.11f, 0);
		LbProductionPanelHotkeyShift = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_SHIFT), 0.011f);
		LbProductionPanelHotkeyShift->setRelativePosition(POS_L, CbProductionPanelHotkeyShift->getFrame(), POS_R, 0.003f, 0);

		//军队面板热键
		LbArmyPanelHotkey = new Label(Panel, StringManager::GetString(STR::PANEL_ARMY), 0.013f);
		LbArmyPanelHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.195f);
		BtnArmyPanelHotkey = new HotkeyButton(Panel, 0.09f, 0.03f, 
			&ArmyPanelHotkey, KEYCODE::KEY_A, "InfoPanel", "HotkeyArmyKey",
			PanelChangeHotkey );
		BtnArmyPanelHotkey->setRelativePosition(
			POS_L, LbArmyPanelHotkey->getFrame(), POS_L, 0.15f, 0);
		//Ctrl
		CbArmyPanelHotkeyCtrl = new CheckBox(Panel, 0.020f, NULL, &ArmyPanelHotkeyCtrl, 
			"InfoPanel", "HotkeyArmyCtrl", true);
		CbArmyPanelHotkeyCtrl->setRelativePosition(POS_L, BtnArmyPanelHotkey->getFrame(), POS_R, 0.01f, 0);
		LbArmyPanelHotkeyCtrl = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_CONTROL), 0.011f);
		LbArmyPanelHotkeyCtrl->setRelativePosition(POS_L, CbArmyPanelHotkeyCtrl->getFrame(), POS_R, 0.003f, 0);
		//Alt
		CbArmyPanelHotkeyAlt = new CheckBox(Panel, 0.020f, NULL, &ArmyPanelHotkeyAlt, 
			"InfoPanel", "HotkeyArmyAlt", true);
		CbArmyPanelHotkeyAlt->setRelativePosition(POS_L, BtnArmyPanelHotkey->getFrame(), POS_R, 0.06f, 0);
		LbArmyPanelHotkeyAlt = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_ALT), 0.011f);
		LbArmyPanelHotkeyAlt->setRelativePosition(POS_L, CbArmyPanelHotkeyAlt->getFrame(), POS_R, 0.003f, 0);
		//Shift
		CbArmyPanelHotkeyShift = new CheckBox(Panel, 0.020f, NULL, &ArmyPanelHotkeyShift, 
			"InfoPanel", "HotkeyArmyShift", false);
		CbArmyPanelHotkeyShift->setRelativePosition(POS_L, BtnArmyPanelHotkey->getFrame(), POS_R, 0.11f, 0);
		LbArmyPanelHotkeyShift = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_SHIFT), 0.011f);
		LbArmyPanelHotkeyShift->setRelativePosition(POS_L, CbArmyPanelHotkeyShift->getFrame(), POS_R, 0.003f, 0);

		//Dota面板热键
		LbDotaPanelHotkey = new Label(Panel, StringManager::GetString(STR::PANEL_DOTA), 0.013f);
		LbDotaPanelHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.222f);
		BtnDotaPanelHotkey = new HotkeyButton(Panel, 0.09f, 0.03f, 
			&DotaPanelHotkey, KEYCODE::KEY_D, "InfoPanel", "HotkeyDotaKey",
			PanelChangeHotkey );
		BtnDotaPanelHotkey->setRelativePosition(
			POS_L, LbDotaPanelHotkey->getFrame(), POS_L, 0.15f, 0);
		//Ctrl
		CbDotaPanelHotkeyCtrl = new CheckBox(Panel, 0.020f, NULL, &DotaPanelHotkeyCtrl, 
			"InfoPanel", "HotkeyDotaCtrl", true);
		CbDotaPanelHotkeyCtrl->setRelativePosition(POS_L, BtnDotaPanelHotkey->getFrame(), POS_R, 0.01f, 0);
		LbDotaPanelHotkeyCtrl = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_CONTROL), 0.011f);
		LbDotaPanelHotkeyCtrl->setRelativePosition(POS_L, CbDotaPanelHotkeyCtrl->getFrame(), POS_R, 0.003f, 0);
		//Alt
		CbDotaPanelHotkeyAlt = new CheckBox(Panel, 0.020f, NULL, &DotaPanelHotkeyAlt, 
			"InfoPanel", "HotkeyDotaAlt", true);
		CbDotaPanelHotkeyAlt->setRelativePosition(POS_L, BtnDotaPanelHotkey->getFrame(), POS_R, 0.06f, 0);
		LbDotaPanelHotkeyAlt = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_ALT), 0.011f);
		LbDotaPanelHotkeyAlt->setRelativePosition(POS_L, CbDotaPanelHotkeyAlt->getFrame(), POS_R, 0.003f, 0);
		//Shift
		CbDotaPanelHotkeyShift = new CheckBox(Panel, 0.020f, NULL, &DotaPanelHotkeyShift, 
			"InfoPanel", "HotkeyDotaShift", false);
		CbDotaPanelHotkeyShift->setRelativePosition(POS_L, BtnDotaPanelHotkey->getFrame(), POS_R, 0.11f, 0);
		LbDotaPanelHotkeyShift = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_SHIFT), 0.011f);
		LbDotaPanelHotkeyShift->setRelativePosition(POS_L, CbDotaPanelHotkeyShift->getFrame(), POS_R, 0.003f, 0);

		//雷达面板热键
		LbRadarPanelHotkey = new Label(Panel, StringManager::GetString(STR::PANEL_RADAR), 0.013f);
		LbRadarPanelHotkey->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.249f);
		BtnRadarPanelHotkey = new HotkeyButton(Panel, 0.09f, 0.03f, 
			&RadarPanelHotkey, KEYCODE::KEY_TAB, "InfoPanel", "HotkeyRadarKey",
			PanelChangeHotkey );
		BtnRadarPanelHotkey->setRelativePosition(
			POS_L, LbRadarPanelHotkey->getFrame(), POS_L, 0.15f, 0);
		//Ctrl
		CbRadarPanelHotkeyCtrl = new CheckBox(Panel, 0.020f, NULL, &RadarPanelHotkeyCtrl, 
			"InfoPanel", "HotkeyRadarCtrl", false);
		CbRadarPanelHotkeyCtrl->setRelativePosition(POS_L, BtnRadarPanelHotkey->getFrame(), POS_R, 0.01f, 0);
		LbRadarPanelHotkeyCtrl = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_CONTROL), 0.011f);
		LbRadarPanelHotkeyCtrl->setRelativePosition(POS_L, CbRadarPanelHotkeyCtrl->getFrame(), POS_R, 0.003f, 0);
		//Alt
		CbRadarPanelHotkeyAlt = new CheckBox(Panel, 0.020f, NULL, &RadarPanelHotkeyAlt, 
			"InfoPanel", "HotkeyRadarAlt", false);
		CbRadarPanelHotkeyAlt->setRelativePosition(POS_L, BtnRadarPanelHotkey->getFrame(), POS_R, 0.06f, 0);
		LbRadarPanelHotkeyAlt = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_ALT), 0.011f);
		LbRadarPanelHotkeyAlt->setRelativePosition(POS_L, CbRadarPanelHotkeyAlt->getFrame(), POS_R, 0.003f, 0);
		//Shift
		CbRadarPanelHotkeyShift = new CheckBox(Panel, 0.020f, NULL, &RadarPanelHotkeyShift, 
			"InfoPanel", "HotkeyRadarShift", false);
		CbRadarPanelHotkeyShift->setRelativePosition(POS_L, BtnRadarPanelHotkey->getFrame(), POS_R, 0.11f, 0);
		LbRadarPanelHotkeyShift = new Label(Panel, KEYCODE::getStr(KEYCODE::KEY_SHIFT), 0.011f);
		LbRadarPanelHotkeyShift->setRelativePosition(POS_L, CbRadarPanelHotkeyShift->getFrame(), POS_R, 0.003f, 0);

		VMProtectEnd();
	}

	void Init()
	{
		CreateMenuContent();
		MainDispatcher()->listen(Jass::EVENT_PLAYER_UNIT_DEATH, CalcLastHitScore);
		MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);
		bIsReplayOrObs = 
			ReplayState() == REPLAY_STATE_STREAMINGOUT
			|| Jass::IsPlayerObserver(Jass::Player(PlayerLocal()));

		PanelPlayerTeamStr.assign( StringManager::GetString(STR::PANEL_TEAM) );
		InitOnGameStart(NULL);
	}

	void Cleanup()
	{
		for (uint32_t i = 0; i < PullDownItemTotal; i++){
			if (DropDownPanels[i]) {delete DropDownPanels[i]; DropDownPanels[i] = NULL;}
		}
		
		ResourcePanel = NULL;

		if (UnitPanelUnits) GroupDestroy(UnitPanelUnits);
		UnitPanelUnits = NULL;
		for (int i = 0; i < 16; i++)
		{
			if (UnitPanelPlayerUnits[i])
			{
				GroupDestroy(UnitPanelPlayerUnits[i]);
				UnitPanelPlayerUnits[i] = NULL;
			}
		}
		UnitPanel = NULL;

		if (HeroPanelHeroes) 
		{
			GroupDestroy(HeroPanelHeroes);
			HeroPanelHeroes = NULL;
		}
		HeroPanel = NULL;

		APMPanel = NULL;

		for (uint32_t i = 0; i < 16; i++)
		{
			DotaPanelLastHitCount[i] = 0;
			DotaPanelDenyCount[i] = 0;
		}
		DotaPanel = NULL;

		if (ProductionPanelUnits) GroupDestroy(ProductionPanelUnits);
		ProductionPanelUnits = NULL;
		for (int i = 0; i < 16; i++)
		{
			if (ProductionPanelPlayerUnits[i])
			{
				GroupDestroy(ProductionPanelPlayerUnits[i]);
				ProductionPanelPlayerUnits[i] = NULL;
			}
		}
		ProductionPanel = NULL;

		ArmyMap.clear();
		ArmyPanel = NULL;
		
		if (frameLevelDropDown) {UISimpleFrame::Destroy(frameLevelDropDown); frameLevelDropDown= NULL;}
		bIsReplayOrObs = false;

		delete PullDown;
		PullDown = NULL;
	}
}