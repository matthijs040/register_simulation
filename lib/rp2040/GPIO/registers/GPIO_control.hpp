#pragma once
#include <HAL/bitfield.hpp>

union STATUS {
  bitfield<26, 1> IRQTOPROC;
  bitfield<24, 1> IRQFROMPAD;
  bitfield<19, 1> INTOPERI;
  bitfield<17, 1> INFROMPAD;
  bitfield<13, 1> OETOPAD;
  bitfield<12, 1> OEFROMPERI;
  bitfield<9, 1> OUTTOPAD;
  bitfield<8, 1> OUTFROMPERI;
};

union CTRL {
  bitfield<28, 2> IRQOVER;
  bitfield<16, 2> INOVER;
  bitfield<12, 2> OEOVER;
  bitfield<8, 2> OUTOVER;
  bitfield<0, 4> FUNCSEL;
};

