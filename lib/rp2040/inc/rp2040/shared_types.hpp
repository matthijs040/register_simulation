#pragma once

#include <system/architecture.hpp>

namespace reg {

constexpr bool mock = arch::get_architecture() != arch::architectures::ARM7;

enum class state : bool {
  disabled = false,
  cleared = false,
  enabled = true,
  set = true,
};

static_assert(reg::state::enabled == reg::state::set &&
              reg::state::disabled == reg::state::cleared);
}; // namespace reg