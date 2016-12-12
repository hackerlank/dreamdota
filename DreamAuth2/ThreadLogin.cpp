#include "stdafx.h"
#include "ThreadLogin.h"
#include "Auth.h"
#include "Connection.h"
#include "InlineUtils.h"
#include "RSA.h"
#include "Message.h"
#include "../DreamWarcraft/Version.h"
#include "Locale.h"
#include <fp_call.h>

//Messages
struct HandshakeMessage {
	uint16_t header;
	uint16_t align_2;
	BYTE key_data[RSA_SIZE];
};
static_assert(sizeof(HandshakeMessage) == 132, "sizeof(HandshakeMessage)");

struct HandshakeResponse {
	char session_id[Auth::SESSION_ID_SIZE];
	BYTE key_data[RSA_SIZE];
};
static_assert(sizeof(HandshakeResponse) == 160, "sizeof(HandshakeResponse)");

inline int GenerateKeyData(uint32_t seed, BYTE key[ENCRYPT_KEY_SIZE], BYTE key_data[RSA_SIZE]) {
	uint32_t key32[ENCRYPT_KEY_SIZE / 4];
	for (int i = 0; i < ENCRYPT_KEY_SIZE / 4; ++i) {
		key32[i] = InlineUtils::Rand(&seed);

#ifdef _DEBUG
		OutputDebug("KEY[%d] = 0x%08X\n", i, key32[i]);
#endif

	}
	memcpy_s(key, ENCRYPT_KEY_SIZE, key32, ENCRYPT_KEY_SIZE);
	memset(key_data, 0, RSA_SIZE);
	int rsa_result = RSA_PublicEncrypt((uint8_t*)key32, ENCRYPT_KEY_SIZE, key_data);

#ifdef _DEBUG
		OutputDebug("RSA Result = %d\n", rsa_result);
#endif

	return rsa_result;
}

INLINE bool Handshake(Connection* conn, BYTE key[ENCRYPT_KEY_SIZE], Auth::SessionType* session) {
	bool rv = false;

	uint32_t* tmp = new uint32_t;
	*tmp = GetTickCount();

	//生成密匙
	uint32_t seed = (*tmp) ^ rand() ^ (uint32_t)tmp;

	//握手
	HandshakeMessage send = {
		MESSAGE_TYPE_HANDSHAKE,
		0,
		{0}
	};

	if (RSA_SIZE == GenerateKeyData(seed, key, send.key_data)) {
		const Connection::ResponseData* response
			= conn->Request(&send, sizeof(HandshakeMessage));
		if (response && response->size == sizeof(HandshakeResponse)) {
			HandshakeResponse* data = (HandshakeResponse*)response->data;
			InlineUtils::XXTEADecrypt((BYTE*)data->session_id, Auth::SESSION_ID_SIZE, key);
			memset(session, 0, sizeof(Auth::SessionType));
			memcpy_s(session->id, Auth::SESSION_ID_SIZE, data->session_id, Auth::SESSION_ID_SIZE);
			memcpy_s(session->KeyData, RSA_SIZE, data->key_data, RSA_SIZE);
			rv = true;
		}
	}

	delete tmp;
	return rv;
}

INLINE const Connection::ResponseData* DoLogin(Connection* conn, BYTE key[ENCRYPT_KEY_SIZE], const char* account, const char* password, Auth::SessionType* session) {
	uint32_t client_id = InlineUtils::GetUniqueId();
	uint32_t version = VERSION.revision;
	uint32_t lcid = Locale::GetPreferedLCID();

	//构建登录数据包，固定格式:
	//account password client_id version lcid
	MessageFieldsData msg;
	uint8_t login_message_buff[1024];
	message_fields_init(&msg, 5);
	message_field_add(&msg, (uint8_t*)(account), strlen(account) + 1);
	message_field_add(&msg, (uint8_t*)(password), strlen(password) + 1);
	message_field_add(&msg, (uint8_t*)&client_id, 4);
	message_field_add(&msg, (uint8_t*)&(version), 4);
	message_field_add(&msg, (uint8_t*)&lcid, 4);
	message_build(MESSAGE_TYPE_LOGIN, &msg, login_message_buff, sizeof(login_message_buff));
	MessageHeader* header = reinterpret_cast<MessageHeader*>(login_message_buff);
	uint32_t login_message_size = message_size_calc(&msg);
	memcpy_s(header->session_id, sizeof(header->session_id), session->id, sizeof(header->session_id));
	InlineUtils::XXTEAEncrypt(
		aero::pointer_calc<uint8_t*>(login_message_buff, sizeof(MessageHeader)), login_message_size - sizeof(MessageHeader), key);
	message_clear_fields(&msg);

	//发包
	return conn->Request(login_message_buff, login_message_size);
}

NOINLINE void ThreadLogin::Login() {
	VMProtectBeginVirtualization("ThreadLogin::Login");
	Auth::SessionDataType* session_data = (Auth::SessionDataType*)this->arg();
	Connection conn;
	jmp_buf env;
	BYTE key[ENCRYPT_KEY_SIZE];
	Auth::SessionType session;
	memset(&session, 0, sizeof(Auth::SessionType));

	int e = setjmp(env);
	if (e == 0) {
		if (!Handshake(&conn, key, &session)) {
			this->login_result_.connect_success = false;
			longjmp(env, Auth::LOGIN_RESULT_FAILED);
		}

		//登录
		const Connection::ResponseData* login_result = DoLogin(&conn, key, this->account_, this->password_md5_, &session);
		if (!login_result) {
			this->login_result_.connect_success = false;
			longjmp(env, Auth::LOGIN_RESULT_FAILED);
		}

		if (login_result->size != 4) {
			this->login_result_.connect_success = true;
			longjmp(env, static_cast<Auth::LoginResultEnumType>(*(uint8_t*)(login_result->data)));
		}

		session.remain_time = *(uint32_t*)(login_result->data);
		this->login_result_.connect_success = true;
		this->login_result_.server_response = Auth::LOGIN_RESULT_OK;
	} else {
		this->login_result_.server_response = (Auth::LoginResultEnumType)e;
	}

#ifdef _DEBUG
		OutputDebug("Login Result: %s (0x%X)\n", this->login_result_.connect_success ? "true" : "false", this->login_result_.server_response);
#endif

	session_data->SetData(&session);
	memset(&session, 0, sizeof(Auth::SessionType));
	InlineUtils::XXTEAKeyDestroy(key);
	VMProtectEnd();
}

void ThreadLogin::Work() {
	this->Login();
	this->set_result(this->login_result_.connect_success && this->login_result_.server_response == Auth::LOGIN_RESULT_OK);
}