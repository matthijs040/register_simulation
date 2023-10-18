#pragma once

#include "registers/ROSC.hpp"
#include <HAL/device_register.hpp>
#include <HAL/simulated_peripheral.hpp>
#include <type_traits>
#include <system_error>
#include <expected>

class ROSC : std::conditional<USE_SIMULATED_REGISTERS,
                              simulated_peripheral<ROSC>, void> {
public:
  static constexpr uintptr_t base_address = 0x40060000;
  static ROSC &get() noexcept;
  ~ROSC();
  void operator delete(void *addr);

  std::expected<uint32_t, std::error_code> get_frequency_kHz();

  reg::ROSC::CTRL CTRL;
  reg::ROSC::FREQA FREQA;
  reg::ROSC::FREQB FREQB;
  reg::ROSC::DORMANT DORMANT;
  reg::ROSC::DIV DIV;
  reg::ROSC::PHASE PHASE;
  reg::ROSC::STATUS STATUS;
  reg::ROSC::RANDOMBIT RANDOMBIT;
  reg::ROSC::COUNT COUNT;

private:
  ROSC();
  void *operator new(std::size_t);
};