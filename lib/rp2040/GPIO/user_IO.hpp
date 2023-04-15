#pragma once

#include "user_IO_registers.hpp"
#include <HAL/device_register.hpp>
#include <HAL/simulated_peripheral.hpp>
#include <memory>
#include <optional>

class user_IO : std::conditional<USE_SIMULATED_REGISTERS,
                                 simulated_peripheral<user_IO>, void> {
public:
  ~user_IO();
  void operator delete(void *addr) {
    static_cast<user_IO *>(addr)->~user_IO();
  };

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
  reg::STATUS GPIO0_STATUS;
  reg::CTRL GPIO0_CTRL;
  reg::STATUS GPIO1_STATUS;
  reg::CTRL GPIO1_CTRL;
  reg::STATUS GPIO2_STATUS;
  reg::CTRL GPIO2_CTRL;
  reg::STATUS GPIO3_STATUS;
  reg::CTRL GPIO3_CTRL;
  reg::STATUS GPIO4_STATUS;
  reg::CTRL GPIO4_CTRL;
  reg::STATUS GPIO5_STATUS;
  reg::CTRL GPIO5_CTRL;
  reg::STATUS GPIO6_STATUS;
  reg::CTRL GPIO6_CTRL;
  reg::STATUS GPIO7_STATUS;
  reg::CTRL GPIO7_CTRL;
  reg::STATUS GPIO8_STATUS;
  reg::CTRL GPIO8_CTRL;
  reg::STATUS GPIO9_STATUS;
  reg::CTRL GPIO9_CTRL;
  reg::STATUS GPIO10_STATUS;
  reg::CTRL GPIO10_CTRL;
  reg::STATUS GPIO11_STATUS;
  reg::CTRL GPIO11_CTRL;
  reg::STATUS GPIO12_STATUS;
  reg::CTRL GPIO12_CTRL;
  reg::STATUS GPIO13_STATUS;
  reg::CTRL GPIO13_CTRL;
  reg::STATUS GPIO14_STATUS;
  reg::CTRL GPIO14_CTRL;
  reg::STATUS GPIO15_STATUS;
  reg::CTRL GPIO15_CTRL;
  reg::STATUS GPIO16_STATUS;
  reg::CTRL GPIO16_CTRL;
  reg::STATUS GPIO17_STATUS;
  reg::CTRL GPIO17_CTRL;
  reg::STATUS GPIO18_STATUS;
  reg::CTRL GPIO18_CTRL;
  reg::STATUS GPIO19_STATUS;
  reg::CTRL GPIO19_CTRL;
  reg::STATUS GPIO20_STATUS;
  reg::CTRL GPIO20_CTRL;
  reg::STATUS GPIO21_STATUS;
  reg::CTRL GPIO21_CTRL;
  reg::STATUS GPIO22_STATUS;
  reg::CTRL GPIO22_CTRL;
  reg::STATUS GPIO23_STATUS;
  reg::CTRL GPIO23_CTRL;
  reg::STATUS GPIO24_STATUS;
  reg::CTRL GPIO24_CTRL;
  reg::STATUS GPIO25_STATUS;
  reg::CTRL GPIO25_CTRL;
  reg::STATUS GPIO26_STATUS;
  reg::CTRL GPIO26_CTRL;
  reg::STATUS GPIO27_STATUS;
  reg::CTRL GPIO27_CTRL;
  reg::STATUS GPIO28_STATUS;
  reg::CTRL GPIO28_CTRL;
  reg::STATUS GPIO29_STATUS;
  reg::CTRL GPIO29_CTRL;
  reg::INTR0 INTR0;
  reg::INTR1 INTR1;
  reg::INTR2 INTR2;
  reg::INTR3 INTR3;
  reg::PROC0_INTE0 PROC0_INTE0;
  reg::PROC0_INTE1 PROC0_INTE1;
  reg::PROC0_INTE2 PROC0_INTE2;
  reg::PROC0_INTE3 PROC0_INTE3;
  reg::PROC0_INTF0 PROC0_INTF0;
  reg::PROC0_INTF1 PROC0_INTF1;
  reg::PROC0_INTF2 PROC0_INTF2;
  reg::PROC0_INTF3 PROC0_INTF3;
  reg::PROC0_INTS0 PROC0_INTS0;
  reg::PROC0_INTS1 PROC0_INTS1;
  reg::PROC0_INTS2 PROC0_INTS2;
  reg::PROC0_INTS3 PROC0_INTS3;
  reg::PROC1_INTE0 PROC1_INTE0;
  reg::PROC1_INTE1 PROC1_INTE1;
  reg::PROC1_INTE2 PROC1_INTE2;
  reg::PROC1_INTE3 PROC1_INTE3;
  reg::PROC1_INTF0 PROC1_INTF0;
  reg::PROC1_INTF1 PROC1_INTF1;
  reg::PROC1_INTF2 PROC1_INTF2;
  reg::PROC1_INTF3 PROC1_INTF3;
  reg::PROC1_INTS0 PROC1_INTS0;
  reg::PROC1_INTS1 PROC1_INTS1;
  reg::PROC1_INTS2 PROC1_INTS2;
  reg::PROC1_INTS3 PROC1_INTS3;
  reg::DORMANT_WAKE_INTE0 DORMANT_WAKE_INTE0;
  reg::DORMANT_WAKE_INTE1 DORMANT_WAKE_INTE1;
  reg::DORMANT_WAKE_INTE2 DORMANT_WAKE_INTE2;
  reg::DORMANT_WAKE_INTE3 DORMANT_WAKE_INTE3;
  reg::DORMANT_WAKE_INTF0 DORMANT_WAKE_INTF0;
  reg::DORMANT_WAKE_INTF1 DORMANT_WAKE_INTF1;
  reg::DORMANT_WAKE_INTF2 DORMANT_WAKE_INTF2;
  reg::DORMANT_WAKE_INTF3 DORMANT_WAKE_INTF3;
  reg::DORMANT_WAKE_INTS0 DORMANT_WAKE_INTS0;
  reg::DORMANT_WAKE_INTS1 DORMANT_WAKE_INTS1;
  reg::DORMANT_WAKE_INTS2 DORMANT_WAKE_INTS2;
  reg::DORMANT_WAKE_INTS3 DORMANT_WAKE_INTS3;
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