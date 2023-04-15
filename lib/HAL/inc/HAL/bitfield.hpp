#pragma once
#include "simulated_device_register.hpp"
#include <cassert>
#include <type_traits>

template <std::size_t offset, std::size_t num_bits>
struct bitfield : std::conditional<USE_SIMULATED_REGISTERS,
                                   simulated_device_register<bitfield>, void> {
  register_integral value;
  static constexpr register_integral max = (0b1 << num_bits) - 1;
  static constexpr register_integral mask = max << offset;

  bitfield() {}
  ~bitfield() {}

    operator register_integral() const noexcept{ return (value >> offset) & max; }

    bitfield &operator=(register_integral v) noexcept {
    assert(v < max);
    value = (value & ~mask) | (v << offset);
    return *this;
  }
};
