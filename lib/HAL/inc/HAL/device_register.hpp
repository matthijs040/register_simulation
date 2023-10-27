#pragma once

#include <cstdint>
#include <type_traits>

using register_integral = std::uint32_t;
using register_mask = register_integral;

#include "simulated_device_register.hpp"
template <typename Underlying> class simulated_device_register;

template <bool simulated>
using register_storage =
    std::conditional_t<simulated, simulated_device_register<register_integral>,
                       register_integral>;