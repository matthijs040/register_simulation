#pragma once

#include <cstdint>

// Device register becomes non-volatile while const evaluated as volatile types
// cannot be interacted in in constexpr functions. Could maybe use
// std::is_constant_evaluated() as a condition? If the simulation tests all run
// consteval?
using register_integral = std::uint32_t;
using register_mask = std::uint32_t;

#include "simulated_device_register.hpp"
#include <cmath>
#include <limits>
#include <type_traits>

using device_register =
    std::conditional<USE_SIMULATED_REGISTERS, class simulated_device_register,
                     volatile register_integral>::type;

constexpr auto all_ones = std::numeric_limits<register_mask>::max();
constexpr auto all_zeros = std::numeric_limits<register_mask>::min();

template <register_mask mask, std::size_t shift, std::size_t length>
void apply_mask(device_register &reg) {

  // If nothing changes, we don't need to AND.
  if constexpr (all_ones & mask != all_ones) {
    // set all bits left-outside our mask.
    constexpr auto msb_mask = all_ones << length + shift;

    // Set all bits right-outside our mask. (not applied if shift is 0)
    constexpr register_mask lsb_mask = std::pow(2, shift) - 1;

    // Apply shift and outside-masks to real-mask.
    constexpr auto and_mask =
        shift == 0 ? mask | msb_mask : ((mask | msb_mask) << shift) | lsb_mask;

    // Apply the AND.
    reg &= mask;
  }

  // If nothing changes, we don't need to OR.
  if constexpr (all_zeros | mask != all_zeros) {
    // We don't need to clear bits outside of mask range. This should be
    // default.
    constexpr auto or_mask = mask << shift;
    reg |= mask;
  }
}

template <register_mask mask, std::size_t shift, std::size_t length>
bool mask_matches(device_register reg) {

  // We have some most-significant-bits that are not part of the mask.
  // Shift them out-left.
  if constexpr (constexpr auto msb = length + shift < sizeof(register_mask)) {
    reg << msb;
    reg >> msb;
  }

  if constexpr (shift > 0)
    reg >> shift;

  return reg == mask;
}
