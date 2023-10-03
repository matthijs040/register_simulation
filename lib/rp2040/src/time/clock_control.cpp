#include <HAL/clock_control.hpp>
#include <algorithm>
#include <cstring>
#include <rp2040/time/clocks.hpp>

static const std::array clock_names = {"pll_sys_clksrc_primary",
                                       "pll_usb_clksrc_primary",
                                       "rosc_clksrc",
                                       "rosc_clksrc_ph",
                                       "xosc_clksrc",
                                       "clksrc_gpin0",
                                       "clksrc_gpin1",
                                       "clk_ref",
                                       "clk_sys",
                                       "clk_peri",
                                       "clk_usb",
                                       "clk_adc",
                                       "clk_rtc"};

std::error_code initialize(clock_control::clock_name name)
{

  if (std::find_if(
          clock_names.begin(), clock_names.end(), [&name](const char *name_)
          { return std::strncmp(
                name, name_, std::min(std::strlen(name), std::strlen(name_))); }) == clock_names.end())
    return std::make_error_code(std::errc::invalid_argument);

  // TODO: Ensure that the selected clock is enabled.

  return {};
}

clock_control::clock_control(clock_name name)
    : addressed_clock(name), initialization_result(initialize(name)) {}

clock_control::~clock_control() {}

std::error_code
clock_control::sleep_for(std::chrono::nanoseconds) const noexcept
{
  return {};
}

std::expected<clock_control::kiloHertz, std::error_code>
clock_control::get_current_frequency() const noexcept
{
  auto ret = std::expected<clock_control::kiloHertz, std::error_code>();
  if (initialization_result)
    return ret = std::unexpected(std::make_error_code(std::errc::operation_not_permitted));

  auto &periph = clocks::get();

  if (periph.CLK_REF_CTRL.SRC != reg::CLK_REF_CTRL::SRC_states::rosc_clksrc_ph)
    periph.CLK_REF_CTRL.SRC = reg::CLK_REF_CTRL::SRC_states::rosc_clksrc_ph;

  if (periph.FC0_STATUS.RUNNING == reg::state::set)
    return std::unexpected(std::make_error_code(std::errc::operation_in_progress));
  if (periph.FC0_STATUS.DIED == reg::state::set)
    return std::unexpected(std::make_error_code(std::errc::operation_canceled));
  if (periph.FC0_STATUS.DONE == reg::state::set)
    return periph.FC0_RESULT.KHZ / periph.FC0_RESULT.FRAC;

  // The +1 is to account for the "none"-element in the enumerator.
  const auto clock = static_cast<reg::FC0_SRC::Clocks>((addressed_clock - clock_names.front()) + 1);

  periph.FC0_INTERVAL.frequency_test_interval = 10U; // FIXME: replace, this value was stolen from pico-SDK.
  periph.FC0_MIN_KHZ.minimum_pass_frequency = 0U;
  periph.FC0_MAX_KHZ.maximum_pass_frequency = periph.FC0_MAX_KHZ.maximum_pass_frequency.max;
  periph.FC0_SRC.clock_to_frequency_count = clock;

  return std::unexpected(std::make_error_code(std::errc::operation_in_progress));
}

std::expected<clock_control::kiloHertz, std::error_code> clock_control::set_current_frequency(kiloHertz /* value */ ) noexcept
{
   // auto &periph = clocks::get();
  

  return {};
}

std::size_t clock_control::get_num_clocks() noexcept
{
  return clock_names.size();
}

std::span<const char *const> clock_control::get_clock_names() noexcept
{
  return std::span(clock_names).subspan(0, clock_names.size());
}
