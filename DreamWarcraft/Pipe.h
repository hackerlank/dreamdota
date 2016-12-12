#include "stdafx.h"
#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED

bool Pipe_Init();
void Pipe_Cleanup();
uint32_t Pipe_Write(void* message, uint32_t message_size);
uint32_t Pipe_Read(void* buffer, uint32_t buffer_size);

#endif