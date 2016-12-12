#ifndef SIMPLEUI_CONTROL_H_
#define SIMPLEUI_CONTROL_H_

#include "Delegate.h"
#include "Window.h"

namespace SimpleUI {

struct ControlColorInfo {
	COLORREF color;
	int bk_mode;
	HBRUSH bk_brush;
};

class Control : public Window {
public:
	Delegate<Control*> onCommand;
	Delegate<Control*> onClick;
	Delegate<Control*> onMouseOver;
	Delegate<Control*> onMouseOut;
	Delegate<Control*> onMouseMove;

	int id() {return this->id_;}
	void set_id(int id) {this->id_ = id;}

	Window* parent() {return this->parent_;}
	void set_parent(Window* window) {this->parent_ = window;}

	void SetFont(HFONT font, bool redraw = true);
	void SetColor(COLORREF color) {this->color_info_.color = color;}
	void SetSolidBrush(COLORREF color) {
		if (this->color_info_.bk_brush)
			DeleteObject(this->color_info_.bk_brush);
		this->color_info_.bk_brush = CreateSolidBrush(color);
	}
	void SetLinkMode(bool fl) {this->link_mode_ = fl;}
	void AppendText(const wchar_t* text) {
		size_t buffer_size = this->GetWindowTextLength() + wcslen(text) + 1 + 2;
		wchar_t* buffer = new wchar_t[buffer_size];
		this->GetWindowText(buffer, buffer_size);
		wcscat_s(buffer, buffer_size, text);
		wcscat_s(buffer, buffer_size, L"\r\n");
		this->SetWindowText(buffer);
		delete buffer;
	}
	using Window::Equal;

	virtual INT_PTR _UpdateControlColor(UINT uMsg, WPARAM wParam, LPARAM lParam);

	Control(HWND handle = NULL);
	virtual ~Control();
private:
	static void OnClickHandler(Control* ctl);
	static void OnMouseOverHandler(Control* ctl);
	static void OnMouseOutHandler(Control* ctl);
	static void OnMouseMoveHandler(Control* ctl);

	int id_;
	Window* parent_;
	bool link_mode_;
	ControlColorInfo color_info_;
};

} //namespace

#endif