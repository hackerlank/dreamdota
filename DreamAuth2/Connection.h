#include "stdafx.h"
#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <zeromq\zmq.h>

typedef uint8_t BYTE;

class Connection {
public:
	static const uint32_t DEFAULT_POLL_TIMEOUT = 15000; //15√Î

	static void Init();
	static void Cleanup();
	static void Term();
	static bool Terminated();

	struct ResponseData {
		void* data;
		uint32_t size;
		uint32_t buffer_size;
	};

	NOINLINE Connection();
	NOINLINE ~Connection();
	NOINLINE const ResponseData* Request(void* data, uint32_t size, uint32_t timeout =  DEFAULT_POLL_TIMEOUT * 1000);
private:
	INLINE bool InitSocket();
	INLINE void CloseSocket();

	static void* ZMQContext;
	void* socket_;
	ResponseData data_;

	DISALLOW_COPY_AND_ASSIGN(Connection);
};

#endif