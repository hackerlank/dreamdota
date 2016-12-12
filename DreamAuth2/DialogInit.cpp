#include "DialogInit.h"

#include "resource.h"
#include "ResString.h"
#include "Utils.h"

INT_PTR DialogInit::ON_WM_CLOSE(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return TRUE;
}

INT_PTR DialogInit::ON_WM_PAINT(SimpleUI::Dialog* dialog, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	DialogInit* t = (DialogInit*)dialog;
	PAINTSTRUCT ps;
	HWND hwnd = dialog->handle();
	RECT client_rect;
	dialog->GetClientRect(&client_rect);
	HDC hdc = BeginPaint(hwnd, &ps);
	HPEN oldpen = (HPEN)SelectObject(hdc, t->border_pen_);
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, t->bg_brush_);
	Rectangle(hdc, client_rect.left, client_rect.top, client_rect.right, client_rect.bottom);
	SelectObject(hdc, oldpen);
	SelectObject(hdc, oldbrush);
	EndPaint(hwnd, &ps);	
	return FALSE;
}

DialogInit::DialogInit() : SimpleUI::Dialog(IDD_INIT) {
	this->AssignItem<Control>(this->l_loading_, L_LOADING);
	this->l_loading_->SetColor(RGB(0x66, 0x66, 0x66));
	SETCONTROLTEXT(l_loading_, INITIALIZING);

	this->bg_brush_ = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	this->border_pen_ = CreatePen(PS_SOLID, 5, RGB(0xC4, 0xF3, 0xFF));

	this->AddDialogMessageHandler(WM_CLOSE, ON_WM_CLOSE);
	this->AddDialogMessageHandler(WM_PAINT, ON_WM_PAINT);
}

DialogInit::~DialogInit() {
	DeleteObject(this->bg_brush_);
	DeleteObject(this->border_pen_);
}