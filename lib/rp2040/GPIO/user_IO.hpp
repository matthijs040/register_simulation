#pragma once

#include "types.hpp"
#include <HAL/device_register.hpp>
#include <HAL/simulated_peripheral.hpp>
#include <memory>
#include <optional>

class user_IO : std::conditional<USE_SIMULATED_REGISTERS, simulated_peripheral<user_IO>,
                            void> {
public:
  ~user_IO();
  void operator delete(void *addr) { static_cast<user_IO *>(addr)->~user_IO(); };

private:
  user_IO();

  void *operator new(std::size_t) {
    return reinterpret_cast<user_IO *>(base_address);
  }

  static constexpr uintptr_t base_address = 0x40014000;
  static std::weak_ptr<user_IO> storage_handle;

  // To force users to use make_shared for initialization.
  friend std::shared_ptr<user_IO> std::make_shared<user_IO>();

  // Start of non-static member variables:
  stub_register GPIO0_STATUS;       // GPIO status
  stub_register GPIO0_CTRL;         // GPIO control
  stub_register GPIO1_STATUS;       // GPIO status
  stub_register GPIO1_CTRL;         // GPIO control
  stub_register GPIO2_STATUS;       // GPIO status
  stub_register GPIO2_CTRL;         // GPIO control
  stub_register GPIO3_STATUS;       // GPIO status
  stub_register GPIO3_CTRL;         // GPIO control
  stub_register GPIO4_STATUS;       // GPIO status
  stub_register GPIO4_CTRL;         // GPIO control
  stub_register GPIO5_STATUS;       // GPIO status
  stub_register GPIO5_CTRL;         // GPIO control
  stub_register GPIO6_STATUS;       // GPIO status
  stub_register GPIO6_CTRL;         // GPIO control
  stub_register GPIO7_STATUS;       // GPIO status
  stub_register GPIO7_CTRL;         // GPIO control
  stub_register GPIO8_STATUS;       // GPIO status
  stub_register GPIO8_CTRL;         // GPIO control
  stub_register GPIO9_STATUS;       // GPIO status
  stub_register GPIO9_CTRL;         // GPIO control
  stub_register GPIO10_STATUS;      // GPIO status
  stub_register GPIO10_CTRL;        // GPIO control
  stub_register GPIO11_STATUS;      // GPIO status
  stub_register GPIO11_CTRL;        // GPIO control
  stub_register GPIO12_STATUS;      // GPIO status
  stub_register GPIO12_CTRL;        // GPIO control
  stub_register GPIO13_STATUS;      // GPIO status
  stub_register GPIO13_CTRL;        // GPIO control
  stub_register GPIO14_STATUS;      // GPIO status
  stub_register GPIO14_CTRL;        // GPIO control
  stub_register GPIO15_STATUS;      // GPIO status
  stub_register GPIO15_CTRL;        // GPIO control
  stub_register GPIO16_STATUS;      // GPIO status
  stub_register GPIO16_CTRL;        // GPIO control
  stub_register GPIO17_STATUS;      // GPIO status
  stub_register GPIO17_CTRL;        // GPIO control
  stub_register GPIO18_STATUS;      // GPIO status
  stub_register GPIO18_CTRL;        // GPIO control
  stub_register GPIO19_STATUS;      // GPIO status
  stub_register GPIO19_CTRL;        // GPIO control
  stub_register GPIO20_STATUS;      // GPIO status
  stub_register GPIO20_CTRL;        // GPIO control
  stub_register GPIO21_STATUS;      // GPIO status
  stub_register GPIO21_CTRL;        // GPIO control
  stub_register GPIO22_STATUS;      // GPIO status
  stub_register GPIO22_CTRL;        // GPIO control
  stub_register GPIO23_STATUS;      // GPIO status
  stub_register GPIO23_CTRL;        // GPIO control
  stub_register GPIO24_STATUS;      // GPIO status
  stub_register GPIO24_CTRL;        // GPIO control
  stub_register GPIO25_STATUS;      // GPIO status
  stub_register GPIO25_CTRL;        // GPIO control
  stub_register GPIO26_STATUS;      // GPIO status
  stub_register GPIO26_CTRL;        // GPIO control
  stub_register GPIO27_STATUS;      // GPIO status
  stub_register GPIO27_CTRL;        // GPIO control
  stub_register GPIO28_STATUS;      // GPIO status
  stub_register GPIO28_CTRL;        // GPIO control
  stub_register GPIO29_STATUS;      // GPIO status
  stub_register GPIO29_CTRL;        // GPIO control
  stub_register INTR0;              // Raw Interrupts
  stub_register INTR1;              // Raw Interrupts
  stub_register INTR2;              // Raw Interrupts
  stub_register INTR3;              // Raw Interrupts
  stub_register PROC0_INTE0;        // Interrupt Enable for proc0
  stub_register PROC0_INTE1;        // Interrupt Enable for proc0
  stub_register PROC0_INTE2;        // Interrupt Enable for proc0
  stub_register PROC0_INTE3;        // Interrupt Enable for proc0
  stub_register PROC0_INTF0;        // Interrupt Force for proc0
  stub_register PROC0_INTF1;        // Interrupt Force for proc0
  stub_register PROC0_INTF2;        // Interrupt Force for proc0
  stub_register PROC0_INTF3;        // Interrupt Force for proc0
  stub_register PROC0_INTS0;        // Interrupt status for proc0
  stub_register PROC0_INTS1;        // Interrupt status for proc0
  stub_register PROC0_INTS2;        // Interrupt status for proc0
  stub_register PROC0_INTS3;        // Interrupt status for proc0
  stub_register PROC1_INTE0;        // Interrupt Enable for proc1
  stub_register PROC1_INTE1;        // Interrupt Enable for proc1
  stub_register PROC1_INTE2;        // Interrupt Enable for proc1
  stub_register PROC1_INTE3;        // Interrupt Enable for proc1
  stub_register PROC1_INTF0;        // Interrupt Force for proc1
  stub_register PROC1_INTF1;        // Interrupt Force for proc1
  stub_register PROC1_INTF2;        // Interrupt Force for proc1
  stub_register PROC1_INTF3;        // Interrupt Force for proc1
  stub_register PROC1_INTS0;        // Interrupt status for proc1
  stub_register PROC1_INTS1;        // Interrupt status for proc1
  stub_register PROC1_INTS2;        // Interrupt status for proc1
  stub_register PROC1_INTS3;        // Interrupt status for proc1
  stub_register DORMANT_WAKE_INTE0; // Interrupt Enable for dormant_wake
  stub_register DORMANT_WAKE_INTE1; // Interrupt Enable for dormant_wake
  stub_register DORMANT_WAKE_INTE2; // Interrupt Enable for dormant_wake
  stub_register DORMANT_WAKE_INTE3; // Interrupt Enable for dormant_wake
  stub_register DORMANT_WAKE_INTF0; // Interrupt Force for dormant_wake
  stub_register DORMANT_WAKE_INTF1; // Interrupt Force for dormant_wake
  stub_register DORMANT_WAKE_INTF2; // Interrupt Force for dormant_wake
  stub_register DORMANT_WAKE_INTF3; // Interrupt Force for dormant_wake
  stub_register DORMANT_WAKE_INTS0; // Interrupt Status for dormant_wake
  stub_register DORMANT_WAKE_INTS1; // Interrupt Status for dormant_wake
  stub_register DORMANT_WAKE_INTS2; // Interrupt Status for dormant_wake
  stub_register DORMANT_WAKE_INTS3; // Interrupt Status for dormant_wake
};

template <> inline std::shared_ptr<user_IO> std::make_shared<user_IO>() {
  if (const auto ptr = user_IO::storage_handle.lock())
    return ptr;

  auto ptr = std::shared_ptr<user_IO>();
  if (USE_SIMULATED_REGISTERS) {
    ptr = std::reinterpret_pointer_cast<user_IO>(
        std::shared_ptr<simulated_peripheral<user_IO>>(
            new simulated_peripheral<user_IO>()));
  } else {
    ptr = std::shared_ptr<user_IO>(new user_IO());
  }
  ::new (ptr.get()) user_IO();

  user_IO::storage_handle = ptr;
  return ptr;
}