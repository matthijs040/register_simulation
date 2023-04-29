#pragma once
#include "shared_types.hpp"
#include <HAL/bitfield.hpp>

namespace reg {
union INTR3 {
  INTR3() {}

  bitfield<reg::state, 23, 1> GPIO29_EDGE_HIGH;
  bitfield<reg::state, 22, 1> GPIO29_EDGE_LOW;
  const bitfield<reg::state, 21, 1> GPIO29_LEVEL_HIGH;
  const bitfield<reg::state, 20, 1> GPIO29_LEVEL_LOW;
  bitfield<reg::state, 19, 1> GPIO28_EDGE_HIGH;
  bitfield<reg::state, 18, 1> GPIO28_EDGE_LOW;
  const bitfield<reg::state, 17, 1> GPIO28_LEVEL_HIGH;
  const bitfield<reg::state, 16, 1> GPIO28_LEVEL_LOW;
  bitfield<reg::state, 15, 1> GPIO27_EDGE_HIGH;
  bitfield<reg::state, 14, 1> GPIO27_EDGE_LOW;
  const bitfield<reg::state, 13, 1> GPIO27_LEVEL_HIGH;
  const bitfield<reg::state, 12, 1> GPIO27_LEVEL_LOW;
  bitfield<reg::state, 11, 1> GPIO26_EDGE_HIGH;
  bitfield<reg::state, 10, 1> GPIO26_EDGE_LOW;
  const bitfield<reg::state, 9, 1> GPIO26_LEVEL_HIGH;
  const bitfield<reg::state, 8, 1> GPIO26_LEVEL_LOW;
  bitfield<reg::state, 7, 1> GPIO25_EDGE_HIGH;
  bitfield<reg::state, 6, 1> GPIO25_EDGE_LOW;
  const bitfield<reg::state, 5, 1> GPIO25_LEVEL_HIGH;
  const bitfield<reg::state, 4, 1> GPIO25_LEVEL_LOW;
  bitfield<reg::state, 3, 1> GPIO24_EDGE_HIGH;
  bitfield<reg::state, 2, 1> GPIO24_EDGE_LOW;
  const bitfield<reg::state, 1, 1> GPIO24_LEVEL_HIGH;
  const bitfield<reg::state, 0, 1> GPIO24_LEVEL_LOW;
};

union INTR2 {
  INTR2() {}

  bitfield<reg::state, 31, 1> GPIO23_EDGE_HIGH;
  bitfield<reg::state, 30, 1> GPIO23_EDGE_LOW;
  const bitfield<reg::state, 29, 1> GPIO23_LEVEL_HIGH;
  const bitfield<reg::state, 28, 1> GPIO23_LEVEL_LOW;
  bitfield<reg::state, 27, 1> GPIO22_EDGE_HIGH;
  bitfield<reg::state, 26, 1> GPIO22_EDGE_LOW;
  const bitfield<reg::state, 25, 1> GPIO22_LEVEL_HIGH;
  const bitfield<reg::state, 24, 1> GPIO22_LEVEL_LOW;
  bitfield<reg::state, 23, 1> GPIO21_EDGE_HIGH;
  bitfield<reg::state, 22, 1> GPIO21_EDGE_LOW;
  const bitfield<reg::state, 21, 1> GPIO21_LEVEL_HIGH;
  const bitfield<reg::state, 20, 1> GPIO21_LEVEL_LOW;
  bitfield<reg::state, 19, 1> GPIO20_EDGE_HIGH;
  bitfield<reg::state, 18, 1> GPIO20_EDGE_LOW;
  const bitfield<reg::state, 17, 1> GPIO20_LEVEL_HIGH;
  const bitfield<reg::state, 16, 1> GPIO20_LEVEL_LOW;
  bitfield<reg::state, 15, 1> GPIO19_EDGE_HIGH;
  bitfield<reg::state, 14, 1> GPIO19_EDGE_LOW;
  const bitfield<reg::state, 13, 1> GPIO19_LEVEL_HIGH;
  const bitfield<reg::state, 12, 1> GPIO19_LEVEL_LOW;
  bitfield<reg::state, 11, 1> GPIO18_EDGE_HIGH;
  bitfield<reg::state, 10, 1> GPIO18_EDGE_LOW;
  const bitfield<reg::state, 9, 1> GPIO18_LEVEL_HIGH;
  const bitfield<reg::state, 8, 1> GPIO18_LEVEL_LOW;
  bitfield<reg::state, 7, 1> GPIO17_EDGE_HIGH;
  bitfield<reg::state, 6, 1> GPIO17_EDGE_LOW;
  const bitfield<reg::state, 5, 1> GPIO17_LEVEL_HIGH;
  const bitfield<reg::state, 4, 1> GPIO17_LEVEL_LOW;
  bitfield<reg::state, 3, 1> GPIO16_EDGE_HIGH;
  bitfield<reg::state, 2, 1> GPIO16_EDGE_LOW;
  const bitfield<reg::state, 1, 1> GPIO16_LEVEL_HIGH;
  const bitfield<reg::state, 0, 1> GPIO16_LEVEL_LOW;
};

union INTR1 {
  INTR1() {}

  bitfield<reg::state, 31, 1> GPIO15_EDGE_HIGH;
  bitfield<reg::state, 30, 1> GPIO15_EDGE_LOW;
  const bitfield<reg::state, 29, 1> GPIO15_LEVEL_HIGH;
  const bitfield<reg::state, 28, 1> GPIO15_LEVEL_LOW;
  bitfield<reg::state, 27, 1> GPIO14_EDGE_HIGH;
  bitfield<reg::state, 26, 1> GPIO14_EDGE_LOW;
  const bitfield<reg::state, 25, 1> GPIO14_LEVEL_HIGH;
  const bitfield<reg::state, 24, 1> GPIO14_LEVEL_LOW;
  bitfield<reg::state, 23, 1> GPIO13_EDGE_HIGH;
  bitfield<reg::state, 22, 1> GPIO13_EDGE_LOW;
  const bitfield<reg::state, 21, 1> GPIO13_LEVEL_HIGH;
  const bitfield<reg::state, 20, 1> GPIO13_LEVEL_LOW;
  bitfield<reg::state, 19, 1> GPIO12_EDGE_HIGH;
  bitfield<reg::state, 18, 1> GPIO12_EDGE_LOW;
  const bitfield<reg::state, 17, 1> GPIO12_LEVEL_HIGH;
  const bitfield<reg::state, 16, 1> GPIO12_LEVEL_LOW;
  bitfield<reg::state, 15, 1> GPIO11_EDGE_HIGH;
  bitfield<reg::state, 14, 1> GPIO11_EDGE_LOW;
  const bitfield<reg::state, 13, 1> GPIO11_LEVEL_HIGH;
  const bitfield<reg::state, 12, 1> GPIO11_LEVEL_LOW;
  bitfield<reg::state, 11, 1> GPIO10_EDGE_HIGH;
  bitfield<reg::state, 10, 1> GPIO10_EDGE_LOW;
  const bitfield<reg::state, 9, 1> GPIO10_LEVEL_HIGH;
  const bitfield<reg::state, 8, 1> GPIO10_LEVEL_LOW;
  bitfield<reg::state, 7, 1> GPIO9_EDGE_HIGH;
  bitfield<reg::state, 6, 1> GPIO9_EDGE_LOW;
  const bitfield<reg::state, 5, 1> GPIO9_LEVEL_HIGH;
  const bitfield<reg::state, 4, 1> GPIO9_LEVEL_LOW;
  bitfield<reg::state, 3, 1> GPIO8_EDGE_HIGH;
  bitfield<reg::state, 2, 1> GPIO8_EDGE_LOW;
  const bitfield<reg::state, 1, 1> GPIO8_LEVEL_HIGH;
  const bitfield<reg::state, 0, 1> GPIO8_LEVEL_LOW;
};

union INTR0 {
  INTR0() {}

  bitfield<reg::state, 31, 1> GPIO7_EDGE_HIGH;
  bitfield<reg::state, 30, 1> GPIO7_EDGE_LOW;
  const bitfield<reg::state, 29, 1> GPIO7_LEVEL_HIGH;
  const bitfield<reg::state, 28, 1> GPIO7_LEVEL_LOW;
  bitfield<reg::state, 27, 1> GPIO6_EDGE_HIGH;
  bitfield<reg::state, 26, 1> GPIO6_EDGE_LOW;
  const bitfield<reg::state, 25, 1> GPIO6_LEVEL_HIGH;
  const bitfield<reg::state, 24, 1> GPIO6_LEVEL_LOW;
  bitfield<reg::state, 23, 1> GPIO5_EDGE_HIGH;
  bitfield<reg::state, 22, 1> GPIO5_EDGE_LOW;
  const bitfield<reg::state, 21, 1> GPIO5_LEVEL_HIGH;
  const bitfield<reg::state, 20, 1> GPIO5_LEVEL_LOW;
  bitfield<reg::state, 19, 1> GPIO4_EDGE_HIGH;
  bitfield<reg::state, 18, 1> GPIO4_EDGE_LOW;
  const bitfield<reg::state, 17, 1> GPIO4_LEVEL_HIGH;
  const bitfield<reg::state, 16, 1> GPIO4_LEVEL_LOW;
  bitfield<reg::state, 15, 1> GPIO3_EDGE_HIGH;
  bitfield<reg::state, 14, 1> GPIO3_EDGE_LOW;
  const bitfield<reg::state, 13, 1> GPIO3_LEVEL_HIGH;
  const bitfield<reg::state, 12, 1> GPIO3_LEVEL_LOW;
  bitfield<reg::state, 11, 1> GPIO2_EDGE_HIGH;
  bitfield<reg::state, 10, 1> GPIO2_EDGE_LOW;
  const bitfield<reg::state, 9, 1> GPIO2_LEVEL_HIGH;
  const bitfield<reg::state, 8, 1> GPIO2_LEVEL_LOW;
  bitfield<reg::state, 7, 1> GPIO1_EDGE_HIGH;
  bitfield<reg::state, 6, 1> GPIO1_EDGE_LOW;
  const bitfield<reg::state, 5, 1> GPIO1_LEVEL_HIGH;
  const bitfield<reg::state, 4, 1> GPIO1_LEVEL_LOW;
  bitfield<reg::state, 3, 1> GPIO0_EDGE_HIGH;
  bitfield<reg::state, 2, 1> GPIO0_EDGE_LOW;
  const bitfield<reg::state, 1, 1> GPIO0_LEVEL_HIGH;
  const bitfield<reg::state, 0, 1> GPIO0_LEVEL_LOW;
};
} // namespace reg