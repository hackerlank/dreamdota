#include "RadioBox.h"

namespace SimpleUI {

void RadioBox::SetCheck(bool check) {
	Button_SetCheck(this->handle(), check ? BST_CHECKED : BST_UNCHECKED);
}

bool RadioBox::IsChecked() {
	return Button_GetCheck(this->handle()) == BST_CHECKED;
}

RadioBox::RadioBox(HWND handle) : Control(handle) {

}

RadioBox::~RadioBox() {

}

} //namespace