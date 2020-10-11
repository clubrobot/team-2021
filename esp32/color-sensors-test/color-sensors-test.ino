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

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  // Fake reset pin. Should return false.
  /*color_sensor_array_mux.begin(34);
  color_sensor_array.begin(&color_sensor_array_mux, 23);
  if (color_sensor_array.begin(1)) {
    digitalWrite(2, HIGH);
  }
  color_sensor_array.setIntegrationTime(1, TCS34725_INTEGRATIONTIME_700MS);*/

  // bind functions
  talks.bind(ON_OPCODE, ON);
  talks.bind(OFF_OPCODE, OFF);
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
