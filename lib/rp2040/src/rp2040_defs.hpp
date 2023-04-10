#pragma once
#include <HAL/device_register.hpp>

enum class GPIO_FUNCSEL : register_mask {
  SPI = 1,
  UART = 2,
  I2C = 3,
  PWM = 4,
  SIO = 5,
  PIO0 = 6,
  PIO1 = 7,
  Clock_GPIO = 8,
  USB = 9,
  Disabled = 0x1F
};