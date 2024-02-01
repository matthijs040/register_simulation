#pragma once
#include "simulated_device_register.hpp"
#include <bit>
#include <cassert>
#include <type_traits>
#include <utility>

template <typename bitstate, std::size_t offset_, std::size_t num_bits,
          typename storage_type>
struct bitfield {
  using stored_type = storage_type;

  constexpr bitfield(auto initial_value)
      : value(static_cast<storage_type>(initial_value)) {}

  static constexpr auto offset = offset_;
  static constexpr auto max = (0b1 << num_bits) - 1;
  static constexpr auto bitrange = max << offset;

  constexpr operator bitstate() const noexcept {
    const register_integral *val =
        std::bit_cast<const register_integral *>(&value);
    return static_cast<bitstate>((*val >> offset) & max);
  }

  constexpr bitfield &operator=(bitstate v) noexcept {
    // Cannot static assert this without a constexpr way of getting largest enum
    // class value.
    const auto shifted_value = [&] {
      if constexpr (std::is_scoped_enum_v<bitstate>)
        return std::to_underlying(v) << offset;
      else
        return v << offset;
    }();
    const auto masked_value = (value & ~bitrange) | shifted_value;
    value = masked_value;
    return *this;
  }

  constexpr bitfield operator&(const auto &mask) const noexcept {
    return value & mask;
  }

  constexpr bitfield operator|(const auto &mask) const noexcept {
    return value | mask;
  }

  constexpr bitfield operator>>(const auto shift) const noexcept {
    return value >> shift;
  }

private:
  storage_type value;
};
