#pragma once

#include <cstdint>
#include <type_traits>

using register_integral = std::uint32_t;
using register_mask = register_integral;

#include "simulated_device_register.hpp"
template <typename field_type, typename storage_type, bool enable_handlers>  class simulated_device_register;