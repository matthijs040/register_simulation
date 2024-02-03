#pragma once

#include <HAL/bitfield.hpp>
#include <HAL/simulated_device_register.hpp>
#include <system/architecture.hpp>

namespace reg {

constexpr bool mock = arch::get_architecture() != arch::architectures::ARM6;
static_assert(arch::get_architecture() != arch::architectures::unknown);

template <typename field_type>
using type =
    std::conditional_t<mock,
                       simulated_device_register<field_type, register_integral>,
                       register_integral>;

template <typename bitstate, std::size_t offset, std::size_t num_bits>
using field = bitfield<
    bitstate, offset, num_bits,
    reg::type<bitfield<bitstate, offset, num_bits, register_integral>>>;

enum class state : bool {
  disabled = false,
  cleared = false,
  enabled = true,
  set = true,
};

static_assert(reg::state::enabled == reg::state::set &&
              reg::state::disabled == reg::state::cleared);

}; // namespace reg