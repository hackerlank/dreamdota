#include "stdafx.h"
#include "OptionMenu.h"
#include "Game.h"
#include "Profile.h"
#include "../DreamAuth2/StringManager.h"
#include "War3Window.h"

const float OPTIONMENU_WIDTH = 0.6f;
const float OPTIONMENU_HEIGHT = 0.375f;
const float OPTIONMENU_CENTER_X = 0.4f;
const float OPTIONMENU_CENTER_Y = 0.375f;
const float NAVIGATION_WIDTH = 0.125f;

OptionMenu::OptionMenu(){
	shown = false;

	bool classic = ProfileFetchInt("Misc", "MenuClassicStyle", 1) > 0;
	mainFrame = UISimpleFrame::Create(UISimpleFrame::GetGameSimpleConsole());
	mainFrame->setBackground(Skin::getPathByName(classic ? "EscMenuBackground" : "EscMenuButtonBackground"));
	mainFrame->setBorder(Skin::getPathByName(classic ? "EscMenuBorder" : "EscMenuButtonBorder"));
	mainFrame->setBorderWidth(classic ? 0.048f : 0.015f);
	mainFrame->setPadding(classic ? 0.01f : 0.005f);
	mainFrame->applyTextureSettings();
	mainFrame->setWidth(OPTIONMENU_WIDTH);
	mainFrame->setHeight(OPTIONMENU_HEIGHT);
	mainFrame->setAbsolutePosition(UILayoutFrame::POSITION_CENTER, OPTIONMENU_CENTER_X, OPTIONMENU_CENTER_Y);
	mainFrame->applyPosition();
	mainFrame->hide();

	navigationFrame = UISimpleFrame::Create(mainFrame);
	navigationFrame->setWidth(NAVIGATION_WIDTH);
	navigationFrame->setHeight(OPTIONMENU_HEIGHT);
	navigationFrame->setRelativePosition(POS_UL, mainFrame, POS_UL, 0, 0);
	navigationFrame->applyPosition();
	navigationFrame->show();

	contentFrame = UISimpleFrame::Create(mainFrame);
	contentFrame->setWidth(OPTIONMENU_WIDTH - NAVIGATION_WIDTH);
	contentFrame->setHeight(OPTIONMENU_HEIGHT);
	contentFrame->setRelativePosition(UILayoutFrame::POSITION_TOP_RIGHT, mainFrame, UILayoutFrame::POSITION_TOP_RIGHT, 0, 0);
	contentFrame->applyPosition();
	contentFrame->show();
}

static std::map<Button*, UISimpleFrame*> OptionMenuCategories;//全局保存按钮到frame映射

OptionMenu::~OptionMenu(){
	UISimpleFrame::Destroy(contentFrame);
	UISimpleFrame::Destroy(navigationFrame);
	UISimpleFrame::Destroy(mainFrame);
	Button* b = NULL; UISimpleFrame *f = NULL;
	for (CategoryNameButtonMapType::iterator iter = categoryNames.begin();
		iter != categoryNames.end();++iter)
	{
		b = iter->second;
		f = OptionMenuCategories.count(b)>0 ? OptionMenuCategories[b] : NULL;
		if(b) {
			OptionMenuCategories.erase(b);
			delete (b);
		}
		if(f) UISimpleFrame::Destroy(f);
	}
	categoryNames.clear();
}



void OptionMenuButtonCallback (Button *button) {//全局处理按钮按下
	if (OptionMenuCategories.count(button)){
		UISimpleFrame* frame = OptionMenuCategories[button];
		std::map<Button*, UISimpleFrame*>::iterator iter;
		for (iter = OptionMenuCategories.begin(); iter != OptionMenuCategories.end(); ++iter){
			if (iter->second != frame){
				iter->first->getCaption()->setTextColor(Color::GOLD);
				iter->second->hide();
			}
			else{
				iter->first->getCaption()->setTextColor(Color::WHITE);
				iter->second->show();
			}
		}
	}
}

void OptionMenu::show(bool flag) {
	if (flag) this->mainFrame->show();
	else this->mainFrame->hide();
	shown = flag;
}

bool OptionMenu::isShown(){
	return this->shown;
}

void OptionMenu::toggleState(){
	if (this)
	{
		show(!this->isShown());
		//MUSTDO 暂时解决菜单不正确的方法
		UI_Refresh();
	}
}

UISimpleFrame* OptionMenu::category(const char* categoryName, const char* tooltip) {
	//如果已有则返回大项对应frame，否则创建大项
	if (categoryNames.count(categoryName)){
		return OptionMenuCategories[categoryNames[categoryName]];
	}
	else {
		//创建按钮
		Button* b = new Button(navigationFrame, 
			0.114f, 0.035f, 
			UISimpleButton::MOUSEBUTTON_LEFT, 
			UISimpleButton::STATE_ENABLED,
			OptionMenuButtonCallback,
			tooltip,
			true
		);
		b->setText(categoryName);

		//自动调整按钮的位置
		//OutputScreen(10, "catCount = %d, y = %.4f", categoryNames.size(), -(0.035f*categoryNames.size()));
		b->setRelativePosition(POS_UL, navigationFrame, POS_UL,
			0.03f,
			-(0.035f*categoryNames.size() + 0.03f)
			);
		b->applyPosition();

		//创建名字到按钮的映射
		categoryNames[categoryName] = b;

		//创建frame
		UISimpleFrame* f = UISimpleFrame::Create(contentFrame);
		f->setWidth(contentFrame->width());
		f->setHeight(contentFrame->height());
		f->setRelativePosition(UILayoutFrame::POSITION_CENTER, contentFrame, UILayoutFrame::POSITION_CENTER, 0, 0);
		if (categoryNames.size() > 1) f->hide();

		//按钮到frame映射
		OptionMenuCategories[b] = f;

		return f;
	}
}

static OptionMenu *pMenu;
static int MenuHotkey;

OptionMenu* DefaultOptionMenuGet(){
	return pMenu;
}

#include "Input.h"
static void onOptionMenuKeyDown(const Event* evt){

	KeyboardEventData *data = evt->data<KeyboardEventData>();
	int keyCode = data->code;
	if (keyCode == MenuHotkey
		&& !data->shift
		&& !data->ctrl
		&& !data->alt
		&& !data->byProgramm
	){
		DefaultOptionMenuGet()->toggleState();
		SoundPlay("GlueScreenClick", NULL, 0);
	}
	else if (keyCode == KEYCODE::KEY_ESC
		&& !data->shift
		&& !data->ctrl
		&& !data->alt
		&& !data->byProgramm
		&& DefaultOptionMenuGet()->isShown()
	){
		DefaultOptionMenuGet()->toggleState();
		SoundPlay("GlueScreenClick", NULL, 0);
	}
}

void CallbackCbForceRatio(CheckBox* cb, bool flag){
	ToggleFullscreen();ToggleFullscreen();
}

static void ButtonToggleMenuCallback (Button *btn){
	DefaultOptionMenuGet()->toggleState();
}

static Button*	MenuButton;
void ShowMenuButtonCallback(CheckBox *cb, bool flag)
{
	MenuButton->setAbsolutePosition(UILayoutFrame::POSITION_BOTTOM_RIGHT, 
		flag ? 0.8f : 1.5f, 
		flag ? 0.155f : 1.5f
	);
	MenuButton->applyPosition();
}

static void CreateMenuContent(){
	//F7按钮
	MenuButton = new Button(
		UISimpleFrame::GetGameSimpleConsole(), 
		0.08f, 0.027f, 
		UISimpleButton::MOUSEBUTTON_LEFT, 
		UISimpleButton::STATE_ENABLED,
		ButtonToggleMenuCallback,
		NULL,
		false,
		false,
		0.011f
	);
	MenuButton->setText(StringManager::GetString(STR::MENU_BUTTON));
	MenuButton->setAbsolutePosition(UILayoutFrame::POSITION_BOTTOM_RIGHT,
		0.8f, 0.155f);
	if (!ProfileFetchBool("Menu", "ShowButton", true))
	{
		MenuButton->setAbsolutePosition(UILayoutFrame::POSITION_BOTTOM_RIGHT, 1.5f, 1.5f);
	}

	//建立"Misc"项
	UISimpleFrame* Panel = DefaultOptionMenuGet()->category(StringManager::GetString(STR::MISC_CATEGORYNAME), NULL);

	CheckBox*		CbSwitchWindowed;
	Label*			LbSwitchWindowed;

	CheckBox*		CbForceRatio;
	Label*			LbForceRatio;

	CheckBox*		CbKeyRepeat;
	Label*			LbKeyRepeat;

	CheckBox*		CbShowMenuButton;
	Label*			LbShowMenuButton;

	HotkeyButton*	BtnMenuHotkey;
	Label*			LbMenuHotkey;

	HotkeyButton*	BtnLockMouseHotkey;
	Label*			LbLockMouseHotkey;
	

	//enable switch (alt enter)
	CbSwitchWindowed = new CheckBox( 
		Panel, 0.024f, NULL, NULL, "Misc", "AllowSwitchWindowed", true );
	CbSwitchWindowed->setRelativePosition(
		POS_UL, Panel, POS_UL, 0.03f, -0.03f);
	LbSwitchWindowed = new Label(Panel, StringManager::GetString(STR::ENABLESWITCHWINDOWED), 0.013f);
	LbSwitchWindowed->setRelativePosition(
		POS_L, 
		CbSwitchWindowed, 
		POS_R,
		0.01f, 0);

	//enable force ratio 4:3
	CbForceRatio = new CheckBox(
		Panel, 0.024f, CallbackCbForceRatio, NULL, "Misc", "WindowKeepRatio", false);
	CbForceRatio->setRelativePosition(
		POS_UL,
		Panel,
		POS_UL,
		0.03f, -0.057f);
	LbForceRatio = new Label(Panel, StringManager::GetString(STR::ENABLEFORCERATIO), 0.013f);
	LbForceRatio->setRelativePosition(POS_L, CbForceRatio, POS_R, 0.01f, 0);

	//key repeat
	CbKeyRepeat = new CheckBox(
		Panel, 0.024f, NULL, NULL, "KeyAutoRepeat", "Enable", true);
	CbKeyRepeat->setRelativePosition(
		POS_UL, Panel, POS_UL,
		0.03f, -0.084f);
	LbKeyRepeat = new Label(Panel, StringManager::GetString(STR::KEYREPEAT_ENABLE), 0.013f);
	LbKeyRepeat->setRelativePosition(
		POS_L, 
		CbKeyRepeat->getFrame(), 
		POS_R,
		0.01f, 0);

	//show menu button
	CbShowMenuButton = new CheckBox(
		Panel, 0.024f, ShowMenuButtonCallback, NULL, "Menu", "ShowButton", true);
	CbShowMenuButton->setRelativePosition(
		POS_UL, Panel, POS_UL,
		0.03f, -0.111f);
	LbShowMenuButton = new Label(Panel, StringManager::GetString(STR::MISC_MENUSHOWBUTTON), 0.013f);
	LbShowMenuButton->setRelativePosition(
		POS_L, 
		CbShowMenuButton, 
		POS_R,
		0.01f, 0);

	//menu hotkey
	LbMenuHotkey = new Label(Panel, StringManager::GetString(STR::MISC_MENUHOTKEYBUTTON), 0.013f);
	LbMenuHotkey->setRelativePosition(
		POS_UL,
		Panel,
		POS_UL,
		0.03f, -0.147f);
	BtnMenuHotkey = new HotkeyButton(
		Panel, 
		0.09f, 0.035f,
		&MenuHotkey,
		KEYCODE::KEY_F7,
		"Menu",
		"Hotkey"	);
	BtnMenuHotkey->setRelativePosition(
		POS_L,
		LbMenuHotkey->getFrame(),
		POS_L,
		0.15f, 0);

	//lock mouse
	LbLockMouseHotkey = new Label(Panel, StringManager::GetString(STR::MISC_LOCKMOUSEHOTKEYBUTTON), 0.013f);
	LbLockMouseHotkey->setRelativePosition(
		POS_UL,
		Panel,
		POS_UL,
		0.03f, -0.182f);
	BtnLockMouseHotkey = new HotkeyButton(
		Panel, 
		0.09f, 0.035f,
		NULL,
		KEYCODE::KEY_SCROLLLOCK,
		"Misc",
		"HotkeyLockMouse"	);
	BtnLockMouseHotkey->setRelativePosition(
		POS_L,
		LbLockMouseHotkey->getFrame(),
		POS_L,
		0.15f, 0);

}

void OptionMenu_Init(){
	pMenu = new OptionMenu();
	MainDispatcher()->listen(EVENT_KEY_DOWN, onOptionMenuKeyDown);

	//UI自定义对象系统初始化
	Button::Init();

	ToolTip_Init();//TODO
	HotkeyButton::Init();

	CreateMenuContent();
}

void OptionMenu_Cleanup(){
	//UI自定义对象系统清理
	HotkeyButton::Cleanup();
	ToolTip_Cleanup();//TODO
	
	Button::Cleanup();

	delete pMenu;//MUSTDO
	MenuButton = NULL;
	pMenu = NULL;
}

