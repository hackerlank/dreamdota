#include "CheckBox.h"

namespace SimpleUI {

void CheckBox::SetCheck(bool check) {
	Button_SetCheck(this->handle(), check ? BST_CHECKED : BST_UNCHECKED);
}

bool CheckBox::IsChecked() {
	return Button_GetCheck(this->handle()) == BST_CHECKED;
}

CheckBox::CheckBox(HWND handle) : Control(handle) {

}

CheckBox::~CheckBox() {

}

} //namespace