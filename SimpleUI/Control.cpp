#include "Control.h"

namespace SimpleUI {

INT_PTR Control::_UpdateControlColor(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (this->color_info_.color == CLR_INVALID && !this->color_info_.bk_brush)
		return FALSE;

	HDC hdc = (HDC)wParam;
	if (this->color_info_.color != CLR_INVALID)
		SetTextColor(hdc, this->color_info_.color);
	SetBkMode(hdc, this->color_info_.bk_mode ? this->color_info_.bk_mode : TRANSPARENT);
	return this->color_info_.bk_brush ? (INT_PTR)this->color_info_.bk_brush : (INT_PTR)GetStockObject(NULL_BRUSH);
}

void Control::SetFont(HFONT font, bool redraw) {
	SendMessage(this->handle(), WM_SETFONT, WPARAM(font), MAKELPARAM(redraw ? 1 : 0, 0));
}

void Control::OnClickHandler(Control* ctl) {
	
}

void Control::OnMouseOverHandler(Control* ctl) {
	if (ctl->link_mode_)
		SetCursor(LoadCursor(NULL,IDC_HAND));
}

void Control::OnMouseOutHandler(Control* ctl) {
	if (ctl->link_mode_)
		SetCursor(LoadCursor(NULL,IDC_ARROW));
}

void Control::OnMouseMoveHandler(Control* ctl) {
	if (ctl->link_mode_)
		SetCursor(LoadCursor(NULL,IDC_HAND));
}

Control::Control(HWND handle) : Window(handle) {
	memset(&(this->color_info_), 0, sizeof(ControlColorInfo));
	this->color_info_.color = CLR_INVALID;
	this->link_mode_ = false;

	this->onClick += Control::OnClickHandler;
	this->onMouseOver += Control::OnMouseOverHandler;
	this->onMouseOut += Control::OnMouseOutHandler;
	this->onMouseMove += Control::OnMouseMoveHandler;
}

Control::~Control() {
	if (this->color_info_.bk_brush)
		DeleteObject(this->color_info_.bk_brush);
}

} //namespace