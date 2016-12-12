#ifndef SIMPLEUI_WINDOW_H_
#define SIMPLEUI_WINDOW_H_

#include <Windows.h>
#include <WindowsX.h>
#include <Commctrl.h>
#include <map>

namespace SimpleUI {

class Window {
public:
	typedef bool (*WindowMessageHandlerType)(Window* window, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* result);
	typedef std::multimap<UINT, WindowMessageHandlerType> MessageMapType;

	static LRESULT CALLBACK WindowRoutingProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//accessor
	HWND handle() {return this->handle_;}
	void set_handle(HWND handle) {this->handle_ = handle;}

	HWND parent() {return this->parent_;}
	void set_parent(HWND parent) {this->parent_ = parent;}

	WNDPROC orginal_wndproc() {return this->orginal_wndproc_;}

	//method
	void AddMessageHandler(UINT msg, WindowMessageHandlerType); //FIXME 线程安全

	bool Equal(HWND handle) {return this->handle_ == handle;}
	bool GetClientCursorPos(LPPOINT lpPoint);
	bool IsCursorOver();
	HWND GetVisibleChildWindowFromPoint(LPPOINT lpPoint);
	void RequestOwnership() {EnterCriticalSection(&(this->critical_section_));}
	void ReleaseOwnership() {LeaveCriticalSection(&(this->critical_section_));}
	const wchar_t* GetText() {
		if (this->text_buffer_) {
			delete [] this->text_buffer_;
			this->text_buffer_ = NULL;
		}
		int size = this->GetWindowTextLength();
		if (size) {
			this->text_buffer_ = new wchar_t[size + 1];
			this->GetWindowText(this->text_buffer_, size + 1);
			return this->text_buffer_;
		} else {
			return L"";
		}
	}

	//Windows api mapping
	BOOL ShowWindow(int nCmdShow) {return ::ShowWindow(this->handle_, nCmdShow);}
	BOOL EnableWindow(BOOL bEnable) {return ::EnableWindow(this->handle_, bEnable);}
	BOOL SetWindowText(LPCTSTR lpString) {return ::SetWindowText(this->handle_, lpString);}
	int GetWindowText(LPTSTR lpString, int nMaxCount) {return ::GetWindowText(this->handle_, lpString, nMaxCount);}
	int GetWindowTextLength() {return ::GetWindowTextLength(this->handle_);}
	BOOL GetWindowRect(LPRECT lpRect) {return ::GetWindowRect(this->handle_, lpRect);}
	BOOL GetClientRect(LPRECT lpRect) {return ::GetClientRect(this->handle_, lpRect);}
	HWND ChildWindowFromPointEx(POINT pt, UINT uFlags) {return ::ChildWindowFromPointEx(this->handle(), pt, uFlags);}
	HWND ChildWindowFromPoint(POINT pt) {return ::ChildWindowFromPoint(this->handle(), pt);}
	BOOL SetForegroundWindow() {return ::SetForegroundWindow(this->handle());}
	BOOL BringWindowToTop() {return ::BringWindowToTop(this->handle());}
	HWND SetFocus() {return ::SetFocus(this->handle());}
	LONG SetWindowLong(int i, LONG v) {return ::SetWindowLong(this->handle(), i, v);}
	LONG GetWindowLong(int i) {return ::GetWindowLong(this->handle(), i);}

	BOOL EnableSystemMenuItem(UINT id, BOOL state) {
		HMENU hMenu;
		UINT dwExtra;
		HWND hwnd = this->handle();	

		if (hwnd == NULL) return FALSE;

		if ((hMenu = GetSystemMenu(hwnd, FALSE)) == NULL) return FALSE;

		dwExtra = state ? MF_ENABLED : (MF_DISABLED | MF_GRAYED);
		return EnableMenuItem(hMenu, id, MF_BYCOMMAND | dwExtra) != -1;
	}

	Window(HWND handle = NULL);
	virtual ~Window();
private:
	wchar_t* text_buffer_;
	WNDPROC orginal_wndproc_;
	HWND handle_;
	HWND parent_;
	MessageMapType route_map_;
	CRITICAL_SECTION critical_section_;
};

} //namespace

#endif