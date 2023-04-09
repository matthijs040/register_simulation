#include "rp2040_gpio.hpp"
#include "gpio.hpp"
#include "rp2040_defs.hpp"

#include <iostream>
#include <utility>

std::weak_ptr<rp2040_gpio> rp2040_gpio::storage_handle =
    std::weak_ptr<rp2040_gpio>();

constexpr std::size_t gpio::get_num_pins() noexcept { return 29u; }
constexpr gpio::pin_number max_pin_num = gpio::get_num_pins() - 1;

rp2040_gpio::rp2040_gpio()
    : GPIO0_STATUS(0), GPIO0_CTRL(0X1F), GPIO1_STATUS(0), GPIO1_CTRL(0X1F),
      GPIO2_STATUS(0), GPIO2_CTRL(0X1F), GPIO3_STATUS(0), GPIO3_CTRL(0X1F),
      GPIO4_STATUS(0), GPIO4_CTRL(0X1F), GPIO5_STATUS(0), GPIO5_CTRL(0X1F),
      GPIO6_STATUS(0), GPIO6_CTRL(0X1F), GPIO7_STATUS(0), GPIO7_CTRL(0X1F),
      GPIO8_STATUS(0), GPIO8_CTRL(0X1F), GPIO9_STATUS(0), GPIO9_CTRL(0X1F),
      GPIO10_STATUS(0), GPIO10_CTRL(0X1F), GPIO11_STATUS(0), GPIO11_CTRL(0X1F),
      GPIO12_STATUS(0), GPIO12_CTRL(0X1F), GPIO13_STATUS(0), GPIO13_CTRL(0X1F),
      GPIO14_STATUS(0), GPIO14_CTRL(0X1F), GPIO15_STATUS(0), GPIO15_CTRL(0X1F),
      GPIO16_STATUS(0), GPIO16_CTRL(0X1F), GPIO17_STATUS(0), GPIO17_CTRL(0X1F),
      GPIO18_STATUS(0), GPIO18_CTRL(0X1F), GPIO19_STATUS(0), GPIO19_CTRL(0X1F),
      GPIO20_STATUS(0), GPIO20_CTRL(0X1F), GPIO21_STATUS(0), GPIO21_CTRL(0X1F),
      GPIO22_STATUS(0), GPIO22_CTRL(0X1F), GPIO23_STATUS(0), GPIO23_CTRL(0X1F),
      GPIO24_STATUS(0), GPIO24_CTRL(0X1F), GPIO25_STATUS(0), GPIO25_CTRL(0X1F),
      GPIO26_STATUS(0), GPIO26_CTRL(0X1F), GPIO27_STATUS(0), GPIO27_CTRL(0X1F),
      GPIO28_STATUS(0), GPIO28_CTRL(0X1F), GPIO29_STATUS(0), GPIO29_CTRL(0X1F) {
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

  if (mode == gpio::mode::disabled || mode == gpio::mode::input_only) {
    auto mask = 0x1 << 12;
    ctrl_reg &= ~mask;
    mask << 1;
    ctrl_reg |= mask;
  } else {
    const auto mask = 0x3 << 12;
    ctrl_reg |= mask;
  }
}

gpio::mode gpio::get_pin_mode(pin_number number) {
  if (is_pin_reserved(number))
    return gpio::mode::disabled;

  auto &status_reg = get_gpio_status_register(
      static_cast<rp2040_gpio *>(impl_handle.get()), number);

  return status_reg & (0x3 << 12) ? gpio::mode::input_and_output
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

  auto mask = 0x1 << 8;
  if (state == gpio::state::high)
    ctrl_reg |= mask;
  mask << 1;
  ctrl_reg |= mask;
}

gpio::state gpio::get_pin_state(pin_number number) {

  const auto &reg = get_gpio_status_register(
      static_cast<rp2040_gpio *>(impl_handle.get()), number);

  return reg & 0x1 << 17 ? gpio::state::high : gpio::state::low;
}