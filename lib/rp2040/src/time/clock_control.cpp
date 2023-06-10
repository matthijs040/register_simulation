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

std::size_t clock_control::get_num_clock_sources() noexcept {
  return clock_names.size();
}

const char *const *
clock_control::get_clock_source_names(std::size_t &num_clock_sources) noexcept {
  num_clock_sources = get_num_clock_sources();
  return clock_names.begin();
}
