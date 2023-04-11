#include "rp2040_gpio.hpp"
#include "rp2040_pad_control.hpp"
#include "rp2040_defs.hpp"
#include <HAL/gpio.hpp>

#include <iostream>
#include <utility>
#include <new>

std::weak_ptr<rp2040_gpio> rp2040_gpio::storage_handle =
    std::weak_ptr<rp2040_gpio>();

template <>
inline std::shared_ptr<rp2040_gpio> std::make_shared<rp2040_gpio>() {
  if (const auto ptr = rp2040_gpio::storage_handle.lock())
    return ptr;

  auto ptr = std::shared_ptr<rp2040_gpio>();
  if (USE_SIMULATED_REGISTERS) {
    ptr = std::reinterpret_pointer_cast<rp2040_gpio>(
        std::shared_ptr<simulated_peripheral<rp2040_gpio>>(
            new simulated_peripheral<rp2040_gpio>()));
  } else {
    ptr = std::shared_ptr<rp2040_gpio>(new rp2040_gpio());
  }
  ::new (ptr.get()) rp2040_gpio();

  rp2040_gpio::storage_handle = ptr;
  return ptr;
}

std::size_t gpio::get_num_pins() noexcept { return 29u; }
static const gpio::pin_number max_pin_num = gpio::get_num_pins() - 1;

rp2040_gpio::rp2040_gpio()
    : GPIO0_STATUS(0U), GPIO0_CTRL(0X1FU), GPIO1_STATUS(0U), GPIO1_CTRL(0X1FU),
      GPIO2_STATUS(0U), GPIO2_CTRL(0X1FU), GPIO3_STATUS(0U), GPIO3_CTRL(0X1FU),
      GPIO4_STATUS(0U), GPIO4_CTRL(0X1FU), GPIO5_STATUS(0U), GPIO5_CTRL(0X1FU),
      GPIO6_STATUS(0U), GPIO6_CTRL(0X1FU), GPIO7_STATUS(0U), GPIO7_CTRL(0X1FU),
      GPIO8_STATUS(0U), GPIO8_CTRL(0X1FU), GPIO9_STATUS(0U), GPIO9_CTRL(0X1FU),
      GPIO10_STATUS(0U), GPIO10_CTRL(0X1FU), GPIO11_STATUS(0U),
      GPIO11_CTRL(0X1FU), GPIO12_STATUS(0U), GPIO12_CTRL(0X1FU),
      GPIO13_STATUS(0U), GPIO13_CTRL(0X1FU), GPIO14_STATUS(0U),
      GPIO14_CTRL(0X1FU), GPIO15_STATUS(0U), GPIO15_CTRL(0X1FU),
      GPIO16_STATUS(0U), GPIO16_CTRL(0X1FU), GPIO17_STATUS(0U),
      GPIO17_CTRL(0X1FU), GPIO18_STATUS(0U), GPIO18_CTRL(0X1FU),
      GPIO19_STATUS(0U), GPIO19_CTRL(0X1FU), GPIO20_STATUS(0U),
      GPIO20_CTRL(0X1FU), GPIO21_STATUS(0U), GPIO21_CTRL(0X1FU),
      GPIO22_STATUS(0U), GPIO22_CTRL(0X1FU), GPIO23_STATUS(0U),
      GPIO23_CTRL(0X1FU), GPIO24_STATUS(0U), GPIO24_CTRL(0X1FU),
      GPIO25_STATUS(0U), GPIO25_CTRL(0X1FU), GPIO26_STATUS(0U),
      GPIO26_CTRL(0X1FU), GPIO27_STATUS(0U), GPIO27_CTRL(0X1FU),
      GPIO28_STATUS(0U), GPIO28_CTRL(0X1FU), GPIO29_STATUS(0U),
      GPIO29_CTRL(0X1FU) {
  // TODO: reset registers to enabled but cleared state.
  std::cout << "constructed impl\n";
}

rp2040_gpio::~rp2040_gpio() {
  // TODO: Set gpio to lowest power state.
  std::cout << "destructed impl\n";
}

gpio::gpio() : impl_handle(std::make_shared<rp2040_gpio>()) {
  std::cout << "constructed wrapper\n";
}

gpio::~gpio() { std::cout << "destructed wrapper\n"; }

inline device_register &get_gpio_status_register(rp2040_gpio *registers,
                                                 gpio::pin_number pin) {
  const auto register_spacing = 2;
  auto *register_block = reinterpret_cast<device_register *>(registers);
  return *(register_block + (pin * register_spacing));
}

inline device_register &get_gpio_control_register(rp2040_gpio *registers,
                                                  gpio::pin_number pin) {
  const auto first_offset = 1;
  const auto register_spacing = 2;

  auto *register_block = reinterpret_cast<device_register *>(registers);
  return *((register_block + first_offset) + (pin * register_spacing));
}

bool gpio::is_pin_reserved(pin_number number) const noexcept {
  if (number > max_pin_num)
    return true;

  const auto &reg = get_gpio_control_register(
      static_cast<rp2040_gpio *>(impl_handle.get()), number);

  return reg != std::to_underlying<GPIO_FUNCSEL>(GPIO_FUNCSEL::Disabled) &&
         reg != std::to_underlying<GPIO_FUNCSEL>(GPIO_FUNCSEL::SIO);
}

void gpio::set_pin_mode(pin_number number, gpio::mode mode) {
  if (is_pin_reserved(number))
    return;

  auto &ctrl_reg = get_gpio_control_register(
      static_cast<rp2040_gpio *>(impl_handle.get()), number);

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

  auto &status_reg = get_gpio_status_register(
      static_cast<rp2040_gpio *>(impl_handle.get()), number);

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

  auto &ctrl_reg = get_gpio_control_register(
      static_cast<rp2040_gpio *>(impl_handle.get()), number);

  if (state == gpio::state::floating)
    return;

  register_mask mask = 0x1 << 8;
  if (state == gpio::state::high)
    ctrl_reg |= mask;
  mask << 1;
  ctrl_reg |= mask;
}

gpio::state gpio::get_pin_state(pin_number number) {

  const auto &reg = get_gpio_status_register(
      static_cast<rp2040_gpio *>(impl_handle.get()), number);

  return reg & static_cast<register_mask>(0x1 << 17) ? gpio::state::high
                                                     : gpio::state::low;
}