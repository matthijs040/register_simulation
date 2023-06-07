#include <HAL/clock_control.hpp>

std::error_code initialize() { return {}; }

clock_control::clock_control() : initialization_result(initialize()) {}

clock_control::~clock_control() {}

std::error_code
clock_control::sleep_for(std::chrono::nanoseconds) const noexcept {
  return {};
}

clock_control::kiloHertz clock_control::get_current_frequency() const noexcept {
  return 0;
}

std::error_code
clock_control::set_current_frequency(clock_control::kiloHertz) noexcept {
  return {};
}