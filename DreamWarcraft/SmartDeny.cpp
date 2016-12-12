#include "stdafx.h"
#include "DreamDotaMain.h"

namespace SmartDeny {
	const float ENABLEDPERCENT = 1.0f;
	static bool Enabled;

	void onActionSent(const Event* evt) {
		if (!Enabled) return;
		ActionEventData *data = evt->data<ActionEventData>();
		if (	!data->byProgramm && 
				data->id == ACTION_SMART && 
				data->target != NULL &&
				!(data->flag & Queued)
		){
			Unit *u = GetUnit(data->target);
			if (u && !u->isEnemyToLocalPlayer()){
				if (	!u->testFlag(UnitFilter::INVULNERABLE)
					&&	u->life() / u->lifeMax() <= ENABLEDPERCENT
				){
					data->discard();
					UnitGroup *g = GroupUnitsOfPlayerSelected(PlayerLocal(), false);
					g->sendAction(
						ACTION_ATTACK,
						Target,
						data->flag,
						NULL,
						Point(data->x, data->y),
						u,
						NULL,
						true
					);

					GroupDestroy(g);
				}
			}
		}
	}

	static CheckBox *CbEnabled;
	static Label *LbEnabled;

	void CreateMenuContent(){
		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::LASTHIT_CATEGORYNAME), NULL); 
		CbEnabled = new CheckBox(Panel);
		CbEnabled->bindProfile("SmartDeny", "Enabled", true);//Ä¬ÈÏ¿ªÆô
		CbEnabled->bindVariable(&Enabled);
		CbEnabled->setRelativePosition( POS_UL,	Panel, POS_UL, 0.03f, -0.111f );
		LbEnabled = new Label( Panel, StringManager::GetString(STR::LASTHIT_ENABLERIGHTCLICKDENY), 0.013f );
		LbEnabled->setRelativePosition(	POS_L, CbEnabled, POS_R, 0.01f, 0 );
	}

	void Init(){
		//UI
		CreateMenuContent();
		MainDispatcher()->listen(EVENT_LOCAL_ACTION, onActionSent);
	}

	void Cleanup(){
	}
}