//本地玩家选中的单位形成多个子组时，使用非高亮子组单位的命令热键会切换至该子组并按出命令按钮。

#include "stdafx.h"
#include "DreamDotaMain.h"

namespace CommandThrough
{
	const float CMD_MAP_THRESHOLD = 0.2f;
	typedef std::map<Unit*, std::pair<uint32_t, float> > CmdMap;
	static CmdMap UnitLastLocalActionMap;
	
	static bool Enabled;

	void loopCheckSelectionState(Timer *tm)
	{
		if ( tm->execCount() > 50 )
		{
			tm->destroy();
			return;
		}
		else
		{
			std::pair<Unit *, uint32_t> data = *(tm->data<std::pair<Unit *, uint32_t>>());
			Unit *u = data.first;
			uint32_t keyCode = data.second;

			Unit *activeUnit = NULL;
			UnitGroup *groupActive = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
			if (groupActive->size() > 0)
			{
				activeUnit = groupActive->getUnit(0);
				if ( u == activeUnit )
				{
					war3::CCommandButton *btn = HotkeyGetButton(keyCode);
					if (btn && btn->baseSimpleButton.currentState == UISimpleButton::STATE_ENABLED)
					{
						//OutputScreen(1, "activeUnit", KEYCODE::getStr(keyCode));
						GameUIButtonClick(btn, MOUSECODE::MOUSE_LEFT, true);
						tm->destroy();
					}
				}
			}
		}
	}

	bool UnitIsExecutingAction(Unit *u, uint32_t actionId)
	{
		if (u->currentOrder() == actionId)
		{
			return true;
		}
		if (UnitLastLocalActionMap.count(u))
		{
			if ( UnitLastLocalActionMap[u].first == actionId )
			{
				return true;
			}
		}
		return false;
	}

	void onKeyDown (const Event *evt) 
	{
		if (!Enabled) return;

		//如果当前面板为取消（正在指定目标），直接返回
		if ( IsCancelPanelOn() )
		{
			return;
		}

		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if ( data->byProgramm ) return;
		int keyCode = data->code;		

		//如果热键对于当前高亮子组为可用技能热键，直接返回
		UnitGroup *groupActive = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
		if (groupActive->size() > 0)
		{
			Unit *activeUnit = groupActive->getUnit(0);
			//Ability *abil = activeUnit->AbilityByHotkey(keyCode, false);
			//if ( abil != NULL && abil->isSpell() )
			//{
			//	//TODO 判断可用状态
			//	if ( abil->isAvailable() && !UnitIsExecutingAction(activeUnit, abil->order()) )
			//	{
			//		GroupDestroy(groupActive);
			//		return;
			//	}
			//}
			war3::CCommandButton *btn = HotkeyGetButton(keyCode);
			if (btn && btn->commandButtonData)
			{
				Ability *abil = (Ability*)btn->commandButtonData->ability;
				if (	abil == NULL 
					|| 
					(
						btn->baseSimpleButton.currentState == UISimpleButton::STATE_ENABLED
					&&	abil->isAvailable() 
					&&	!UnitIsExecutingAction(activeUnit, abil->order()) 
					&&	activeUnit->mana() >= btn->commandButtonData->manaCost
					)
				)
				{
					GroupDestroy(groupActive);
					return;
				}
			}
		}
		else//没有高亮单位
		{
			GroupDestroy(groupActive);
			return;
		}

		//寻找热键对应的非高亮子组单位可用技能
		UnitGroup *groupSelected = GroupUnitsOfPlayerSelected(PlayerLocal(), false);
		groupSelected->remove(groupActive);
		for ( UnitGroup::iterator iter = groupSelected->begin();
			iter != groupSelected->end(); ++iter )
		{
			Unit *selectedUnit = *iter;
			if ( selectedUnit )
			{
				Ability *abil = selectedUnit->AbilityByHotkey(keyCode, false);
				if ( abil != NULL )
				{
					if (	abil->isSpell()
						&&	abil->isAvailable() 
						&&	!UnitIsExecutingAction(selectedUnit, abil->order()) 
						&&	selectedUnit->mana() >= abil->mana()
					)
					{
						SetLocalSubgroup(selectedUnit);
						Timer *tm = GetTimer(0.005, loopCheckSelectionState, true);
						tm->setData<std::pair<Unit *, uint32_t>>(
							&std::pair<Unit *, uint32_t>(selectedUnit, keyCode)
							);
						tm->start();
						break;
					}
				}
			}
		}

		GroupDestroy(groupActive);
		GroupDestroy(groupSelected);
	}

	void onActionSent(const Event *evt)
	{
		ActionEventData *data = evt->data<ActionEventData>();
		if (data->byProgramm) return;

		UnitGroup *groupActive = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
		if (groupActive->size() > 0)
		{
			Unit *activeUnit = groupActive->getUnit(0);
			std::pair<uint32_t, float> actionSig ( data->id, Time() );
			UnitLastLocalActionMap[activeUnit] = actionSig;
			//清理
			for (CmdMap::iterator iter = UnitLastLocalActionMap.begin(); iter != UnitLastLocalActionMap.end();)
			{
				if ( Time() - iter->second.second > CMD_MAP_THRESHOLD )
				{
					UnitLastLocalActionMap.erase(iter);
					iter = UnitLastLocalActionMap.begin();
				}
				else
				{
					++iter;
				}
			}
		}
		GroupDestroy(groupActive);
	}

	void CreateMenuContent()
	{
		VMProtectBeginVirtualization("CommandThroughMenuContent");

		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::MICRO_CATEGORYNAME));

		CheckBox*	CbEnable;
		Label*		LbEnable;

		CbEnable = new CheckBox(
			Panel, 0.024f, NULL, &Enabled, "CommandThrough", "Enable", true );
		CbEnable->setRelativePosition(
			POS_UL, Panel, POS_UL, 0.03f, -0.111f);
		LbEnable = new Label(Panel, StringManager::GetString(STR::COMMAND_THROUGH_ENABLE), 0.013f);
		LbEnable->setRelativePosition(
			POS_L, CbEnable, POS_R, 0.01f, 0);

		VMProtectEnd();
	}

	void Init()
	{

		CreateMenuContent();

		//捕捉按键事件
		MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);

		//捕捉本地发送命令事件：发送了命令的技能将被认为等同于不可用，被排除
		MainDispatcher()->listen(EVENT_LOCAL_ACTION, onActionSent);
	}

	void Cleanup()
	{
		UnitLastLocalActionMap.clear();
	}
}