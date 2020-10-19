#include "instructions.h"
#include "constants.h"

#include <SerialTalks.h>

extern uint16_t vl53_status[VL53L0X_COUNT];

void CHECK_ERROR(SerialTalks &inst, Deserializer &input, Serializer &output)
{
    uint8_t error = 0;

    for(int i; i < VL53L0X_COUNT; i++)
    {
        if(vl53_status[i] == 1)
        {
            error |= (1 << i);
        }
    }

    output.write<uint8_t>(error);
}