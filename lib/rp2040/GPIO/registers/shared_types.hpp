#pragma once

namespace reg {
enum class state : bool {
  disabled = false,
  cleared = false,
  enabled = true,
  set = true,
};
};