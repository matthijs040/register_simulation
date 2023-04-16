#pragma once
#include <HAL/bitfield.hpp>
#include "shared_types.hpp"

namespace reg {
union GPIO {
  GPIO() {}
  bitfield<reg::state, 7, 1> OD;
  bitfield<reg::state, 6, 1> IE;
  bitfield<reg::state, 4, 2> DRIVE;
  bitfield<reg::state, 3, 1> PUE;
  bitfield<reg::state, 2, 1> PDE;
  bitfield<reg::state, 1, 1> SCHMITT;
  bitfield<reg::state, 0, 1> SLEWFAST;
};

} // namespace reg