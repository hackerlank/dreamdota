#pragma once
#include "Frame.h"
#include "Texture.h"
#include "Unit.h"

class MinimapRadar : public Frame
{
	Texture *BG;
	std::deque<Texture *> HeroIcons;

	//每周期获得所有单位，显示到小地图上
#define RADAR_SIZE 0.2f
public:
	MinimapRadar()
		: Frame(UI_NULL, RADAR_SIZE, RADAR_SIZE)
	{
		BG = new Texture(this, RADAR_SIZE, RADAR_SIZE, "war3mapmap.blp");
		BG->setOwner(this);
		BG->setRelativePosition(POS_C, this, POS_C);
	}

	virtual ~MinimapRadar()
	{
		for(uint32_t i = 0; i < HeroIcons.size(); i++)
		{
			delete HeroIcons[i];
		}
		delete BG;
	}

	void RefreshData()//should be ticked by extern timer
	{
#define CAMERABOUNDFIX 1024
		float WorldMinX = Jass::GetCameraBoundMinX() - CAMERABOUNDFIX;
		float WorldMaxX = Jass::GetCameraBoundMaxX() + CAMERABOUNDFIX;
		float WorldMinY = Jass::GetCameraBoundMinY() - CAMERABOUNDFIX;
		float WorldMaxY = Jass::GetCameraBoundMaxY() + CAMERABOUNDFIX;
		float WorldSizeX = WorldMaxX - WorldMinX;
		float WorldSizeY = WorldMaxY - WorldMinY;

		UnitGroup *g = GroupUnitAll();
		UnitGroup *g_heroes = GroupUnits(g, NULL, PlayerGroupAll(), NULL, UnitFilter(UnitFilter::HERO, NULL));

		int origSize = HeroIcons.size();
		int newSize = g_heroes->size();

		//clear
		for(int i = newSize; i < origSize; i++)
		{
			delete HeroIcons[i];
		}
		HeroIcons.resize(newSize);
		//create
		for(int i = origSize; i < newSize; i++)
		{
			HeroIcons[i] = new Texture(this, 0.005f, 0.005f, "UI\\MiniMap\\minimap-hero.blp");
			HeroIcons[i]->setOwner(this);
		}
		for(uint32_t i = 0; i < g_heroes->size(); i++)
		{
			Unit *u = g_heroes->getUnit(i);
			Point pos = u->position();
			float unit2DSize = RADAR_SIZE * 512 / WorldSizeX;
			HeroIcons[i]->setSize(unit2DSize);
			HeroIcons[i]->setRelativePosition(POS_C, BG, POS_BL, RADAR_SIZE*(pos.x-WorldMinX)/WorldSizeX, RADAR_SIZE*(pos.y-WorldMinY)/WorldSizeY );
			int owner = u->owner();
			if ( owner == PlayerLocal() )
			{
				HeroIcons[i]->setColor(Color::WHITE);
			}
			else
			{
				switch (Jass::GetAllyColorFilterState())
				{
				case 0:
					HeroIcons[i]->setColor(GetPlayerColor(owner, false));
					break;
				default:
					HeroIcons[i]->setColor(u->isAllyToLocalPlayer()? Color::BLUE : Color::RED);
					break;
				}
			}
		}
		

		GroupDestroy(g_heroes);
		GroupDestroy(g);
	}
};