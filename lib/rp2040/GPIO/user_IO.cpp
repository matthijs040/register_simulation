#include "user_IO.hpp"
#include "pad_control.hpp"
#include <HAL/GPIO.hpp>

#include <iostream>
#include <new>

std::weak_ptr<user_IO> user_IO::storage_handle = std::weak_ptr<user_IO>();

user_IO::user_IO() {
  // TODO: reset registers to enabled but cleared state.
}

user_IO::~user_IO() {
  // TODO: Set gpio to lowest power state.
}