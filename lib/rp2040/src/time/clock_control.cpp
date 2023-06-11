#include <HAL/clock_control.hpp>
#include <algorithm>

static const std::array clock_names = {"gpout0", "gpout1", "gpout2", "gpout3",
                                       "ref",    "sys",    "peri",   "usb",
                                       "adc",    "rtc"};

std::error_code initialize(clock_control::clock_name name) {
  if (std::find(clock_names.begin(), clock_names.end(), name) ==
      std::end(clock_names))
    return std::make_error_code(std::errc::invalid_argument);
  return {};
}

clock_control::clock_control(clock_name name)
    : addressed_clock(name), initialization_result(initialize(name)) {}

clock_control::~clock_control() {}

std::error_code
clock_control::sleep_for(std::chrono::nanoseconds) const noexcept {
  return {};
}

std::error_code
clock_control::get_current_frequency(kiloHertz &value) const noexcept {
  (void)value;
  return {};
}

std::error_code clock_control::set_current_frequency(kiloHertz value) noexcept {
  (void)value;
  return {};
}

std::size_t clock_control::get_num_clocks() noexcept {
  return clock_names.size();
}

std::span<const char *const> clock_control::get_clock_names() noexcept {
  return std::span(clock_names).subspan(0, clock_names.size());
}
