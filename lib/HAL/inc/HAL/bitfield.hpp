#pragma once
#include "simulated_device_register.hpp"
#include <cassert>
#include <type_traits>

template <std::size_t offset, std::size_t num_bits>
struct bitfield
    : std::conditional<USE_SIMULATED_REGISTERS,
                       simulated_device_register<bitfield<offset, num_bits>>,
                       void> {

  bitfield(register_integral initial_value = 0b0) : value(initial_value) {}

  register_integral value;
  static constexpr register_integral max = (0b1 << num_bits) - 1;
  static constexpr register_integral mask = max << offset;

  operator register_integral() const noexcept {
    return (value >> offset) & max;
  }

  bitfield &operator=(register_integral v) noexcept {
    assert(v < max);
    value = (value & ~mask) | (v << offset);
    return *this;
  }
};
