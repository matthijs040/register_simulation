#include "GPIO_handle.hpp"
#include "user_IO.hpp"
#include <HAL/GPIO.hpp>
#include <iostream>
#include <utility>

std::size_t GPIO::get_num_pins() noexcept { return 29u; }
static const GPIO::pin_number max_pin_num = GPIO::get_num_pins() - 1;

GPIO::GPIO() : impl_handle(std::make_shared<GPIO_handle>()) {}

GPIO::~GPIO() {}

inline reg::STATUS &get_gpio_status_register(const GPIO &handle,
                                             GPIO::pin_number pin) {
  auto *registers = handle.impl_handle.get()->gpio.get();
  const auto register_spacing = 2;
  auto *register_block = reinterpret_cast<reg::STATUS *>(registers);
  return *(register_block + (pin * register_spacing));
}

inline reg::CTRL &get_gpio_control_register(const GPIO &handle,
                                            GPIO::pin_number pin) {
  auto *reg = handle.impl_handle.get()->gpio.get();
  const auto first_offset = 1;
  const auto register_spacing = 2;

  auto *register_block = reinterpret_cast<reg::CTRL *>(reg);
  return *((register_block + first_offset) + (pin * register_spacing));
}

inline reg::GPIO &get_pad_register(const GPIO &handle, GPIO::pin_number pin) {
  auto *reg = handle.impl_handle.get()->pads.get();
  const auto first_offset = 1;
  const auto register_spacing = 1;

  auto *register_block = reinterpret_cast<reg::GPIO *>(reg);
  return *((register_block + first_offset) + (pin * register_spacing));
}

bool GPIO::is_pin_reserved(pin_number number) const noexcept {
  if (number > max_pin_num)
    return true;

  const auto &reg = get_gpio_control_register(*this, number);
  const auto current_function = reg.FUNCSEL;

  const bool is_disabled = current_function == std::to_underlying<GPIO_FUNCSEL>(GPIO_FUNCSEL::disabled);
  const bool is_software_controlled = current_function == std::to_underlying<GPIO_FUNCSEL>(GPIO_FUNCSEL::SIO);
  return !is_disabled && !is_software_controlled;
}        

void GPIO::set_pin_mode(pin_number number, GPIO::mode mode) {
  if (is_pin_reserved(number))
    return;

  auto &ctrl_reg = get_gpio_control_register(*this, number);
  auto &pad_reg = get_pad_register(*this, number);

  ctrl_reg.FUNCSEL = std::to_underlying(GPIO_FUNCSEL::SIO);
  switch (mode) {
  case GPIO::mode::input_only: {
    ctrl_reg.OEOVER = true;
    pad_reg.OD = false;
    pad_reg.IE = true;
    break;
  }
  case GPIO::mode::output_only: {
    ctrl_reg.OEOVER = true;
    ctrl_reg.OUTOVER = true;
    pad_reg.IE = false;
    break;
  }
  case GPIO::mode::input_and_output: {
    ctrl_reg.OUTOVER = 0b11;
    pad_reg.OD = false;
    pad_reg.IE = true;
    break;
  }
  case GPIO::mode::disabled: {
    ctrl_reg.FUNCSEL = std::to_underlying(GPIO_FUNCSEL::disabled);
    ctrl_reg.OEOVER = false;
    pad_reg.OD = true;
    pad_reg.IE = false;
    break;
  }
  case GPIO::mode::reserved: {
    // Setting to reserved is not to be done through this public interface.
    break;
  }
  }
}

GPIO::mode GPIO::get_pin_mode(pin_number number) {
  if (is_pin_reserved(number))
    return GPIO::mode::reserved;

  auto &status = get_gpio_status_register(*this, number);
  auto &pad = get_pad_register(*this, number);

  const bool input_enabled = pad.IE;
  const bool output_enabled = !pad.OD && status.OETOPAD;

  if (input_enabled && output_enabled)
    return GPIO::mode::input_and_output;
  if (input_enabled)
    return GPIO::mode::input_only;
  if (output_enabled)
    return GPIO::mode::output_only;
  return GPIO::mode::disabled;
}

void GPIO::set_pin_state(pin_number number, GPIO::state state) {
  if (is_pin_reserved(number))
    return;

  const auto mode = get_pin_mode(number);
  if (mode == GPIO::mode::input_only || mode == GPIO::mode::disabled)
    return;

  auto &ctrl_reg = get_gpio_control_register(*this, number);

  switch (state) {
  case GPIO::state::floating: {
    return;
  }
  case GPIO::state::high: {
    ctrl_reg.OUTOVER = 0b11;
    break;
  }
  case GPIO::state::low: {
    ctrl_reg.OUTOVER = 0b10;
    break;
  }
  }
}

GPIO::state GPIO::get_pin_state(pin_number number) {
  const auto &reg = get_gpio_status_register(*this, number);
  return reg.OUTTOPAD ? GPIO::state::high : GPIO::state::low;
}