#include "instructions.h"
#include "constants.h"

#include <SerialTalks.h>
#include <TaskManager.h>

extern Mutex mutex;

extern uint16_t vl53_status[VL53L0X_COUNT];
extern uint16_t vl53_measurement[VL53L0X_COUNT];

void GET_SENSOR1(SerialTalks &inst, Deserializer &input, Serializer &output)
{
    mutex.acquire();
    output.write<uint16_t>(vl53_measurement[0]);
    mutex.release();
}

void GET_SENSOR2(SerialTalks &inst, Deserializer &input, Serializer &output)
{
    mutex.acquire();
    output.write<uint16_t>(vl53_measurement[1]);
    mutex.release();
}

void GET_SENSOR3(SerialTalks &inst, Deserializer &input, Serializer &output)
{
    mutex.acquire();
    output.write<uint16_t>(vl53_measurement[2]);
    mutex.release();
}

void GET_SENSOR4(SerialTalks &inst, Deserializer &input, Serializer &output)
{
    mutex.acquire();
    output.write<uint16_t>(vl53_measurement[3]);
    mutex.release();
}

void GET_SENSOR5(SerialTalks &inst, Deserializer &input, Serializer &output)
{
    mutex.acquire();
    output.write<uint16_t>(vl53_measurement[4]);
    mutex.release();
}

void GET_SENSOR6(SerialTalks &inst, Deserializer &input, Serializer &output)
{
    mutex.acquire();
    output.write<uint16_t>(vl53_measurement[5]);
    mutex.release();
}

void GET_SENSOR7(SerialTalks &inst, Deserializer &input, Serializer &output)
{
    mutex.acquire();
    output.write<uint16_t>(vl53_measurement[6]);
    mutex.release();
}

void GET_SENSOR8(SerialTalks &inst, Deserializer &input, Serializer &output)
{
    mutex.acquire();
    output.write<uint16_t>(vl53_measurement[7]);
    mutex.release();
}

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