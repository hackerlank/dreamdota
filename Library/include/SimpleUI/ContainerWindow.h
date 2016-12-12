#ifndef SIMPLEUI_CONTAINERWINDOW_H_
#define SIMPLEUI_CONTAINERWINDOW_H_

#include <Windows.h>
#include "Window.h"

namespace SimpleUI {

class ContainerWindow : public Window {
public:
	ContainerWindow(HWND handle = NULL);
	virtual ~ContainerWindow();
};

} //namespace

#endif