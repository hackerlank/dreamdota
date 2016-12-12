#include "stdafx.h"
#include "Exception.h"
#include "ThreadMessage.h"
#include "LocaleString.h"
#include "Pipe.h"

LRESULT CALLBACK ThreadMessage::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message > WM_USER && message <= 0x7FFF) {
		VMProtectBeginVirtualization("ThreadMessage::WndProc");
#ifdef _DEBUG
	OutputDebug("ThreadMessage(0x%08X) message: 0x%X.\n", message);
#endif
		MSG msg;
		msg.message = message;
		msg.lParam = lParam;
		msg.wParam = wParam;
		((ThreadMessage*)GetWindowLongPtr(hWnd, GWL_USERDATA))->onMessage.Invoke(&msg);
		VMProtectEnd();
		return TRUE;
	} else if (message == WM_QUIT) {
		PostQuitMessage(0);
		return TRUE;
	} else
		return DefWindowProc(hWnd, message, wParam, lParam);
}

ThreadMessage::ThreadMessage() {

}

ThreadMessage::~ThreadMessage() {
	
}

void ThreadMessage::StopSignal() {
	VMProtectBeginVirtualization("ThreadMessage::StopSignal");
	PostMessage(this->win_, WM_QUIT, NULL, NULL);
	VMProtectEnd();
}

void ThreadMessage::Work() {
	VMProtectBeginVirtualization("ThreadMessage::Work");
	
	std::wstring& class_name = StringManager::StringUnicode(STR::WIN_CLASS_NAME);
	
	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.lpfnWndProc = ThreadMessage::WndProc;
	wc.hInstance = (HINSTANCE)GetCurrentProcess();
	wc.lpszClassName = class_name.c_str();
	if (!RegisterClass(&wc)) {
		Abort(EXCEPTION_REGISTER_CLASS_FAILED);
	}
	this->win_ = CreateWindow(class_name.c_str(), L"", WS_DISABLED, 0, 0, 1, 1, HWND_MESSAGE, NULL, (HINSTANCE)GetCurrentProcess(), NULL);

	if (!this->win_)
		Abort(EXCEPTION_CREATE_WINDOW_FAILED);

	SetWindowLongPtr(this->win_, GWL_USERDATA, (LONG)this);

	this->onWindowCreated.Invoke(this->win_);

	VMProtectEnd();

#ifdef _DEBUG
	OutputDebug("ThreadMessage(0x%08X) message loop started.\n", this);
#endif

	BOOL ret;
	MSG msg;
    while( (ret = GetMessage(&msg, NULL, 0, 0 )) != 0)
    { 
        if (ret == -1)
        {
            // handle the error and possibly exit
			this->set_result(0xFFFFFFFF);
			break;
        }
        else
        {
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }
    }
	this->set_result(0);

#ifdef _DEBUG
	OutputDebug("ThreadMessage(0x%08X) ended.\n", this);
#endif

	DestroyWindow(this->win_);
}