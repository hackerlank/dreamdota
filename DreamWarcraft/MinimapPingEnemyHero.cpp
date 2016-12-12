#include "stdafx.h"
#include "DreamDotaMain.h"
#include "UnitStateIcon.h"

//test
#include "StatePanel.h"

namespace MinimapPingEnemyHero {

	static bool Enable;
	static bool ShowEnemy;
	static bool ShowFriend;
	static bool AltIcon;
	static bool IgnoreSpecialHero;

	//测试显示方向
	static UnitGroup *Heroes;
	static std::map<Unit *, UnitStateIcon *> HeroDirectionIconMap;

	void onRefreshHeroDirection(Timer *tm)
	{
		for (std::map<Unit *, UnitStateIcon *>::iterator iter = HeroDirectionIconMap.begin();
			iter != HeroDirectionIconMap.end(); ++iter)
		{
			if (!Heroes->has(iter->first))
			{
				delete (iter->second);
				HeroDirectionIconMap.erase(iter->first);
				break;
			}
		}

		for (UnitGroup::iterator iter = Heroes->begin(); iter != Heroes->end(); ++iter)
		{
			Unit *hero = *iter;
			//计算相对于当前屏幕方向
			Point pointCamera(Jass::GetCameraTargetPositionX(), Jass::GetCameraTargetPositionY());
			float direction = pointCamera.angleTo(hero->position());
			float distance = pointCamera.distanceTo(hero->position());

			//FramePoint fp; 
			//hero->framepointGet(&fp);
			bool bIsInvisible = //fp.x < 0 || fp.x > 0.8f || fp.y < 0 || fp.y > 0.6f;
				distance > 1300;
			
			UnitStateIcon *icon;
			float size = 0.02f;
			if ( !HeroDirectionIconMap.count(hero) )
			{
				icon = new UnitStateIcon(UI_NULL, size, size, hero );
				icon->setParent(UIObject::GetMinimapFrame());
				HeroDirectionIconMap[hero] = icon;
			}
			else
			{
				icon = HeroDirectionIconMap[hero];
			}

			float bottom = 0.15f + size/2, top = 0.575f - size/2, left = size/2, right = 0.8f - size/2;
			float height = top - bottom, width = right - left;
			float midX = left + width/2;
			float midY = bottom + height/2;

			float diag = atan2(height, width);

			//clip
			float x, y;
			if ( abs(sin(direction)) > sin(diag) )
			{
				if (sin(direction) > 0)
				{
					y = height/2;
					x = y / tan(direction);
				}
				else
				{
					y = -height/2;
					x = y / tan(direction);
				}
			}
			else
			{
				if (cos(direction) > 0)
				{
					x = width/2;
					y = x * tan(direction);
				}
				else
				{
					x = -width/2;
					y = x * tan(direction);
				}
			}

			if (bIsInvisible)
			{
				icon->show(true);
				//icon->setColor(1, 1, 1, 
				//	1 - ( (distance - 1300) / 7500)
				//);
				icon->setAbsolutePosition(POS_C, midX + x, midY + y);
			}
			else
			{
				icon->show(false);
			}
			
		}
	}


	static void DumpAbilities(Unit* u) {
		OutputDebug("UNIT: 0x%X TYPE: %s\n", u->handleId(), u->typeIdChar());
		Ability* head = u->AbilityListHead();
		while (head) {

			OutputDebug("%s %s\n", head->typeIdChar(), head->className());

			head = head->nextNode();
		}
	}

	static bool WantIgnore(Unit* u) {
		bool rv = false;
		//忽略有永久无敌和蝗虫的英雄
		if (IgnoreSpecialHero) {
			rv = rv || (NULL != u->AbilityById('Avul') || NULL != u->AbilityById('Aloc'));
		}
		return rv;
	}

	void onTimer(Timer *tm) {
		if (!Enable) return;
		
		PlayerGroup p;
		if (!ShowEnemy && !ShowFriend) return;
		else if (ShowEnemy && ShowFriend) p = PlayerGroupAll();
		else if (ShowEnemy && !ShowFriend) {
			p = PlayerGroup(
				NULL,
				PlayerFilter::ALLIANCE_PASSIVE | PlayerFilter::ALLIANCE_SHARED_VISION,
				PlayerLocal()
			);
		}
		else {
			p = PlayerGroup(
				PlayerFilter::ALLIANCE_PASSIVE | PlayerFilter::ALLIANCE_SHARED_VISION,
				NULL,
				PlayerLocal()
			);
		}

		UnitGroup *groupAllHeroes = 
			GroupUnits(
				NULL,
				NULL,
				p,
				NULL,
				UnitFilter(
					UnitFilter::HERO | UnitFilter::VISIBLE,
					UnitFilter::DEAD
				)
			);

		Heroes->copy(groupAllHeroes);
		
		uint32_t red, green, blue, alpha;
		GroupForEachUnit(groupAllHeroes, hero,
			if (!WantIgnore(hero)) {
				if ( !AltIcon )
				{
					Jass::UnitSetUsesAltIcon(hero->handleId(), false);
					GetPlayerColor(hero->owner(), red, green, blue, alpha, false);
					PingMinimapEx(hero->x(), hero->y(), 0.3f, red, green, blue, false);
				}
				else
				{
					Jass::SetAltMinimapIcon("UI\\Minimap\\MinimapIconCreepLoc.blp");
					Jass::UnitSetUsesAltIcon(hero->handleId(), true);
				}
			}
		);
		GroupDestroy(groupAllHeroes);
	}

	

	static CheckBox*	CbEnablePing;
	static Label*		LbEnablePing;
	static CheckBox*	CbEnablePingEnemy;
	static Label*		LbEnablePingEnemy;
	static CheckBox*	CbEnablePingAlly;
	static Label*		LbEnablePingAlly;
	static CheckBox*	CbEnableAltIcon;
	static Label*		LbEnableAltIcon;
	static CheckBox*	CbIgnoreInvulnerableUnit;
	static Label*		LbIgnoreInvulnerableUnit;

	static void Dependency(CheckBox* cb, bool flag) {
		CbEnablePingEnemy->activate(flag);
		LbEnablePingEnemy->activate(flag);
		CbEnablePingAlly->activate(flag);
		LbEnablePingAlly->activate(flag);
		CbEnableAltIcon->activate(flag);
		LbEnableAltIcon->activate(flag);
		CbIgnoreInvulnerableUnit->activate(flag);
		LbIgnoreInvulnerableUnit->activate(flag);
	}

	static void CreateMenuContent(){

		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::MAPHACK_CATEGORYNAME));

		CbEnablePing = new CheckBox(Panel);
		CbEnablePing->bindProfile("MinimapPingEnemyHero", "Enable", true);
		CbEnablePing->bindVariable(&Enable);
		CbEnablePing->bindCallback(Dependency);
		CbEnablePing->setRelativePosition(
			POS_UL, Panel, POS_UL,
			0.03f + Panel->width()/2, -0.03f);
		LbEnablePing = new Label(Panel, StringManager::GetString(STR::PINGHERO_ENABLE), 0.013f);
		LbEnablePing->setRelativePosition(
			POS_L, 
			CbEnablePing->getFrame(), 
			POS_R,
			0.01f, 0);

		CbEnablePingEnemy = new CheckBox(Panel);
		CbEnablePingEnemy->bindProfile("MinimapPingEnemyHero", "ShowEnemy", true);
		CbEnablePingEnemy->bindVariable(&ShowEnemy);
		CbEnablePingEnemy->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f + Panel->width()/2, -0.057f);
		LbEnablePingEnemy = new Label(Panel, StringManager::GetString(STR::PINGHERO_ENEMY), 0.013f);
		LbEnablePingEnemy->setRelativePosition(
			POS_L, 
			CbEnablePingEnemy->getFrame(), 
			POS_R,
			0.01f, 0);

		CbEnablePingAlly = new CheckBox(Panel);
		CbEnablePingAlly->bindProfile("MinimapPingEnemyHero", "ShowFriend", false);
		CbEnablePingAlly->bindVariable(&ShowFriend);
		CbEnablePingAlly->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f + Panel->width()/2, -0.084f);
		LbEnablePingAlly = new Label(Panel, StringManager::GetString(STR::PINGHERO_FRIEND), 0.013f);
		LbEnablePingAlly->setRelativePosition(
			POS_L, 
			CbEnablePingAlly->getFrame(), 
			POS_R,
			0.01f, 0);

		CbEnableAltIcon = new CheckBox(Panel);
		CbEnableAltIcon->bindProfile("MinimapPingEnemyHero", "AltIcon", false);
		CbEnableAltIcon->bindVariable(&AltIcon);
		CbEnableAltIcon->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f + Panel->width()/2, -0.111f);
		LbEnableAltIcon = new Label(Panel, StringManager::GetString(STR::PINGHERO_ALTICON), 0.013f);
		LbEnableAltIcon->setRelativePosition(
			POS_L, 
			CbEnableAltIcon->getFrame(), 
			POS_R,
			0.01f, 0);


		CbIgnoreInvulnerableUnit = new CheckBox(Panel);
		CbIgnoreInvulnerableUnit->bindProfile("MinimapPingEnemyHero", "IgnoreSpecialHero", true);
		CbIgnoreInvulnerableUnit->bindVariable(&IgnoreSpecialHero);
		CbIgnoreInvulnerableUnit->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f + Panel->width()/2, -0.138f);
		LbIgnoreInvulnerableUnit = new Label(Panel, StringManager::GetString(STR::PINGHERO_IGNORE_SPECIAL), 0.013f);
		LbIgnoreInvulnerableUnit->setRelativePosition(
			POS_L, 
			CbIgnoreInvulnerableUnit->getFrame(), 
			POS_R,
			0.01f, 0);

		Dependency(CbEnablePing, CbEnablePing->isChecked());
	}

	void Init(){
		CreateMenuContent();
		GetTimer(1.5, onTimer, true)->start();

		Heroes = new UnitGroup();
		//GetTimer(0.01, onRefreshHeroDirection, true)->start();
	}

	void Cleanup(){
		//for (std::map<Unit *, UnitStateIcon *>::iterator iter = HeroDirectionIconMap.begin();
		//	iter != HeroDirectionIconMap.end(); ++iter)
		//{
		//	delete iter->second;
		//}
		//HeroDirectionIconMap.clear();

		GroupDestroy(Heroes);
	}
}