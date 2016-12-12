#include "Window.h"
#include "WindowManager.h"

namespace SimpleUI {

LRESULT CALLBACK Window::WindowRoutingProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Window* window = (Window*)::GetWindowLongPtr(hwnd, GWL_USERDATA);
	LRESULT result;
	bool processed = false;
	if (window) {
		typedef Window::MessageMapType::iterator iter_type;
		std::pair<iter_type, iter_type> range = window->route_map_.equal_range(uMsg);
		iter_type iter;
		for (iter = range.first; iter != range.second && !processed; ++iter) {
			if (iter->second) {
				processed = iter->second(window, uMsg, wParam, lParam, &result);
			}
		}
	}
	return processed ? result : CallWindowProc(window->orginal_wndproc(), hwnd, uMsg, wParam, lParam);
}

void Window::AddMessageHandler(UINT msg, WindowMessageHandlerType handler) {
	if (!this->orginal_wndproc_) {
		//子类化
		this->orginal_wndproc_ = (WNDPROC)this->GetWindowLongPtr(GWL_WNDPROC);
		this->SetWindowLongPtr(GWL_USERDATA, (LONG_PTR)this);
		this->SetWindowLongPtr(GWL_WNDPROC, (LONG_PTR)WindowRoutingProc);
	}
	this->route_map_.insert(std::pair<UINT, WindowMessageHandlerType>(msg, handler));
}

bool Window::GetClientCursorPos(LPPOINT lpPoint) {
	return GetCursorPos(lpPoint) == TRUE &&	ScreenToClient(this->handle(), lpPoint) == TRUE;
}

bool Window::IsCursorOver() {
	RECT rect;
	POINT pt;
	this->GetClientCursorPos(&pt);
	this->GetClientRect(&rect);
	return PtInRect(&rect, pt) == TRUE;
}

HWND Window::GetVisibleChildWindowFromPoint(LPPOINT lpPoint) {
	return this->ChildWindowFromPointEx(*lpPoint, CWP_SKIPINVISIBLE);
}

Window::Window(HWND handle) {
	WindowManager::GetInstance()->Add(this);
	InitializeCriticalSectionAndSpinCount(&(this->critical_section_), 0x00000400);

	this->orginal_wndproc_ = NULL; //之所以不直接获取是因为参数有可能是NULL
	this->handle_ = handle;
	this->parent_ = NULL;
	this->text_buffer_ = NULL;
}

Window::~Window() {
	if (this->text_buffer_) {
		delete [] this->text_buffer_;
		this->text_buffer_ = NULL;
	}
	DeleteCriticalSection(&(this->critical_section_));
	WindowManager::GetInstance()->Remove(this);
}

} //namespace