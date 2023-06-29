#pragma once
#include "simulated_device_register.hpp"
#include <cassert>
#include <type_traits>
#include <utility>

template <typename bitstate, std::size_t offset, std::size_t num_bits,
          bool uses_simulated_registers = USE_SIMULATED_REGISTERS>
struct bitfield {
  template<typename U = bitstate>
  bitfield(std::enable_if_t<std::is_scoped_enum_v<U>, U> initial_value) : value(initial_value) {}
 
  bitfield(bitstate initial_value)
      : value(static_cast<storage_type>(initial_value)) {}

  static constexpr register_integral max = (0b1 << num_bits) - 1;
  static constexpr register_integral bitrange = max << offset;

  operator bitstate() const noexcept {
    return static_cast<bitstate>((value >> offset) & max);
  }

  bitfield &operator=(const bitstate &v) noexcept {
    // Cannot static assert this without a constexpr way of getting largest enum
    // class value.
    const auto &as_integral = reinterpret_cast<register_integral &>(value);
    const auto shifted_value = std::to_underlying(v) << offset;
    const auto masked_value = (as_integral & ~bitrange) | shifted_value;
    if constexpr(uses_simulated_registers)
      value = reinterpret_cast<const stored_bits &>(masked_value);
    else
      value = masked_value;
    return *this;
  }

  using stored_bits = bitfield<bitstate, offset, num_bits, false>;
  using sim_storage = simulated_device_register<stored_bits>;
  using storage_type = std::conditional<uses_simulated_registers, sim_storage,
                                        register_integral>::type;

private:
  friend std::conditional<uses_simulated_registers, sim_storage, void>::type;
  storage_type value;
};
