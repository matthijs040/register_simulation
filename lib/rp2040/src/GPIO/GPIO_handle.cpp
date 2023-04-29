#include <HAL/GPIO.hpp>
#include <rp2040/GPIO/GPIO_handle.hpp>
#include <rp2040/GPIO/GPIO.hpp>
#include <rp2040/GPIO/user_IO.hpp>

#include <iostream>
#include <new>
#include <typeinfo>


reg::state get_peripheral_pin_state(GPIO::pin_number,
                                    reg::CTRL::FUNCSEL_states function) {
  if (function == reg::CTRL::FUNCSEL_states::disabled)
    return reg::state::disabled;

  // TODO! implement.
  // Once additional peripheral interfaces are implemented. Make this function
  // access an internal function on that interface that checks a pin-state it
  // uses by pin-number.
  return reg::state::disabled;
}

reg::state is_peripheral_enabled(GPIO::pin_number,
                                 reg::CTRL::FUNCSEL_states function) {
  if (function == reg::CTRL::FUNCSEL_states::disabled)
    return reg::state::disabled;

  // TODO! implement.
  // Have to find the peripheral block with the given pin and check an
  // is-enabled-register/bitstate.
  return reg::state::disabled;
}

void init_FUNCSEL_handlers(GPIO::pin_number pin, reg::CTRL &ctrl, reg::STATUS &,
                           std::ostream &logging_handle) {
  using FUNCSEL = decltype(reg::CTRL::FUNCSEL);
  auto FUNCSEL_handlers = FUNCSEL::sim_storage::effect_handlers();
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
  FUNCSEL::sim_storage::set_effect_handlers(&ctrl, FUNCSEL_handlers);
}

void init_OEOVER_handlers(GPIO::pin_number pin, reg::CTRL &ctrl,
                          reg::STATUS &status, std::ostream &logging_handle) {
  using OEOVER = decltype(reg::CTRL::OEOVER);
  auto OEOVER_handlers = OEOVER::sim_storage::effect_handlers();
  OEOVER_handlers.on_read = [pin, &logging_handle](
                                const OEOVER::stored_bits &read_value) {
    logging_handle << "OEOVER for pin: " << pin << " at: " << &read_value
                   << " was read as: "
                   << std::to_underlying<reg::CTRL::OEOVER_states>(read_value)
                   << ".\n";
  };

  OEOVER_handlers.on_write = [pin, &status, &ctrl, &logging_handle](
                                 OEOVER::stored_bits before,
                                 const OEOVER::stored_bits &after) mutable {
    logging_handle << "OEOVER for pin: " << pin << " at: " << &after
                   << " was set to: "
                   << std::to_underlying<reg::CTRL::OEOVER_states>(after)
                   << ".\n";
    if (before != after) {
      auto peripheral_enabled = is_peripheral_enabled(pin, ctrl.FUNCSEL);
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
    }
  };
  OEOVER::storage_type::set_effect_handlers(&ctrl, OEOVER_handlers);
}

void init_OUTOVER_handlers(GPIO::pin_number pin, reg::CTRL &ctrl,
                           reg::STATUS &status, std::ostream &logging_handle) {
  using OUTOVER = decltype(reg::CTRL::OUTOVER);
  auto OUTOVER_handlers = OUTOVER::sim_storage::effect_handlers();

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
      status.OUTTOPAD = get_peripheral_pin_state(pin, ctrl.FUNCSEL);
      break;
    case reg::CTRL::OUTOVER_states::inverse_FUNCSEL_defined:
      status.OUTTOPAD =
          get_peripheral_pin_state(pin, ctrl.FUNCSEL) == reg::state::set
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
  OUTOVER::sim_storage::set_effect_handlers(&ctrl, OUTOVER_handlers);
}

std::weak_ptr<GPIO_handle> initialize() {
  assert(USE_SIMULATED_REGISTERS);
  static std::ostream logging_handle = std::ostream(nullptr);
  logging_handle << "initialize called.\n";
  using namespace std::placeholders;

  auto handle = GPIO(); // This will allocate the pointer that
                        // we are assigning our weak ptr to.
                        // But It's fine I think.

  // Set handlers for every CTRL reg in the block.
  for (GPIO::pin_number pin = 0; pin < GPIO::get_num_pins(); pin++) {
    reg::CTRL &ctrl = get_control_register(handle, pin);
    reg::STATUS &status = get_status_register(handle, pin);

    init_FUNCSEL_handlers(pin, ctrl, status, logging_handle);
    init_OEOVER_handlers(pin, ctrl, status, logging_handle);
    init_OUTOVER_handlers(pin, ctrl, status, logging_handle);
  }

  return handle.impl_handle;
}

std::weak_ptr<GPIO_handle> GPIO_handle::handle = USE_SIMULATED_REGISTERS ? initialize() : std::weak_ptr<GPIO_handle>();

GPIO_handle::GPIO_handle()
    : gpio(std::make_shared<user_IO>()), pads(std::make_shared<pad_control>()) {
}

void *GPIO_handle::operator new(std::size_t) { return storage.data(); }

void GPIO_handle::operator delete(void *adr) {
  static_cast<GPIO_handle *>(adr)->~GPIO_handle();
  storage.fill(nullptr);
};

