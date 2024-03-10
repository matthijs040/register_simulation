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
      : value(std::bit_cast<storage_type>(initial_value)) {}

  static constexpr auto offset = offset_;
  static constexpr auto max = (0b1 << num_bits) - 1;
  static constexpr auto bitrange = max << offset;

  constexpr operator bitstate() const noexcept {
    return static_cast<bitstate>((value & bitrange) >> offset);
  }

  constexpr bitfield &operator=(bitstate v) noexcept {

    // If the "to-be-assigned type" perfectly maps to an "array-index" of the
    // storage type. It can be assigned without reading or masking.
    if constexpr (
        // For this, it must perfectly fit into the number of bits.
        sizeof(v) * 8 == num_bits &&
        // Its offset must match a multiple of its size in bits.
        offset % (sizeof(v) * 8) == 0
        // And it must be integral.
        // (Could also be enum but then the underlying type must comply with the
        // above requirements.)
        && std::is_integral_v<bitstate>) {

      constexpr std::size_t pointer_shift = offset / (sizeof(bitstate) * 8);

      // If our storage type is non-trivial. (e.g. simulated_device_register)
      // Defer the conversion to it.
      if constexpr (std::is_class_v<storage_type>) {
        value.assign_as(v, pointer_shift);
        return *this;
      }

      // Otherwise do it ourselves.
      *(std::bit_cast<bitstate *>(&value) + pointer_shift) = v;
      return *this;
    }

    // If it cannot be written to directly (due to sharing its storage at the
    // byte-level with other bitfields) The full state must first be read and
    // our value be masked before assigned. This is to prevent changing state
    // of other registers, be they reserved space or explicitly defined ones.
    const auto shifted_value = [&] {
      if constexpr (std::is_scoped_enum_v<bitstate>)
        return std::to_underlying(v) << offset;
      else
        return v << offset;
    }();
    value = (value & ~bitrange) | shifted_value;
    return *this;
  }

private:
  storage_type value;
};
