/*
使用上下左右移动所选单位。（限定玩家仅选中1个可控制单位）
会自动把屏幕对准单位。

捕捉上下左右按键事件并屏蔽。
当捕捉到事件时，改写方向脉冲：判断上下左右键状态

TODO 判断地形

*/

#include "stdafx.h"
#include "DreamDotaMain.h"

namespace DirectionMove {
	static bool Enabled;

	static std::set<int> Keys;

	const float MoveDistance = 512.0f;
	const float UpdatePeriod = 0.5f;

	bool enabled() {
		//return ProfileFetchInt("DirectionMove", "Enable", 0) > 0;
		return Enabled;
	}

	bool keyCodeAllowed(int keyCode) {
		switch(keyCode){
		case KEYCODE::KEY_UP:		return true;
		case KEYCODE::KEY_DOWN:		return true;
		case KEYCODE::KEY_LEFT:		return true;
		case KEYCODE::KEY_RIGHT:	return true;
		}
		return false;
	}

	int oppositeDirection(int keyCode) {
		switch(keyCode){
		case KEYCODE::KEY_UP:		return KEYCODE::KEY_DOWN;
		case KEYCODE::KEY_DOWN:		return KEYCODE::KEY_UP;
		case KEYCODE::KEY_LEFT:		return KEYCODE::KEY_RIGHT;
		case KEYCODE::KEY_RIGHT:	return KEYCODE::KEY_LEFT;
		}
		return -1;
	}

	void updateDirection (bool stop) {
		if (!stop && !Keys.size()) return;
		UnitGroup *g = GroupUnitsOfPlayerSelected(PlayerLocal(), false);
		if (g->size() == 1) {
			Unit *u = g->getUnit(0);
			if (u->testFlag(UnitFilter::CONTROLLABLE, PlayerLocal())){
				if (stop){
					Jass::PanCameraToTimed(Jass::GetCameraTargetPositionX(), Jass::GetCameraTargetPositionY(), 0);
					u->sendAction(
						ACTION_STOP,
						TargetNone,
						None,
						NULL,
						POINT_NONE,
						NULL,
						true,
						false
					);
					return;
				}
				Point p = u->position(), pDest = p;
				bool up, down, left, right, stop = false;
				up		= Keys.count(KEYCODE::KEY_UP)>0;
				down	= Keys.count(KEYCODE::KEY_DOWN)>0;
				left	= Keys.count(KEYCODE::KEY_LEFT)>0;
				right	= Keys.count(KEYCODE::KEY_RIGHT)>0;
				if (right && up){
					pDest = p.offsetPolarDeg(MoveDistance, 45);
				}
				else if (left && up){
					pDest = p.offsetPolarDeg(MoveDistance, 135);
				}
				else if (left && down){
					pDest = p.offsetPolarDeg(MoveDistance, 225);
				}
				else if (right && down){
					pDest = p.offsetPolarDeg(MoveDistance, 315);
				}
				else if (right){
					pDest = p.offsetPolarDeg(MoveDistance, 0);
				}
				else if (up){
					pDest = p.offsetPolarDeg(MoveDistance, 90);
				}
				else if (left){
					pDest = p.offsetPolarDeg(MoveDistance, 180);
				}
				else if (down){
					pDest = p.offsetPolarDeg(MoveDistance, 270);
				}
				else {
					return;
				}
				Jass::SetCameraTargetController(u->handleId(), 0, 0, false);
				u->sendAction(
					ACTION_SMART,
					Target,
					None,
					NULL,
					pDest,
					NULL,
					true,
					false
				);//假造玩家操作
			}
		}
		GroupDestroy(g);
	}

	void onTimer (Timer *tm) {
		if (enabled()){
			updateDirection(false);
		}
	}

	void onKeyDown (const Event *evt) {
		if (enabled()){
			KeyboardEventData *data = evt->data<KeyboardEventData>();
			int keyCode = data->code;
			if (keyCodeAllowed(keyCode)){
				data->discard();	 DiscardCurrentEvent();
				if (!Keys.count(keyCode)){
					Keys.insert(keyCode);
					Keys.erase(oppositeDirection(keyCode));
					updateDirection(false);
				}
			}
		}
	}

	void onKeyUp (const Event *evt) {
		if (enabled()){
			KeyboardEventData *data = evt->data<KeyboardEventData>();
			int keyCode = data->code;
			if (keyCodeAllowed(keyCode)){
				data->discard(); DiscardCurrentEvent();
				Keys.erase(keyCode);
				if (!Keys.size())	updateDirection(true);
				else	updateDirection(false);
			}
		}
	}

	void onFocus (const Event *evt) {
		Keys.clear();
	}

	void CreateMenuContent(){
		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::MICRO_CATEGORYNAME));

		CheckBox*	CbDirectionMove;
		Label*		LbDirectionMove;

		CbDirectionMove = new CheckBox(
			Panel, 
			0.024f, 
			NULL, 
			&Enabled,
			"DirectionMove", 
			"Enable", 
			false );
		CbDirectionMove->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.084f);
		LbDirectionMove = new Label(Panel, StringManager::GetString(STR::DIRECTIONMOVE_ENABLE), 0.013f);
		LbDirectionMove->setRelativePosition(
			POS_L, 
			CbDirectionMove, 
			POS_R,
			0.01f, 0);
	}

	void Init(){
		CreateMenuContent();

		Keys.clear();
		MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);
		MainDispatcher()->listen(EVENT_KEY_UP, onKeyUp);
		MainDispatcher()->listen(EVENT_FOCUS, onFocus);
		GetTimer(UpdatePeriod, onTimer, true)->start();
	}

	void Cleanup(){
	}
}