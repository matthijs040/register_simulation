#include <rp2040/GPIO/GPIO.hpp>
#include <rp2040/GPIO/SIO.hpp>
#include <rp2040/GPIO/user_IO.hpp>
#include <rp2040/shared_types.hpp>

#include <bit>
#include <expected>
#include <iostream>
#include <new>
#include <typeinfo>

std::expected<reg::state, error::code>
is_peripheral_output_enabled(GPIO::pin_number pin_number,
                             reg::CTRL::FUNCSEL_states function) {
  auto result = std::expected<reg::state, error::code>();
  switch (function) {
  case reg::CTRL::FUNCSEL_states::disabled:
    result = reg::state::disabled;
    break;
  case reg::CTRL::FUNCSEL_states::SPI:
    result = std::unexpected(error::standard_value::not_supported);
    break;
  case reg::CTRL::FUNCSEL_states::UART:
    result = std::unexpected(error::standard_value::not_supported);
    break;
  case reg::CTRL::FUNCSEL_states::I2C:
    result = std::unexpected(error::standard_value::not_supported);
    break;
  case reg::CTRL::FUNCSEL_states::PWM:
    result = std::unexpected(error::standard_value::not_supported);
    break;
  case reg::CTRL::FUNCSEL_states::SIO:
    result = SIO::get().get_pin_OE(pin_number);
    break;
  case reg::CTRL::FUNCSEL_states::PIO0:
    result = std::unexpected(error::standard_value::not_supported);
    break;
  case reg::CTRL::FUNCSEL_states::PIO1:
    result = std::unexpected(error::standard_value::not_supported);
    break;
  case reg::CTRL::FUNCSEL_states::Clock_GPIO:
    result = std::unexpected(error::standard_value::not_supported);
    break;
  case reg::CTRL::FUNCSEL_states::USB:
    result = std::unexpected(error::standard_value::not_supported);
    break;
  default:
    result = std::unexpected(error::standard_value::invalid_argument);
  }
  return result;
}

void init_FUNCSEL_handlers(GPIO::pin_number pin, reg::CTRL &ctrl, reg::STATUS &,
                           std::ostream &logging_handle) {
  using FUNCSEL = decltype(reg::CTRL::FUNCSEL)::stored_type;
  auto FUNCSEL_handlers = FUNCSEL::effect_handlers();
  FUNCSEL_handlers.on_read = [pin, &logging_handle](
                                 const FUNCSEL::stored_bits &read_value) {
    logging_handle << "Function of pin: " << pin << " was read as: "
                   << std::to_underlying<reg::CTRL::FUNCSEL_states>(read_value)
                   << "\n";
  };
  FUNCSEL_handlers.on_write = [pin, &logging_handle](
                                  FUNCSEL::stored_bits,
                                  const FUNCSEL::stored_bits &after_write) {
    logging_handle << "Function for pin: " << pin << " is set to: "
                   << std::to_underlying<reg::CTRL::FUNCSEL_states>(after_write)
                   << " .\n";
  };
  FUNCSEL::set_effect_handlers(&ctrl, FUNCSEL_handlers);
}

void init_OEOVER_handlers(GPIO::pin_number pin, reg::CTRL &ctrl,
                          reg::STATUS &status, std::ostream &logging_handle) {
  using OEOVER = decltype(reg::CTRL::OEOVER)::stored_type;
  auto OEOVER_handlers = OEOVER::effect_handlers();
  OEOVER_handlers.on_read = [pin, &logging_handle](
                                const OEOVER::stored_bits &read_value) {
    logging_handle << "OEOVER for pin: " << pin << " at: " << &read_value
                   << " was read as: "
                   << std::to_underlying<reg::CTRL::OEOVER_states>(read_value)
                   << ".\n";
  };

  OEOVER_handlers.on_write = [pin, &status, &ctrl, &logging_handle](
                                 OEOVER::stored_bits,
                                 const OEOVER::stored_bits &after) mutable {
    logging_handle << "OEOVER for pin: " << pin << " at: " << &after
                   << " was set to: "
                   << std::to_underlying<reg::CTRL::OEOVER_states>(after)
                   << ".\n";

    auto peripheral_enabled =
        is_peripheral_output_enabled(pin, ctrl.FUNCSEL).value();
    switch (after) {
    case reg::CTRL::OEOVER_states::disabled:
      status.OETOPAD = reg::state::disabled;
      status.OEFROMPERI = peripheral_enabled;
      break;
    case reg::CTRL::OEOVER_states::enabled:
      status.OEFROMPERI = peripheral_enabled;
      status.OETOPAD = reg::state::enabled;
      logging_handle << "set &STATUS " << &status << " to enabled.\n";
      break;
    case reg::CTRL::OEOVER_states::FUNCSEL_defined:
      status.OEFROMPERI = peripheral_enabled;
      status.OETOPAD = peripheral_enabled;
      break;
    case reg::CTRL::OEOVER_states::inverse_FUNCSEL_defined:
      const auto inverse = peripheral_enabled == reg::state::enabled
                               ? reg::state::disabled
                               : reg::state::enabled;
      status.OEFROMPERI = inverse;
      status.OETOPAD = inverse;
      break;
    }
  };
  OEOVER::set_effect_handlers(&ctrl, OEOVER_handlers);
}

void init_OETOPAD_handlers(GPIO::pin_number pin, reg::CTRL &ctrl,
                           reg::STATUS &status, std::ostream &logging_handle) {
  using OETOPAD = decltype(status.OETOPAD)::stored_type;
  auto OETOPAD_handlers = OETOPAD::effect_handlers();
  OETOPAD_handlers.on_read = [pin, &ctrl, &status, &logging_handle](
                                 const OETOPAD::stored_bits &read_value) {
    logging_handle << "OETOPAD for pin: " << pin
                   << " was read from, yielding value: "
                   << std::to_underlying<reg::state>(read_value) << "\n";
  };
  OETOPAD_handlers.on_write =
      [pin, &logging_handle](OETOPAD::stored_bits,
                             const OETOPAD::stored_bits &after) {
        logging_handle << "OETOPAD for pin: " << pin
                       << " was written to, setting value: "
                       << std::to_underlying<reg::state>(after) << "\n";
      };
  OETOPAD::set_effect_handlers(&status, OETOPAD_handlers);
}

void init_OUTOVER_handlers(GPIO::pin_number pin, reg::CTRL &ctrl,
                           reg::STATUS &status, std::ostream &logging_handle) {
  using OUTOVER = decltype(reg::CTRL::OUTOVER)::stored_type;
  auto OUTOVER_handlers = OUTOVER::effect_handlers();

  OUTOVER_handlers.on_read = [pin, &logging_handle](
                                 const OUTOVER::stored_bits &read_value) {
    logging_handle << "OUTOVER of pin: " << pin << " was read as: "
                   << std::to_underlying<reg::CTRL::OUTOVER_states>(read_value)
                   << "\n";
  };
  OUTOVER_handlers.on_write =
      [pin, &ctrl, &status,
       &logging_handle](OUTOVER::stored_bits,
                        const OUTOVER::stored_bits &after_write) -> void {
    logging_handle << "OUTOVER for pin: " << pin << " is set to: "
                   << std::to_underlying<reg::CTRL::OUTOVER_states>(after_write)
                   << " .\n";

    switch (after_write) {
    case reg::CTRL::OUTOVER_states::FUNCSEL_defined:
      status.OUTTOPAD = is_peripheral_output_enabled(pin, ctrl.FUNCSEL).value();
      break;
    case reg::CTRL::OUTOVER_states::inverse_FUNCSEL_defined:
      status.OUTTOPAD =
          is_peripheral_output_enabled(pin, ctrl.FUNCSEL) == reg::state::set
              ? reg::state::cleared
              : reg::state::set;
      break;
    case reg::CTRL::OUTOVER_states::driven_high:
      status.OUTTOPAD = reg::state::set;
      break;
    case reg::CTRL::OUTOVER_states::driven_low:
      status.OUTTOPAD = reg::state::cleared;
      break;
    }
    return;
  };
  
  OUTOVER::set_effect_handlers(&ctrl, OUTOVER_handlers);
}

void initialize_handlers() {
  // Set handlers for every CTRL reg in the block.
  static auto logging_handle = std::ostream(nullptr);

  for (GPIO::pin_number pin = 0; pin < GPIO::get_num_pins(); pin++) {
    reg::CTRL &ctrl = get_control_register(pin);
    reg::STATUS &status = get_status_register(pin);

    init_FUNCSEL_handlers(pin, ctrl, status, logging_handle);
    init_OEOVER_handlers(pin, ctrl, status, logging_handle);
    init_OUTOVER_handlers(pin, ctrl, status, logging_handle);
    init_OETOPAD_handlers(pin, ctrl, status, logging_handle);
  }
}

user_IO::user_IO() {
  // TODO: reset registers to enabled but cleared state.
}

user_IO::~user_IO() {
  // TODO: Set gpio to lowest power state.
}

void user_IO::operator delete(void *addr) {
  static_cast<user_IO *>(addr)->~user_IO();
};

void *user_IO::operator new(std::size_t size) {
  if constexpr (reg::mock)
    return simulated_peripheral<user_IO>::operator new(size);
  return std::bit_cast<user_IO *>(base_address);
}

user_IO &user_IO::get() noexcept {
  static user_IO *handle;
  if (handle)
    return *handle;
  handle = new user_IO();

  if constexpr (reg::mock)
    initialize_handlers();

  return *handle;
}