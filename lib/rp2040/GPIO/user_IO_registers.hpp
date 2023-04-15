#pragma once

#include <bitfield.hpp>

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

union INTR0 {
  bitfield<31, 1> GPIO7_EDGE_HIGH;
  bitfield<30, 1> GPIO7_EDGE_LOW;
  const bitfield<29, 1> GPIO7_LEVEL_HIGH;
  const bitfield<28, 1> GPIO7_LEVEL_LOW;
  bitfield<27, 1> GPIO6_EDGE_HIGH;
  bitfield<26, 1> GPIO6_EDGE_LOW;
  const bitfield<25, 1> GPIO6_LEVEL_HIGH;
  const bitfield<24, 1> GPIO6_LEVEL_LOW;
  bitfield<23, 1> GPIO5_EDGE_HIGH;
  bitfield<22, 1> GPIO5_EDGE_LOW;
  const bitfield<21, 1> GPIO5_LEVEL_HIGH;
  const bitfield<20, 1> GPIO5_LEVEL_LOW;
  bitfield<19, 1> GPIO4_EDGE_HIGH;
  bitfield<18, 1> GPIO4_EDGE_LOW;
  const bitfield<17, 1> GPIO4_LEVEL_HIGH;
  const bitfield<16, 1> GPIO4_LEVEL_LOW;
  bitfield<15, 1> GPIO3_EDGE_HIGH;
  bitfield<14, 1> GPIO3_EDGE_LOW;
  const bitfield<13, 1> GPIO3_LEVEL_HIGH;
  const bitfield<12, 1> GPIO3_LEVEL_LOW;
  bitfield<11, 1> GPIO2_EDGE_HIGH;
  bitfield<10, 1> GPIO2_EDGE_LOW;
  const bitfield<9, 1> GPIO2_LEVEL_HIGH;
  const bitfield<8, 1> GPIO2_LEVEL_LOW;
  bitfield<7, 1> GPIO1_EDGE_HIGH;
  bitfield<6, 1> GPIO1_EDGE_LOW;
  const bitfield<5, 1> GPIO1_LEVEL_HIGH;
  const bitfield<4, 1> GPIO1_LEVEL_LOW;
  bitfield<3, 1> GPIO0_EDGE_HIGH;
  bitfield<2, 1> GPIO0_EDGE_LOW;
  const bitfield<1, 1> GPIO0_LEVEL_HIGH;
  const bitfield<0, 1> GPIO0_LEVEL_LOW
};