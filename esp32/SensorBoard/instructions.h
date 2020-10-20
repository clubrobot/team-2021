#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include <SerialTalks.h>

#define CHECK_ERROR_OPCODE 0x18

void CHECK_ERROR(SerialTalks &inst, Deserializer &input, Serializer &output);

#endif // __INSTRUCTIONS_H__
