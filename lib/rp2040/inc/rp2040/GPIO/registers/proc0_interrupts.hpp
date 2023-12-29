#pragma once
#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {
union PROC0_INTS3 {
  PROC0_INTS3() {}
  bitfield<reg::state, 23, 1, reg::mock> GPIO29_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO29_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO29_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO29_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO28_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO28_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO28_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO28_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO27_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO27_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO27_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO27_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO26_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO26_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO26_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO26_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO25_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO25_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO25_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO25_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO24_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO24_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO24_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO24_LEVEL_LOW;
};

union PROC0_INTS2 {
  PROC0_INTS2() {}
  bitfield<reg::state, 31, 1, reg::mock> GPIO23_EDGE_HIGH;
  bitfield<reg::state, 30, 1, reg::mock> GPIO23_EDGE_LOW;
  bitfield<reg::state, 29, 1, reg::mock> GPIO23_LEVEL_HIGH;
  bitfield<reg::state, 28, 1, reg::mock> GPIO23_LEVEL_LOW;
  bitfield<reg::state, 27, 1, reg::mock> GPIO22_EDGE_HIGH;
  bitfield<reg::state, 26, 1, reg::mock> GPIO22_EDGE_LOW;
  bitfield<reg::state, 25, 1, reg::mock> GPIO22_LEVEL_HIGH;
  bitfield<reg::state, 24, 1, reg::mock> GPIO22_LEVEL_LOW;
  bitfield<reg::state, 23, 1, reg::mock> GPIO21_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO21_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO21_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO21_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO20_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO20_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO20_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO20_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO19_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO19_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO19_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO19_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO18_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO18_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO18_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO18_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO17_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO17_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO17_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO17_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO16_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO16_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO16_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO16_LEVEL_LOW;
};

union PROC0_INTS1 {
  PROC0_INTS1() {}
  bitfield<reg::state, 31, 1, reg::mock> GPIO15_EDGE_HIGH;
  bitfield<reg::state, 30, 1, reg::mock> GPIO15_EDGE_LOW;
  bitfield<reg::state, 29, 1, reg::mock> GPIO15_LEVEL_HIGH;
  bitfield<reg::state, 28, 1, reg::mock> GPIO15_LEVEL_LOW;
  bitfield<reg::state, 27, 1, reg::mock> GPIO14_EDGE_HIGH;
  bitfield<reg::state, 26, 1, reg::mock> GPIO14_EDGE_LOW;
  bitfield<reg::state, 25, 1, reg::mock> GPIO14_LEVEL_HIGH;
  bitfield<reg::state, 24, 1, reg::mock> GPIO14_LEVEL_LOW;
  bitfield<reg::state, 23, 1, reg::mock> GPIO13_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO13_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO13_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO13_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO12_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO12_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO12_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO12_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO11_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO11_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO11_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO11_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO10_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO10_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO10_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO10_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO9_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO9_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO9_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO9_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO8_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO8_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO8_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO8_LEVEL_LOW;
};

union PROC0_INTS0 {
  PROC0_INTS0() {}
  bitfield<reg::state, 31, 1, reg::mock> GPIO7_EDGE_HIGH;
  bitfield<reg::state, 30, 1, reg::mock> GPIO7_EDGE_LOW;
  bitfield<reg::state, 29, 1, reg::mock> GPIO7_LEVEL_HIGH;
  bitfield<reg::state, 28, 1, reg::mock> GPIO7_LEVEL_LOW;
  bitfield<reg::state, 27, 1, reg::mock> GPIO6_EDGE_HIGH;
  bitfield<reg::state, 26, 1, reg::mock> GPIO6_EDGE_LOW;
  bitfield<reg::state, 25, 1, reg::mock> GPIO6_LEVEL_HIGH;
  bitfield<reg::state, 24, 1, reg::mock> GPIO6_LEVEL_LOW;
  bitfield<reg::state, 23, 1, reg::mock> GPIO5_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO5_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO5_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO5_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO4_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO4_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO4_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO4_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO3_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO3_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO3_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO3_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO2_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO2_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO2_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO2_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO1_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO1_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO1_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO1_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO0_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO0_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO0_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO0_LEVEL_LOW;
};

union PROC0_INTF3 {
  PROC0_INTF3() {}
  bitfield<reg::state, 23, 1, reg::mock> GPIO29_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO29_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO29_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO29_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO28_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO28_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO28_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO28_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO27_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO27_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO27_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO27_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO26_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO26_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO26_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO26_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO25_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO25_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO25_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO25_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO24_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO24_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO24_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO24_LEVEL_LOW;
};

union PROC0_INTF2 {
  PROC0_INTF2() {}
  bitfield<reg::state, 31, 1, reg::mock> GPIO23_EDGE_HIGH;
  bitfield<reg::state, 30, 1, reg::mock> GPIO23_EDGE_LOW;
  bitfield<reg::state, 29, 1, reg::mock> GPIO23_LEVEL_HIGH;
  bitfield<reg::state, 28, 1, reg::mock> GPIO23_LEVEL_LOW;
  bitfield<reg::state, 27, 1, reg::mock> GPIO22_EDGE_HIGH;
  bitfield<reg::state, 26, 1, reg::mock> GPIO22_EDGE_LOW;
  bitfield<reg::state, 25, 1, reg::mock> GPIO22_LEVEL_HIGH;
  bitfield<reg::state, 24, 1, reg::mock> GPIO22_LEVEL_LOW;
  bitfield<reg::state, 23, 1, reg::mock> GPIO21_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO21_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO21_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO21_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO20_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO20_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO20_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO20_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO19_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO19_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO19_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO19_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO18_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO18_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO18_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO18_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO17_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO17_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO17_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO17_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO16_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO16_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO16_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO16_LEVEL_LOW;
};

union PROC0_INTF1 {
  PROC0_INTF1() {}
  bitfield<reg::state, 31, 1, reg::mock> GPIO15_EDGE_HIGH;
  bitfield<reg::state, 30, 1, reg::mock> GPIO15_EDGE_LOW;
  bitfield<reg::state, 29, 1, reg::mock> GPIO15_LEVEL_HIGH;
  bitfield<reg::state, 28, 1, reg::mock> GPIO15_LEVEL_LOW;
  bitfield<reg::state, 27, 1, reg::mock> GPIO14_EDGE_HIGH;
  bitfield<reg::state, 26, 1, reg::mock> GPIO14_EDGE_LOW;
  bitfield<reg::state, 25, 1, reg::mock> GPIO14_LEVEL_HIGH;
  bitfield<reg::state, 24, 1, reg::mock> GPIO14_LEVEL_LOW;
  bitfield<reg::state, 23, 1, reg::mock> GPIO13_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO13_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO13_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO13_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO12_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO12_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO12_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO12_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO11_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO11_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO11_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO11_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO10_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO10_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO10_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO10_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO9_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO9_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO9_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO9_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO8_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO8_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO8_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO8_LEVEL_LOW;
};

union PROC0_INTF0 {
  PROC0_INTF0() {}
  bitfield<reg::state, 31, 1, reg::mock> GPIO7_EDGE_HIGH;
  bitfield<reg::state, 30, 1, reg::mock> GPIO7_EDGE_LOW;
  bitfield<reg::state, 29, 1, reg::mock> GPIO7_LEVEL_HIGH;
  bitfield<reg::state, 28, 1, reg::mock> GPIO7_LEVEL_LOW;
  bitfield<reg::state, 27, 1, reg::mock> GPIO6_EDGE_HIGH;
  bitfield<reg::state, 26, 1, reg::mock> GPIO6_EDGE_LOW;
  bitfield<reg::state, 25, 1, reg::mock> GPIO6_LEVEL_HIGH;
  bitfield<reg::state, 24, 1, reg::mock> GPIO6_LEVEL_LOW;
  bitfield<reg::state, 23, 1, reg::mock> GPIO5_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO5_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO5_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO5_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO4_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO4_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO4_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO4_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO3_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO3_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO3_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO3_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO2_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO2_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO2_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO2_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO1_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO1_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO1_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO1_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO0_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO0_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO0_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO0_LEVEL_LOW;
};

union PROC0_INTE3 {
  PROC0_INTE3() {}
  bitfield<reg::state, 23, 1, reg::mock> GPIO29_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO29_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO29_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO29_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO28_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO28_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO28_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO28_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO27_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO27_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO27_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO27_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO26_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO26_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO26_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO26_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO25_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO25_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO25_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO25_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO24_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO24_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO24_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO24_LEVEL_LOW;
};

union PROC0_INTE2 {
  PROC0_INTE2() {}
  bitfield<reg::state, 31, 1, reg::mock> GPIO23_EDGE_HIGH;
  bitfield<reg::state, 30, 1, reg::mock> GPIO23_EDGE_LOW;
  bitfield<reg::state, 29, 1, reg::mock> GPIO23_LEVEL_HIGH;
  bitfield<reg::state, 28, 1, reg::mock> GPIO23_LEVEL_LOW;
  bitfield<reg::state, 27, 1, reg::mock> GPIO22_EDGE_HIGH;
  bitfield<reg::state, 26, 1, reg::mock> GPIO22_EDGE_LOW;
  bitfield<reg::state, 25, 1, reg::mock> GPIO22_LEVEL_HIGH;
  bitfield<reg::state, 24, 1, reg::mock> GPIO22_LEVEL_LOW;
  bitfield<reg::state, 23, 1, reg::mock> GPIO21_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO21_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO21_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO21_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO20_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO20_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO20_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO20_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO19_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO19_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO19_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO19_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO18_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO18_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO18_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO18_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO17_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO17_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO17_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO17_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO16_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO16_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO16_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO16_LEVEL_LOW;
};

union PROC0_INTE1 {
  PROC0_INTE1() {}
  bitfield<reg::state, 31, 1, reg::mock> GPIO15_EDGE_HIGH;
  bitfield<reg::state, 30, 1, reg::mock> GPIO15_EDGE_LOW;
  bitfield<reg::state, 29, 1, reg::mock> GPIO15_LEVEL_HIGH;
  bitfield<reg::state, 28, 1, reg::mock> GPIO15_LEVEL_LOW;
  bitfield<reg::state, 27, 1, reg::mock> GPIO14_EDGE_HIGH;
  bitfield<reg::state, 26, 1, reg::mock> GPIO14_EDGE_LOW;
  bitfield<reg::state, 25, 1, reg::mock> GPIO14_LEVEL_HIGH;
  bitfield<reg::state, 24, 1, reg::mock> GPIO14_LEVEL_LOW;
  bitfield<reg::state, 23, 1, reg::mock> GPIO13_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO13_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO13_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO13_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO12_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO12_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO12_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO12_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO11_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO11_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO11_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO11_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO10_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO10_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO10_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO10_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO9_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO9_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO9_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO9_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO8_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO8_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO8_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO8_LEVEL_LOW;
};

union PROC0_INTE0 {
  PROC0_INTE0() {}
  bitfield<reg::state, 31, 1, reg::mock> GPIO7_EDGE_HIGH;
  bitfield<reg::state, 30, 1, reg::mock> GPIO7_EDGE_LOW;
  bitfield<reg::state, 29, 1, reg::mock> GPIO7_LEVEL_HIGH;
  bitfield<reg::state, 28, 1, reg::mock> GPIO7_LEVEL_LOW;
  bitfield<reg::state, 27, 1, reg::mock> GPIO6_EDGE_HIGH;
  bitfield<reg::state, 26, 1, reg::mock> GPIO6_EDGE_LOW;
  bitfield<reg::state, 25, 1, reg::mock> GPIO6_LEVEL_HIGH;
  bitfield<reg::state, 24, 1, reg::mock> GPIO6_LEVEL_LOW;
  bitfield<reg::state, 23, 1, reg::mock> GPIO5_EDGE_HIGH;
  bitfield<reg::state, 22, 1, reg::mock> GPIO5_EDGE_LOW;
  bitfield<reg::state, 21, 1, reg::mock> GPIO5_LEVEL_HIGH;
  bitfield<reg::state, 20, 1, reg::mock> GPIO5_LEVEL_LOW;
  bitfield<reg::state, 19, 1, reg::mock> GPIO4_EDGE_HIGH;
  bitfield<reg::state, 18, 1, reg::mock> GPIO4_EDGE_LOW;
  bitfield<reg::state, 17, 1, reg::mock> GPIO4_LEVEL_HIGH;
  bitfield<reg::state, 16, 1, reg::mock> GPIO4_LEVEL_LOW;
  bitfield<reg::state, 15, 1, reg::mock> GPIO3_EDGE_HIGH;
  bitfield<reg::state, 14, 1, reg::mock> GPIO3_EDGE_LOW;
  bitfield<reg::state, 13, 1, reg::mock> GPIO3_LEVEL_HIGH;
  bitfield<reg::state, 12, 1, reg::mock> GPIO3_LEVEL_LOW;
  bitfield<reg::state, 11, 1, reg::mock> GPIO2_EDGE_HIGH;
  bitfield<reg::state, 10, 1, reg::mock> GPIO2_EDGE_LOW;
  bitfield<reg::state, 9, 1, reg::mock> GPIO2_LEVEL_HIGH;
  bitfield<reg::state, 8, 1, reg::mock> GPIO2_LEVEL_LOW;
  bitfield<reg::state, 7, 1, reg::mock> GPIO1_EDGE_HIGH;
  bitfield<reg::state, 6, 1, reg::mock> GPIO1_EDGE_LOW;
  bitfield<reg::state, 5, 1, reg::mock> GPIO1_LEVEL_HIGH;
  bitfield<reg::state, 4, 1, reg::mock> GPIO1_LEVEL_LOW;
  bitfield<reg::state, 3, 1, reg::mock> GPIO0_EDGE_HIGH;
  bitfield<reg::state, 2, 1, reg::mock> GPIO0_EDGE_LOW;
  bitfield<reg::state, 1, 1, reg::mock> GPIO0_LEVEL_HIGH;
  bitfield<reg::state, 0, 1, reg::mock> GPIO0_LEVEL_LOW;
};
} // namespace reg