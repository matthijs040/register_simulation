#include "application.hpp"
#include <functional>
#include <iostream>

#include <cstring>
#include <span>

#include <hardware/clocks.h>
#include <pico/stdlib.h>

#include <charconv>
#include <rp2040/GPIO/user_IO.hpp>
#include <rp2040/time/clocks.hpp>

#include <rp2040/time/ROSC.hpp>
#include <rp2040/time/registers/ROSC.hpp>

void application::enable_LED(const char *) {
  LED_handle.set_pin_mode(GPIO::mode::output_only);
  LED_handle.set_pin_state(GPIO::state::high);
  const char *state =
      LED_handle.get_pin_state() == GPIO::state::high ? "high" : "low";
  std::cout << "LED state is now: " << state << "\n";
}

void application::disable_LED(const char *) {
  LED_handle.set_pin_mode(GPIO::mode::output_only);
  LED_handle.set_pin_state(GPIO::state::low);
  std::cout << "Set LED low.\n";
}

void application::get_LED_state(const char *) {
  const char *state =
      LED_handle.get_pin_state() == GPIO::state::high ? "high" : "low";
  std::cout << "LED state is: " << state << '\n';
}

void attach_clock(reg::CLK_GPOUT_CTRL::AUXSRC_states source) {
  auto &pin_handle = user_IO::get();
  if (pin_handle.GPIO21_CTRL.FUNCSEL != reg::CTRL::FUNCSEL_states::Clock_GPIO) {
    if (pin_handle.GPIO21_CTRL.FUNCSEL != reg::CTRL::FUNCSEL_states::disabled) {
      std::cerr << "Pin to expose clock signal on is occupied.\n";
      return;
    }
    pin_handle.GPIO21_CTRL.FUNCSEL = reg::CTRL::FUNCSEL_states::Clock_GPIO;
  }

  auto &clock_handle = clocks::get();
  clock_handle.CLK_GPOUT0_CTRL.AUXSRC = source;
  clock_handle.CLK_GPOUT0_DIV.INT = 1u;
  clock_handle.CLK_GPOUT0_DIV.FRAC = 0u;
  clock_handle.CLK_GPOUT0_CTRL.ENABLE = reg::state::enabled;
}

void application::attach_ROSC(const char *) {
  attach_clock(reg::CLK_GPOUT_CTRL::AUXSRC_states::rosc_clksrc);
}

void application::attach_sys(const char *) {
  attach_clock(reg::CLK_GPOUT_CTRL::AUXSRC_states::clk_sys);
}

void application::detach_clock(const char *) {
  // Detach by making clock index " clk_gpout* " sourceless?
  // Cannot do that. Each allowed source value is a clock signal.
  // Just disable the output.
  auto &clock_handle = clocks::get();
  clock_handle.CLK_GPOUT0_CTRL.ENABLE = reg::state::disabled;
  auto &pin_handle = user_IO::get();
  if (pin_handle.GPIO21_CTRL.FUNCSEL == reg::CTRL::FUNCSEL_states::Clock_GPIO)
    pin_handle.GPIO21_CTRL.FUNCSEL = reg::CTRL::FUNCSEL_states::disabled;
}

reg::ROSC::drive_strength take_drive_strength(uint32_t &strength) {
  if (strength >= 3) {
    strength -= 3;
    return reg::ROSC::drive_strength::quadruple_strength;
  }
  if (strength >= 2) {
    strength -= 2;
    return reg::ROSC::drive_strength::triple_strength;
  }
  if (strength >= 1) {
    strength -= 1;
    return reg::ROSC::drive_strength::double_strength;
  }

  return reg::ROSC::drive_strength::default_strength;
}

reg::ROSC::CTRL::FREQ_RANGE_states
determine_frequency_range(uint32_t &strength) {
  // The three power-stages of all 8 drive-strength registers. (used in the
  // "low" frequency range)
  constexpr auto low_range_power = 8 * 3;
  // the three power-stages of the 6 drive-strength registers used in the "mid"
  // frequency range.
  constexpr auto mid_range_power = 6 * 3;

  if (strength <= low_range_power)
    return reg::ROSC::CTRL::FREQ_RANGE_states::low;
  strength -= low_range_power;
  if (strength <= mid_range_power)
    return reg::ROSC::CTRL::FREQ_RANGE_states::medium;
  strength -= mid_range_power;
  return reg::ROSC::CTRL::FREQ_RANGE_states::high;
}

void apply_settings(
    reg::ROSC::CTRL::FREQ_RANGE_states frequency_range,
    reg::ROSC::drive_strength DS0 = reg::ROSC::drive_strength::default_strength,
    reg::ROSC::drive_strength DS1 = reg::ROSC::drive_strength::default_strength,
    reg::ROSC::drive_strength DS2 = reg::ROSC::drive_strength::default_strength,
    reg::ROSC::drive_strength DS3 = reg::ROSC::drive_strength::default_strength,
    reg::ROSC::drive_strength DS4 = reg::ROSC::drive_strength::default_strength,
    reg::ROSC::drive_strength DS5 = reg::ROSC::drive_strength::default_strength,
    reg::ROSC::drive_strength DS6 = reg::ROSC::drive_strength::default_strength,
    reg::ROSC::drive_strength DS7 =
        reg::ROSC::drive_strength::default_strength) {
  auto &handle = ROSC::get();

  handle.CTRL.FREQ_RANGE = frequency_range;
  handle.FREQA.DS0 = DS0;
  handle.FREQA.DS1 = DS1;
  handle.FREQA.DS2 = DS2;
  handle.FREQA.DS3 = DS3;
  handle.FREQA.PASSWD = reg::ROSC::PASSWD_states::apply;

  handle.FREQB.DS4 = DS4;
  handle.FREQB.DS5 = DS5;
  handle.FREQB.DS6 = DS6;
  handle.FREQB.DS7 = DS7;
  handle.FREQB.PASSWD = reg::ROSC::PASSWD_states::apply;
}

void application::set_ROSC_state(const char *state) {
  uint32_t power_level = 0u;
  auto result = std::from_chars(state, state + std::strlen(state), power_level);
  if (result.ec != std::errc())
    return;

  const auto frequency_range = determine_frequency_range(power_level);
  apply_settings(
      frequency_range, take_drive_strength(power_level),
      take_drive_strength(power_level), take_drive_strength(power_level),
      take_drive_strength(power_level),
      // The following DS registers have their DS set based on given strength
      // only if their frequency range uses those stages. The datasheet mentions
      // that these stages must *at least* have the strength of the lowest-power
      // stage that is active in the loop. Setting these at their highest anyway
      // guarantees this condition while not affecting frequency.
      frequency_range == reg::ROSC::CTRL::FREQ_RANGE_states::low ||
              frequency_range == reg::ROSC::CTRL::FREQ_RANGE_states::medium
          ? take_drive_strength(power_level)
          : reg::ROSC::drive_strength::quadruple_strength,
      frequency_range == reg::ROSC::CTRL::FREQ_RANGE_states::low ||
              frequency_range == reg::ROSC::CTRL::FREQ_RANGE_states::medium
          ? take_drive_strength(power_level)
          : reg::ROSC::drive_strength::quadruple_strength,
      frequency_range == reg::ROSC::CTRL::FREQ_RANGE_states::low
          ? take_drive_strength(power_level)
          : reg::ROSC::drive_strength::quadruple_strength,
      frequency_range == reg::ROSC::CTRL::FREQ_RANGE_states::low
          ? take_drive_strength(power_level)
          : reg::ROSC::drive_strength::quadruple_strength);
}

void get_string(std::span<char> data) {
  std::size_t index = 0;
  while (index < data.size()) {
    int character = 0;
    while ((character = getchar_timeout_us(1)) == PICO_ERROR_TIMEOUT)
      sleep_ms(1);
    std::cout << static_cast<char>(character);
    std::cout.flush();

    if (character == '\n' || character == '\r')
      break;
    data[index++] = character & 0xFF;
  }
}

application::application(GPIO &LED_handle_)
    : LED_handle(LED_handle_),
      RPCs(
          {named_function{"LED.set.high",
                          std::bind(&application::enable_LED, this,
                                    std::placeholders::_1)},
           named_function{"LED.set.low",
                          std::bind(&application::disable_LED, this,
                                    std::placeholders::_1)},
           named_function{"LED.get", std::bind(&application::get_LED_state,
                                               this, std::placeholders::_1)},
           named_function{"CLK.attach.ROSC",
                          std::bind(&application::attach_ROSC, this,
                                    std::placeholders::_1)},
           named_function{"CLK.attach.sys",
                          std::bind(&application::attach_sys, this,
                                    std::placeholders::_1)},
           named_function{"CLK.detach", std::bind(&application::detach_clock,
                                                  this, std::placeholders::_1)},
           named_function{"ROSC.set.state",
                          std::bind(&application::set_ROSC_state, this,
                                    std::placeholders::_1)}})

{}

application::~application() { detach_clock(); }

void application::run() {
  while (true) {
    constexpr size_t max_command_size = 30;
    char storage[max_command_size] = {};
    std::memset(storage, '\0', sizeof(storage));

    std::cout << "Enter command." << std::endl;
    std::span<char> line = {storage, sizeof(storage)};
    get_string(line.subspan(0, line.size() - 1));
    line.back() = '\0';

    std::cout << "gotten line: '" << line.data() << "'" << std::endl;

    const auto found =
        std::find_if(RPCs.begin(), RPCs.end(), [line](named_function fn) {
          return std::strlen(line.data()) >= std::strlen(fn.first) &&
                 std::strcmp(line.data(), fn.first) == 0;
        });

    if (found != RPCs.end())
      found->second(line.data() + std::strlen(found->first));
  }
}
