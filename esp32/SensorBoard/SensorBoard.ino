#include <Arduino.h>

#include "instructions.h"
#include "topics.h"
#include "PIN.h"
#include "constants.h"

#include <SerialTalks.h>
#include <SerialTopics.h>
#include <ShiftRegister.h>

ShiftRegister shutdown_register(SHIFT_REG_SIZE);

void setup()
{
    // Communication
    Serial.begin(SERIALTALKS_BAUDRATE);
    talks.begin(Serial);
    topics.begin(talks);

    // bind functions
    talks.bind(ON_OPCODE, ON);
    talks.bind(OFF_OPCODE, OFF);

    //bind subscription
    topics.bind(SUBSCRIPTION_OPCODE, SUBSCRIPTION);

    pinMode(2, OUTPUT);
}

// Loop

void loop()
{
    talks.execute();
    topics.execute();
}
