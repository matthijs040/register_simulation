#include "IO.hpp"
#include <HAL/gpio.hpp>
#include <iostream>
#include <utility>

std::size_t gpio::get_num_pins() noexcept { return 29u; }
static const gpio::pin_number max_pin_num = gpio::get_num_pins() - 1;

gpio::gpio() : impl_handle(std::make_shared<IO>()) {
  std::cout << "constructed wrapper\n";
}

gpio::~gpio() { std::cout << "destructed wrapper\n"; }

inline device_register &get_gpio_status_register(IO *registers,
                                                 gpio::pin_number pin) {
  const auto register_spacing = 2;
  auto *register_block = reinterpret_cast<device_register *>(registers);
  return *(register_block + (pin * register_spacing));
}

inline device_register &get_gpio_control_register(IO *registers,
                                                  gpio::pin_number pin) {
  const auto first_offset = 1;
  const auto register_spacing = 2;

  auto *register_block = reinterpret_cast<device_register *>(registers);
  return *((register_block + first_offset) + (pin * register_spacing));
}

bool gpio::is_pin_reserved(pin_number number) const noexcept {
  if (number > max_pin_num)
    return true;

  const auto &reg =
      get_gpio_control_register(static_cast<IO *>(impl_handle.get()), number);

  return reg != std::to_underlying<GPIO_FUNCSEL>(GPIO_FUNCSEL::Disabled) &&
         reg != std::to_underlying<GPIO_FUNCSEL>(GPIO_FUNCSEL::SIO);
}

void gpio::set_pin_mode(pin_number number, gpio::mode mode) {
  if (is_pin_reserved(number))
    return;

  auto &ctrl_reg =
      get_gpio_control_register(static_cast<IO *>(impl_handle.get()), number);

  switch (mode) {
  case gpio::mode::reserved: {
    const auto mask = 0b11 << 12;
    ctrl_reg &= ~mask;
    return;
  }
  case gpio::mode::disabled:
  // No way to disable pad sensing.
  case gpio::mode::input_only: {
    auto mask = 0b1 << 12;
    ctrl_reg &= ~mask;
    mask << 1;
    ctrl_reg |= mask;
    return;
  }
  case gpio::mode::output_only:
  // No way to disable pad sensing.
  case gpio::mode::input_and_output: {
    const auto mask = 0b11 << 12;
    ctrl_reg |= mask;
  }
  }
}

gpio::mode gpio::get_pin_mode(pin_number number) {
  if (is_pin_reserved(number))
    return gpio::mode::disabled;

  auto &status_reg =
      get_gpio_status_register(static_cast<IO *>(impl_handle.get()), number);

  return status_reg & static_cast<register_mask>(0x3 << 12)
             ? gpio::mode::input_and_output
             : gpio::mode::input_only;
}

void gpio::set_pin_state(pin_number number, gpio::state state) {
  if (is_pin_reserved(number))
    return;

  const auto mode = get_pin_mode(number);
  if (mode == gpio::mode::input_only || mode == gpio::mode::disabled)
    return;

  auto &ctrl_reg =
      get_gpio_control_register(static_cast<IO *>(impl_handle.get()), number);

  if (state == gpio::state::floating)
    return;

  register_mask mask = 0x1 << 8;
  if (state == gpio::state::high)
    ctrl_reg |= mask;
  mask << 1;
  ctrl_reg |= mask;
}

gpio::state gpio::get_pin_state(pin_number number) {

  const auto &reg =
      get_gpio_status_register(static_cast<IO *>(impl_handle.get()), number);

  return reg & static_cast<register_mask>(0x1 << 17) ? gpio::state::high
                                                     : gpio::state::low;
}