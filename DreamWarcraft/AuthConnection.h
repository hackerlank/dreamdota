#include "stdafx.h"
#ifndef AUTH_CONNECTION_H_INCLUDED
#define AUTH_CONNECTION_H_INCLUDED

#include "../DreamAuth2/Pipe.h"
#include "Profile.h"
#include "Foundation.h"
#include "Version.h"
#include <fp_call.h>

extern PipeContext AuthConnection_Ctx;

INLINE bool AuthConnection_Init(void* smem) {
#ifndef _SERVERSTRING
	Profile_Init(GetPath(PROFILE_FILENAME));
	strcpy_s(RootPath, sizeof(RootPath), GetSelfPath());
	return true;
#endif
	bool rv = false;
	BYTE buffer[RSA_SIZE + MAX_PATH];
	memcpy_s(&AuthConnection_Ctx, sizeof(PipeContext), smem, sizeof(PipeContext));
	memset(smem, 0, sizeof(PipeContext));
	if (Pipe_Connect(&AuthConnection_Ctx)) {
		BYTE req = PIPE_MESSAGE_REQUEST_DATA;
		DWORD bytes = 0;

		#ifdef _MSC_VER
		#pragma pack(push, 1)
		#endif // _MSC_VER
		struct {
			BYTE req;
			uint32_t revision;
		} conn_packet = {
			req,
			VERSION.revision
		};
		#ifdef _MSC_VER
		#pragma pack(pop)
		#endif // _MSC_VER

		rv = 
			Pipe_Write(&AuthConnection_Ctx, &conn_packet, sizeof(conn_packet), &bytes) && bytes == sizeof(conn_packet) &&
			Pipe_Read(&AuthConnection_Ctx, buffer, sizeof(buffer), &bytes) && bytes > RSA_SIZE;

		if (rv) {
			memcpy_s(PUBLIC_ENCRYPTED_KEY, RSA_SIZE, buffer, RSA_SIZE);
			strcpy_s(RootPath, sizeof(RootPath), aero::pointer_calc<char*>(buffer, RSA_SIZE));
			char path[MAX_PATH];
			sprintf_s(path, "%s\\%s", RootPath, PROFILE_FILENAME);
			Profile_Init(path);
		}
	}
	return rv;
}

INLINE void AuthConnection_Cleanup() {
	Pipe_Term(&AuthConnection_Ctx);
}

#endif