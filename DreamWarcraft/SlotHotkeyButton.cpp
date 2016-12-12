#include "stdafx.h"
#include "SlotHotkeyButton.h"
#include "Profile.h"

static void show(SlotHotkeyButton *btn){
	(btn)->showText(true);
	(btn)->getCloseButton()->show();
	if (btn->stateProfileApp && btn->stateProfileKey){
		ProfileSetInt(btn->stateProfileApp, btn->stateProfileKey, 1);
	}
	btn->isHidden = false;
}

static void hide(SlotHotkeyButton *btn){
	btn->showText(false);
	btn->getCloseButton()->hide();
	if (btn->stateProfileApp && btn->stateProfileKey){
		ProfileSetInt(btn->stateProfileApp, btn->stateProfileKey, 0);
	}
	btn->isHidden = true;
}

void SlotHotkeyCloseButtonEventHandler(Observer *ob, uint32_t evtId){
	SlotHotkeyButton *btn = *(ob->data<SlotHotkeyButton*>());
	switch (evtId) {
	case EVENT_CLICK:
		hide(btn);
		break;
	default: break;
	}
}

void SlotHotkeyCallback(Button *btn){
	show((SlotHotkeyButton *)btn);
}

SlotHotkeyButton::SlotHotkeyButton(
		UISimpleFrame*			parent,
		float					width,
		float					height,
		int*					hotkeyVar,
		int						defaultHotkey,
		char*					profileApp,
		char*					profileKey,
		char*					enabledProfileKey
):
	HotkeyButton(parent, width, height, hotkeyVar, defaultHotkey, profileApp, profileKey, SlotHotkeyCallback, true)
{
	this->isHidden = false;
	this->stateProfileApp = profileApp;
	this->stateProfileKey = enabledProfileKey;
	
	UISimpleButton *sb = this->getButton();

	this->btnClose = UISimpleButton::Create(
		sb, 
		width/3.f, height/3.f,
		"ReplaceableTextures\\CommandButtonsDisabled\\DISBTNCancel.blp",//disabled
		"ReplaceableTextures\\CommandButtons\\BTNCancel.blp",//enabled
		"ReplaceableTextures\\CommandButtons\\BTNCancel.blp",//pushed
		UISimpleButton::MOUSEBUTTON_LEFT,
		UISimpleButton::STATE_ENABLED
	);
	this->btnClose->setRelativePosition(
		UISimpleButton::POSITION_TOP_RIGHT,
		sb,
		UISimpleButton::POSITION_TOP_RIGHT,
		-0.001f, -0.001f);
	this->btnClose->show();

	SlotHotkeyButton *Obj = this;
	this->obsBtnClose = Observer::Create(SlotHotkeyCloseButtonEventHandler);
	this->obsBtnClose->setData<SlotHotkeyButton*>(&Obj);
	this->btnClose->setClickEventObserver(EVENT_CLICK, this->obsBtnClose);

	if (stateProfileApp && stateProfileKey){
		ProfileGetInt(stateProfileApp, stateProfileKey, 0) > 0 ?
			show(this) : hide(this);
	}
}

SlotHotkeyButton::~SlotHotkeyButton(){
	Observer::Destroy(this->obsBtnClose);
	UISimpleButton::Destroy(this->btnClose);
}

void SlotHotkeyButton::enable(bool flag){
	this->Button::enable(flag);
	if (this->isHidden) {
		hide(this);
	}
	else{
		show(this);
	}
	this->getCloseButton()->setState(flag ? UISimpleButton::STATE_ENABLED : UISimpleButton::STATE_DISABLED);
}