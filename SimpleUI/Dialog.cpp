#include "Dialog.h"
#include <process.h>

namespace SimpleUI {

void Dialog::_End() {
	this->RequestOwnership();
	DestroyWindow(this->handle());
	this->set_handle(NULL);
	this->ReleaseOwnership();
	PostQuitMessage(0);
	SetEvent(this->close_event_);
}

INT_PTR CALLBACK Dialog::DialogRoutingProc(	HWND hwndDlg, UINT uMsg, WPARAM wParam, 
									LPARAM lParam) {
	Dialog* dialog;
	INT_PTR result = FALSE;
	if (uMsg == WM_INITDIALOG) {
		dialog = (Dialog*)lParam;
		dialog->set_handle(hwndDlg);
		SetEvent(dialog->init_event());
		return TRUE;
	} else {
		dialog = (Dialog*)::GetWindowLongPtr(hwndDlg, GWL_USERDATA);
	}

	if (dialog) {
		typedef Dialog::MessageMapType::iterator iter_type;
		std::pair<iter_type, iter_type> range = dialog->msg_map_.equal_range(uMsg);
		if (range.first != dialog->msg_map_.end()) {
			for (iter_type iter = range.first; result == FALSE && iter != range.second; ++iter) {
				result = iter->second(dialog, uMsg, wParam, lParam);
			}
		} else if (dialog->default_dlgproc()) {
			result = dialog->default_dlgproc()(dialog, uMsg, wParam, lParam);
		}
	}

	if (uMsg == WM_EXIT_DIALOG || (result == FALSE && uMsg == WM_CLOSE)) {
		dialog->_End();
		dialog->onClose(dialog);
		return TRUE;
	}
	
	return result;
}

unsigned int WINAPI Dialog::DialogThreadProc(void* lpParameter) {
	Dialog* dialog = (Dialog*)lpParameter;
	BOOL bRet;
	MSG& msg = dialog->last_msg_;
	HWND dialog_handle = CreateDialogParam(
		GetModuleHandle(NULL),
		MAKEINTRESOURCE(dialog->tpl()),
		dialog->parent(),
		Dialog::DialogRoutingProc,
		LPARAM(dialog));

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) 
	{ 
		if (bRet == -1) {
			return 0xFFFFFFFF;
		}
		else {
			assert(IsWindow(dialog_handle));
			if (!IsDialogMessage(dialog_handle, &msg)) {
				TranslateMessage(&msg); 
				DispatchMessage(&msg); 
			}
		}
	}
	return 0;
}

//TODO 支持WM_CTLCOLORBTN WM_CTLCOLOREDIT WM_CTLCOLORLISTBOX WM_CTLCOLORSCROLLBAR等
INT_PTR Dialog::ON_WM_CTLCOLORSTATIC(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HWND control = (HWND)lParam;
	INT_PTR rv = FALSE;
	if (dialog->IsItem(control)) {
		rv = dialog->GetItem(control)->_UpdateControlColor(uMsg, wParam, lParam);
	}
	return rv;
}

INT_PTR Dialog::ON_WM_MOUSEMOVE(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	INT_PTR rv = FALSE;
	Control* ctl;
	if (NULL != (ctl = dialog->GetItemUnderCursor(true))) {
		ctl->onMouseMove.Invoke(ctl);
		if (ctl != dialog->cursor_control_) {
			if (dialog->cursor_control_)
				dialog->cursor_control_->onMouseOut.Invoke(dialog->cursor_control_);
			dialog->cursor_control_ = ctl;
			ctl->onMouseOver.Invoke(ctl);
		}
	} else if (dialog->cursor_control_ != NULL) {
		dialog->cursor_control_->onMouseOut.Invoke(dialog->cursor_control_);
		dialog->cursor_control_ = NULL;
	}
	return rv;
}

INT_PTR Dialog::ON_WM_LBUTTONUP(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Control* ctl;
	if (NULL != (ctl = dialog->GetItemUnderCursor())) {
		ctl->onClick.Invoke(ctl);
		dialog->onControlClick.Invoke(ctl);
	}
	return FALSE;
}

INT_PTR Dialog::ON_WM_COMMAND(Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Control* ctl;
	HWND ctl_handle = (HWND)lParam;
	if (NULL != (ctl = dialog->GetItem(ctl_handle))) {
		ctl->onCommand.Invoke(ctl);
		dialog->onCommand.Invoke(ctl);
	}
	return FALSE;
}

Dialog::Dialog(WORD tpl) : ContainerWindow(NULL) {
	this->init_event_ = CreateEvent(NULL, FALSE, FALSE, NULL);
	this->close_event_ = CreateEvent(NULL, FALSE, FALSE, NULL);
	this->dialog_thread_ = NULL;
	this->default_dlgproc_ = NULL;
	this->cursor_control_ = NULL;
	this->tpl_ = tpl;

	this->dialog_thread_ = (HANDLE)_beginthreadex(
		NULL,
		0,
		Dialog::DialogThreadProc,
		this,
		CREATE_SUSPENDED,
		NULL);
	ResumeThread(this->dialog_thread_);
	WaitForSingleObject(this->init_event_, INFINITE);
	this->SetWindowLongPtr(GWL_USERDATA, (LONG_PTR)this);

	this->AddDialogMessageHandler(WM_CTLCOLORSTATIC, ON_WM_CTLCOLORSTATIC); //控件颜色
	this->AddDialogMessageHandler(WM_MOUSEMOVE, ON_WM_MOUSEMOVE); //控件鼠标指针
	this->AddDialogMessageHandler(WM_LBUTTONUP, ON_WM_LBUTTONUP);
	this->AddDialogMessageHandler(WM_COMMAND, ON_WM_COMMAND);
}

Dialog::~Dialog() {
	this->Close();
	for (ItemMapType::iterator iter = this->item_map_.begin(); iter != this->item_map_.end(); ++iter)
		delete iter->second;
	
	if (WaitForSingleObject(this->dialog_thread_, Dialog::THREAD_EXIT_WAIT_TIMEOUT) != WAIT_OBJECT_0) {
		TerminateThread(this->dialog_thread_, -1);
	}
	this->dialog_thread_ = NULL;
}

void Dialog::Close() {
	if (this->handle()) {
		PostMessage(this->handle(), WM_EXIT_DIALOG, NULL, NULL);
	}
}

void Dialog::Show(bool fl) {
	if (this->handle()) {
		this->ShowWindow(fl ? SW_SHOW : SW_HIDE);
		this->SetForegroundWindow();
	}
}

void Dialog::Lock(bool fl) {
	if (this->handle())
		this->EnableWindow(fl ? TRUE : FALSE);
}

void Dialog::WaitClose() {
	if (this->dialog_thread_) {
		WaitForSingleObject(this->close_event_, INFINITE);
	}
}

void Dialog::AddDialogMessageHandler(UINT msg, DialogMessageHandlerType handler) {
	this->msg_map_.insert(std::pair<UINT, DialogMessageHandlerType>(msg, handler));
}

Control* Dialog::GetItemUnderCursor(bool search_map) {
	Control* rv = NULL;
	if (search_map) {
		for (ItemMapType::iterator iter = this->item_map_.begin(); !rv && iter != this->item_map_.end(); ++iter) {
			if (iter->second->IsCursorOver()) {
				rv = iter->second;
				break;
			}
		}
	} else {
		POINT pt;
		this->GetClientCursorPos(&pt);
		HWND child = this->ChildWindowFromPoint(pt);
		if (child && child != this->handle()) {
			if (this->IsItem(child))
				rv = (this->item_map_[child]);
		}
	}
	return rv;
}

} //namespace