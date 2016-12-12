#include "stdafx.h"
#include "GameEventObserver.h"
#include "Profile.h"
#include "DreamDotaMain.h"
#include <VMP.h>
#include "JassNativeHook.h"

namespace MapHack {
	void Update() {
		VMProtectBeginVirtualization("MapHackUpdate");
		bool mainmap_removeFog	= ProfileFetchInt("MapHack", "MainMapRemoveFog", 1) > 0;
		bool mainmap_showunit	= ProfileFetchInt("MapHack", "MainMapShowUnit", 1) > 0;
		bool minimap_showunit	= ProfileFetchInt("MapHack", "MiniMapShowUnit", 1) > 0;
		bool bypass_AH	= ProfileFetchInt("MapHack", "BypassAH", 0) > 0;

		MapHackSet(
			mainmap_removeFog
			,mainmap_showunit
			,minimap_showunit
			,bypass_AH
			//...
		);
		VMProtectEnd();
	}

	static CheckBox*	CbMainMapRemoveFog;
	static Label*		LbMainMapRemoveFog;

	static CheckBox*	CbMainMapShowUnit;
	static Label*		LbMainMapShowUnit;

	static CheckBox*	CbMiniMapShowUnit;
	static Label*		LbMiniMapShowUnit;

	static CheckBox*	CbBypassAH;
	static Label*		LbBypassAH;

	static void CheckBoxCallback(CheckBox* cb, bool flag){
		Update();
	}

	void CreateMenuContent() {

		UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::MAPHACK_CATEGORYNAME));

		CbMainMapRemoveFog = new CheckBox(Panel);
		CbMainMapRemoveFog->bindProfile("MapHack", "MainMapRemoveFog", true);
		CbMainMapRemoveFog->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.03f);
		CbMainMapRemoveFog->bindCallback(CheckBoxCallback);
		LbMainMapRemoveFog = new Label(Panel, StringManager::GetString(STR::MAPHACK_REMOVEFOGMAIN), 0.013f);
		LbMainMapRemoveFog->setRelativePosition(
			POS_L, 
			CbMainMapRemoveFog->getFrame(), 
			POS_R,
			0.01f, 0);

		CbMainMapShowUnit = new CheckBox(Panel);
		CbMainMapShowUnit->bindProfile("MapHack", "MainMapShowUnit", true);
		CbMainMapShowUnit->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.057f);
		CbMainMapShowUnit->bindCallback(CheckBoxCallback);
		LbMainMapShowUnit = new Label(Panel, StringManager::GetString(STR::MAPHACK_SHOWUNITMAINMAP), 0.013f);
		LbMainMapShowUnit->setRelativePosition(
			POS_L, 
			CbMainMapShowUnit->getFrame(), 
			POS_R,
			0.01f, 0);

		CbMiniMapShowUnit = new CheckBox(Panel);
		CbMiniMapShowUnit->bindProfile("MapHack", "MiniMapShowUnit", true);
		CbMiniMapShowUnit->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.084f);
		CbMiniMapShowUnit->bindCallback(CheckBoxCallback);
		LbMiniMapShowUnit = new Label(Panel, StringManager::GetString(STR::MAPHACK_SHOWUNITMINIMAP), 0.013f);
		LbMiniMapShowUnit->setRelativePosition(
			POS_L, 
			CbMiniMapShowUnit->getFrame(), 
			POS_R,
			0.01f, 0);

		CbBypassAH = new CheckBox(Panel);
		CbBypassAH->bindProfile("MapHack", "BypassAH", false);
		CbBypassAH->setRelativePosition(
			POS_UL,
			Panel,
			POS_UL,
			0.03f, -0.111f);
		CbBypassAH->bindCallback(CheckBoxCallback);
		LbBypassAH = new Label(Panel, StringManager::GetString(STR::MAPHACK_BYPASSAH), 0.013f);
		LbBypassAH->setRelativePosition(
			POS_L, 
			CbBypassAH->getFrame(), 
			POS_R,
			0.01f, 0);
	}

	static bool IsPointVisible(float x, float y) {
		return Jass::IsVisibleToPlayer(x, y, Jass::GetLocalPlayer());
	}
	
	static bool MapHackPaused = false;

	static void PauseMapHack(bool v) {
		//OutputDebug("PauseMaphack %s", v ? "true" : "false");
		if (v) {
			MapHackOptions options;
			GetCurrentMapHackOptions(&options);
			MapHackSet(
				false, //options.MainMapRemoveFog, 
				false, 
				false, //options.MiniMapShowUnit, 
				false //options.BypassAH
			);
			
		} else {
			Update();
		}
		MapHackPaused = v;
	}

	JASS_PROTOTYPE_SetCameraTargetController OrgSetCameraTargetController;
	static void DetourSetCameraTargetController(handle whichUnit, float* xoffset, float* yoffset, bool inheritOrientation) {
		bool visible = IsPointVisible(Jass::GetUnitX(whichUnit) + *xoffset, Jass::GetUnitY(whichUnit) + *yoffset);
		if (!visible && !MapHackPaused) {
			PauseMapHack(true);
		}
		
		aero::generic_c_call<void>(OrgSetCameraTargetController, whichUnit, xoffset, yoffset, inheritOrientation);

		if (visible && MapHackPaused) {
			PauseMapHack(false);
		}
	}

	JASS_PROTOTYPE_ResetToGameCamera OrgResetToGameCamera;
	static void DetourResetToGameCamera(float* duration) {
		aero::generic_c_call<void>(OrgResetToGameCamera, duration);

		if (MapHackPaused) {
			PauseMapHack(false);
		}
	}

	JASS_PROTOTYPE_PanCameraTo OrgPanCameraTo;
	static void DetourPanCameraTo(float* x, float* y) {
		bool visible = IsPointVisible(*x, *y);
		if (!visible && !MapHackPaused) {
			PauseMapHack(true);
		}

		aero::generic_c_call<void>(OrgPanCameraTo, x, y);

		if (visible && MapHackPaused) {
			PauseMapHack(false);
		}
	}

	JASS_PROTOTYPE_PanCameraToTimed OrgPanCameraToTimed;
	static void DetourPanCameraToTimed(float* x, float* y, float* duration) {
		bool visible = IsPointVisible(*x, *y);

		if (!visible && !MapHackPaused) {
			PauseMapHack(true);
		}

		aero::generic_c_call<void>(OrgPanCameraToTimed, x, y, duration);

		if (visible && MapHackPaused) {
			PauseMapHack(false);
		}
	}

	JASS_PROTOTYPE_AddLightningEx OrgAddLightningEx;
	static handle DetourAddLightningEx(string a1, bool a2, float* x1, float* y1, float* z1, float* x2, float* y2, float* z2) {
		bool visible = IsPointVisible(*x1, *y1) && IsPointVisible(*x2, *y2);
		if (!visible) {
			return 0;
		} else
			return aero::generic_c_call<handle>(OrgAddLightningEx, a1, a2, x1, y1, z1, x2, y2, z2);
	}

	static bool DisableSelectUnit = false;
	JASS_PROTOTYPE_SelectUnit OrgSelectUnit;
	void DetourSelectUnit(handle unit, bool v) {
		//OutputDebug("[%u]SelectUnit %s", TimeRaw(), v ? "t" : "f");
		if (!DisableSelectUnit)
			aero::generic_c_call<void>(OrgSelectUnit, unit, v);
	}

	void onSelected(const Event* evt) {
		//OutputDebug("[%u]Selected!", TimeRaw());
	}

	void onDeselected(const Event* evt) {
		//OutputDebug("[%u]Deselected!", TimeRaw());
	}

	void onMHDetectWaitCompleted(Timer* tm) {
		//OutputDebug("[%u]Timer Restore!", TimeRaw());
		DisableSelectUnit = false;
	}

	JASS_PROTOTYPE_SetFogStateRadius OrgSetFogStateRadius;
	void DetourSetFogStateRadius(handle player, handle v, float *x, float *y, float* r, bool share) {
		if (player == Jass::GetLocalPlayer() && !DisableSelectUnit) {
			//OutputDebug("[%u]Disable SelectUnit!", TimeRaw());
			DisableSelectUnit = true;
			GetTimer(0.5, onMHDetectWaitCompleted)->start();
		}
		aero::generic_c_call<void>(OrgSetFogStateRadius, player, v, x, y, r, share);
	}

	void Init() {
		//MainDispatcher()->listen(Jass::EVENT_PLAYER_UNIT_SELECTED, onSelected);
		//MainDispatcher()->listen(Jass::EVENT_PLAYER_UNIT_DESELECTED, onDeselected);

		OrgSetCameraTargetController = SetJassNativeDetour(SetCameraTargetController, DetourSetCameraTargetController);
		OrgResetToGameCamera = SetJassNativeDetour(ResetToGameCamera, DetourResetToGameCamera);
		OrgPanCameraTo = SetJassNativeDetour(PanCameraTo, DetourPanCameraTo);
		OrgPanCameraToTimed = SetJassNativeDetour(PanCameraToTimed, DetourPanCameraToTimed);
		OrgAddLightningEx = SetJassNativeDetour(AddLightningEx, DetourAddLightningEx);
		OrgSelectUnit = SetJassNativeDetour(SelectUnit, DetourSelectUnit);
		OrgSetFogStateRadius = SetJassNativeDetour(SetFogStateRadius, DetourSetFogStateRadius);

		CreateMenuContent();
		Update();
	}

	void Cleanup() {
	}
}