#include "stdafx.h"
#include "MHMain.h"
#include "NTDLL.h"
#include "DialogMain.h"
#include "ThreadSearch.h"
#include "Exception.h"
#include "Injection.h"

static ThreadSearch::ResultType Result;
static DialogMain* Dialog;

static void onWar3Found() {
	bool success;
	Dialog->t_status()->SetWindowText(L"检测到游戏，注入中...");
	VMProtectBeginVirtualization("Inject");
	success = Inject(Result.win, Result.process_handle, Result.invoker, L"MHModule.dll");
	VMProtectEnd();
	if (success)
		Dialog->t_status()->SetWindowText(L"注入成功");
	else {
		MessageBox(Dialog->handle(), L"注入失败！请尝试关闭杀毒软件。", NULL, MB_ICONERROR);
		Dialog->t_status()->SetWindowText(L"注入失败");
	}
}

static void onWar3Closed() {
	Dialog->t_status()->SetWindowText(L"等待游戏开启");
}

int Main() {

	BOOLEAN enabled;
	VMProtectBeginVirtualization("AdjustPrivilege");
	if (!NT_SUCCESS(NTDLL::RtlAdjustPrivilege(NTDLL::SE_DEBUG_PRIVILEGE, 1, 0, &enabled))) {
		Abort(EXCEPTION_ADJUST_PRIVILEGE);
	}
	VMProtectEnd();

	ThreadSearch ts;
	ts.onWar3WindowFound += onWar3Found;
	ts.onWar3WindowClosed += onWar3Closed;
	ts.Run((DWORD)&Result);

	Dialog = new DialogMain();
	Dialog->Show(true);
	Dialog->WaitClose();
	delete Dialog;
	
	ts.Term();
	return 0;
}