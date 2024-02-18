#pragma once

#include "registers/ROSC.hpp"
#include <HAL/simulatable_peripheral.hpp>
#include <expected>
#include <span>
#include <type_traits>

class ROSC : public simulatable_peripheral<ROSC, reg::mock> {
public:
  ~ROSC();

  std::uint32_t get_power_stage() const noexcept;
  void set_power_stage(uint32_t) noexcept;
  static std::span<const unsigned int>
  get_frequencies_by_power_stage() noexcept;

  std::expected<uint32_t, error::code> get_frequency_Hz() const noexcept;
  std::expected<uint32_t, error::code> set_frequency_Hz(std::uint32_t) noexcept;

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

  void apply_settings(reg::ROSC::CTRL::FREQ_RANGE_states,
                      reg::ROSC::drive_strength, reg::ROSC::drive_strength,
                      reg::ROSC::drive_strength, reg::ROSC::drive_strength,
                      reg::ROSC::drive_strength, reg::ROSC::drive_strength,
                      reg::ROSC::drive_strength,
                      reg::ROSC::drive_strength) noexcept;

  static constexpr std::array base_addresses = {0x40060000};

  void initialize_effect_handlers(std::size_t) {}

  friend simulatable_peripheral<ROSC, reg::mock>;
};