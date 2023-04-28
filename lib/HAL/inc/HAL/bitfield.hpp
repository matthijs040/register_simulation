#pragma once
#include "simulated_device_register.hpp"
#include <cassert>
#include <type_traits>
#include <utility>

template <typename bitstate, std::size_t offset, std::size_t num_bits,
          bool uses_simulated_registers = USE_SIMULATED_REGISTERS>
struct bitfield {

  bitfield(register_integral initial_value = 0b0) : value(initial_value) {}

  static constexpr register_integral max = (0b1 << num_bits) - 1;
  static constexpr register_integral mask = max << offset;

  operator bitstate() const noexcept {
    return static_cast<bitstate>(((value >> offset) & max));
  }

  bitfield &operator=(bitstate v) noexcept {
    // Cannot static assert this without a constexpr way of getting largest enum
    // class value.
    value = (value & ~mask) | (std::to_underlying(v) << offset);
    return *this;
  }

  static_assert(std::is_scoped_enum_v<bitstate>);

  using stored_bits = bitfield<bitstate, offset, num_bits, false>;
  using sim_storage = simulated_device_register<stored_bits>;
  using storage_type = std::conditional<uses_simulated_registers, sim_storage, register_integral>::type;

private:
  friend std::conditional<uses_simulated_registers, sim_storage, void>::type;
  storage_type value;
};
