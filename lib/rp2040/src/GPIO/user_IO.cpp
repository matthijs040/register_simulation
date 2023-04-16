#include <rp2040/GPIO/user_IO.hpp>
#include <HAL/GPIO.hpp>

#include <iostream>
#include <new>

std::weak_ptr<user_IO> initialize()
{
  std::clog << "initialize called.\n";
  return std::weak_ptr<user_IO>();
}

std::weak_ptr<user_IO> user_IO::storage_handle = USE_SIMULATED_REGISTERS ? initialize() : std::weak_ptr<user_IO>();

user_IO::user_IO() {
  // TODO: reset registers to enabled but cleared state.
}

user_IO::~user_IO() {
  // TODO: Set gpio to lowest power state.
}