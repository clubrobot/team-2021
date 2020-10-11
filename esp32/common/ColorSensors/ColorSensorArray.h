#ifndef _COLOR_SENSOR_ARRAY_
#define _COLOR_SENSOR_ARRAY_

#include <TCA9548A.h>
#include <Adafruit_TCS34725.h>

class ColorSensorArray {
  protected:
  Adafruit_TCS34725 sensor_interface_;
  TCA9548A *mux_;
  uint8_t leds_pin_;

  bool set_channel(uint8_t channel);

  public:
  ColorSensorArray();

  void begin(TCA9548A *mux, uint8_t leds_pin);
  bool begin(uint8_t channel);

  bool getRGB(uint8_t channel, float *r, float *g, float *b);
  bool setIntegrationTime(uint8_t channel, tcs34725IntegrationTime_t it);
  bool setGain(uint8_t channel, tcs34725Gain_t gain);
  bool enable(uint8_t channel);
  bool disable(uint8_t channel);
  void set_leds(uint8_t val);
};

#endif // _COLOR_SENSOR_ARRAY_
