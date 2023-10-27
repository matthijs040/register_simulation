#pragma once

#include "registers/ROSC.hpp"
#include <HAL/device_register.hpp>
#include <HAL/simulated_peripheral.hpp>
#include <expected>
#include <span>
#include <system_error>
#include <type_traits>

class ROSC
    : public std::conditional<reg::mock, simulated_peripheral<ROSC>, void> {
public:
  static constexpr uintptr_t base_address = 0x40060000;
  static ROSC &get() noexcept;
  ~ROSC();
  void operator delete(void *addr);

  std::uint32_t get_power_stage() const noexcept;
  void set_power_stage(uint32_t) noexcept;
  static std::span<const unsigned int> get_frequencies_by_power_stage() noexcept;

  std::expected<uint32_t, std::error_code> get_frequency_Hz() const noexcept;
  std::expected<uint32_t, std::error_code>
      set_frequency_Hz(std::uint32_t) noexcept;

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

  void apply_settings(reg::ROSC::CTRL::FREQ_RANGE_states,
                      reg::ROSC::drive_strength, reg::ROSC::drive_strength,
                      reg::ROSC::drive_strength, reg::ROSC::drive_strength,
                      reg::ROSC::drive_strength, reg::ROSC::drive_strength,
                      reg::ROSC::drive_strength,
                      reg::ROSC::drive_strength) noexcept;
};