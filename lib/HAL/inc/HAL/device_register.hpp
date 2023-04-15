#pragma once

#include <cstdint>

// Device register becomes non-volatile while const evaluated as volatile types
// cannot be interacted in in constexpr functions. Could maybe use
// std::is_constant_evaluated() as a condition? If the simulation tests all run
// consteval?
using register_integral = std::uint32_t;
using register_mask = register_integral;

union stub_register {
  register_integral storage;
};
