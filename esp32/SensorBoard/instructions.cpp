#include "instructions.h"

#include <SerialTalks.h>

void CHECK_ERROR(SerialTalks &inst, Deserializer &input, Serializer &output)
{
    uint8_t error = 0;

    error |= (1 << 1);
    output.write<uint8_t>(error);
}