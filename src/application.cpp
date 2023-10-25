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

void application::set_ROSC_state(const char *state) {
  std::cout << "called set ROSC state with state: " << state << "\n";
  uint32_t power_level = 0u;
  auto result = std::from_chars(state, state + std::strlen(state), power_level);
  if (result.ec != std::errc()) {
    std::cout << "failed to extract number from: '" << state
              << "' with error: " << std::to_underlying(result.ec) << "\n";
    return;
  }

  auto &handle = ROSC::get();
  handle.set_power_stage(power_level);

  const auto range_to_string = [](reg::ROSC::CTRL::FREQ_RANGE_states state) {
    return state == reg::ROSC::CTRL::FREQ_RANGE_states::low      ? "low"
           : state == reg::ROSC::CTRL::FREQ_RANGE_states::medium ? "medium"
           : state == reg::ROSC::CTRL::FREQ_RANGE_states::high   ? "high"
                                                                 : "invalid";
  };

  auto DS_to_string = [](reg::ROSC::drive_strength DS) {
    return DS == reg::ROSC::drive_strength::default_strength     ? "default"
           : DS == reg::ROSC::drive_strength::double_strength    ? "double"
           : DS == reg::ROSC::drive_strength::triple_strength    ? "triple"
           : DS == reg::ROSC::drive_strength::quadruple_strength ? "quadruple"
                                                                 : "invalid";
  };

  printf("ROSC state is now:\n\
    frequency range: %s\n\
    power stages: DS0: %s, DS1: %s, DS2: %s, DS3: %s, DS4: %s, DS5: %s, DS6: %s, DS7: %s\n\
    DIV: %u\n",
         range_to_string(handle.CTRL.FREQ_RANGE),
         DS_to_string(handle.FREQA.DS0), DS_to_string(handle.FREQA.DS1),
         DS_to_string(handle.FREQA.DS2), DS_to_string(handle.FREQA.DS3),
         DS_to_string(handle.FREQB.DS4), DS_to_string(handle.FREQB.DS5),
         DS_to_string(handle.FREQB.DS6), DS_to_string(handle.FREQB.DS7),
         handle.DIV.divisor);
}

void application::set_ROSC_devisor(const char *param) {
  uint8_t divisor = 0u;
  auto result = std::from_chars(param, param + std::strlen(param), divisor);
  if (result.ec != std::errc()) {
    std::cout << "failed to extract number from: '" << param
              << "' with error: " << std::to_underlying(result.ec) << "\n";
    return;
  }

  if (divisor > 31) {
    std::cout << "parsed divisor is > 31 and thus invalid.\n";
    return;
  }
  auto &handle = ROSC::get();
  handle.DIV.divisor = 0xaa0 + divisor;
  std::cout << "devisor is now set to: " << handle.DIV.divisor << "\n";
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
           named_function{"ROSC.set.state ", 
                          std::bind(&application::set_ROSC_state, this,
                                    std::placeholders::_1)},
           named_function{"ROSC.set.divisor ",
                          std::bind(&application::set_ROSC_devisor, this,
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
                 std::strncmp(line.data(), fn.first, std::strlen(fn.first)) ==
                     0;
        });

    if (found != RPCs.end())
      found->second(line.data() + std::strlen(found->first));
  }
}
