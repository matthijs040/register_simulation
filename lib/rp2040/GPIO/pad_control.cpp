#include "pad_control.hpp"
#include <iostream>

pad_control::pad_control()
    : VOLTAGE_SELECT(0), GPIO0(0b110110), GPIO1(0b110110), GPIO2(0b110110),
      GPIO3(0b110110), GPIO4(0b110110), GPIO5(0b110110), GPIO6(0b110110),
      GPIO7(0b110110), GPIO8(0b110110), GPIO9(0b110110), GPIO10(0b110110),
      GPIO11(0b110110), GPIO12(0b110110), GPIO13(0b110110), GPIO14(0b110110),
      GPIO15(0b110110), GPIO16(0b110110), GPIO17(0b110110), GPIO18(0b110110),
      GPIO19(0b110110), GPIO20(0b110110), GPIO21(0b110110), GPIO22(0b110110),
      GPIO23(0b110110), GPIO24(0b110110), GPIO25(0b110110), GPIO26(0b110110),
      GPIO27(0b110110), GPIO28(0b110110), GPIO29(0b110110), SWCLK(0b1111010),
      SWD(0b111010) {
  std::clog << "initialized pad registers.\n";
}

pad_control::~pad_control() {
  std::clog << "de-initialized pad registers.\n";
}

void pad_control::operator delete(void *addr) {
  static_cast<pad_control *>(addr)->~pad_control();
}

void *pad_control::operator new(size_t) {
  return reinterpret_cast<pad_control *>(base_address);
}