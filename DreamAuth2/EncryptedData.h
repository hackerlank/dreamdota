#include "stdafx.h"
#ifndef ENCRYPTED_DATA_H_
#define ENCRYPTED_DATA_H_

template <typename DataType>
class EncryptedData {
public:
	static const uint32_t DATASIZE = sizeof(DataType);
	typedef void (*DataProcessCallback)(DataType* data, void* arg);

	template <typename DataType>
	static void SetDataCallback(DataType* data, DataType* src) {
		memcpy_s(data, sizeof(DataType), src, sizeof(DataType));
	}

	template <typename DataType>
	static void GetDataCallback(DataType* data, DataType* dst) {
		memcpy_s(dst, sizeof(DataType), data, sizeof(DataType));
	}

	EncryptedData() {
		this->data_ = new BYTE[DATASIZE];
	}

	~EncryptedData() {
		delete [] this->data_;
	}

	INLINE void SetData(DataType* in) {
		this->Process((DataProcessCallback)EncryptedData<DataType>::SetDataCallback<DataType>, (void*)in);
	}

	INLINE  void GetData(DataType* out) {
		this->Process((DataProcessCallback)EncryptedData<DataType>::GetDataCallback<DataType>, (void*)out);
	}

	INLINE void Process(DataProcessCallback callback, void* arg) {
		DataType data;
		this->Decode(&data);
		callback(&data, arg);
		this->Encode(&data);
	}
private:
	void XOR(BYTE* in, uint32_t size, BYTE* out) {
		uint32_t key = (uint32_t)this ^ 0x88888888;
		uint32_t r = 4 - (size % 4);
		uint32_t r_data = 0;
		for (uint32_t i = 0; i < size - r; i += 4)
			*(uint32_t*)(out + i) = (*(uint32_t*)(in + i)) ^ key;
		if (r) {
			memcpy_s(&r_data, 4, in + size - r, r);
			r_data ^= key;
			memcpy_s(out + size - r, r, &r_data, r);
		}
	}

	void Decode(DataType* out) {
		this->XOR((BYTE*)this->data_, DATASIZE, (BYTE*)out);
	}

	void Encode(DataType* in) {
		this->XOR((BYTE*)in, DATASIZE, (BYTE*)this->data_);
	}

	BYTE* data_;

	DISALLOW_COPY_AND_ASSIGN(EncryptedData);
};

#endif