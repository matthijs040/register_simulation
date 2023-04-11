#pragma once

#include <HAL/device_register.hpp>
#include <HAL/simulated_peripheral.hpp>
#include <memory>
#include <type_traits>

class pad_control : std::conditional<USE_SIMULATED_REGISTERS,
                                     simulated_peripheral<pad_control>, void> {
public:
  static constexpr uintptr_t base_address = 0x4001c000;

  ~pad_control();
  void operator delete(void *addr) {
    static_cast<pad_control *>(addr)->~pad_control();
  };

private:
  pad_control();
  void *operator new(std::size_t) {
    return reinterpret_cast<pad_control *>(base_address);
  }

  static std::weak_ptr<pad_control> storage_handle;
  friend std::shared_ptr<pad_control> std::make_shared<pad_control>();

  device_register VOLTAGE_SELECT; // Voltage select. Per bank control
  device_register GPIO0;          // Pad control register
  device_register GPIO1;          // Pad control register
  device_register GPIO2;          // Pad control register
  device_register GPIO3;          // Pad control register
  device_register GPIO4;          // Pad control register
  device_register GPIO5;          // Pad control register
  device_register GPIO6;          // Pad control register
  device_register GPIO7;          // Pad control register
  device_register GPIO8;          // Pad control register
  device_register GPIO9;          // Pad control register
  device_register GPIO10;         // Pad control register
  device_register GPIO11;         // Pad control register
  device_register GPIO12;         // Pad control register
  device_register GPIO13;         // Pad control register
  device_register GPIO14;         // Pad control register
  device_register GPIO15;         // Pad control register
  device_register GPIO16;         // Pad control register
  device_register GPIO17;         // Pad control register
  device_register GPIO18;         // Pad control register
  device_register GPIO19;         // Pad control register
  device_register GPIO20;         // Pad control register
  device_register GPIO21;         // Pad control register
  device_register GPIO22;         // Pad control register
  device_register GPIO23;         // Pad control register
  device_register GPIO24;         // Pad control register
  device_register GPIO25;         // Pad control register
  device_register GPIO26;         // Pad control register
  device_register GPIO27;         // Pad control register
  device_register GPIO28;         // Pad control register
  device_register GPIO29;         // Pad control register
  device_register SWCLK;          // Pad control register
  device_register SWD;            // Pad control register
};