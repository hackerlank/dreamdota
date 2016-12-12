#include "stdafx.h"
#include "Message.h"
#include <fp_call.h>

// for n elements
// no  OFFSET_#1 cause it's always 0
// HEADER | OFFSET_#2 | ... | OFFSET_#n | DATA
// data are NOT null terminated
bool message_get_fields(MessageFieldsData* fields_data, void* message, uint32_t size) {
	bool rv = false;
	MessageHeader* header = reinterpret_cast<MessageHeader*>(message);
	
	uint32_t fieldc = header->fieldc;

	uint8_t* body = aero::pointer_calc<uint8_t*>(message, sizeof(MessageHeader));
	//uint32_t body_size = size - sizeof(MessageHeader);
	
	uint8_t* data = aero::pointer_calc<uint8_t*>(body, 4 * fieldc);
	int32_t data_size = size - sizeof(MessageHeader) - (4 * fieldc);

	if (data_size > 0) {
		uint32_t *offsets = reinterpret_cast<uint32_t*>(body);
		uint32_t cur_offset;
		uint32_t next_offset;
		uint32_t field_size;

		//offset check
		//TODO combine loops into 1
		for (uint32_t i = 0; i < header->fieldc; ++i) {
			cur_offset = (i == 0 ? 0 : offsets[i - 1]);
			next_offset = offsets[i];
			field_size = next_offset - cur_offset;

			if (field_size < 0 || cur_offset + field_size > (uint32_t)data_size) {
				offsets = NULL;
				break;
			}
		}

		//save
		if (NULL != offsets) {
			fields_data->fieldc = fieldc;
			fields_data->fields_size = new uint32_t[fieldc];
			fields_data->fields_data = new uint8_t*[fieldc];

			for (uint32_t i = 0; i < fieldc; ++i) {
				cur_offset = (i == 0 ? 0 : offsets[i - 1]);
				next_offset = offsets[i];
				field_size = next_offset - cur_offset;

				fields_data->fields_size[i] = field_size;

				if (field_size) {
					fields_data->fields_data[i] = new uint8_t[field_size];
					memcpy_s(fields_data->fields_data[i], field_size, aero::pointer_calc<uint8_t*>(data, cur_offset), field_size);
				}
			}
			rv = true;
		}
	}
	return rv;
}

void message_clear_fields(MessageFieldsData* data) {
	for (uint32_t i = 0; i < data->fieldc; ++i) {
		if (data->fields_size[i] > 0) {
			delete [] data->fields_data[i];
		}
	}
	delete [] data->fields_size;
	delete [] data->fields_data;
	data->fieldc = 0;
}

uint32_t message_size_calc(MessageFieldsData* data) {
	uint32_t rv = sizeof(MessageHeader); // Header

	rv += (data->fieldc * 4); // Offsets

	for (uint32_t i = 0; i < data->fieldc; ++i) {
		rv += data->fields_size[i]; //Data
	}

	if (rv % 4)
		rv += (4 - (rv % 4));

	return rv;
}

bool message_build(uint16_t type, MessageFieldsData* data, void* buffer, uint32_t buffer_size) {
	bool rv = false;
	uint32_t message_size = message_size_calc(data);
	if (message_size <= buffer_size) {
		uint32_t offset = sizeof(MessageHeader);
		
		MessageHeader* header = reinterpret_cast<MessageHeader*>(buffer);
		
		memset(header->session_id, 0, sizeof(header->session_id));
		header->hash = 0;
		header->type = type;
		header->fieldc = data->fieldc;

		uint32_t field_offset = 0;
		for (uint32_t i = 0; i < data->fieldc; ++i) {
			field_offset += data->fields_size[i];
			*aero::pointer_calc<uint32_t*>(buffer, offset) = field_offset;
			offset += 4;
		}

		for (uint32_t i = 0; i < data->fieldc; ++i) {
			uint32_t field_size = data->fields_size[i];
			if (field_size) {
				memcpy_s(aero::pointer_calc<uint8_t*>(buffer, offset), field_size, data->fields_data[i], field_size);
				offset += field_size;
			}
		}

		rv = true;
	}
	return rv;
}

void message_fields_init(MessageFieldsData* data, uint32_t fieldc) {
	data->fieldc = fieldc;
	data->fields_size = new uint32_t[fieldc];
	memset(data->fields_size, 0, fieldc * 4);
	data->fields_data = new uint8_t*[fieldc];
	memset(data->fields_data, 0, fieldc * 4);
}

bool message_field_add(MessageFieldsData* data, uint8_t* buffer, uint32_t buffer_size) {
	if (data->fields_size[data->fieldc - 1] > 0)
		return false;

	uint32_t i = 0;
	while (data->fields_size[i] > 0 && i < data->fieldc) ++i;

	data->fields_size[i] = buffer_size;
	data->fields_data[i] = new uint8_t[buffer_size];
	memcpy_s(data->fields_data[i], buffer_size, buffer, buffer_size);

	return true;
}
