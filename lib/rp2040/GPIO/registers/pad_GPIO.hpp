#pragma once
#include <HAL/bitfield.hpp>

namespace reg {
union GPIO {
  GPIO() {}
  bitfield<7, 1> OD;
  bitfield<6, 1> IE;
  bitfield<4, 2> DRIVE;
  bitfield<3, 1> PUE;
  bitfield<2, 1> PDE;
  bitfield<1, 1> SCHMITT;
  bitfield<0, 1> SLEWFAST;
};

} // namespace reg