#include "pad_control.hpp"

pad_control::pad_control() {}

pad_control::~pad_control() {}

void pad_control::operator delete(void *addr) {
  static_cast<pad_control *>(addr)->~pad_control();
}

void *pad_control::operator new(size_t) {
  return reinterpret_cast<pad_control *>(base_address);
}