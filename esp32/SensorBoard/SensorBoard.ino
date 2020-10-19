#include <Arduino.h>
#include <list>

#include "instructions.h"
#include "topics.h"
#include "PIN.h"
#include "constants.h"

#include <Wire.h>
#include <SerialTalks.h>
#include <SerialTopics.h>
#include <ShiftRegister.h>
#include <VL53L0X.h>
#include <VL6180X.h>
#include <TaskManager.h>

using namespace std;

TaskManager tm;

Mutex mutex;

ShiftRegister ShutdownRegister(SHIFT_REGISTER_2_BYTES);

VL53L0X vl53_1 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_1_SHUTDOWN_INDEX, &ShutdownRegister);
VL53L0X vl53_2 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_2_SHUTDOWN_INDEX, &ShutdownRegister);
VL53L0X vl53_3 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_3_SHUTDOWN_INDEX, &ShutdownRegister);
VL53L0X vl53_4 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_4_SHUTDOWN_INDEX, &ShutdownRegister);
VL53L0X vl53_5 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_5_SHUTDOWN_INDEX, &ShutdownRegister);
VL53L0X vl53_6 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_6_SHUTDOWN_INDEX, &ShutdownRegister);
VL53L0X vl53_7 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_7_SHUTDOWN_INDEX, &ShutdownRegister);
VL53L0X vl53_8 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_8_SHUTDOWN_INDEX, &ShutdownRegister);

list<VL53L0X*> sensors_vl53 = {&vl53_1, &vl53_2, &vl53_3, &vl53_4, &vl53_5, &vl53_6, &vl53_7, &vl53_8};

uint8_t vl53_status[VL53L0X_COUNT] = {0, };
uint16_t vl53_measurement[VL53L0X_COUNT] = {65535, };


// Second loop prototype
void loop_aux(void *aux);

void setup()
{
    static int count = 0;

    // Attach shift register pin
    ShutdownRegister.attach(SHIFT_REG_LATCH, SHIFT_REG_CLOCK, SHIFT_REG_DATA);

    // I2C Communication
    Wire.begin();

    // Serial Communication
    Serial.begin(SERIALTALKS_BAUDRATE);
    talks.begin(Serial);
    topics.begin(talks);

    // bind functions
    talks.bind(CHECK_ERROR_OPCODE, CHECK_ERROR);

    //bind subscription
    topics.bind(GET_ALL_OPCODE, GET_ALL);

    // Shutdown all VL53L0X sensors
    for (const auto& cur_sensor : sensors_vl53)
    {
        cur_sensor->shutdown();
    }

    // Starting all VL53L0X sensors
    for (const auto& cur_sensor : sensors_vl53)
    {
        if(!cur_sensor->begin())
        {
            vl53_status[count++] = 1;
        }
    }
    count = 0;

    // Set all VL53L0X timeout in ms
    for (const auto& cur_sensor : sensors_vl53)
    {
        cur_sensor->setTimeout(30);
    }

    // Starting all VL53L0X measure
    for (const auto& cur_sensor : sensors_vl53)
    {
        cur_sensor->startContinuous();
    }

    // Starting Second thread
    tm.create_task(loop_aux, NULL);

}

// Loop
void loop()
{
    talks.execute();
    topics.execute();

    //Yield
    vTaskDelay(pdMS_TO_TICKS(1));
}

// Second loop on core 1
void loop_aux(void *aux)
{
    static int count = 0;
    for(;;)
    {
        for (const auto& cur_sensor : sensors_vl53)
        {
            mutex.acquire();
            vl53_measurement[count++] = cur_sensor->readRangeContinuousMillimeters();
            mutex.release();
        }
        count = 0;
    }

    //Yield
    vTaskDelay(pdMS_TO_TICKS(1));
}
