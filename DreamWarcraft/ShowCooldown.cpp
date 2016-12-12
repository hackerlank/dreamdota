#include "stdafx.h"
#include "DreamDotaMain.h"

namespace ShowCooldown
{
	static bool Enabled;
	static std::map<war3::CCommandButton*, Label*> ButtonLabelMap;

	void CleanButtonLabelMap ( )
	{
		for (static std::map<war3::CCommandButton*, Label*>::iterator iter = ButtonLabelMap.begin();
			iter != ButtonLabelMap.end(); ++iter)
		{
			if (iter->second) delete iter->second;
		}
		ButtonLabelMap.clear();
	}

	void onTimer ( Timer *tm )
	{
		if (!Enabled) 
		{
			CleanButtonLabelMap();
			return;
		}
		war3::CSimpleTop *simpleTop = *(war3::CSimpleTop **)Offset(GLOBAL_SIMPLETOP);
		war3::CCommandButton *button = NULL;
		UISimpleFrame frm;
		war3::CAbility *abil;
		Label *lb;
		int cd;
		if (!simpleTop) 
		{
			return;
		}
		for (uint32_t i = 0; i < simpleTop->buttonListArrayCount; i++) 
		{
			button = (war3::CCommandButton *)simpleTop->pButtonListArray->pButtonLists[i]->firstButton;
			if (!button || !IsCommandButton((war3::CSimpleButton*)button))
			{
				continue;
			}
			frm = UISimpleFrame(button);
			if ( ButtonLabelMap.count(button) )
			{
				lb = ButtonLabelMap[button];
			}
			else
			{
				lb = new Label(&frm, "", 0.013f, Color::WHITE);
				ButtonLabelMap[button] = lb;
				lb->setRelativePosition(POS_C, &frm, POS_C);
			}
			if (button->commandButtonData)
			{
				abil = button->commandButtonData->ability;
				if (abil)
				{
					if (AgentHasAncestor(AgentTypeIdGet((war3::CAgent*)abil), 'AAbt'))
					{
						cd = (int)ceil((GetAbility(abil)->cooldownRemain()));	
						
						if (cd > 0)
						{
							lb->show(true);//TODO
							if (cd >= 60)
							{
								int minute = cd / 60;
								int second = cd % 60;
								lb->setText("%d:%02d", minute, second);
							}
							else
							{
								lb->setText("%d", cd);
							}
									
							continue;
						}
					}
				}
			}
			lb->show(false);
		}
	}

	static CheckBox*		CbEnabled;
	static Label*			LbEnabled;

	void CreateMenuContent()
	{
		VMProtectBeginVirtualization("ShowCooldownCreateMenuContent");
		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::UIENHANCEMENT_CATEGORYNAME));
		CbEnabled = new CheckBox(
			Panel, 
			0.024f,
			NULL,
			&Enabled, 
			"ShowCooldown", 
			"Enable", 
			true );
		CbEnabled->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.247f);

		LbEnabled = new Label(Panel, StringManager::GetString(STR::COOLDOWN_ENABLE), 0.013f);
		LbEnabled->setRelativePosition(
			POS_L, 
			CbEnabled, 
			POS_R,
			0.01f, 0);

		VMProtectEnd();
	}

	void Init()
	{
		CreateMenuContent();
		GetTimer(0.05f, onTimer, true)->start();
	}

	void Cleanup()
	{
		CleanButtonLabelMap();
	}
}