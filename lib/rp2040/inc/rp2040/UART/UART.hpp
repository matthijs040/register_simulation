#pragma once

#include <HAL/simulated_peripheral.hpp>
#include <cstdint>
#include <type_traits>

class UART : std::conditional<USE_SIMULATED_REGISTERS,
                              simulated_peripheral<UART>, void> {
public:
  static constexpr uintptr_t base_address_0 = 0x40034000;
  static constexpr uintptr_t base_address_1 = 0x40038000;

  enum class ID { first, second };
  static UART &get(ID which) noexcept;
  ~UART();
  void operator delete(void *addr);

private:
  UART(/* args */);
  void *operator new(std::size_t);
};