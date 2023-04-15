#pragma once
#include <HAL/bitfield.hpp>
namespace reg {
union INTR3 {
  INTR3() : GPIO29_EDGE_HIGH() {}

  bitfield<23, 1> GPIO29_EDGE_HIGH;
  bitfield<22, 1> GPIO29_EDGE_LOW;
  const bitfield<21, 1> GPIO29_LEVEL_HIGH;
  const bitfield<20, 1> GPIO29_LEVEL_LOW;
  bitfield<19, 1> GPIO28_EDGE_HIGH;
  bitfield<18, 1> GPIO28_EDGE_LOW;
  const bitfield<17, 1> GPIO28_LEVEL_HIGH;
  const bitfield<16, 1> GPIO28_LEVEL_LOW;
  bitfield<15, 1> GPIO27_EDGE_HIGH;
  bitfield<14, 1> GPIO27_EDGE_LOW;
  const bitfield<13, 1> GPIO27_LEVEL_HIGH;
  const bitfield<12, 1> GPIO27_LEVEL_LOW;
  bitfield<11, 1> GPIO26_EDGE_HIGH;
  bitfield<10, 1> GPIO26_EDGE_LOW;
  const bitfield<9, 1> GPIO26_LEVEL_HIGH;
  const bitfield<8, 1> GPIO26_LEVEL_LOW;
  bitfield<7, 1> GPIO25_EDGE_HIGH;
  bitfield<6, 1> GPIO25_EDGE_LOW;
  const bitfield<5, 1> GPIO25_LEVEL_HIGH;
  const bitfield<4, 1> GPIO25_LEVEL_LOW;
  bitfield<3, 1> GPIO24_EDGE_HIGH;
  bitfield<2, 1> GPIO24_EDGE_LOW;
  const bitfield<1, 1> GPIO24_LEVEL_HIGH;
  const bitfield<0, 1> GPIO24_LEVEL_LOW;
};

union INTR2 {
  INTR2() : GPIO23_EDGE_HIGH() {}

  bitfield<31, 1> GPIO23_EDGE_HIGH;
  bitfield<30, 1> GPIO23_EDGE_LOW;
  const bitfield<29, 1> GPIO23_LEVEL_HIGH;
  const bitfield<28, 1> GPIO23_LEVEL_LOW;
  bitfield<27, 1> GPIO22_EDGE_HIGH;
  bitfield<26, 1> GPIO22_EDGE_LOW;
  const bitfield<25, 1> GPIO22_LEVEL_HIGH;
  const bitfield<24, 1> GPIO22_LEVEL_LOW;
  bitfield<23, 1> GPIO21_EDGE_HIGH;
  bitfield<22, 1> GPIO21_EDGE_LOW;
  const bitfield<21, 1> GPIO21_LEVEL_HIGH;
  const bitfield<20, 1> GPIO21_LEVEL_LOW;
  bitfield<19, 1> GPIO20_EDGE_HIGH;
  bitfield<18, 1> GPIO20_EDGE_LOW;
  const bitfield<17, 1> GPIO20_LEVEL_HIGH;
  const bitfield<16, 1> GPIO20_LEVEL_LOW;
  bitfield<15, 1> GPIO19_EDGE_HIGH;
  bitfield<14, 1> GPIO19_EDGE_LOW;
  const bitfield<13, 1> GPIO19_LEVEL_HIGH;
  const bitfield<12, 1> GPIO19_LEVEL_LOW;
  bitfield<11, 1> GPIO18_EDGE_HIGH;
  bitfield<10, 1> GPIO18_EDGE_LOW;
  const bitfield<9, 1> GPIO18_LEVEL_HIGH;
  const bitfield<8, 1> GPIO18_LEVEL_LOW;
  bitfield<7, 1> GPIO17_EDGE_HIGH;
  bitfield<6, 1> GPIO17_EDGE_LOW;
  const bitfield<5, 1> GPIO17_LEVEL_HIGH;
  const bitfield<4, 1> GPIO17_LEVEL_LOW;
  bitfield<3, 1> GPIO16_EDGE_HIGH;
  bitfield<2, 1> GPIO16_EDGE_LOW;
  const bitfield<1, 1> GPIO16_LEVEL_HIGH;
  const bitfield<0, 1> GPIO16_LEVEL_LOW;
};

union INTR1 {
  INTR1() : GPIO15_EDGE_HIGH() {}

  bitfield<31, 1> GPIO15_EDGE_HIGH;
  bitfield<30, 1> GPIO15_EDGE_LOW;
  const bitfield<29, 1> GPIO15_LEVEL_HIGH;
  const bitfield<28, 1> GPIO15_LEVEL_LOW;
  bitfield<27, 1> GPIO14_EDGE_HIGH;
  bitfield<26, 1> GPIO14_EDGE_LOW;
  const bitfield<25, 1> GPIO14_LEVEL_HIGH;
  const bitfield<24, 1> GPIO14_LEVEL_LOW;
  bitfield<23, 1> GPIO13_EDGE_HIGH;
  bitfield<22, 1> GPIO13_EDGE_LOW;
  const bitfield<21, 1> GPIO13_LEVEL_HIGH;
  const bitfield<20, 1> GPIO13_LEVEL_LOW;
  bitfield<19, 1> GPIO12_EDGE_HIGH;
  bitfield<18, 1> GPIO12_EDGE_LOW;
  const bitfield<17, 1> GPIO12_LEVEL_HIGH;
  const bitfield<16, 1> GPIO12_LEVEL_LOW;
  bitfield<15, 1> GPIO11_EDGE_HIGH;
  bitfield<14, 1> GPIO11_EDGE_LOW;
  const bitfield<13, 1> GPIO11_LEVEL_HIGH;
  const bitfield<12, 1> GPIO11_LEVEL_LOW;
  bitfield<11, 1> GPIO10_EDGE_HIGH;
  bitfield<10, 1> GPIO10_EDGE_LOW;
  const bitfield<9, 1> GPIO10_LEVEL_HIGH;
  const bitfield<8, 1> GPIO10_LEVEL_LOW;
  bitfield<7, 1> GPIO9_EDGE_HIGH;
  bitfield<6, 1> GPIO9_EDGE_LOW;
  const bitfield<5, 1> GPIO9_LEVEL_HIGH;
  const bitfield<4, 1> GPIO9_LEVEL_LOW;
  bitfield<3, 1> GPIO8_EDGE_HIGH;
  bitfield<2, 1> GPIO8_EDGE_LOW;
  const bitfield<1, 1> GPIO8_LEVEL_HIGH;
  const bitfield<0, 1> GPIO8_LEVEL_LOW;
};

union INTR0 {
  INTR0() : GPIO7_EDGE_HIGH() {}

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
  const bitfield<0, 1> GPIO0_LEVEL_LOW;
};
} // namespace reg