#include "stdafx.h"
#include "ThreadGetUpdate.h"
#include "Auth.h"
#include "Connection.h"
#include "Message.h"

struct GetUpdateMessage {
	uint16_t header;
	char session_id[Auth::SESSION_ID_SIZE];
};
static_assert(sizeof(GetUpdateMessage) == 34, "sizeof(GetUpdateMessage)");

void ThreadGetUpdate::Work() {
	bool rv = false;
	VMProtectBeginVirtualization("ThreadGetUpdate::Work");
	
	Auth::SessionDataType* session_data = (Auth::SessionDataType*)Auth::GetSessionData();	
	Connection conn;
	GetUpdateMessage msg;
	msg.header = MESSAGE_TYPE_UPDATE;

	Auth::SessionType session;
	session_data->GetData(&session);

	memcpy_s(msg.session_id, Auth::SESSION_ID_SIZE, session.id, Auth::SESSION_ID_SIZE);
	const Connection::ResponseData* result = conn.Request(&msg, sizeof(GetUpdateMessage));

	if (NULL != result && result->size > 2) {
			MessageFieldsData data;
			if (message_get_fields(&data, result->data, result->size) && data.fieldc == 4) {
				int len = MultiByteToWideChar(CP_UTF8, NULL, (LPCSTR)data.fields_data[2], data.fields_size[2], NULL, 0);
				wchar_t* buff;
				if (len) {
					buff = new wchar_t[len + 1];
					MultiByteToWideChar(CP_UTF8, NULL, (LPCSTR)data.fields_data[2], data.fields_size[2], buff, len);
					buff[len] = '\0';
					this->update_info_.desc.assign(buff);
					delete [] buff;
				}

				this->update_info_.link_utf8.assign((LPCSTR)data.fields_data[1], data.fields_size[1]);
				len = MultiByteToWideChar(CP_UTF8, NULL, (LPCSTR)data.fields_data[1], data.fields_size[1], NULL, 0);
				if (len) {
					buff = new wchar_t[len + 1];
					MultiByteToWideChar(CP_UTF8, NULL, (LPCSTR)data.fields_data[1], data.fields_size[1], buff, len);
					buff[len] = '\0';
					this->update_info_.link.assign(buff);
					delete [] buff;
				}

				this->update_info_.build = *(uint32_t*)(data.fields_data[0]);
				this->update_info_.date = *(uint32_t*)(data.fields_data[3]);
				rv = true;
			} else
				rv = false;
			message_clear_fields(&data);		
	} else {
		
	}
	memset(&session, 0, sizeof(Auth::SessionType));
	this->set_result(rv);

	VMProtectEnd();
}