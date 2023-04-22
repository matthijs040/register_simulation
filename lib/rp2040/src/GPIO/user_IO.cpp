#include <HAL/GPIO.hpp>
#include <rp2040/GPIO/GPIO.hpp>
#include <rp2040/GPIO/user_IO.hpp>

#include <iostream>
#include <new>
#include <typeinfo>

using FUNCSEL_bits = decltype(reg::CTRL::FUNCSEL)::storage_type;

void on_CTRL_register_read(const FUNCSEL_bits &read_value) {
  std::clog << "CTRL register is read from.\n";
}

void on_CTRL_register_write(FUNCSEL_bits before_write,
                            const FUNCSEL_bits &after_write) {
  std::clog << "CTRL register is written to.\n";
}

std::weak_ptr<user_IO> initialize() {
  std::clog << "initialize called.\n";
  using namespace std::placeholders;

  auto handle = std::make_shared<GPIO>(); // This will allocate the pointer that
                                          // we are assigning our weak ptr to.
                                          // But It's fine I think.

  // Set handlers for every CTRL reg in the block.
  for (GPIO::pin_number pin = 0; pin < GPIO::get_num_pins(); pin++) {
    reg::CTRL &ctrl = get_control_register(*handle, pin);

    auto handlers = simulated_device_register<FUNCSEL_bits>::effect_handlers();
    handlers.on_read = std::bind(on_CTRL_register_read, _1);
    handlers.on_write = std::bind(on_CTRL_register_write, _1, _2);
    simulated_device_register<FUNCSEL_bits>::set_effect_handlers(&ctrl,
                                                                 handlers);
    std::clog << "registered handlers in map: "
              << &FUNCSEL_bits::register_effects
              << " of type: " << typeid(FUNCSEL_bits::register_effects).name() << " at: " << &ctrl
              << '\n';
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