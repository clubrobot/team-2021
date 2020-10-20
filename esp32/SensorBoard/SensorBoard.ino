#include <Arduino.h>

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

ShiftRegister ShutdownRegister(SHIFT_REG_SIZE);

VL53L0X vl53_1 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_1_SHUTDOWN_INDEX, &ShutdownRegister);
// VL53L0X vl53_2 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_2_SHUTDOWN_INDEX, &ShutdownRegister);
// VL53L0X vl53_3 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_3_SHUTDOWN_INDEX, &ShutdownRegister);
// VL53L0X vl53_4 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_4_SHUTDOWN_INDEX, &ShutdownRegister);
// VL53L0X vl53_5 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_5_SHUTDOWN_INDEX, &ShutdownRegister);
// VL53L0X vl53_6 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_6_SHUTDOWN_INDEX, &ShutdownRegister);
// VL53L0X vl53_7 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_7_SHUTDOWN_INDEX, &ShutdownRegister);
// VL53L0X vl53_8 = VL53L0X(VL53L0X_1_I2C_ADDR, VL53L0X_8_SHUTDOWN_INDEX, &ShutdownRegister);

// VL6180X vl61_1 = VL6180X(VL6180X_1_I2C_ADDR, VL6180X_1_SHUTDOWN_INDEX, &ShutdownRegister);
// VL6180X vl61_2 = VL6180X(VL6180X_2_I2C_ADDR, VL6180X_2_SHUTDOWN_INDEX, &ShutdownRegister);
// VL6180X vl61_3 = VL6180X(VL6180X_3_I2C_ADDR, VL6180X_3_SHUTDOWN_INDEX, &ShutdownRegister);
// VL6180X vl61_4 = VL6180X(VL6180X_4_I2C_ADDR, VL6180X_4_SHUTDOWN_INDEX, &ShutdownRegister);
// VL6180X vl61_5 = VL6180X(VL6180X_5_I2C_ADDR, VL6180X_5_SHUTDOWN_INDEX, &ShutdownRegister);
// VL6180X vl61_6 = VL6180X(VL6180X_6_I2C_ADDR, VL6180X_6_SHUTDOWN_INDEX, &ShutdownRegister);
// VL6180X vl61_7 = VL6180X(VL6180X_7_I2C_ADDR, VL6180X_7_SHUTDOWN_INDEX, &ShutdownRegister);
// VL6180X vl61_8 = VL6180X(VL6180X_8_I2C_ADDR, VL6180X_8_SHUTDOWN_INDEX, &ShutdownRegister);

void setup()
{
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
    // vl53_1.shutdown();
    // vl53_2.shutdown();
    // vl53_3.shutdown();
    // vl53_4.shutdown();
    // vl53_5.shutdown();
    // vl53_6.shutdown();
    // vl53_7.shutdown();
    // vl53_8.shutdown();

    // Shutdown all VL6180X sensors
    // vl61_1.shutdown();
    // vl61_2.shutdown();
    // vl61_3.shutdown();
    // vl61_4.shutdown();
    // vl61_5.shutdown();
    // vl61_6.shutdown();
    // vl61_7.shutdown();
    // vl61_8.shutdown();

    // Starting all VL53L0X sensors
    // vl53_1.begin();
    // vl53_2.begin();
    // vl53_3.begin();
    // vl53_4.begin();
    // vl53_5.begin();
    // vl53_6.begin();
    // vl53_7.begin();
    // vl53_8.begin();

    // Starting all VL6180X sensors
    // vl61_1.begin();
    // vl61_2.begin();
    // vl61_3.begin();
    // vl61_4.begin();
    // vl61_5.begin();
    // vl61_6.begin();
    // vl61_7.begin();
    // vl61_8.begin();

    // Set all VL53L0X timeout in ms
    // vl53_1.setTimeout(30);
    // vl53_2.setTimeout(30);
    // vl53_3.setTimeout(30);
    // vl53_4.setTimeout(30);
    // vl53_5.setTimeout(30);
    // vl53_6.setTimeout(30);
    // vl53_7.setTimeout(30);
    // vl53_8.setTimeout(30);

    // Set all VL6180X timeout in ms
    // vl61_1.setTimeout(30);
    // vl61_2.setTimeout(30);
    // vl61_3.setTimeout(30);
    // vl61_4.setTimeout(30);
    // vl61_5.setTimeout(30);
    // vl61_6.setTimeout(30);
    // vl61_7.setTimeout(30);
    // vl61_8.setTimeout(30);

    // Configure all VL6180X as default
    // vl61_1.configureDefault();
    // vl61_2.configureDefault();
    // vl61_3.configureDefault();
    // vl61_4.configureDefault();
    // vl61_5.configureDefault();
    // vl61_6.configureDefault();
    // vl61_7.configureDefault();
    // vl61_8.configureDefault();

    // Starting all VL53L0X measure
    // vl53_1.startContinuous();
    // vl53_2.startContinuous();
    // vl53_3.startContinuous();
    // vl53_4.startContinuous();
    // vl53_5.startContinuous();
    // vl53_6.startContinuous();
    // vl53_7.startContinuous();
    // vl53_8.startContinuous();

    // Starting all VL6180X measure
    // vl61_1.startRangeContinuous(60);
    // vl61_2.startRangeContinuous(60);
    // vl61_3.startRangeContinuous(60);
    // vl61_4.startRangeContinuous(60);
    // vl61_5.startRangeContinuous(60);
    // vl61_6.startRangeContinuous(60);
    // vl61_7.startRangeContinuous(60);
    // vl61_8.startRangeContinuous(60);
}

// Loop

void loop()
{
    talks.execute();
    topics.execute();

    // Debug
    // Serial.println(vl53_1.readRangeContinuousMillimeters());
}
