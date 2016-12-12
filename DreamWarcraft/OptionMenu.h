//游戏内可调出的选项菜单
//由左边的导航与右边的面板组成

#include "stdafx.h"
#ifndef OPTION_MENU_H_
#define OPTION_MENU_H_

#include "Tools.h"
#include "UISimpleFrame.h"

#include "Button.h"
#include "CheckBox.h"
#include "Label.h"
#include "ToolTip.h"
#include "HotkeyButton.h"
#include "SlotHotkeyButton.h"

class CategoryNameCompare {
	public:
		bool operator()(const std::string& l, const std::string& r) const { return strcmp(l.c_str(), r.c_str()) < 0; }
};

typedef std::map<std::string, Button*, CategoryNameCompare> CategoryNameButtonMapType;

class OptionMenu {
public:
	CategoryNameButtonMapType categoryNames;
	UISimpleFrame* mainFrame;
	UISimpleFrame* navigationFrame;
	UISimpleFrame* contentFrame;
	bool shown;

	OptionMenu();
	~OptionMenu();

	UISimpleFrame* category(const char* categoryName, const char* tooltip = NULL);
	void show(bool flag);
	void toggleState();
	bool isShown();
};

OptionMenu* DefaultOptionMenuGet();

void OptionMenu_Init();
void OptionMenu_Cleanup();

#endif