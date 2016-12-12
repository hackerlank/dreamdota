#include "stdafx.h"
#include "HotkeyButton.h"
#include "Game.h"
#include "Profile.h"

static std::set<HotkeyButton *> HotkeyButtonSet;

void CallbackHotkeyButton(Button *btn) {
	HotkeyButton *btnhot = (HotkeyButton *)btn;
	btnhot->toggleEnteringHotkey();
	if (btnhot->isEnteringHotkey()){
		//set text to "..."
		btnhot->setText("...");
	}
	else {
		//set back text
		btnhot->setKey(btnhot->getKey());
	}
}

void DetectHotkey (const Event *evt) {

	KeyboardEventData *data = evt->data<KeyboardEventData>();
	//OutputScreen(10, "langid = %d, key = 0x%X, name = %s", (int)LOWORD((DWORD)GetKeyboardLayout(0)), data->code, KEYCODE::getStr(data->code));
	for (std::set<HotkeyButton *>::iterator iter = HotkeyButtonSet.begin();
		iter != HotkeyButtonSet.end(); ++iter)
	{
		if ((*iter)->isEnteringHotkey()){
			(*iter)->toggleEnteringHotkey();
			(*iter)->setKey(data->code);
			SoundPlay("GlueScreenClick", NULL, 0);
			if ((*iter)->hotkeyButtonCallback) (*iter)->hotkeyButtonCallback((*iter));
			data->discard();	 DiscardCurrentEvent();
			break;
		}
	}
}

void HotkeyButton::setKey(int keyCode){
	std::string str;
	str+="|cffffcc00";
	str+=KEYCODE::
		//ToString(keyCode);
		getStr(keyCode);
	str+="|r";
	this->_hotkey = keyCode;
	this->setText(str.c_str());
	if (_profileApp && _profileKey) ProfileSetInt(_profileApp, _profileKey, keyCode);
	if (_pVarHotkey) *(_pVarHotkey) = keyCode;
}

HotkeyButton::HotkeyButton(
		UISimpleFrame*			parent,
		float					width,
		float					height,
		int*					hotkeyVar,
		int						defaultHotkey,
		char*					profileApp,
		char*					profileKey,
		ButtonCallback			callback,
		bool					noSurface
) : Button(parent, width, height, UISimpleButton::MOUSEBUTTON_LEFT, UISimpleButton::STATE_ENABLED, CallbackHotkeyButton, NULL, false, noSurface),
_hotkey(NULL), _enteringHotkey(false), _pVarHotkey(hotkeyVar), _profileApp(profileApp), _profileKey(profileKey),
hotkeyButtonCallback(callback)
{
	this->setKey(ProfileFetchInt(profileApp, profileKey, defaultHotkey));
	HotkeyButtonSet.insert(this);
}

HotkeyButton::~HotkeyButton(){
}

void HotkeyButton::Init(){
	HotkeyButtonSet.clear();
	MainDispatcher()->listen(EVENT_KEY_DOWN, DetectHotkey);
}

void HotkeyButton::Cleanup(){
	HotkeyButtonSet.clear();
}