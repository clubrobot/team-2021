#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include <SerialTalks.h>
#include <ColorSensorArray.h>

extern ColorSensorArray color_sensor_array;

#define CSA_GET_RGB_OPCODE 0X10
#define CSA_SET_INTEGRATION_TIME_OPCODE 0X12
#define CSA_SET_GAIN_OPCODE 0X13
#define CSA_ENABLE_OPCODE 0X14
#define CSA_DISABLE_OPCODE 0X15
#define CSA_LEDS_ON_OPCODE 0X16
#define CSA_LEDS_OFF_OPCODE 0X17

void CSA_GET_RGB(SerialTalks &inst, Deserializer &input, Serializer &output);
void CSA_SET_INTEGRATION_TIME(SerialTalks &inst, Deserializer &input, Serializer &output);
void CSA_SET_GAIN(SerialTalks &inst, Deserializer &input, Serializer &output);
void CSA_ENABLE(SerialTalks &inst, Deserializer &input, Serializer &output);
void CSA_DISABLE(SerialTalks &inst, Deserializer &input, Serializer &output);
void CSA_LEDS_ON(SerialTalks &inst, Deserializer &input, Serializer &output);
void CSA_LEDS_OFF(SerialTalks &inst, Deserializer &input, Serializer &output);

#endif // __INSTRUCTIONS_H__
