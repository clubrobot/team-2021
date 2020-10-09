#include <Arduino.h>
#include <Adafruit_TCS34725.h>

#include <SerialTalks.h>

Adafruit_TCS34725 color_sensor;

void setup()
{
  // Communication
  Serial.begin(SERIALTALKS_BAUDRATE);
  //talks.begin(Serial);
  pinMode(2, OUTPUT);
  if (color_sensor.begin()) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }
  pinMode(23, OUTPUT); // LED pin.
  digitalWrite(23, LOW);
}

void loop()
{
  float red, green, blue;
  delay(60);  // takes 50ms to read

  color_sensor.getRGB(&red, &green, &blue);
  //talks.execute();

  Serial.print("R:\t"); Serial.print(int(red));
  Serial.print("\tG:\t"); Serial.print(int(green));
  Serial.print("\tB:\t"); Serial.print(int(blue));

  Serial.print("\n");
}
