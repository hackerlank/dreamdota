#include "stdafx.h"
#include "DreamDotaMain.h"

namespace RuneNotify {
	static bool RuneNotifyEnabled;

	void onItemCreated (const Event *evt) {
		if (!RuneNotifyEnabled){
			return;
		}
		ItemCreationEventData *data = evt->data<ItemCreationEventData>();
		Item *createdItem = GetItem(data->createdItem);
		if (createdItem->itemType() == Jass::ITEM_TYPE_POWERUP){
			//TODO: 引入地图数据库
			if (createdItem->typeId() == 'I0KK') return;
			if (createdItem->typeId() == 'I0HM') return;

			Point pos = createdItem->position();
			OutputScreen(10, StringManager::GetString(STR::POWERUPSPAWN), 
				createdItem->name(),
				pos.toString().c_str()
			);
			uint32_t red = 254, green = 0, blue = 0;
			PingMinimapEx(pos.x, pos.y, 3.f, red, green, blue, true);
		}
	}

	void onUnitCreated (const Event *evt) {
		if (!RuneNotifyEnabled){
			return;
		}
		Unit *u = GetUnit(evt->data<UnitCreationEventData>()->createdUnit);
		if (u){
/*
n00O 1级地雷
n00P 2级地雷
n00Q 3级地雷
n00N 4级地雷

otot 1级－3级陷阱
o018 1级遥控炸弹
o002 2级遥控炸弹
o00B 3级遥控炸弹

o004 假眼
oeye 真眼

u012 小强
*/
			switch (u->typeId()){
			case 'n00O':
			case 'n00P':
			case 'n00Q':
			case 'n00N':
			case 'otot':
			case 'o018':
			case 'o002':
			case 'o00B':
			case 'o004':
			case 'oeye':
			case 'u012':
#ifdef _DEBUG
				u->debugPanel->set("name", "|cffffcc00%s|r", u->name());
				u->debugPanel->setShowName(false);
#endif
				break;
			default:
				break;
			}
		}
	}

	void CreateMenuContent() {
		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::MAPHACK_CATEGORYNAME));

		CheckBox*	CbRuneNotify;
		Label*		LbRuneNotify;

		CbRuneNotify = new CheckBox(
			Panel, 0.024f, NULL, &RuneNotifyEnabled,
			"RuneNotify", "Enable", true );
		CbRuneNotify->setRelativePosition(
			POS_UL,	Panel, POS_UL, 0.03f + Panel->width()/2, -0.165f);
		LbRuneNotify = new Label(Panel, StringManager::GetString(STR::POWERUP_NOTIFY_ENABLE), 0.013f);
		LbRuneNotify->setRelativePosition(
			POS_L, CbRuneNotify, POS_R,	0.01f, 0);
	}

	void Init(){
		CreateMenuContent();
		MainDispatcher()->listen(EVENT_ITEM_CREATED, onItemCreated);
		//MainDispatcher()->listen(EVENT_UNIT_CREATED, onUnitCreated);
	}

	void Cleanup(){
	}
}