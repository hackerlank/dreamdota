#include "stdafx.h"
#include "ThreadAlive.h"
#include "Auth.h"
#include "Connection.h"
#include "Message.h"

struct AliveMessage {
	uint16_t header;
	char session_id[Auth::SESSION_ID_SIZE];
};
static_assert(sizeof(AliveMessage) == 34, "sizeof(AliveMessage)");

void ThreadAlive::Work() {
	VMProtectBeginVirtualization("ThreadAlive::Work");
	
	Auth::SessionDataType* session_data = (Auth::SessionDataType*)this->arg();
	
	while (true) {
		WaitForSingleObject(this->evt_stop_, Auth::ALIVE_INTERVAL);
#ifdef _DEBUG
		OutputDebug("Alive(0x%08X)...\n", this);
#endif
		if (this->term_) 
			break;
	
		Connection conn;
		AliveMessage msg;
		msg.header = MESSAGE_TYPE_ALIVE;

		Auth::SessionType session;
		session_data->GetData(&session);

		memcpy_s(msg.session_id, Auth::SESSION_ID_SIZE, session.id, Auth::SESSION_ID_SIZE);
		const Connection::ResponseData* alive_result = conn.Request(&msg, sizeof(AliveMessage));

		if (NULL != alive_result && alive_result->size == 2) {
			this->success_count_++;
			this->failed_count_ = 0;
#ifdef _DEBUG
			OutputDebug("Alive success(0x%08X).\n", this);
#endif
		} else {
			this->failed_count_++;
#ifdef _DEBUG
			OutputDebug("Alive failed, count %d.(0x%08X).\n", this->failed_count_, this);
#endif
			if (this->failed_count_ >= MAX_FAILED_ALIVE) {
				//Çå¿Õsession
				memset(&session, 0, sizeof(Auth::SessionType));
				session_data->SetData(&session);
				break;
			}
		}
		
		memset(&session, 0, sizeof(Auth::SessionType));

	}

#ifdef _DEBUG
		OutputDebug("Alive thread 0x%08X ended.\n", this);
#endif
	VMProtectEnd();
}