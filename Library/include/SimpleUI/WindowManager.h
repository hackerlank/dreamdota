#ifndef SIMPLEUI_WINDOWMANAGER_
#define SIMPLEUI_WINDOWMANAGER_

#include <Windows.h>
#include <set>

namespace SimpleUI {

class Window;
class WindowManager {
public:
	typedef std::set<Window*> WindowSetType;

	static WindowManager* GetInstance();

	void Add(Window* window);
	void Remove(Window* window);

	friend void WindowManagerInstanceCleanup();

	WindowManager();
	~WindowManager();
private:
	static WindowManager* Instance;
	WindowSetType window_set;
	CRITICAL_SECTION cs_;
};

} //namespace

#endif