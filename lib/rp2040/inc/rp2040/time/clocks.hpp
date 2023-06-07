#pragma once

#include <HAL/device_register.hpp>
#include <HAL/simulated_peripheral.hpp>
#include <type_traits>

class clocks : std::conditional<USE_SIMULATED_REGISTERS,
                                     simulated_peripheral<clocks>, void> {
public:
  static constexpr uintptr_t base_address = 0x40008000;

  static clocks& get() noexcept;

  ~clocks();
  void operator delete(void *addr);

private:
  clocks();
  void *operator new(std::size_t);

};