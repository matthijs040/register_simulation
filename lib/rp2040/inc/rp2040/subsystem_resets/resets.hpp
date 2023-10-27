#pragma once

#include "registers/resets.hpp"
#include <HAL/simulated_peripheral.hpp>
#include <cstdint>
#include <type_traits>

class resets
    : public std::conditional<reg::mock, simulated_peripheral<resets>, void> {
public:
  static constexpr uintptr_t base_address = 0x4000c000;

  reg::RESET RESET;
  reg::WDSEL WDSEL;
  reg::RESET_DONE RESET_DONE;

  static resets &get() noexcept;
  ~resets();
  void operator delete(void *addr);

private:
  resets(/* args */);
  void *operator new(std::size_t);
};
