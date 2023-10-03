#pragma once
#include "simulated_device_register.hpp"
#include <cassert>
#include <type_traits>
#include <utility>
#include <bit>

template <typename bitstate, std::size_t offset, std::size_t num_bits,
          bool uses_simulated_registers = USE_SIMULATED_REGISTERS>
struct bitfield
{
  template <typename U = bitstate>
  constexpr bitfield(std::enable_if_t<std::is_scoped_enum_v<U>, U> initial_value) : value(initial_value) {}

  constexpr bitfield(bitstate initial_value)
      : value(static_cast<storage_type>(initial_value)) {}

  static constexpr register_integral max = (0b1 << num_bits) - 1;
  static constexpr register_integral bitrange = max << offset;

  constexpr operator bitstate() const noexcept
  {
    return static_cast<bitstate>((value >> offset) & max);
  }

  constexpr bitfield &operator=(const bitstate &v) noexcept
  {
    // Cannot static assert this without a constexpr way of getting largest enum
    // class value.
    const auto* as_integral = std::bit_cast<register_integral *>(&value);
    const register_integral shifted_value = [&]
    {
      if constexpr (std::is_scoped_enum_v<bitstate>)
        return std::to_underlying(v) << offset;
      else
        return v << offset;
    }();
    const auto masked_value = (*as_integral & ~bitrange) | shifted_value;
    if constexpr (uses_simulated_registers)
      value = std::bit_cast<stored_bits>(masked_value);
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
