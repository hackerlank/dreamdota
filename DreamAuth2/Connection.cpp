#include "stdafx.h"
#include "Connection.h"
#include "LocaleString.h"
#include <zeromq\zmq.h>
#include "Exception.h"

void* Connection::ZMQContext = NULL;

void Connection::Init() {
	ZMQContext = zmq_init(3);
	if (!ZMQContext)
		Abort(EXCEPTION_ZMQ_INIT_FAILED);
}

volatile long TermLock = 0;

void Connection::Cleanup() {
	Connection::Term();
}

void Connection::Term() {
	_InterlockedIncrement(&TermLock);
	zmq_term(ZMQContext);
	ZMQContext = NULL;
	_InterlockedDecrement(&TermLock);
}

bool Connection::Terminated() {
	while(TermLock);
	return ZMQContext == NULL;
}

INLINE bool Connection::InitSocket() {
	bool rv = false;
	if (ZMQContext && NULL != (this->socket_ = zmq_socket(ZMQContext, ZMQ_REQ))) {
		jmp_buf env;
		
#ifdef _TEST_SERVER
		std::string& conn_string = StringManager::StringUTF8(STR::SERVER_STRING_TEST);
#else
		std::string& conn_string = StringManager::StringUTF8(STR::SERVER_STRING);
#endif
		OutputDebugStringA(conn_string.c_str());
		int e = setjmp(env);
		if (e == 0) {
			int zero = 0;
			if (0 != zmq_setsockopt(this->socket_, ZMQ_LINGER, &zero, sizeof(zero)))
				longjmp(env, 1);

#ifdef _DEBUG
				OutputDebug("Connect: %s\n", conn_string.c_str());
#endif

			if (0 != zmq_connect(this->socket_, conn_string.c_str()))
				longjmp(env, 2);

			rv = true;

		} else { //Exception
			zmq_close(this->socket_);
			this->socket_ = NULL;
		}

		conn_string.assign("");
	}
	return rv;
}

INLINE void Connection::CloseSocket() {
	if (this->socket_) {
		zmq_close(this->socket_);
		this->socket_ = NULL;
	}
}

NOINLINE Connection::Connection() {
	VMProtectBeginVirtualization("Connection::Connection");

	this->socket_ = NULL;
	this->data_.data = NULL;
	this->data_.size = 0;
	this->data_.buffer_size = 0;

#ifdef _DEBUG
		OutputDebug("Connection created: 0x%08X\n", this);
#endif

	VMProtectEnd();
}

NOINLINE Connection::~Connection() {
	VMProtectBeginVirtualization("Connection::~Connection");

	this->CloseSocket();
	if (this->data_.buffer_size)
		delete [] this->data_.data;

#ifdef _DEBUG
		OutputDebug("Connection destoryed: 0x%08X\n", this);	
#endif

	VMProtectEnd();
}

inline bool ZMQRecv(void* socket, zmq_msg_t* msg, uint32_t timeout) {
	zmq_pollitem_t items[1];
	items[0].events = ZMQ_POLLOUT;
	items[0].socket = socket;
	return (0 == zmq_recv(socket, msg, ZMQ_NOBLOCK) && 1 == zmq_poll(items, 1, timeout));
}

inline bool ZMQSend(void* socket, zmq_msg_t* msg, uint32_t timeout) {
	zmq_pollitem_t items[1];
	items[0].events = ZMQ_POLLIN;
	items[0].socket = socket;
	return (0 == zmq_send(socket, msg, ZMQ_NOBLOCK) && 1 == zmq_poll(items, 1, timeout));
}

NOINLINE const Connection::ResponseData* Connection::Request(void* data, uint32_t size, uint32_t timeout) {
	VMProtectBeginVirtualization("Connection::Request");
	
	jmp_buf env;
	ResponseData* rv = NULL;
	zmq_msg_t msg_send, msg_recv;
	zmq_msg_init_data(&msg_send, data, size, NULL, NULL);
	zmq_msg_init(&msg_recv);

	int e = setjmp(env);
	if (e == 0) {
		if (!this->socket_) {
			if (!this->InitSocket())
				longjmp(env, 1);
		}
		
		if (!ZMQSend(this->socket_, &msg_send, timeout))
			longjmp(env, 2);

#ifdef _DEBUG
			OutputDebug("Connection: %u bytes sent.\n", size);
#endif
		
		if (!ZMQRecv(this->socket_, &msg_recv, timeout))
			longjmp(env, 3);

		size_t msg_size = zmq_msg_size(&msg_recv);
		void* msg_data = zmq_msg_data(&msg_recv);

#ifdef _DEBUG
			OutputDebug("Connection: %u bytes recieved.\n", msg_size);
#endif

		if (this->data_.buffer_size < msg_size) {
			if (this->data_.data)
				delete [] this->data_.data;
			this->data_.data = new BYTE[msg_size];
			this->data_.buffer_size = msg_size;
		}
		this->data_.size = msg_size;
		memcpy_s(this->data_.data, this->data_.buffer_size, msg_data, msg_size);
		rv = &(this->data_);
	} else {
		rv = NULL;

#ifdef _DEBUG
			OutputDebug("Connection::Request Exception %d, zmq_errno() = %d.\n", e, zmq_errno());
#endif
	}

	zmq_msg_close(&msg_send);
	zmq_msg_close(&msg_recv);

	VMProtectEnd();
	return rv;
}