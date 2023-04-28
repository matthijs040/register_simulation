#include <HAL/GPIO.hpp>
#include <rp2040/GPIO/GPIO.hpp>
#include <rp2040/GPIO/user_IO.hpp>

#include <iostream>
#include <new>
#include <typeinfo>

reg::state is_peripheral_enabled(GPIO::pin_number,
                                 reg::CTRL::FUNCSEL_states function) {
  if (function == reg::CTRL::FUNCSEL_states::disabled)
    return reg::state::disabled;

  // TODO! implement.
  // Have to find the peripheral block with the given pin and check an
  // is-enabled-register/bitstate.
  return reg::state::disabled;
}

using FUNCSEL = decltype(reg::CTRL::FUNCSEL);
using OEOVER = decltype(reg::CTRL::OEOVER);

std::weak_ptr<user_IO> initialize() {
  std::clog << "initialize called.\n";
  using namespace std::placeholders;

  auto handle = std::make_shared<GPIO>(); // This will allocate the pointer that
                                          // we are assigning our weak ptr to.
                                          // But It's fine I think.

  // Set handlers for every CTRL reg in the block.
  for (GPIO::pin_number pin = 0; pin < GPIO::get_num_pins(); pin++) {
    reg::CTRL &ctrl = get_control_register(*handle, pin);
    reg::STATUS &status = get_status_register(*handle, pin);

    // Setup handlers for FUNCSEL. Just for diagnostics.
    auto FUNCSEL_handlers = FUNCSEL::sim_storage::effect_handlers();
    FUNCSEL_handlers.on_read = [pin](const FUNCSEL::stored_bits &read_value) {
      std::cout << "Function of pin: " << pin << " was read as: "
                << std::to_underlying<reg::CTRL::FUNCSEL_states>(read_value)
                << "\n";
    };
    FUNCSEL_handlers.on_write = [pin](FUNCSEL::stored_bits,
                                      const FUNCSEL::stored_bits &after_write) {
      std::cout << "Function for pin: " << pin << " is set to: "
                << std::to_underlying<reg::CTRL::FUNCSEL_states>(after_write)
                << " .\n";
    };
    FUNCSEL::sim_storage::set_effect_handlers(&ctrl, FUNCSEL_handlers);

    // Setup handlers for OEOVER. These must - on write - update a status
    // register bit.
    auto OEOVER_handlers = OEOVER::sim_storage::effect_handlers();
    OEOVER_handlers.on_read = [pin](const OEOVER::stored_bits &read_value) {
      std::cout << "OEOVER for pin: " << pin << " at: " << &read_value
                << " was read as: "
                << std::to_underlying<reg::CTRL::OEOVER_states>(read_value)
                << ".\n";
    };

    OEOVER_handlers.on_write = [pin, status, ctrl](
                                   OEOVER::stored_bits before,
                                   const OEOVER::stored_bits &after) mutable {
      std::cout << "OEOVER was set to: "
                << std::to_underlying<reg::CTRL::OEOVER_states>(after) << ".\n";
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
          std::clog << "set &STATUS " << &status << " to enabled.\n";
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

  return std::weak_ptr<user_IO>();
}

std::weak_ptr<user_IO> user_IO::storage_handle =
    USE_SIMULATED_REGISTERS ? initialize() : std::weak_ptr<user_IO>();

user_IO::user_IO() {
  // TODO: reset registers to enabled but cleared state.
}

user_IO::~user_IO() {
  // TODO: Set gpio to lowest power state.
}