#ifndef _COLOR_SENSOR_ARRAY_
#define _COLOR_SENSOR_ARRAY_

#include "TCA9548A.h"
#include "Adafruit_TCS34725.h"

class ColorSensorArray {
  protected:
  TCA9548A *mux_;
  Adafruit_TCS34725 sensor_interface_;

  void set_channel(uint8_t channel);

  public:
  ColorSensorArray(tcs34725IntegrationTime_t it = TCS34725_INTEGRATIONTIME_2_4MS,
                   tcs34725Gain_t gain = TCS34725_GAIN_1X);

  void begin(uint8_t reset_pin, uint8_t mux_address = TCA9548A_DEFAULT_ADDRESS, TwoWire *wire = &Wire);
  bool begin(uint8_t channel);

  void getRGB(uint8_t channel, float *r, float *g, float *b);
  void enable(uint8_t channel);
  void disable(uint8_t channel);
};

#endif // _COLOR_SENSOR_ARRAY_
