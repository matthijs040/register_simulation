#pragma once

#include "registers/pad_GPIO.hpp"
#include <HAL/simulated_peripheral.hpp>
#include <rp2040/shared_types.hpp>
#include <type_traits>

class pad_control
    : public std::conditional<reg::mock, simulated_peripheral<pad_control>, void> {
public:
  static constexpr uintptr_t base_address = 0x4001c000;

  static pad_control &get() noexcept;

  ~pad_control();
  void operator delete(void *addr);

private:
  pad_control();
  void *operator new(std::size_t);

  reg::VOLTAGE_SELECT VOLTAGE_SELECT; // Voltage select. Per bank control
  reg::GPIO GPIO0;                    // Pad control register
  reg::GPIO GPIO1;                    // Pad control register
  reg::GPIO GPIO2;                    // Pad control register
  reg::GPIO GPIO3;                    // Pad control register
  reg::GPIO GPIO4;                    // Pad control register
  reg::GPIO GPIO5;                    // Pad control register
  reg::GPIO GPIO6;                    // Pad control register
  reg::GPIO GPIO7;                    // Pad control register
  reg::GPIO GPIO8;                    // Pad control register
  reg::GPIO GPIO9;                    // Pad control register
  reg::GPIO GPIO10;                   // Pad control register
  reg::GPIO GPIO11;                   // Pad control register
  reg::GPIO GPIO12;                   // Pad control register
  reg::GPIO GPIO13;                   // Pad control register
  reg::GPIO GPIO14;                   // Pad control register
  reg::GPIO GPIO15;                   // Pad control register
  reg::GPIO GPIO16;                   // Pad control register
  reg::GPIO GPIO17;                   // Pad control register
  reg::GPIO GPIO18;                   // Pad control register
  reg::GPIO GPIO19;                   // Pad control register
  reg::GPIO GPIO20;                   // Pad control register
  reg::GPIO GPIO21;                   // Pad control register
  reg::GPIO GPIO22;                   // Pad control register
  reg::GPIO GPIO23;                   // Pad control register
  reg::GPIO GPIO24;                   // Pad control register
  reg::GPIO GPIO25;                   // Pad control register
  reg::GPIO GPIO26;                   // Pad control register
  reg::GPIO GPIO27;                   // Pad control register
  reg::GPIO GPIO28;                   // Pad control register
  reg::GPIO GPIO29;                   // Pad control register
  reg::GPIO SWCLK;                    // Pad control register
  reg::GPIO SWD;                      // Pad control register
};
