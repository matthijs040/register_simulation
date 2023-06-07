#pragma once

namespace reg {
enum class state : bool {
  disabled = false,
  cleared = false,
  enabled = true,
  set = true,
};

static_assert(reg::state::enabled == reg::state::set &&
              reg::state::disabled == reg::state::cleared);
}; // namespace reg