#include "stdafx.h"
#include "DreamDotaMain.h"

//Quas: 'A21W' 0xD00C4
//Wex: 'A21X' 0xD022E
//Exort: 'A21V' 0xD0277
//Invoke: 'A21Y' 0xD026C

//Cold Snap		A0VZ
//Sun Strike	A0VG
//Ice Wall		A0VP
//Forge Spirit	A0VO
//Chaos Meteor	A0VN
//Defeaning Blast	A0VM
//Ghost Walk	A0XL
//Alacrity		A0VQ
//Tornado		A0VK
//EMP			A0VS

namespace Invoker
{
	static bool Enabled;
	static bool UseSpell;
	static bool UseKey;

	const uint32_t InvokerTypeId = 'H00U';

	enum InvokerSpell
	{
		None			= NULL,

		Quas			= 'A21W',	//A0VB, D00D1
		Wex				= 'A21X',	//A0VA, D026D
		Exort			= 'A21V',	//A0V9, D022E
		Invoke			= 'A21Y',	//A0VF, D00A3
		InvokeUpgrade	= 'A1GU',

		ColdSnap		= 'A0VZ',
		SunStrike		= 'A0VG',
		IceWall			= 'A0VP',
		ForgeSpirit		= 'A0VO',
		ChaosMeteor		= 'A0VN',
		DefeaningBlast	= 'A0VM',
		GhostWalk		= 'A0XL',
		Alacrity		= 'A0VQ',
		Tornado			= 'A0VK',
		EMP				= 'A0VS'
	};

	int InvokerSpellToKeyCode (uint32_t id)
	{
		switch (id)
		{
		case Quas:
			return KEYCODE::KEY_Q;
		case Wex:
			return KEYCODE::KEY_W;
		case Exort:
			return KEYCODE::KEY_E;
		case Invoke:
		case InvokeUpgrade:
			return KEYCODE::KEY_R;
		}
		return -1;
	}

	struct InvokerOrbSlot
	{
		InvokerSpell	orb1;
		InvokerSpell	orb2;
		InvokerSpell	orb3;//最新的一个

		InvokerOrbSlot() : orb1(None), orb2(None), orb3(None) { }
	};
	typedef std::map<Unit*, InvokerOrbSlot> InvokerOrbState;
	static InvokerOrbState InvokerOrbStateMap;

	bool Cast( Unit *invoker, bool queued, uint32_t spellId1, uint32_t spellId2 = NULL, uint32_t spellId3 = NULL, uint32_t spellId4 = NULL )
	{
		uint32_t spellId[4];

		bool inverse = false;
		if ( invoker->currentOrder() == ACTION_STUN )
		{
			inverse = true;
		}

		spellId[0] = inverse ? spellId4 : spellId1;
		spellId[1] = inverse ? spellId3 : spellId2;
		spellId[2] = inverse ? spellId2 : spellId3;
		spellId[3] = inverse ? spellId1 : spellId4;

		bool bNotNull = false;
		//必须拥有全部技能
		if ( UseKey )
		{
			for (int i = 0; i < 4; i++)
			{
				if (spellId[i] == NULL) 
				{
					continue;
				}
				else
				{
					bNotNull = true;
					int keyCode;
					if ( -1 != ( keyCode = InvokerSpellToKeyCode(spellId[i]) ) )
					{
						if ( !HotkeyGetButton(keyCode) )
						{
							return false;
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if (spellId[i] == NULL) 
				{
					continue;
				}
				else
				{
					bNotNull = true;
					if (invoker->abilityLevel(spellId[i]) <= 0)
					{
						return false;
					}
				}
			}
		}

		if ( !bNotNull )
		{
			return false;
		}

		ActionFlag QueueFlag = queued ? Queued : ActionFlag::None;

		for (int i = 0; i < 4; i++)
		{
			switch (spellId[i])
			{
			case Quas:
				if ( UseKey )
				{
					if ( queued ) GameUIKeyPress(KEYCODE::KEY_SHIFT, true, true);
					GameUIKeyPress(KEYCODE::KEY_Q, true, true);
					GameUIKeyPress(KEYCODE::KEY_Q, false, true);
					if ( queued ) GameUIKeyPress(KEYCODE::KEY_SHIFT, false, true);
				}
				else
				{
					invoker->sendAction(ACTION_ROAR, TargetNone, 
						SmartCast | Preemt | Subgroup | QueueFlag, 
						NULL, POINT_NONE, NULL, true);
				}
				break;
			case Wex:
				if ( UseKey )
				{
					if ( queued ) GameUIKeyPress(KEYCODE::KEY_SHIFT, true, true);
					GameUIKeyPress(KEYCODE::KEY_W, true, true);
					GameUIKeyPress(KEYCODE::KEY_W, false, true);
					if ( queued ) GameUIKeyPress(KEYCODE::KEY_SHIFT, false, true);
				}
				else
				{
					invoker->sendAction(ACTION_FANOFKNIVES, TargetNone, 
						Preemt | Subgroup | QueueFlag,
						NULL, POINT_NONE, NULL, true);
				}
				break;
			case Exort:
				if ( UseKey )
				{
					if ( queued ) GameUIKeyPress(KEYCODE::KEY_SHIFT, true, true);
					GameUIKeyPress(KEYCODE::KEY_E, true, true);
					GameUIKeyPress(KEYCODE::KEY_E, false, true);
					if ( queued ) GameUIKeyPress(KEYCODE::KEY_SHIFT, false, true);
				}
				else
				{
					invoker->sendAction(ACTION_BATTLEROAR, TargetNone, 
						SmartCast | Preemt | Subgroup | QueueFlag,
						NULL, POINT_NONE, NULL, true);
				}
				break;
			case Invoke:
			case InvokeUpgrade:
				if ( UseKey )
				{
					war3::CCommandButton *btn;
					if ( NULL != ( btn = HotkeyGetButton(KEYCODE::KEY_R) ) )
					{
						Ability *abil = (Ability *)btn->commandButtonData->ability;
						if (abil->cooldownRemain() > 0)
						{
							SoundPlay("InterfaceError", NULL, 0);
						}
						else
						{
							if ( queued ) GameUIKeyPress(KEYCODE::KEY_SHIFT, true, true);
							GameUIKeyPress(KEYCODE::KEY_R, true, true);
							GameUIKeyPress(KEYCODE::KEY_R, false, true);
							if ( queued ) GameUIKeyPress(KEYCODE::KEY_SHIFT, false, true);
						}
					}					
				}
				else
				{
					if (	invoker->abilityCooldownRemain(Invoke) > 0
						||	invoker->abilityCooldownRemain(InvokeUpgrade) > 0
						)
					{
						SoundPlay("InterfaceError", NULL, 0);
					}
					else
					{
						invoker->sendAction(ACTION_HOWLOFTERROR, TargetNone, 
							SmartCast | Preemt | Subgroup | QueueFlag,
							NULL, POINT_NONE, NULL, true);
						SoundPlay("InterfaceClick", NULL, 0);
					}
				}
				break;
			default:
				break;
			}
		}

		return true;
	}

	void loopCheckSelectionState (Timer *tm)
	{
		if ( !UseSpell || tm->execCount() > 50 )
		{
			tm->destroy();
			return;
		}

		int keyCode = *tm->data<int>();
		war3::CCommandButton *btn = HotkeyGetButton(keyCode);
		if (btn)
		{
			GameUIButtonClick(btn, MOUSECODE::MOUSE_LEFT, true);
			tm->destroy();
		}
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
		if ( data->byProgramm ) return;//禁止程序的按键触发
		if ( data->ctrl ) return;
		if ( data->alt ) return;//禁止alt + 热键
		
		bool bWantQueue = data->shift;

		int keyCode = data->code;

		if (	keyCode == KEYCODE::KEY_CONTROL //禁止会引起混乱的按键，即使这些是正确的hotkey
			||	keyCode == KEYCODE::KEY_ALT
			||	keyCode == KEYCODE::KEY_SHIFT )
		{
			return;
		}

		UnitGroup *groupActive = GroupUnitsOfPlayerSelected(PlayerLocal(), true);
		if (groupActive->size() > 0)
		{
			Unit *activeUnit = groupActive->getUnit(0);
			if (	activeUnit->typeId() == InvokerTypeId
				&&	!activeUnit->testFlag(UnitFilter::ILLUSION) )
			{
				Unit *invoker = activeUnit;
				Ability *invokeAbil = NULL;
				InvokerSpell invokeSpellId = None;

				//OutputScreen(10, "invoker abils:");
				//Ability *abiltest = invoker->AbilityListHead();
				//while (abiltest)
				//{
				//	if (abiltest->order())
				//	{
				//		OutputScreen(10, "%s %s order 0x%X", abiltest->typeIdChar(), abiltest->name(), abiltest->order());
				//	}
				//	abiltest = abiltest->nextNode();
				//}

				//如果当前热键有对应按钮，什么也不做
				if ( HotkeyGetButton(keyCode) != NULL )
				{
					GroupDestroy(groupActive);
					return;
				}

				//判断合成技能是否存在
				if ( UseKey )
				{
					war3::CCommandButton *btn = HotkeyGetButton(KEYCODE::KEY_R);
					if (btn && btn->commandButtonData)
					{
						Ability *abil = (Ability *)btn->commandButtonData->ability;
						if (!(abil->flag() & 0x20))
						{
							invokeAbil = abil;
							invokeSpellId = Invoke;
						}
					}
				}
				else
				{
					invokeAbil = invoker->AbilityById(Invoke);
					invokeSpellId = Invoke;
					if ( invokeAbil == NULL )
					{
						invokeAbil = invoker->AbilityById(InvokeUpgrade);
						invokeSpellId = InvokeUpgrade;
					}
				}

				//如果合成技能不存在，什么也不做
				if ( invokeAbil == NULL )
				{
					GroupDestroy(groupActive);
					return;
				}
				else //寻找热键对应的技能
				{
					Ability *abil = invoker->AbilityListHead();
					Ability *desiredAbil = NULL;
					while ( abil != NULL )
					{
						bool bIsSpell = abil->isSpell();
						//bool bIsNotBuff = !IsAbilityBuff((war3::CAbility*)abil);	//TODO 包装
						//bool bNotHiddenAbil = ( !(abil->flag() & 0x80000000) || ((abil->flag() & 0x10000000) && (abil->flag() & 0x10)) );//不是光环以外隐藏技能(buff)
						bool bNotItem = !(abil->flag() & 0x20);//不是物品

						if ( bIsSpell && bNotItem )
						{
							if ( keyCode == abil->hotkey() )
							{
								if ( !UseSpell )
								{
									desiredAbil = abil;
								}
								else
								{
									bool bBreak = false;
									if (!bBreak)
									{
										if (  invoker->mana() < ( abil->mana() + invokeAbil->mana() ) )
										{
											SoundPlay(Skin::getPathByName("NoManaSound"), NULL, 0);	//播放没有魔法音效
											bBreak = true;
										}
									}

									if (!bBreak)
									{
										if ( abil->cooldownRemain() > 0 )
										{
											SoundPlay("InterfaceError", NULL, 0);
											bBreak = true;
										}
									}

									if (!bBreak)
									{
										desiredAbil = abil;
									}
								}
								break;
							}
						}
						abil = abil->nextNode();
					}

					if ( desiredAbil != NULL )
					{
						bool bWantCast = true;
						InvokerSpell orb1 = InvokerOrbStateMap[invoker].orb1;
						InvokerSpell orb2 = InvokerOrbStateMap[invoker].orb2;
						InvokerSpell orb3 = InvokerOrbStateMap[invoker].orb3;

						InvokerSpell cast1 = None, cast2 = None, cast3 = None, cast4 = invokeSpellId;

						switch(desiredAbil->typeId())
						{
						case ColdSnap:
							cast1 = Quas; cast2 = Quas; cast3 = Quas;
							break;
						case GhostWalk:
							cast1 = Quas; cast2 = Quas; cast3 = Wex;
							break;
						case Tornado:
							cast1 = Quas; cast2 = Wex; cast3 = Wex;
							break;
						case EMP:
							cast1 = Wex; cast2 = Wex; cast3 = Wex;
							break;
						case Alacrity:
							cast1 = Wex; cast2 = Wex; cast3 = Exort;
							break;
						case ChaosMeteor:
							cast1 = Wex; cast2 = Exort; cast3 = Exort;
							break;
						case SunStrike:
							cast1 = Exort; cast2 = Exort; cast3 = Exort;
							break;
						case ForgeSpirit:
							cast1 = Quas; cast2 = Exort; cast3 = Exort;
							break;
						case IceWall:
							cast1 = Quas; cast2 = Quas; cast3 = Exort;
							break;
						case DefeaningBlast:
							cast1 = Quas; cast2 = Wex; cast3 = Exort;
							break;
						default:
							OutputScreen(10, "Desired Abil: %s (%s)", desiredAbil->name(), desiredAbil->typeIdChar() );
							bWantCast = false;
							break;
						}

						if (bWantCast)
						{
							if ( Cast(invoker, bWantQueue, cast1, cast2, cast3, cast4) )
							{
								if ( !bWantQueue )
								{
									if ( UseSpell )
									{
										Timer *tm = GetTimer(0.005, loopCheckSelectionState, true);
										tm->setData<int>(&keyCode);
										tm->start();
									}
								}

								Cast(invoker, bWantQueue, orb1, orb2, orb3);
							}
						}
					}
				}
			}
		}
		GroupDestroy(groupActive);
	}

	void onSpell ( const Event *evt )
	{
		Unit *u = GetUnit(Jass::GetSpellAbilityUnit());
		if ( u != NULL && u->typeId() == InvokerTypeId )
		{
			uint32_t spellId = Jass::GetSpellAbilityId();
			if (spellId == Quas || spellId == Wex || spellId == Exort)
			{
				InvokerOrbStateMap[u].orb1 = InvokerOrbStateMap[u].orb2;
				InvokerOrbStateMap[u].orb2 = InvokerOrbStateMap[u].orb3;
				InvokerOrbStateMap[u].orb3 = (InvokerSpell)spellId;
			}
		}		
	}

	void CreateMenuContent(){
		VMProtectBeginVirtualization("InvokerMenuContent");

		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::MICRO_CATEGORYNAME));

		CheckBox*	CbInvoker;
		Label*		LbInvoker;

		CheckBox*	CbInvokerExecute;
		Label*		LbInvokerExecute;

		CheckBox*	CbInvokerUseKey;
		Label*		LbInvokerUseKey;

		CbInvoker = new CheckBox(
			Panel, 0.024f, NULL, &Enabled, "Invoker", "Enable", true );
		CbInvoker->setRelativePosition(
			POS_UL, Panel, POS_UL, 0.03f, -0.138f);
		LbInvoker = new Label(Panel, StringManager::GetString(STR::INVOKER_ENABLE), 0.013f);
		LbInvoker->setRelativePosition(
			POS_L, CbInvoker, POS_R, 0.01f, 0);

		CbInvokerExecute = new CheckBox(
			Panel, 0.024f, NULL, &UseSpell, "Invoker", "UseSpell", true );
		CbInvokerExecute->setRelativePosition(
			POS_UL, Panel, POS_UL, 0.2f, -0.138f);
		LbInvokerExecute = new Label(Panel, StringManager::GetString(STR::INVOKER_USE), 0.013f);
		LbInvokerExecute->setRelativePosition(
			POS_L, CbInvokerExecute, POS_R, 0.01f, 0);

		CbInvokerUseKey = new CheckBox(
			Panel, 0.024f, NULL, &UseKey, "Invoker", "UseKey", false );
		CbInvokerUseKey->setRelativePosition(
			POS_UL, Panel, POS_UL, 0.32f, -0.138f);
		LbInvokerUseKey = new Label(Panel, StringManager::GetString(STR::INVOKER_USEKEY), 0.013f);
		LbInvokerUseKey->setRelativePosition(
			POS_L, CbInvokerUseKey, POS_R, 0.01f, 0);

		VMProtectEnd();
	}


	void Init()
	{
		CreateMenuContent();

		//施法事件：记录invoker的球状态
		MainDispatcher()->listen(Jass::EVENT_PLAYER_UNIT_SPELL_EFFECT, onSpell);

		//按键事件：合成技能
		MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);
	}

	void Cleanup()
	{
		InvokerOrbStateMap.clear();
	}
}