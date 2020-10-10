#include "ColorSensorArray.h"


ColorSensorArray::ColorSensorArray(
  tcs34725IntegrationTime_t it,
  tcs34725Gain_t gain)
    : mux_(nullptr), sensor_interface_(it, gain) {
}


void ColorSensorArray::set_channel(uint8_t channel) {
  this->mux_->set_selected_channels(1 << (channel % 8));
}

void ColorSensorArray::begin(uint8_t reset_pin, uint8_t mux_address, TwoWire *wire) {
  this->mux_->begin(reset_pin, mux_address, wire);
}

bool ColorSensorArray::begin(uint8_t channel) {
  this->set_channel(channel);
  return this->sensor_interface_.begin(TCS34725_ADDRESS, this->mux_->get_wire());
}

void ColorSensorArray::getRGB(uint8_t channel, float *r, float *g, float *b) {
  this->set_channel(channel);
  this->sensor_interface_.getRGB(r, g, b);
}

void ColorSensorArray::enable(uint8_t channel) {
  this->set_channel(channel);
  this->sensor_interface_.enable();
}

void ColorSensorArray::disable(uint8_t channel) {
  this->set_channel(channel);
  this->sensor_interface_.disable();
}
