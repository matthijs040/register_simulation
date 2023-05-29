#include <HAL/GPIO.hpp>
#include <rp2040/GPIO/GPIO.hpp>
#include <rp2040/GPIO/SIO.hpp>
#include <rp2040/GPIO/pad_control.hpp>
#include <rp2040/GPIO/user_IO.hpp>

#include <cstdint>
#include <system_error>

std::size_t GPIO::get_num_pins() noexcept { return 29u; }
static const GPIO::pin_number max_pin_num = GPIO::get_num_pins() - 1;

reg::CTRL &get_control_register(GPIO::pin_number pin) {
  auto *reg = &user_IO::get();
  const auto first_offset = 1;
  const auto register_spacing = 2;

  auto *register_block = reinterpret_cast<reg::CTRL *>(reg);
  return *((register_block + first_offset) + (pin * register_spacing));
}

reg::STATUS &get_status_register(GPIO::pin_number pin) {
  auto *registers = &user_IO::get();
  const auto register_spacing = 2;
  auto *register_block = reinterpret_cast<reg::STATUS *>(registers);
  return *(register_block + (pin * register_spacing));
}

reg::GPIO &get_pad_register(GPIO::pin_number pin) {
  auto *reg = &pad_control::get();
  const auto first_offset = 1;
  const auto register_spacing = 1;

  auto *register_block = reinterpret_cast<reg::GPIO *>(reg);
  return *((register_block + first_offset) + (pin * register_spacing));
}

std::error_code reserve_pin(const GPIO::pin_number pin) {
  if (GPIO::is_pin_reserved(pin))
    return std::make_error_code(std::errc::device_or_resource_busy);
  auto &ctrl = get_control_register(pin);
  ctrl.FUNCSEL = reg::CTRL::FUNCSEL_states::SIO;
  return std::error_code();
}

GPIO::GPIO(const pin_number number)
    : acquired_pin(number), initialization_result(reserve_pin(number)) {}

GPIO::~GPIO() {
  if (initialization_result)
    return;

  auto &ctrl = get_control_register(acquired_pin);
  ctrl.FUNCSEL = reg::CTRL::FUNCSEL_states::disabled;
}

bool GPIO::is_pin_reserved(pin_number number) noexcept {
  if (number > max_pin_num)
    return true;

  const auto &reg = get_control_register(number);

  const bool is_disabled = reg.FUNCSEL == reg::CTRL::FUNCSEL_states::disabled;
  const bool is_used_here = reg.FUNCSEL == reg::CTRL::FUNCSEL_states::SIO;
  return !is_disabled && !is_used_here;
}

std::error_code GPIO::set_pin_mode(GPIO::mode mode) {
  if (is_pin_reserved(acquired_pin))
    return std::make_error_code(std::errc::operation_not_permitted);

  auto &ctrl_reg = get_control_register(acquired_pin);
  auto &pad_reg = get_pad_register(acquired_pin);

  switch (mode) {
  case GPIO::mode::input_only: {
    SIO::get().set_pin_OE(acquired_pin, reg::state::disabled);
    ctrl_reg.OEOVER = reg::CTRL::OEOVER_states::FUNCSEL_defined;
    pad_reg.OD = reg::state::enabled;
    pad_reg.IE = reg::state::enabled;
    break;
  }
  case GPIO::mode::output_only: {
    SIO::get().set_pin_OE(acquired_pin, reg::state::enabled);
    ctrl_reg.OEOVER = reg::CTRL::OEOVER_states::FUNCSEL_defined;
    pad_reg.OD = reg::state::disabled;
    pad_reg.IE = reg::state::disabled;
    break;
  }
  case GPIO::mode::input_and_output: {
    SIO::get().set_pin_OE(acquired_pin, reg::state::enabled);
    ctrl_reg.OEOVER = reg::CTRL::OEOVER_states::FUNCSEL_defined;
    pad_reg.OD = reg::state::disabled;
    pad_reg.IE = reg::state::enabled;

    break;
  }
  case GPIO::mode::disabled: {
    SIO::get().set_pin_OE(acquired_pin, reg::state::disabled);
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

GPIO::mode GPIO::get_pin_mode() {
  if (is_pin_reserved(acquired_pin))
    return GPIO::mode::reserved;

  auto &status = get_status_register(acquired_pin);
  auto &pad = get_pad_register(acquired_pin);

  const bool input_enabled = pad.IE == reg::state::set;

  const bool pad_enabled = pad.OD == reg::state::cleared;
  const bool to_pad_enabled = status.OETOPAD == reg::state::set;
  const bool SIO_out_enabled = SIO::get().get_pin_OE(acquired_pin).value() == reg::state::enabled;
  const bool all_out_enabled = pad_enabled && to_pad_enabled && SIO_out_enabled;

  if (input_enabled && all_out_enabled)
    return GPIO::mode::input_and_output;
  if (input_enabled)
    return GPIO::mode::input_only;
  if (all_out_enabled)
    return GPIO::mode::output_only;
  return GPIO::mode::disabled;
}

std::error_code GPIO::set_pin_state(GPIO::state state) {
  if (is_pin_reserved(acquired_pin))
    return std::make_error_code(std::errc::operation_not_permitted);

  const auto mode = get_pin_mode();
  if (mode == GPIO::mode::input_only || mode == GPIO::mode::disabled)
    return std::make_error_code(std::errc::operation_not_permitted);

  auto &ctrl_reg = get_control_register(acquired_pin);

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

GPIO::state GPIO::get_pin_state() {
  const auto &reg = get_status_register(acquired_pin);
  return reg.OUTTOPAD == reg::state::set ? GPIO::state::high : GPIO::state::low;
}