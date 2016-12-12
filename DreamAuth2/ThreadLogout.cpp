#include "stdafx.h"
#include "ThreadLogout.h"
#include "Auth.h"
#include "Connection.h"
#include "Message.h"

struct LogoutMessage {
	uint16_t header;
	char session_id[Auth::SESSION_ID_SIZE];
};
static_assert(sizeof(LogoutMessage) == 34, "sizeof(LogoutMessage)");

void ThreadLogout::Work() {
	VMProtectBeginVirtualization("ThreadLogout::Work");
	Auth::SessionDataType* session_data = (Auth::SessionDataType*)this->arg();
	
	Connection conn;
	LogoutMessage msg;
	msg.header = MESSAGE_TYPE_LOGOUT;

	Auth::SessionType session;
	session_data->GetData(&session);

	memcpy_s(msg.session_id, Auth::SESSION_ID_SIZE, session.id, Auth::SESSION_ID_SIZE);
	this->set_result(NULL != conn.Request(&msg, sizeof(LogoutMessage)));

	//Çå¿ÕSession
	memset(&session, 0, sizeof(Auth::SessionType));
	session_data->SetData(&session);
	
	VMProtectEnd();
}