#include <HAL/GPIO.hpp>
#include <rp2040/GPIO/GPIO.hpp>
#include <rp2040/GPIO/GPIO_handle.hpp>
#include <rp2040/GPIO/user_IO.hpp>

#include <system_error>

std::size_t GPIO::get_num_pins() noexcept { return 29u; }
static const GPIO::pin_number max_pin_num = GPIO::get_num_pins() - 1;

reg::CTRL &get_control_register(const GPIO &handle, GPIO::pin_number pin) {
  auto *reg = handle.impl_handle.get()->gpio.get();
  const auto first_offset = 1;
  const auto register_spacing = 2;

  auto *register_block = reinterpret_cast<reg::CTRL *>(reg);
  return *((register_block + first_offset) + (pin * register_spacing));
}

reg::STATUS &get_status_register(const GPIO &handle, GPIO::pin_number pin) {
  auto *registers = handle.impl_handle.get()->gpio.get();
  const auto register_spacing = 2;
  auto *register_block = reinterpret_cast<reg::STATUS *>(registers);
  return *(register_block + (pin * register_spacing));
}

reg::GPIO &get_pad_register(const GPIO &handle, GPIO::pin_number pin) {
  auto *reg = handle.impl_handle.get()->pads.get();
  const auto first_offset = 1;
  const auto register_spacing = 1;

  auto *register_block = reinterpret_cast<reg::GPIO *>(reg);
  return *((register_block + first_offset) + (pin * register_spacing));
}

GPIO::GPIO() : impl_handle(std::make_shared<GPIO_handle>()) {}

GPIO::~GPIO() {}

bool GPIO::is_pin_reserved(pin_number number) const noexcept {
  if (number > max_pin_num)
    return true;

  const auto &reg = get_control_register(*this, number);

  const bool is_disabled = reg.FUNCSEL == reg::CTRL::FUNCSEL_states::disabled;
  const bool is_used_here = reg.FUNCSEL == reg::CTRL::FUNCSEL_states::SIO;
  return !is_disabled && !is_used_here;
}

std::error_code GPIO::set_pin_mode(pin_number number, GPIO::mode mode) {
  if (is_pin_reserved(number))
    return std::make_error_code(std::errc::operation_not_permitted);

  auto &ctrl_reg = get_control_register(*this, number);
  auto &pad_reg = get_pad_register(*this, number);

  ctrl_reg.FUNCSEL = reg::CTRL::FUNCSEL_states::SIO;
  switch (mode) {
  case GPIO::mode::input_only: {
    ctrl_reg.OEOVER = reg::CTRL::OEOVER_states::FUNCSEL_defined;
    impl_handle->SIO_handle->set_pin_OE(number, reg::state::disabled);
    pad_reg.OD = reg::state::enabled;
    pad_reg.IE = reg::state::enabled;
    break;
  }
  case GPIO::mode::output_only: {
    ctrl_reg.OEOVER = reg::CTRL::OEOVER_states::FUNCSEL_defined;
    impl_handle->SIO_handle->set_pin_OE(number, reg::state::enabled);
    pad_reg.OD = reg::state::disabled;
    pad_reg.IE = reg::state::disabled;
    break;
  }
  case GPIO::mode::input_and_output: {
    ctrl_reg.OEOVER = reg::CTRL::OEOVER_states::FUNCSEL_defined;
    impl_handle->SIO_handle->set_pin_OE(number, reg::state::enabled);
    pad_reg.OD = reg::state::disabled;
    pad_reg.IE = reg::state::enabled;

    break;
  }
  case GPIO::mode::disabled: {
    ctrl_reg.FUNCSEL = reg::CTRL::FUNCSEL_states::disabled;
    impl_handle->SIO_handle->set_pin_OE(number, reg::state::disabled);
    ctrl_reg.OEOVER = reg::CTRL::OEOVER_states::disabled;
    pad_reg.OD = reg::state::disabled;
    pad_reg.IE = reg::state::disabled;
    break;
  }
  case GPIO::mode::reserved: {
    // Setting to reserved is not to be done through this public interface.
    return std::make_error_code(std::errc::operation_not_permitted);
  }
  }
  return std::error_code();
}

GPIO::mode GPIO::get_pin_mode(pin_number number) {
  if (is_pin_reserved(number))
    return GPIO::mode::reserved;

  auto &status = get_status_register(*this, number);
  auto &pad = get_pad_register(*this, number);

  const bool input_enabled = pad.IE == reg::state::set;
  const bool output_enabled = pad.OD == reg::state::cleared &&
                              status.OETOPAD == reg::state::set &&
                              impl_handle->SIO_handle->get_pin_OE(number);

  if (input_enabled && output_enabled)
    return GPIO::mode::input_and_output;
  if (input_enabled)
    return GPIO::mode::input_only;
  if (output_enabled)
    return GPIO::mode::output_only;
  return GPIO::mode::disabled;
}

std::error_code GPIO::set_pin_state(pin_number number, GPIO::state state) {
  if (is_pin_reserved(number))
    return std::make_error_code(std::errc::operation_not_permitted);

  const auto mode = get_pin_mode(number);
  if (mode == GPIO::mode::input_only || mode == GPIO::mode::disabled)
    return std::make_error_code(std::errc::resource_unavailable_try_again);

  auto &ctrl_reg = get_control_register(*this, number);

  switch (state) {
  case GPIO::state::floating: {
    return std::make_error_code(std::errc::operation_not_supported);
  }
  case GPIO::state::high: {
    ctrl_reg.OUTOVER = reg::CTRL::OUTOVER_states::driven_high;
    break;
  }
  case GPIO::state::low: {
    ctrl_reg.OUTOVER = reg::CTRL::OUTOVER_states::driven_low;
    break;
  }
  }
  return std::error_code();
}

GPIO::state GPIO::get_pin_state(pin_number number) {
  const auto &reg = get_status_register(*this, number);
  return reg.OUTTOPAD == reg::state::set ? GPIO::state::high : GPIO::state::low;
}