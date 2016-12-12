//按ctrl + 右键物品 = 将物品扔到当前位置
//按alt + 右键物品 = 拿起多个物品

#include "stdafx.h"
#include "DreamWar3Main.h"
#include <VMP.h>

namespace QuickDropItem {

	static bool EnableNextQuickTransfer;

	void dropItemAction (Unit *hero, item whichItem, bool queued){
		//TRIGGER_CALL_1 = GetOrderTarg获取单位当前命令目标
		hero->sendActionDropItem(
			0,//TODO
			hero->position(),
			NULL,
			whichItem,
			true
		);
	}

	static bool FastDropItemEnabled;
	void onItemCtrlRightClicked (const Event *evt) {
		if (!FastDropItemEnabled) return;
		ItemClickData *data = evt->data<ItemClickData>();
		if (	data->mouseCode == MOUSECODE::MOUSE_RIGHT
			&&	!data->byProgramm
			&&	KeyIsDown(KEYCODE::KEY_CONTROL)
			&&	!KeyIsDown(KEYCODE::KEY_ALT)
			&&	!KeyIsDown(KEYCODE::KEY_SHIFT)
		){
			item clickedItem = data->clickedItem;
			bool queued = KeyIsDown(KEYCODE::KEY_SHIFT);
			if (clickedItem) {
				//把物品扔在脚下
				UnitGroup *group = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
				if (group->size() > 0){
					Unit *hero = group->getUnit(0);
					data->discard();
					SoundPlay("InterfaceClick", NULL, 0);
					dropItemAction(hero, clickedItem, queued);
				}
				GroupDestroy(group);
			}
		}
	}

	static war3::CCommandButton*		LastClickedInv;
	static std::set<item>			ItemsTaken;
	static bool MultipleItemEnabled;

	void onItemAltRightClicked (const Event *evt) {
		if (!MultipleItemEnabled) return;
		ItemClickData *data = evt->data<ItemClickData>();
		if (	data->mouseCode == MOUSECODE::MOUSE_RIGHT
			&&	!data->byProgramm
			&&	!KeyIsDown(KEYCODE::KEY_CONTROL)
			&&	KeyIsDown(KEYCODE::KEY_ALT)
		){
			data->discard();
			item clickedItem = data->clickedItem;
			if (clickedItem) {
				if (!LastClickedInv)
					ItemsTaken.clear();//拿取物品过程开端
				ItemsTaken.insert(clickedItem);//增加所拿起的物品记录
				LastClickedInv = (war3::CCommandButton *)data->evtObj->baseEvent.object;//记忆最后的按钮
				SoundPlay("InterfaceClick", NULL, 0);//点击音效
			}
		}
	}

	void onKeyAltUp (const Event *evt) {
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (	data->code == KEYCODE::KEY_ALT
			&&	LastClickedInv
		){
			GameUIButtonClick(LastClickedInv, MOUSECODE::MOUSE_RIGHT, true);//右键最后拿起的物品
			LastClickedInv = NULL;//拿取物品过程结束
		}
	}

	Timer *dropItemTimer;
	void onTimerAction(Timer *tm) {
		if (LastClickedInv) {
			MousePosition* pos = GetMousePosition();
			if (pos->x < 0.5 || pos->x > 0.6 || pos->y > 0.12) {//判断鼠标在物品栏外
				GameUIButtonClick(LastClickedInv, MOUSECODE::MOUSE_RIGHT, true);//右键最后拿起的物品
				LastClickedInv = NULL;//拿取物品过程结束
			}
		}
	}

	void dropMultipleItemAction(std::set<item> *items, Unit *hero, Point position, Unit *targetUnit, uint32_t flag) {
		std::set<item>::iterator iter;
		bool wantQueue = false;
		for (iter = items->begin(); iter != items->end(); ++iter) {
			hero->sendActionDropItem(
				wantQueue ? (flag | Queued) : flag,
				position,
				targetUnit,
				*iter,
				true
			);
			wantQueue = true;
		}
	}

	void onActionSent (const Event *evt) {
		//判断是给予物品操作，改写操作
		//其它操作则直接清理流程
		ActionEventData *data = evt->data<ActionEventData>();
		//OutputScreen(10, "onActionSent");
		if (	!data->byProgramm 
			&&	ItemsTaken.size()
		){
			uint32_t actionId = data->id;
			if ( actionId == ACTION_DROPITEM ) {
				//OutputScreen(10, "actionId == ACTION_DROPITEM");
				item actionTransferItem = data->transferItem;
				if ( actionTransferItem && ItemsTaken.count(actionTransferItem) ){
					UnitGroup *group = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
					if (group->size() > 0){
						Unit *hero = group->getUnit(0);
						PacketSenderDestroy(data->packetSender);//先屏蔽掉操作
						dropMultipleItemAction(
							&ItemsTaken, 
							hero, 
							Point(data->x, data->y),
							GetUnit(data->target),
							data->flag
						);
					}
					GroupDestroy(group);
				}
				ItemsTaken.clear();
			}
			else {
				//OutputScreen(10, "actionId != ACTION_DROPITEM");
				ItemsTaken.clear();
			}
		}
	}

	void onItemRightClicked (const Event *evt) {
		ItemClickData *data = evt->data<ItemClickData>();
		if (	data->mouseCode == MOUSECODE::MOUSE_RIGHT){
			item clickedItem = data->clickedItem;
			if (clickedItem) {
				EnableNextQuickTransfer = true;
			}
		}
		else {
			EnableNextQuickTransfer = false;
		}
	}

	void onItemKeyPressed (const Event *evt) {
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (	data->code == KEYCODE::KEY_NUMPAD7
			||	data->code == KEYCODE::KEY_NUMPAD8
			||	data->code == KEYCODE::KEY_NUMPAD4
			||	data->code == KEYCODE::KEY_NUMPAD5
			||	data->code == KEYCODE::KEY_NUMPAD1
			||	data->code == KEYCODE::KEY_NUMPAD2	)
		{
			EnableNextQuickTransfer = false;
		}
	}

	void onHeroBarPressed (const Event *evt) {
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (	EnableNextQuickTransfer
			&&	data->code >= KEYCODE::KEY_F1
			&&	data->code <= KEYCODE::KEY_F5	//TODO 研究如何获得reserved hero数量
		){
			UnitGroup *group = GroupUnits(
					NULL,
					NULL,
					PlayerGroup(
						PlayerFilter::ALLIANCE_SHARED_ADVANCED_CONTROL,
						NULL,
						PlayerLocal()
					),
					NULL,
					UnitFilter(
						UnitFilter::HERO,
						NULL
					)
				);
			UnitGroup *groupActive = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
			if (group->size() > 0){
				Unit *hero = group->getUnit(data->code - KEYCODE::KEY_F1);
				if (hero && hero->life() > 0) {//死掉的英雄当作不存在处理
					void *heroButton = hero->heroButton();
					if (heroButton){
						bool heroIsCurrent = (groupActive->size()>0 && groupActive->getUnit(0)==hero);
						if (!heroIsCurrent){
							data->discard();
							GameUIButtonClick(heroButton, MOUSECODE::MOUSE_LEFT, true);
						}
						EnableNextQuickTransfer = false;
					}
				}
			}
			GroupDestroy(group);
			GroupDestroy(groupActive);
		}
	}

	void CreateMenuContent() {
		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::MICRO_CATEGORYNAME));

		CheckBox*	CbPickMultipleItem;
		Label*		LbPickMultipleItem;

		CheckBox*	CbFastDropItem;
		Label*		LbFastDropItem;

		CbPickMultipleItem = new CheckBox(
			Panel, 0.024f, NULL, &MultipleItemEnabled, 
			"ItemMultiPick", "Enable", true );
		CbPickMultipleItem->setRelativePosition(
			POS_UL,	Panel, POS_UL, 0.03f, -0.03f);
		LbPickMultipleItem = new Label(Panel, StringManager::GetString(STR::MULTIPICKITEM_ENABLE), 0.013f);
		LbPickMultipleItem->setRelativePosition(
			POS_L, CbPickMultipleItem, POS_R, 0.01f, 0);

		//fast drop item
		CbFastDropItem = new CheckBox(
			Panel, 0.024f, NULL, &FastDropItemEnabled, 
			"ItemFastDrop", "Enable", true );
		CbFastDropItem->setRelativePosition(
			POS_UL,	Panel, POS_UL, 0.03f, -0.057f);
		LbFastDropItem = new Label(Panel, StringManager::GetString(STR::FASTDROPITEM_ENABLE), 0.013f);
		LbFastDropItem->setRelativePosition(
			POS_L, CbFastDropItem, POS_R, 0.01f, 0);
	}

	void Init() {
		VMProtectBeginVirtualization("QuickDropItemInit");

		CreateMenuContent();

		MainDispatcher()->listen(EVENT_ITEM_CLICK, onItemRightClicked);
		MainDispatcher()->listen(EVENT_KEY_DOWN, onHeroBarPressed);//检测下一个操作
		MainDispatcher()->listen(EVENT_KEY_DOWN, onItemKeyPressed);//检测按物品(左键点击/小键盘)

		MainDispatcher()->listen(EVENT_ITEM_CLICK, onItemCtrlRightClicked);

		ItemsTaken.clear();
		MainDispatcher()->listen(EVENT_ITEM_CLICK, onItemAltRightClicked);
		MainDispatcher()->listen(EVENT_KEY_UP, onKeyAltUp);
		MainDispatcher()->listen(EVENT_LOCAL_ACTION, onActionSent);//检测下一个操作
		dropItemTimer = GetTimer(0.2, onTimerAction, true);
		dropItemTimer->start();

		VMProtectEnd();
	}
}