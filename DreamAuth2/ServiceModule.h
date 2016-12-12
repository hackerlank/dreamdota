#ifndef SERVICE_DIALOG_H_
#define SERVICE_DIALOG_H_

#include <SimpleUI\Delegate.h>
#include "SingleInstanceObject.h"

struct ServiceModule {
	SimpleUI::Delegate<bool> onPerformComplete;

	virtual void Perform() = 0;
	virtual void Term() = 0;
private:
	SimpleUI::Delegate<bool> onAsyncActionComplete;
	void AsyncActionComplete(bool success = true) {
		this->onAsyncActionComplete.Invoke(success);
	}
};

#endif