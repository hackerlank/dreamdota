//事件：单位受到伤害
//条件：单位是英雄

//默认样式:
//物理伤害 = 白色， 暴击 = ?
//法术伤害 = 黄色， 暴击 = ?
//

#include "stdafx.h"
#include "DreamDotaMain.h"

namespace DamageDisplay {
	static bool Enabled = false;

	static std::set<Unit*> DisableSet;
	static std::set<Unit*> EnableSet;
	static uint32_t tid = 0;
	static uint32_t count = 0;

	//color 0xAARRGGBB
	//0 = 对敌军， 1 = 对友军
	static uint32_t Color_Normal[2]		= { 0xFFFFFFFF, 0xFFFFFFFF };
	static uint32_t Color_Crit[2]		= { 0xFFFF0000, 0xFFFF0000 };
	static uint32_t Color_Spell[2]		= { 0xFFFFFF00, 0xFFFFFF00 };
	static uint32_t Color_Heal[2]		= { 0xFF00FF00, 0xFF00FF00 };

	static double Size_Tiny		= 0.0115;
	static double Size_Small	= 0.023;
	static double Size_Middle	= 0.046;
	static double Size_Large	= 0.0575;
	static double Size_Ultra	= 0.069;

	float SizedVelocity (double size) {
		if (size <= Size_Tiny)	return 0.09f;
		if (size <= Size_Small) return 0.08f;
		if (size <= Size_Middle) return 0.06f;
		if (size <= Size_Large) return 0.03f;
		if (size <= Size_Ultra) return 0.01f;
		return 0.01f;
	}

	bool WantEnable(Unit *u) {
		if (!u) return false;
		if (u->testFlag(UnitFilter::HERO)) return true;	//英雄单位允许
		//return true;
		return false;
	}

	void onReceiveDamage (const Event *evt) {
		if (!Enabled) return;
		Unit *eventUnit, *sourceUnit;
		float damageRaw;
		uint32_t color;
		double size = Size_Middle;

		//OutputScreen(10, "EVENT_UNIT_RECEIVE_DAMAGE");

		UnitDamagedEventData *data = evt->data<UnitDamagedEventData>();
		if (data->target){
			eventUnit = GetUnit(data->target);
			sourceUnit = GetUnit(data->source);
			
			if (!(eventUnit && sourceUnit))
				return;

			if (DisableSet.count(eventUnit))
				return;

			if (!EnableSet.count(eventUnit)) {
				if (WantEnable(eventUnit)) EnableUnit(eventUnit);
				else {	DisableUnit(eventUnit);	return;	}
			}
				
			damageRaw = data->damageRaw;

			char buffer[20];
			sprintf_s(buffer, 20, "%d", (int)damageRaw);

			int dmgAllyFlag = eventUnit->isAllyToLocalPlayer()? 1 : 0;
			if (data->isSpell) {//法术
				color = Color_Spell[dmgAllyFlag]; 
				size = damageRaw >= 700 ? Size_Ultra : 
					(damageRaw >= 400 ? Size_Large : Size_Middle);
			} 
			else if (damageRaw > (sourceUnit->damage(0, eventUnit).maxValue())) {//暴击
				color = Color_Crit[dmgAllyFlag];		//TODO 武器0/1判断问题
				size = Size_Large;
			}
			else { 
				color = Color_Normal[dmgAllyFlag]; 
				size = Size_Middle; 
			}
			if (damageRaw < 10) size = Size_Small;
			if (damageRaw < 5) size = Size_Tiny;

			war3::CTextTagManager* m = GetMapTTM();
			tid = TTMCreateTag(m, buffer, size);
			TTMSetTagPermanent(m, tid, false);
			TTMSetTagColor(m, tid, color);
			TTMSetTagPos(m, tid, eventUnit->x(), eventUnit->y(), 150.f);
			//TTMSetTagPos3D(m, tid, eventUnit->x(), eventUnit->y(), 150.f);
			//TTMSetTagVisibility(m, tid, false);
			TTMSetTagVisibility(m, tid, true);
			TTMSetTagVelocity(m, tid, 0.f, SizedVelocity(size));
			TTMSetTagLifespan(m, tid, 2.5f * (float)(size / Size_Middle));
			//OutputScreen(2, "TextTag Id: %u", tid);

		}
	}

	void DisableUnit(Unit* u) {
		if (!u) return;
		DisableSet.insert(u);
		EnableSet.erase(u);
	}

	void EnableUnit(Unit* u) {
		if (!u) return;
		DisableSet.erase(u);
		EnableSet.insert(u);
	}

	static CheckBox*		CbEnabled;
	static Label*			LbEnabled;

	void CreateMenuContent(){
		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::UIENHANCEMENT_CATEGORYNAME), NULL);
		CbEnabled = new CheckBox(Panel, 0.024f, NULL, &Enabled, "DamageDisplay", "Enable", true);
		CbEnabled->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.084f);
		LbEnabled = new Label(Panel, StringManager::GetString(STR::DAMAGEDISPLAY_ENABLE), 0.013f);
		LbEnabled->setRelativePosition(
			POS_L, 
			CbEnabled, 
			POS_R,
			0.01f, 0);

	}

	void Init ( ) {
		//UI
		CreateMenuContent();

		MainDispatcher()->listen(EVENT_UNIT_RECEIVE_DAMAGE, onReceiveDamage);
	}

	void Cleanup( ) {
		DisableSet.clear();
		EnableSet.clear();
	}
}