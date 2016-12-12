#ifndef SIMPLEUI_DIALOG_H_
#define SIMPLEUI_DIALOG_H_

#include <Windows.h>
#include <map>
#include <set>
#include <assert.h>

#include "Delegate.h"
#include "Control.h"
#include "ContainerWindow.h"

namespace SimpleUI {

class Dialog : public ContainerWindow {
public:
	Delegate<Dialog*> onClose;
	Delegate<Control*> onControlClick;
	Delegate<Control*> onControlMouseOver;
	Delegate<Control*> onControlMouseOut;
	Delegate<Control*> onCommand;

	struct ControlEventData {
		Control* control;
	};

	//typedef
	typedef INT_PTR (*DialogMessageHandlerType)(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam); 
	typedef std::multimap<UINT, DialogMessageHandlerType> MessageMapType; 

	//accsssor
	MessageMapType& msg_map() {return this->msg_map_;}

	HANDLE init_event() {return this->init_event_;}
	HANDLE close_event() {return this->close_event_;}

	DialogMessageHandlerType default_dlgproc() {return this->default_dlgproc_;}
	void set_default_dlgproc(DialogMessageHandlerType proc) {this->default_dlgproc_ = proc;}

	WORD tpl() {return this->tpl_;}

	//method
	void Close();
	void Show(bool fl);
	void Lock(bool fl);
	void WaitClose();
	void AddDialogMessageHandler(UINT msg, DialogMessageHandlerType handler); //FIXME 线程安全
	HWND GetItem(int item) {return GetDlgItem(this->handle(), item);}
	Control* GetItem(HWND handle) {return this->IsItem(handle) ? this->item_map_[handle] : NULL;}
	Control* GetItemUnderCursor(bool search_map = false);
	bool IsItem(HWND handle) {return this->item_map_.count(handle) > 0;}
	const MSG* GetLastDialogMessage() {return &(this->last_msg_);}

	template <class T>
	T* AssignItem(T*& var, int item) {
		HWND handle = this->GetItem(item);
		if (handle) {
			var = new T(handle);
			this->item_map_[handle] = var;
			Control* control = static_cast<Control*>(var);
			control->set_id(item);
			control->set_parent(this);
		}
		return var;
	}

	Dialog(WORD tpl);
	virtual ~Dialog();
private:
	//static
	static INT_PTR CALLBACK DialogRoutingProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); 
	static unsigned int WINAPI Dialog::DialogThreadProc(void* lpParameter);
	static INT_PTR ON_WM_CTLCOLORSTATIC(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR ON_WM_MOUSEMOVE(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR ON_WM_LBUTTONUP(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR ON_WM_COMMAND(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	static const DWORD THREAD_EXIT_WAIT_TIMEOUT = 1000;
	static const DWORD WM_EXIT_DIALOG = WM_USER + 0x8000;

	void _End();

	HANDLE init_event_;
	HANDLE close_event_;
	HANDLE dialog_thread_;
	Control* cursor_control_;
	WORD tpl_;
	DialogMessageHandlerType default_dlgproc_;
	MessageMapType msg_map_;
	MSG last_msg_;

	typedef std::map<HWND, Control*> ItemMapType;
	ItemMapType item_map_;
};

} //namespace
#endif