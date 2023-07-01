#include <HAL/clock_control.hpp>
#include <algorithm>
#include <rp2040/time/clocks.hpp>

static const std::array clock_names = {"gpout0", "gpout1", "gpout2", "gpout3",
                                       "ref",    "sys",    "peri",   "usb",
                                       "adc",    "rtc"};

std::error_code initialize(clock_control::clock_name name) {
  if (std::find(clock_names.begin(), clock_names.end(), name) ==
      std::end(clock_names))
    return std::make_error_code(std::errc::invalid_argument);
  // TODO: Ensure that the selected clock is enabled.

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
  if (initialization_result)
    return std::make_error_code(std::errc::operation_not_permitted);

  auto &periph = clocks::get();
  auto return_code = std::error_code();
  if (periph.CLK_REF_CTRL.SRC != reg::CLK_REF_CTRL::SRC_states::rosc_clksrc_ph)
    periph.CLK_REF_CTRL.SRC = reg::CLK_REF_CTRL::SRC_states::rosc_clksrc_ph;

  if (periph.FC0_STATUS.RUNNING == reg::state::set)
    return std::make_error_code(std::errc::operation_would_block);
  if (periph.FC0_STATUS.DIED == reg::state::set)
    return_code = std::make_error_code(std::errc::operation_canceled);
  if (periph.FC0_STATUS.DONE == reg::state::set) {
    value = periph.FC0_RESULT.KHZ / periph.FC0_RESULT.FRAC;
    return return_code;
  }

  const auto clock = static_cast<reg::FC0_SRC::Clocks>(
      (&addressed_clock - &clock_names.front()) + 3);

  periph.FC0_SRC.clock_to_frequency_count = clock;
  return std::make_error_code(std::errc::device_or_resource_busy);
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
