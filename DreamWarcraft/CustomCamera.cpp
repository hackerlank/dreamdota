#include "stdafx.h"
#include "DreamDotaMain.h"
#include "Tools.h"

namespace CustomCamera {
	static bool EnableScroll;

	void ZoomOut(){
		Jass::AdjustCameraField(Jass::CAMERA_FIELD_FIELD_OF_VIEW, 10, 0.05f);
	}

	void ZoomIn(){
		Jass::AdjustCameraField(Jass::CAMERA_FIELD_FIELD_OF_VIEW, -10, 0.05f);
	}

	void ResetCamera(){
		Jass::SetCameraField(Jass::CAMERA_FIELD_FIELD_OF_VIEW, 70, 0);
		Jass::SetCameraField(Jass::CAMERA_FIELD_ANGLE_OF_ATTACK, 304, 0);
	}

	void onMouseDown (const Event *evt) {
		if(!EnableScroll) return;
		MouseEventData *data = evt->data<MouseEventData>();
		if (data->mouseCode == MOUSECODE::MOUSE_MIDDLE) {
			ResetCamera();
		}
	}

	void onMouseScroll (const Event *evt) {
		if(!EnableScroll) return;
		MouseEventScrollData *data = evt->data<MouseEventScrollData>();
		
		data->discard();
		if (data->up) {
			if (KeyIsDown(KEYCODE::KEY_CONTROL))
				Jass::SetCameraField(Jass::CAMERA_FIELD_ANGLE_OF_ATTACK, 270, 0.15f);
			else ZoomIn();
		}
		else{
			if (KeyIsDown(KEYCODE::KEY_CONTROL))
				Jass::SetCameraField(Jass::CAMERA_FIELD_ANGLE_OF_ATTACK, 304, 0.15f);
			else ZoomOut();
		}
	}

	static int ZoomOutHotkey, ZoomInHotkey, ResetCameraHotkey;

	void onKeyDown (const Event *evt) {
		KeyboardEventData *data = evt->data<KeyboardEventData>();
		if (data->code == ZoomOutHotkey)
		{
			ZoomOut();
		}
		else if (data->code == ZoomInHotkey)//ProfileFetchInt("CustomCamera", "HotkeyZoomIn", KEYCODE::KEY_ADD))
		{
			ZoomIn();
		}
		else if (data->code == ResetCameraHotkey)//ProfileFetchInt("CustomCamera", "HotkeyResetCamera", KEYCODE::KEY_DIVIDE))
		{
			ResetCamera();
		}
	}


	static CheckBox*		CbEnabled;
	static Label*			LbEnabled;

	static Label*			LbHotkeyZoomOut;
	static HotkeyButton*	BtnHotkeyZoomOut;

	static Label*			LbHotkeyZoomIn;
	static HotkeyButton*	BtnHotkeyZoomIn;

	static Label*			LbHotkeyResetCamera;
	static HotkeyButton*	BtnHotkeyResetCamera;

	void CreateMenuContent(){
		VMProtectBeginVirtualization("CustomCamera_MenuContent");

		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::UIENHANCEMENT_CATEGORYNAME), NULL);
		CbEnabled = new CheckBox(
			Panel, 
			0.024f,
			NULL,
			&EnableScroll, 
			"CustomCamera", 
			"Enable", 
			true );
		CbEnabled->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.111f);
		LbEnabled = new Label(Panel, StringManager::GetString(STR::CAMERA_ENABLE), 0.013f);
		LbEnabled->setRelativePosition(
			POS_L, 
			CbEnabled, 
			POS_R,
			0.01f, 0);

		//zoom out
		LbHotkeyZoomOut = new Label(Panel, StringManager::GetString(STR::CAMERA_HOTKEYZOOMOUT), 0.013f);
		LbHotkeyZoomOut->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.147f);
		BtnHotkeyZoomOut = new HotkeyButton(
			Panel, 
			0.09f, 0.035f,
			&ZoomOutHotkey,
			KEYCODE::KEY_SUBTRACT,
			"CustomCamera",
			"HotkeyZoomOut"	);
		BtnHotkeyZoomOut->setRelativePosition(
			POS_L,
			LbHotkeyZoomOut->getFrame(),
			POS_L,
			0.15f, 0);

		//zoom in
		LbHotkeyZoomIn = new Label(Panel, StringManager::GetString(STR::CAMERA_HOTKEYZOOMIN), 0.013f);
		LbHotkeyZoomIn->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.182f);
		BtnHotkeyZoomIn = new HotkeyButton(
			Panel, 
			0.09f, 0.035f,
			&ZoomInHotkey,
			KEYCODE::KEY_ADD,
			"CustomCamera",
			"HotkeyZoomIn"	);
		BtnHotkeyZoomIn->setRelativePosition(
			POS_L,
			LbHotkeyZoomIn->getFrame(),
			POS_L,
			0.15f, 0);

		//reset camera
		LbHotkeyResetCamera = new Label(Panel, StringManager::GetString(STR::CAMERA_HOTKEYRESETCAMERA), 0.013f);
		LbHotkeyResetCamera->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.217f);
		BtnHotkeyResetCamera = new HotkeyButton(
			Panel, 
			0.09f, 0.035f,
			&ResetCameraHotkey,
			KEYCODE::KEY_DIVIDE,
			"CustomCamera",
			"HotkeyResetCamera"	);
		BtnHotkeyResetCamera->setRelativePosition(
			POS_L,
			LbHotkeyResetCamera->getFrame(),
			POS_L,
			0.15f, 0);
		
		VMProtectEnd();
	}

	void Init() {
		VMProtectBeginVirtualization("CustomCamera");
#ifdef _FREEPLUGIN
		if (	ReplayState() == REPLAY_STATE_STREAMINGOUT
			||	Jass::GetPlayerState(Jass::Player(PlayerLocal()), Jass::PLAYER_STATE_OBSERVER)
		)
		{
#endif
			CreateMenuContent();
			MainDispatcher()->listen(EVENT_MOUSE_SCROLL, onMouseScroll);
			MainDispatcher()->listen(EVENT_MOUSE_DOWN, onMouseDown);
			MainDispatcher()->listen(EVENT_KEY_DOWN, onKeyDown);
#ifdef _FREEPLUGIN
		}
#endif
		VMProtectEnd();
	}

	void Cleanup() {

	}
}