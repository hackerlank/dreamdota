#include "stdafx.h"
#ifndef LOGGEDIN_H_
#define LOGGEDIN_H_

#include <SimpleUI\Delegate.h>
class DialogMain;

namespace Loggedin {
	enum EventEnum {
		EVENT_LOGOUT,
		EVENT_EXIT
	};

	extern SimpleUI::Delegate<EventEnum> onEvent;

	void Init();
	void Cleanup();
	void MainDialog();
	void OutputEncryptedMessage(uint32_t id, ...);
	void OutputMessage(const wchar_t* format, ...);
	
}//namespace

#endif