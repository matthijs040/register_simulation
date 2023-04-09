#pragma once
#include <cstdint>
#include <type_traits>
#include "simulated_device_register.hpp"

constexpr bool in_test_mode = true;

// Device register becomes non-volatile while const evaluated as volatile types cannot be interacted in in constexpr functions.
// Could maybe use std::is_constant_evaluated() as a condition? If the simulation tests all run consteval?
using device_register = std::conditional<in_test_mode, std::uint32_t volatile, class simulated_device_register>::type;
using register_mask = std::uint32_t;