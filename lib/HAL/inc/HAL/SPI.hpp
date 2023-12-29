#pragma once

#include "system/error_code.hpp"
#include <HAL/GPIO.hpp>

class SPI {
private:
  /* data */
public:
  const struct pins {
    GPIO::pin_number clock_pin;
    GPIO::pin_number chip_select_pin;
    GPIO::pin_number transmit_pin;
    GPIO::pin_number receive_pin;
  } used_pins;

  const enum class mode { Motorola, TI_synchronous, Microwire } used_mode;

  SPI();
  ~SPI();
};