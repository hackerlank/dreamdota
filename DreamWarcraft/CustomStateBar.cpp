#include "stdafx.h"
#include "Offsets.h"
#include "GameStructs.h"
#include "Tools.h"
#include "Jass.h"
#include "Hook.h"
#include "LayoutFrame.h"

#include "GameTime.h"
#include <math.h>

typedef std::map<war3::CUnit*, war3::CStatBar*> statBarMap;

static statBarMap UnitManaBar;

//函数
static void* Func_StatBarInit;
static void* Func_StatBarRefresh;

void StatBarInit(war3::CStatBar *statBar, int param1, int param2, int param3) {
	int push_1 = param1;
	int push_2 = param2;
	int push_3 = param3;
	__asm{
		mov ecx, statBar;
		xor edx, edx;
		push push_3;
		push push_2;
		push push_1;
		call Func_StatBarInit;
	}
}

//LayoutFrame::updatePosition
void StatBarRefresh(war3::CStatBar *statBar, int param1) { 
	int push_1 = param1;
	__asm{
		mov ecx, statBar;
		xor edx, edx;
		push push_1;
		call Func_StatBarRefresh;
	}
}

void StatBarShow(war3::CStatBar *statBar) {
	__asm{
		mov ecx, statBar;
		mov eax, [ecx];
		mov eax, [eax + 0x68];
		xor edx, edx;
		call eax;
	}
}

war3::CStatBar* CreateStatBar (war3::CUnit *u, float valueBase) {
	if (valueBase <= 0) return NULL;

	war3::CStatBar *obj = (war3::CStatBar *)malloc(sizeof(war3::CStatBar));
	StatBarInit(obj, 0, 0, 0);

	obj->owner = u;

	obj->baseSimpleFrame.baseLayoutFrame.width = 0.03f;
	obj->baseSimpleFrame.baseLayoutFrame.height = 0.004f;
	StatBarRefresh(obj, 0);
	LayoutFrame::setAbsolutePosition(obj, LayoutFrame::Position::TOP_CENTER, 0.3f, 0.4f);

	StatBarCallVtable0x64(obj);

	return obj;
}

uint32_t ColorCalc(float percent, uint8_t redFull, uint8_t greenFull, uint8_t blueFull, uint8_t redEmpty, uint8_t greenEmpty, uint8_t blueEmpty) {
	uint32_t r = (uint32_t)(redFull * percent + redEmpty * (1 - percent));
	uint32_t g = (uint32_t)(greenFull * percent + greenEmpty * (1 - percent));
	uint32_t b = (uint32_t)(blueFull * percent + blueEmpty * (1 - percent));
	return 0x000000FF | (b << 0x8) | (g << 0x10) | ( r << 0x18) ;
}

void ShowUnitStatBarReport (war3::CStatBar *hpBar, bool show) {
	war3::CUnit *u = hpBar->owner;
	if (u) {//TODO 这一段单做一个函数
		war3::CPreselectUI *ui = u->preSelectUI;
		if (ui){
			war3::CStatBar *hpBar = ui->statBarHP;
			war3::CStatBar *manaBar;
			if (!UnitManaBar.count(u)){
				uint32_t uhandle = ObjectToHandle(u);
				float manaMax = Jass::GetUnitState(uhandle, Jass::UNIT_STATE_MAX_MANA);
				UnitManaBar[u] = CreateStatBar(u, manaMax);
			}
			manaBar = UnitManaBar[u];
			if (manaBar) {
				if (show){
					
				}
				else {
					StatBarCallVtable0x64(manaBar);
				}
			}
		}
	}
	
}

void UpdateUnitStatBarReport (war3::CUnit *u);
//FIXME vtable 0x34 貌似也没什么用
void TimedUpdateUnitStatBarReport (war3::CStatBar *hpBar, float param) {
	if (!Func_StatBarInit) return;
	war3::CUnit *u = hpBar->owner;
	if (u) {
		war3::CPreselectUI *ui = u->preSelectUI;
		if (ui){
			war3::CStatBar *hpBar = ui->statBarHP;
			war3::CStatBar *manaBar;
			if (!UnitManaBar.count(u)){
				uint32_t uhandle = ObjectToHandle(u);
				float manaMax = Jass::GetUnitState(uhandle, Jass::UNIT_STATE_MAX_MANA);
				UnitManaBar[u] = CreateStatBar(u, manaMax);
			}
			manaBar = UnitManaBar[u];
			if (manaBar) {
				StatBarCallVtable0x34(manaBar, param);
				//OutputScreen(10, "StatBarCallVtable0x34(%X, %.4f)", manaBar, param);
			}
		}
	}
}

void UpdateUnitStatBarReport (war3::CUnit *u) {
	if (u) {
		war3::CPreselectUI *ui = u->preSelectUI;
		if (ui){
			war3::CStatBar *hpBar = ui->statBarHP;
			war3::CStatBar *manaBar;
			if (!UnitManaBar.count(u)){
				uint32_t uhandle = ObjectToHandle(u);
				float manaMax = Jass::GetUnitState(uhandle, Jass::UNIT_STATE_MAX_MANA);
				UnitManaBar[u] = CreateStatBar(u, manaMax);
			}
			manaBar = UnitManaBar[u];
			if (!manaBar) return;
			

			//ClearTextMessages();
			//OutputScreen(10, "time = %.3f, hpBar = %X, manaBar = %X", Time(), hpBar, manaBar);

			void* posfunc = Offset(UNIT_FRAMEPOSITION_GET);
			float xypos[2]; float rv2;
			__asm{
				mov ecx, u;
				lea edx, xypos;
				lea eax, rv2;
				push eax;
				call posfunc;
			}
			if (rv2 < 0){
				return;
			}
			//manaBar->visibleState = hpBar->visibleState;//TODO 这个好像是“是否preselect”	
			//manaBar->baseSimpleFrame.unk_88 = 0xFF990000;//这是在干吗?

			//uint32_t uhandle = ObjectToHandle(u);

			manaBar->baseSimpleFrame.baseLayoutFrame.width = hpBar->baseSimpleFrame.baseLayoutFrame.width;

			manaBar->baseSimpleFrame.baseLayoutFrame.height = hpBar->baseSimpleFrame.baseLayoutFrame.height;
			

			//float manaMax = GetUnitState(uhandle, Jass::UNIT_STATE_MAX_MANA);
			//manaBar->valuePercent = GetUnitState(uhandle, Jass::UNIT_STATE_MANA)
			//	/ manaMax;

			manaBar->unkTexture_134->baseSimpleRegion.colorRed = 0;
			manaBar->unkTexture_134->baseSimpleRegion.colorGreen = 0x40;
			manaBar->unkTexture_134->baseSimpleRegion.colorBlue = 0xFF;
			manaBar->unkTexture_134->baseSimpleRegion.colorAlpha = 0xFF;
				
			StatBarRefresh(manaBar, 0);

			StatBarCallVtable0x74(manaBar, u);
			

			float posx = xypos[0];
			float posy = xypos[1] - (hpBar->baseSimpleFrame.baseLayoutFrame.height + 0.001f);

			LayoutFrame::setAbsolutePosition(manaBar, LayoutFrame::Position::TOP_CENTER, posx, posy);

			//StatBarCallVtable0x64(manaBar);
			StatBarShow(manaBar);
			//OutputScreen(10, "time = %.4f, refresh", Time());
		}
	}
}

void CustomStatBar_Init() {
	Func_StatBarInit = Offset(STATBAR_INIT);
	Func_StatBarRefresh = Offset(STATBAR_REFRESH);

	for (statBarMap::iterator iter = UnitManaBar.begin(); iter!=UnitManaBar.end(); ++iter){
		free((*iter).second);
	}
	UnitManaBar.clear();
}

void CustomStatBar_Cleanup() {
}