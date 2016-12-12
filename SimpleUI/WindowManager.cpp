#include "WindowManager.h"
#include "Window.h"

#include <cstdlib>
#include <cassert>

namespace SimpleUI {

WindowManager* WindowManager::Instance = NULL;
void WindowManagerInstanceCleanup();

WindowManager* WindowManager::GetInstance() {
	if (!WindowManager::Instance) {
		WindowManager::Instance = new WindowManager();
		atexit(WindowManagerInstanceCleanup);
	}
	return WindowManager::Instance;
}

void WindowManager::Add(Window* window) {
	EnterCriticalSection(&this->cs_);
	this->window_set.insert(window);
	LeaveCriticalSection(&this->cs_);
}

void WindowManager::Remove(Window* window) {
	EnterCriticalSection(&this->cs_);
	this->window_set.erase(window);
	LeaveCriticalSection(&this->cs_);
}

WindowManager::WindowManager() {
	InitializeCriticalSection(&this->cs_);
}

WindowManager::~WindowManager() {
#ifdef _DEBUG
	EnterCriticalSection(&this->cs_);
	assert(this->window_set.size() == 0);
	for (WindowManager::WindowSetType::iterator iter = this->window_set.begin(); iter != this->window_set.end(); ++iter) {
		OutputDebugString((*iter)->GetText());
	}
	LeaveCriticalSection(&this->cs_);
#endif
	DeleteCriticalSection(&this->cs_);
}

void WindowManagerInstanceCleanup() {
	delete WindowManager::Instance;
}

} //namespace