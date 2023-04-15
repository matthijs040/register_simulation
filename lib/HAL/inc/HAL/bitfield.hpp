#pragma once
#include "simulated_device_register.hpp"
#include <cassert>
#include <type_traits>
#include <utility>

template <typename bitstate, std::size_t offset, std::size_t num_bits>
struct bitfield
    : std::conditional<
          USE_SIMULATED_REGISTERS,
          simulated_device_register<bitfield<bitstate, offset, num_bits>>,
          void> {

  bitfield(register_integral initial_value = 0b0) : value(initial_value) {}

  register_integral value;
  static constexpr register_integral max = (0b1 << num_bits) - 1;
  static constexpr register_integral mask = max << offset;

  operator bitstate() const noexcept {
    return static_cast<bitstate>((value >> offset) & max);
  }

  bitfield &operator=(bitstate v) noexcept {
    // Cannot static assert this without a constexpr way of getting largest enum class value.
    assert(std::to_underlying(v) <= max); 

    value = (value & ~mask) | (std::to_underlying(v) << offset);
    return *this;
  }

  static_assert(std::is_scoped_enum_v<bitstate>);
};
