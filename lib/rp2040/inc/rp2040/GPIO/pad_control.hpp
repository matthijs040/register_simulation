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
  void operator delete(void *addr);

private:
  pad_control();
  void *operator new(std::size_t);

  static inline std::weak_ptr<pad_control> storage_handle;
  friend std::shared_ptr<pad_control> std::make_shared<pad_control>();

  register_integral VOLTAGE_SELECT; // Voltage select. Per bank control
  register_integral GPIO0;          // Pad control register
  register_integral GPIO1;          // Pad control register
  register_integral GPIO2;          // Pad control register
  register_integral GPIO3;          // Pad control register
  register_integral GPIO4;          // Pad control register
  register_integral GPIO5;          // Pad control register
  register_integral GPIO6;          // Pad control register
  register_integral GPIO7;          // Pad control register
  register_integral GPIO8;          // Pad control register
  register_integral GPIO9;          // Pad control register
  register_integral GPIO10;         // Pad control register
  register_integral GPIO11;         // Pad control register
  register_integral GPIO12;         // Pad control register
  register_integral GPIO13;         // Pad control register
  register_integral GPIO14;         // Pad control register
  register_integral GPIO15;         // Pad control register
  register_integral GPIO16;         // Pad control register
  register_integral GPIO17;         // Pad control register
  register_integral GPIO18;         // Pad control register
  register_integral GPIO19;         // Pad control register
  register_integral GPIO20;         // Pad control register
  register_integral GPIO21;         // Pad control register
  register_integral GPIO22;         // Pad control register
  register_integral GPIO23;         // Pad control register
  register_integral GPIO24;         // Pad control register
  register_integral GPIO25;         // Pad control register
  register_integral GPIO26;         // Pad control register
  register_integral GPIO27;         // Pad control register
  register_integral GPIO28;         // Pad control register
  register_integral GPIO29;         // Pad control register
  register_integral SWCLK;          // Pad control register
  register_integral SWD;            // Pad control register
};

template <> inline std::shared_ptr<pad_control> std::make_shared<pad_control>() {
  if (const auto ptr = pad_control::storage_handle.lock())
    return ptr;

  auto ptr = std::shared_ptr<pad_control>();
  if (USE_SIMULATED_REGISTERS) {
    ptr = std::reinterpret_pointer_cast<pad_control>(
        std::shared_ptr<simulated_peripheral<pad_control>>(
            new simulated_peripheral<pad_control>()));
  } else {
    ptr = std::shared_ptr<pad_control>(new pad_control());
  }
  ::new (ptr.get()) pad_control();

  pad_control::storage_handle = ptr;
  return ptr;
}