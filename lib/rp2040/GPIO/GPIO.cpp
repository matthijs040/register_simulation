#include "user_IO.hpp"
#include <HAL/GPIO.hpp>
#include <iostream>
#include <utility>

std::size_t GPIO::get_num_pins() noexcept { return 29u; }
static const GPIO::pin_number max_pin_num = GPIO::get_num_pins() - 1;

GPIO::GPIO() : impl_handle(std::make_shared<user_IO>()) {
  std::cout << "constructed wrapper\n";
}

GPIO::~GPIO() { std::cout << "destructed wrapper\n"; }

inline device_register &get_gpio_status_register(user_IO *registers,
                                                 GPIO::pin_number pin) {
  const auto register_spacing = 2;
  auto *register_block = reinterpret_cast<device_register *>(registers);
  return *(register_block + (pin * register_spacing));
}

inline device_register &get_gpio_control_register(user_IO *registers,
                                                  GPIO::pin_number pin) {
  const auto first_offset = 1;
  const auto register_spacing = 2;

  auto *register_block = reinterpret_cast<device_register *>(registers);
  return *((register_block + first_offset) + (pin * register_spacing));
}

bool GPIO::is_pin_reserved(pin_number number) const noexcept {
  if (number > max_pin_num)
    return true;

  const auto &reg = get_gpio_control_register(
      static_cast<user_IO *>(impl_handle.get()), number);

  return reg != std::to_underlying<GPIO_FUNCSEL>(GPIO_FUNCSEL::Disabled) &&
         reg != std::to_underlying<GPIO_FUNCSEL>(GPIO_FUNCSEL::SIO);
}

void GPIO::set_pin_mode(pin_number number, GPIO::mode mode) {
  if (is_pin_reserved(number))
    return;

  auto &ctrl_reg = get_gpio_control_register(
      static_cast<user_IO *>(impl_handle.get()), number);

  switch (mode) {
  case GPIO::mode::reserved: {
    const auto mask = 0b11 << 12;
    ctrl_reg &= ~mask;
    return;
  }
  case GPIO::mode::disabled:
  // No way to disable pad sensing.
  case GPIO::mode::input_only: {
    auto mask = 0b1 << 12;
    ctrl_reg &= ~mask;
    mask << 1;
    ctrl_reg |= mask;
    return;
  }
  case GPIO::mode::output_only:
  // No way to disable pad sensing.
  case GPIO::mode::input_and_output: {
    const auto mask = 0b11 << 12;
    ctrl_reg |= mask;
  }
  }
}

GPIO::mode GPIO::get_pin_mode(pin_number number) {
  if (is_pin_reserved(number))
    return GPIO::mode::disabled;

  auto &status_reg = get_gpio_status_register(
      static_cast<user_IO *>(impl_handle.get()), number);

  return status_reg & static_cast<register_mask>(0x3 << 12)
             ? GPIO::mode::input_and_output
             : GPIO::mode::input_only;
}

void GPIO::set_pin_state(pin_number number, GPIO::state state) {
  if (is_pin_reserved(number))
    return;

  const auto mode = get_pin_mode(number);
  if (mode == GPIO::mode::input_only || mode == GPIO::mode::disabled)
    return;

  auto &ctrl_reg =
      get_gpio_control_register(static_cast<user_IO *>(impl_handle.get()), number);

  if (state == GPIO::state::floating)
    return;

  register_mask mask = 0x1 << 8;
  if (state == GPIO::state::high)
    ctrl_reg |= mask;
  mask << 1;
  ctrl_reg |= mask;
}

GPIO::state GPIO::get_pin_state(pin_number number) {

  const auto &reg = get_gpio_status_register(
      static_cast<user_IO *>(impl_handle.get()), number);

  return reg & static_cast<register_mask>(0x1 << 17) ? GPIO::state::high
                                                     : GPIO::state::low;
}