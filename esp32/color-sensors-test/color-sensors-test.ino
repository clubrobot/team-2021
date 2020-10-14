#include <Arduino.h>

#include <SerialTalks.h>
#include <ColorSensorArray.h>

#include "instructions.h"

TCA9548A color_sensor_array_mux;
ColorSensorArray color_sensor_array;

void setup()
{
  // Communication
  Serial.begin(SERIALTALKS_BAUDRATE);
  talks.begin(Serial);

  // Fake reset pin. Should return false.
  color_sensor_array_mux.begin(34);
  color_sensor_array.begin(&color_sensor_array_mux, 23);
  if (!color_sensor_array.begin(1)) {
    // ERROR.
  }

  // bind functions
  talks.bind(CSA_GET_RGB_OPCODE, CSA_GET_RGB);
  talks.bind(CSA_SET_INTEGRATION_TIME_OPCODE, CSA_SET_INTEGRATION_TIME);
  talks.bind(CSA_SET_GAIN_OPCODE, CSA_SET_GAIN);
  talks.bind(CSA_ENABLE_OPCODE, CSA_ENABLE);
  talks.bind(CSA_DISABLE_OPCODE, CSA_DISABLE);
  talks.bind(CSA_LEDS_ON_OPCODE, CSA_LEDS_ON);
  talks.bind(CSA_LEDS_OFF_OPCODE, CSA_LEDS_OFF);
}

void loop()
{
  talks.execute();
  /*float red, green, blue;

  color_sensor_array.getRGB(1, &red, &green, &blue);

  Serial.print("R: "); Serial.print(int(red));
  Serial.print("\tG: "); Serial.print(int(green));
  Serial.print("\tB: "); Serial.print(int(blue));

  Serial.print("\n");*/
}
