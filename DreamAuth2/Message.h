#include "stdafx.h"
#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

const uint32_t MESSAGE_MAX_SIZE		= 2048;

const uint16_t MESSAGE_TYPE_NULL		= 0;
const uint16_t MESSAGE_TYPE_HANDSHAKE	= 1;
const uint16_t MESSAGE_TYPE_LOGIN 		= 2;
const uint16_t MESSAGE_TYPE_ALIVE 		= 3;
const uint16_t MESSAGE_TYPE_LOGOUT 		= 4;
const uint16_t MESSAGE_TYPE_GET_OFFSETS	= 5;
const uint16_t MESSAGE_TYPE_UPDATE      = 6;

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif // _MSC_VER

struct MessageHeader {
	uint16_t 	type;
	uint8_t		session_id[32];
	uint16_t 	fieldc;
	uint32_t	hash;
};

struct HandshakeReply {
	uint8_t		session_id[16];
};

#ifdef _MSC_VER
#pragma pack(pop)
#endif // _MSC_VER

struct MessageFieldsData {
	uint8_t 			fieldc;
	uint32_t*			fields_size;
	uint8_t**			fields_data;
};

bool message_get_fields(MessageFieldsData* data, void* message, uint32_t size);
void message_clear_fields(MessageFieldsData* data);

uint32_t message_size_calc(MessageFieldsData* data);
bool message_build(uint16_t type, MessageFieldsData* data, void* buffer, uint32_t buffer_size);

void message_fields_init(MessageFieldsData* data, uint32_t fieldc);
bool message_field_add(MessageFieldsData* data, uint8_t* buffer, uint32_t buffer_size);

#endif