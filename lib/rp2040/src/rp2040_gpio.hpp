#pragma once

#include "rp2040_defs.hpp"
#include <HAL/device_register.hpp>
#include <HAL/simulated_peripheral.hpp>
#include <memory>
#include <optional>

class rp2040_gpio : std::conditional<USE_SIMULATED_REGISTERS,
                                     simulated_peripheral<rp2040_gpio>, void> {
public:
  ~rp2040_gpio();
  void operator delete(void *){};

private:
  rp2040_gpio();

  void *operator new(std::size_t) {
    return reinterpret_cast<rp2040_gpio *>(base_address);
  }

  static constexpr uintptr_t base_address = 0x40014000;
  static std::weak_ptr<rp2040_gpio> storage_handle;

  // To force users to use make_shared for initialization.
  friend std::shared_ptr<rp2040_gpio> std::make_shared<rp2040_gpio>();

  // Start of non-static member variables:
  device_register GPIO0_STATUS; // GPIO status
  device_register
      GPIO0_CTRL; // GPIO control including function select and overrides.
  device_register GPIO1_STATUS; // GPIO status
  device_register
      GPIO1_CTRL; // GPIO control including function select and overrides.
  device_register GPIO2_STATUS; // GPIO status
  device_register
      GPIO2_CTRL; // GPIO control including function select and overrides.
  device_register GPIO3_STATUS; // GPIO status
  device_register
      GPIO3_CTRL; // GPIO control including function select and overrides.
  device_register GPIO4_STATUS; // GPIO status
  device_register
      GPIO4_CTRL; // GPIO control including function select and overrides.
  device_register GPIO5_STATUS; // GPIO status
  device_register
      GPIO5_CTRL; // GPIO control including function select and overrides.
  device_register GPIO6_STATUS; // GPIO status
  device_register
      GPIO6_CTRL; // GPIO control including function select and overrides.
  device_register GPIO7_STATUS; // GPIO status
  device_register
      GPIO7_CTRL; // GPIO control including function select and overrides.
  device_register GPIO8_STATUS; // GPIO status
  device_register
      GPIO8_CTRL; // GPIO control including function select and overrides.
  device_register GPIO9_STATUS; // GPIO status
  device_register
      GPIO9_CTRL; // GPIO control including function select and overrides.
  device_register GPIO10_STATUS; // GPIO status
  device_register
      GPIO10_CTRL; // GPIO control including function select and overrides.
  device_register GPIO11_STATUS; // GPIO status
  device_register
      GPIO11_CTRL; // GPIO control including function select and overrides.
  device_register GPIO12_STATUS; // GPIO status
  device_register
      GPIO12_CTRL; // GPIO control including function select and overrides.
  device_register GPIO13_STATUS; // GPIO status
  device_register
      GPIO13_CTRL; // GPIO control including function select and overrides.
  device_register GPIO14_STATUS; // GPIO status
  device_register
      GPIO14_CTRL; // GPIO control including function select and overrides.
  device_register GPIO15_STATUS; // GPIO status
  device_register
      GPIO15_CTRL; // GPIO control including function select and overrides.
  device_register GPIO16_STATUS; // GPIO status
  device_register
      GPIO16_CTRL; // GPIO control including function select and overrides.
  device_register GPIO17_STATUS; // GPIO status
  device_register
      GPIO17_CTRL; // GPIO control including function select and overrides.
  device_register GPIO18_STATUS; // GPIO status
  device_register
      GPIO18_CTRL; // GPIO control including function select and overrides.
  device_register GPIO19_STATUS; // GPIO status
  device_register
      GPIO19_CTRL; // GPIO control including function select and overrides.
  device_register GPIO20_STATUS; // GPIO status
  device_register
      GPIO20_CTRL; // GPIO control including function select and overrides.
  device_register GPIO21_STATUS; // GPIO status
  device_register
      GPIO21_CTRL; // GPIO control including function select and overrides.
  device_register GPIO22_STATUS; // GPIO status
  device_register
      GPIO22_CTRL; // GPIO control including function select and overrides.
  device_register GPIO23_STATUS; // GPIO status
  device_register
      GPIO23_CTRL; // GPIO control including function select and overrides.
  device_register GPIO24_STATUS; // GPIO status
  device_register
      GPIO24_CTRL; // GPIO control including function select and overrides.
  device_register GPIO25_STATUS; // GPIO status
  device_register
      GPIO25_CTRL; // GPIO control including function select and overrides.
  device_register GPIO26_STATUS; // GPIO status
  device_register
      GPIO26_CTRL; // GPIO control including function select and overrides.
  device_register GPIO27_STATUS; // GPIO status
  device_register
      GPIO27_CTRL; // GPIO control including function select and overrides.
  device_register GPIO28_STATUS; // GPIO status
  device_register
      GPIO28_CTRL; // GPIO control including function select and overrides.
  device_register GPIO29_STATUS; // GPIO status
  device_register
      GPIO29_CTRL; // GPIO control including function select and overrides.
  device_register INTR0;       // Raw Interrupts
  device_register INTR1;       // Raw Interrupts
  device_register INTR2;       // Raw Interrupts
  device_register INTR3;       // Raw Interrupts
  device_register PROC0_INTE0; // Interrupt Enable for proc0
  device_register PROC0_INTE1; // Interrupt Enable for proc0
  device_register PROC0_INTE2; // Interrupt Enable for proc0
  device_register PROC0_INTE3; // Interrupt Enable for proc0
  device_register PROC0_INTF0; // Interrupt Force for proc0
  device_register PROC0_INTF1; // Interrupt Force for proc0
  device_register PROC0_INTF2; // Interrupt Force for proc0
  device_register PROC0_INTF3; // Interrupt Force for proc0
  device_register
      PROC0_INTS0; // Interrupt status after masking & forcing for proc0
  device_register
      PROC0_INTS1; // Interrupt status after masking & forcing for proc0
  device_register
      PROC0_INTS2; // Interrupt status after masking & forcing for proc0
  device_register
      PROC0_INTS3; // Interrupt status after masking & forcing for proc0
  device_register PROC1_INTE0; // Interrupt Enable for proc1
  device_register PROC1_INTE1; // Interrupt Enable for proc1
  device_register PROC1_INTE2; // Interrupt Enable for proc1
  device_register PROC1_INTE3; // Interrupt Enable for proc1
  device_register PROC1_INTF0; // Interrupt Force for proc1
  device_register PROC1_INTF1; // Interrupt Force for proc1
  device_register PROC1_INTF2; // Interrupt Force for proc1
  device_register PROC1_INTF3; // Interrupt Force for proc1
  device_register
      PROC1_INTS0; // Interrupt status after masking & forcing for proc1
  device_register
      PROC1_INTS1; // Interrupt status after masking & forcing for proc1
  device_register
      PROC1_INTS2; // Interrupt status after masking & forcing for proc1
  device_register
      PROC1_INTS3; // Interrupt status after masking & forcing for proc1
  device_register DORMANT_WAKE_INTE0; // Interrupt Enable for dormant_wake
  device_register DORMANT_WAKE_INTE1; // Interrupt Enable for dormant_wake
  device_register DORMANT_WAKE_INTE2; // Interrupt Enable for dormant_wake
  device_register DORMANT_WAKE_INTE3; // Interrupt Enable for dormant_wake
  device_register DORMANT_WAKE_INTF0; // Interrupt Force for dormant_wake
  device_register DORMANT_WAKE_INTF1; // Interrupt Force for dormant_wake
  device_register DORMANT_WAKE_INTF2; // Interrupt Force for dormant_wake
  device_register DORMANT_WAKE_INTF3; // Interrupt Force for dormant_wake
  device_register DORMANT_WAKE_INTS0; // Interrupt status after masking &
                                      // forcing for dormant_wake
  device_register DORMANT_WAKE_INTS1; // Interrupt status after masking &
                                      // forcing for dormant_wake
  device_register DORMANT_WAKE_INTS2; // Interrupt status after masking &
                                      // forcing for dormant_wake
  device_register DORMANT_WAKE_INTS3; // Interrupt status after masking &
                                      // forcing for dormant_wake
};

template <>
inline std::shared_ptr<rp2040_gpio> std::make_shared<rp2040_gpio>() {
  if (const auto ptr = rp2040_gpio::storage_handle.lock())
    return ptr;

  const auto ptr = USE_SIMULATED_REGISTERS
                       ? std::reinterpret_pointer_cast<rp2040_gpio>(
                             std::shared_ptr<simulated_peripheral<rp2040_gpio>>(
                                 new simulated_peripheral<rp2040_gpio>()))
                       : std::shared_ptr<rp2040_gpio>(new rp2040_gpio());
  rp2040_gpio::storage_handle = ptr;
  return ptr;
}