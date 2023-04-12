#include "GPIO_handle.hpp"
#include "user_IO.hpp"
#include <HAL/GPIO.hpp>
#include <iostream>
#include <utility>

std::size_t GPIO::get_num_pins() noexcept { return 29u; }
static const GPIO::pin_number max_pin_num = GPIO::get_num_pins() - 1;

GPIO::GPIO() : impl_handle(std::make_shared<GPIO_handle>()) {
  std::cout << "constructed wrapper\n";
}

GPIO::~GPIO() { std::cout << "destructed wrapper\n"; }

inline device_register &get_gpio_status_register(const GPIO &handle,
                                                 GPIO::pin_number pin) {
  auto *registers =
      static_cast<GPIO_handle *>(handle.impl_handle.get())->gpio.get();
  const auto register_spacing = 2;
  auto *register_block = reinterpret_cast<device_register *>(registers);
  return *(register_block + (pin * register_spacing));
}

inline device_register &get_gpio_control_register(const GPIO &handle,
                                                  GPIO::pin_number pin) {
  auto *reg = static_cast<GPIO_handle *>(handle.impl_handle.get())->gpio.get();
  const auto first_offset = 1;
  const auto register_spacing = 2;

  auto *register_block = reinterpret_cast<device_register *>(reg);
  return *((register_block + first_offset) + (pin * register_spacing));
}

inline device_register &get_pad_register(const GPIO &handle,
                                         GPIO::pin_number pin) {
  auto *reg = static_cast<GPIO_handle *>(handle.impl_handle.get())->pads.get();
  const auto first_offset = 1;
  const auto register_spacing = 1;

  auto *register_block = reinterpret_cast<device_register *>(reg);
  return *((register_block + first_offset) + (pin * register_spacing));
}

bool GPIO::is_pin_reserved(pin_number number) const noexcept {
  if (number > max_pin_num)
    return true;

  const auto &reg = get_gpio_control_register(*this, number);

  return reg != std::to_underlying<GPIO_FUNCSEL>(GPIO_FUNCSEL::disabled) &&
         reg != std::to_underlying<GPIO_FUNCSEL>(GPIO_FUNCSEL::SIO);
}

void GPIO::set_pin_mode(pin_number number, GPIO::mode mode) {
  if (is_pin_reserved(number))
    return;

  auto &ctrl_reg = get_gpio_control_register(*this, number);
  auto &pad_reg = get_pad_register(*this, number);

  switch (mode) {
  case GPIO::mode::disabled: {
    apply_mask<std::to_underlying(GPIO_FUNCSEL::disabled), 0, 7>(ctrl_reg); // reset "FUNCSEL"-bits
    apply_mask<0b10, 12, 2>(ctrl_reg); // disable "output override"
    apply_mask<0b1, 7, 1>(pad_reg);    // set the "output disable"-bit
    apply_mask<0b0, 6, 1>(pad_reg);    // clear the "input enable"-bit
    break;
  }
  case GPIO::mode::reserved: {
    // Setting to reserved is not to be done through this public interface.
    break;
  }
  apply_mask<std::to_underlying(GPIO_FUNCSEL::SIO), 0, 7>(ctrl_reg); // set "FUNCSEL" for pin to SIO (Software Input Output)
  case GPIO::mode::input_only: {
    apply_mask<0b11, 12, 2>(ctrl_reg); // enable "output override"
    apply_mask<0b0, 7, 1>(pad_reg);    // clear the "output disable"-bit
    apply_mask<0b1, 6, 1>(pad_reg);    // set the "input enable"-bit
    break;
  }
  case GPIO::mode::output_only: {
    apply_mask<0b11, 12, 2>(ctrl_reg); // enable "output override"
    apply_mask<0b0, 7, 1>(pad_reg);    // clear the "output disable"-bit
    apply_mask<0b0, 6, 1>(pad_reg);    // clear the "input enable"-bit
  }

  case GPIO::mode::input_and_output: {
    apply_mask<0b11, 12, 2>(ctrl_reg); // enable "output override"
    apply_mask<0b0, 7, 1>(pad_reg);    // clear the "output disable"-bit
    apply_mask<0b1, 6, 1>(pad_reg);    // set the "input enable"-bit
  }
  }
}

GPIO::mode GPIO::get_pin_mode(pin_number number) {
  if (is_pin_reserved(number))
    return GPIO::mode::reserved;

  auto &status_reg = get_gpio_status_register(*this, number);

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

  auto &ctrl_reg = get_gpio_control_register(*this, number);

  if (state == GPIO::state::floating)
    return;

  register_mask mask = 0x1 << 8;
  if (state == GPIO::state::high)
    ctrl_reg |= mask;
  mask << 1;
  ctrl_reg |= mask;
}

GPIO::state GPIO::get_pin_state(pin_number number) {

  const auto &reg = get_gpio_status_register(*this, number);

  return reg & static_cast<register_mask>(0x1 << 17) ? GPIO::state::high
                                                     : GPIO::state::low;
}