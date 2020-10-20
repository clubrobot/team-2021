#include "topics.h"

#include <SerialTalks.h>

static uint16_t i = 0;

void GET_ALL(Serializer &output)
{
    output.write<uint16_t>(i);
    output.write<uint16_t>(i);
    output.write<uint16_t>(i);
    output.write<uint16_t>(i);
    output.write<uint16_t>(i);
    output.write<uint16_t>(i);
    output.write<uint16_t>(i);
    output.write<uint16_t>(i);

    i++;
}