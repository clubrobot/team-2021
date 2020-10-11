#include "ColorSensorArray.h"
#include <Arduino.h>


ColorSensorArray::ColorSensorArray() : mux_(nullptr), leds_pin_(-1) {
}

bool ColorSensorArray::set_channel(uint8_t channel) {
  /*return*/ this->mux_->set_selected_channels(1 << (channel % 8)) == I2C_ERROR_OK;
  return true;
}

void ColorSensorArray::begin(TCA9548A *mux, uint8_t leds_pin) {
  this->mux_ = mux;
  this->leds_pin_ = leds_pin;
  pinMode(this->leds_pin_, OUTPUT);
  this->set_leds(LOW);
}

bool ColorSensorArray::begin(uint8_t channel) {
  if (!this->set_channel(channel)) {
    return false;
  }
  return this->sensor_interface_.begin(TCS34725_ADDRESS, this->mux_->get_wire());
}

bool ColorSensorArray::getRGB(uint8_t channel, float *r, float *g, float *b) {
  if (!this->set_channel(channel)) {
    return false;
  }
  this->sensor_interface_.getRGB(r, g, b);
}

bool ColorSensorArray::setIntegrationTime(uint8_t channel, tcs34725IntegrationTime_t it) {
  if (!this->set_channel(channel)) {
    return false;
  }
  this->sensor_interface_.setIntegrationTime(it);
}

bool ColorSensorArray::setGain(uint8_t channel, tcs34725Gain_t gain) {
  if (!this->set_channel(channel)) {
    return false;
  }
  this->sensor_interface_.setGain(gain);
}

bool ColorSensorArray::enable(uint8_t channel) {
  if (!this->set_channel(channel)) {
    return false;
  }
  this->sensor_interface_.enable();
}

bool ColorSensorArray::disable(uint8_t channel) {
  if (!this->set_channel(channel)) {
    return false;
  }
  this->sensor_interface_.disable();
}

void ColorSensorArray::set_leds(uint8_t val) {
  digitalWrite(this->leds_pin_, val);
}
