#pragma once

#include <cstdint>
#include <type_traits>

// Device register becomes non-volatile while const evaluated as volatile types
// cannot be interacted in in constexpr functions. Could maybe use
// std::is_constant_evaluated() as a condition? If the simulation tests all run
// consteval?
using register_integral = std::uint32_t;
using register_mask = register_integral;

#include "simulated_device_register.hpp"
template<typename Underlying>
class simulated_device_register;

using register_storage =
    std::conditional_t<USE_SIMULATED_REGISTERS,
                       simulated_device_register<register_integral>,
                       register_integral>;