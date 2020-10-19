#include "topics.h"
#include "constants.h"

#include <SerialTalks.h>
#include <TaskManager.h>

extern Mutex mutex;
extern uint16_t vl53_measurement[VL53L0X_COUNT];

void GET_ALL(Serializer &output)
{
    for(int i; i < VL53L0X_COUNT; i++)
    {
        mutex.acquire();
        output.write<uint16_t>(vl53_measurement[i]);
        mutex.release();
    }

}