#include "stdafx.h"
#include "DreamWar3Main.h"
#include "Table.h"

namespace ReplayMode
{
	const float GAPMINWIDTH = 0.003f;
	const float SIZE = 0.011f;
	const float SIZEICON = 0.015f;
	static PlayerGroup ValidPlayers = PlayerGroup();
	static Table *ResourceDisplayer;

	static bool ShowResource;

	void RefreshPlayer ( Timer *tm )
	{
		ValidPlayers = PlayerGroup(
			PlayerFilter::STATE_PLAYING, 
			PlayerFilter::CONTROL_CREEP | PlayerFilter::CONTROL_NEUTRAL 
		);
	}

	void RefreshResourcePlayer(int team, int indexInTeam, int indexTotal, int player)
	{
		//0: 玩家颜色块
		//1-2: 金子
		//3: 空
		//4-5: 木材
		//6: 空
		//7-8: 人口
		int row = indexTotal;
		int column = 0;
		bool bRefreshTable = false;

		if (row > -1)
		{
			column = 0;
			Texture *colorIcon = ResourceDisplayer->getElement<Texture *>(row, column);
			if ( colorIcon == NULL )
			{
				colorIcon = new Texture(UI_NULL, SIZEICON, SIZEICON);
				ResourceDisplayer->setElement(row, column, colorIcon);
			}
			colorIcon->fillColor(GetPlayerColor(player, false));

			column = 1;
			Texture *goldIcon = ResourceDisplayer->getElement<Texture *>(row, column);
			if ( goldIcon == NULL )
			{
				goldIcon = new Texture(UI_NULL, SIZEICON, SIZEICON, Skin::getPathByName("GoldIcon"));
				ResourceDisplayer->setElement(row, column, goldIcon);
			}

			column = 2;
			Label *goldLabel = ResourceDisplayer->getElement<Label *>(row, column);
			if ( goldLabel == NULL )
			{
				goldLabel = new Label(UI_NULL, "", SIZE, Color::WHITE);
				ResourceDisplayer->setElement(row, column, goldLabel);
			}
			if ( goldLabel->setText( "%d", Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_RESOURCE_GOLD)) )
			{
				bRefreshTable = true;
			}

			column = 4;
			Texture *woodIcon = ResourceDisplayer->getElement<Texture *>(row, column);
			if ( woodIcon == NULL )
			{
				woodIcon = new Texture(UI_NULL, SIZEICON, SIZEICON, Skin::getPathByName("LumberIcon"));
				ResourceDisplayer->setElement(row, column, woodIcon);
			}

			column = 5;
			Label *woodLabel = ResourceDisplayer->getElement<Label *>(row, column);
			if ( woodLabel == NULL )
			{
				woodLabel = new Label(UI_NULL, "", SIZE, Color::WHITE);
				ResourceDisplayer->setElement(row, column, woodLabel);
			}
			if ( woodLabel->setText( "%d", Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_RESOURCE_LUMBER) ) )
			{
				bRefreshTable = true;
			}

			column = 7;
			Texture *foodIcon = ResourceDisplayer->getElement<Texture *>(row, column);
			if ( foodIcon == NULL )
			{
				foodIcon = new Texture(UI_NULL, SIZEICON, SIZEICON, Skin::getPathByName("SupplyIcon"));
				ResourceDisplayer->setElement(row, column, foodIcon);
			}

			column = 8;
			Label *foodLabel = ResourceDisplayer->getElement<Label *>(row, column);
			if ( foodLabel == NULL )
			{
				foodLabel = new Label(UI_NULL, "", SIZE, Color::WHITE);
				ResourceDisplayer->setElement(row, column, foodLabel);
			}
			int cap = Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_RESOURCE_FOOD_CAP);
			cap = min(cap, Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_FOOD_CAP_CEILING));
			if ( foodLabel->setText( cap > 0 ? "%d/%d" : "%d", 
				Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_RESOURCE_FOOD_USED),
				cap ) )
			{
				bRefreshTable = true;
			}
			int upkeep = Jass::GetPlayerState(Jass::Player(player), Jass::PLAYER_STATE_GOLD_UPKEEP_RATE);
			if (upkeep < 30)
			{
				foodLabel->setTextColor(Color::GREEN);
			}
			else if (upkeep < 60)
			{
				foodLabel->setTextColor(Color::YELLOW);
			}
			else
			{
				foodLabel->setTextColor(Color::RED);
			}

			if ( bRefreshTable )
			{
				ResourceDisplayer->setRefresh();
			}
		}
	}

	void RefreshResource( Timer *tm )
	{
		if ( ShowResource && ResourceDisplayer && ResourceDisplayer->isShown() )
		{
			if ( ValidPlayers.count() != ResourceDisplayer->sizeRow() )
			{
				ResourceDisplayer->setRowColumnCount(ValidPlayers.count(), ResourceDisplayer->sizeColumn());
			}
			ValidPlayers.forEachTeam(RefreshResourcePlayer);
		}
	}

	void onEnableShowResource(CheckBox* cb, bool flag) 
	{
		ResourceDisplayer->show(flag);
	}

	void CreateMenuContent()
	{
		CheckBox *CbEnabled;
		Label *LbEnabled;

		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::OBSERVER), NULL);
		CbEnabled = new CheckBox(Panel, 0.024f, onEnableShowResource, &ShowResource, "Observer", "ShowResource", true);
		CbEnabled->setRelativePosition(POS_UL, Panel, POS_UL, 0.03f, -0.03f);
		LbEnabled = new Label(Panel, StringManager::GetString(STR::OBSERVER_SHOWRESOURCE), 0.013f);
		LbEnabled->setRelativePosition(POS_L, CbEnabled, POS_R, 0.01f, 0);
	}
	

	void Init()
	{
		bool bIsObserverMode;
#ifdef _DEBUG
		bIsObserverMode = true;
#else
		bIsObserverMode = ReplayState() == REPLAY_STATE_STREAMINGOUT
			|| Jass::IsPlayerObserver(Jass::Player(PlayerLocal()));
#endif

		if ( bIsObserverMode )
		{
			CreateMenuContent();

			GetTimer(0.5, RefreshPlayer, true)->startImmediate();

			//在屏幕右上显示所有玩家颜色 + 玩家资源（金－木－人口）
			ResourceDisplayer = new Table(UI_NULL, 0, 10, false, 0, false);
			ResourceDisplayer->showRowFrame(false);
			ResourceDisplayer->setColumnMinWidth(2, 0.02f);
			ResourceDisplayer->setColumnMinWidth(3, GAPMINWIDTH);
			ResourceDisplayer->setColumnMinWidth(5, 0.02f);
			ResourceDisplayer->setColumnMinWidth(6, GAPMINWIDTH);
			ResourceDisplayer->setColumnMinWidth(8, 0.03f);
			ResourceDisplayer->setColumnMinWidth(9, GAPMINWIDTH);
			ResourceDisplayer->setElementPadding(0.001f, 0.003f);
			ResourceDisplayer->setAbsolutePosition( POS_UR, 0.799f, 0.577f );
			ResourceDisplayer->show(true);
			GetTimer(0.5, RefreshResource, true)->startImmediate();
		}
	}

	void Cleanup()
	{
		delete ResourceDisplayer;
		ResourceDisplayer = NULL;
	}

}