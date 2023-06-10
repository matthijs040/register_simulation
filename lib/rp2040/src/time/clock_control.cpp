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

static const std::array clock_names = {"gpout0", "gpout1", "gpout2", "gpout3",
                                       "ref",    "sys",    "peri",   "usb",
                                       "adc",    "rtc"};

std::size_t clock_control::get_num_clocks() noexcept {
  return clock_names.size();
}

std::span<const char *const> clock_control::get_clock_names() noexcept {
  return std::span(clock_names).subspan(0, clock_names.size());
}
