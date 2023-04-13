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

  // set all bits left-outside our mask.
  constexpr auto msb_mask = all_ones << length + shift;

  // Set all bits right-outside our mask. (not applied if shift is 0)
  constexpr register_mask lsb_mask = std::pow(2, shift) - 1;

  // Apply shift and outside-masks to real-mask.
  constexpr auto and_mask =
      shift == 0 ? mask | msb_mask : ((mask << shift) | msb_mask) | lsb_mask;

  // If nothing changes, we don't need to AND.
  if constexpr (and_mask != all_ones) {

    // Apply the AND.
    reg &= and_mask;
  }

  // If nothing changes, we don't need to OR.
  if constexpr (mask != all_zeros) {
    // We don't need to clear bits outside of mask range. This should be
    // default.
    constexpr auto or_mask = mask << shift;
    reg |= mask;
  }
}

template <register_mask mask, std::size_t shift, std::size_t length>
bool mask_matches(register_integral reg) {

  // We have some most-significant-bits that are not part of the mask.
  // Shift them out-left.
  constexpr auto msb = (length - 1 + shift);
  if constexpr (msb < sizeof(register_mask) * 8) {
    reg = reg << msb;
    reg = reg >> msb;
  }

  if constexpr (shift > 0)
    reg = reg >> shift - length;

  return reg == mask;
}
