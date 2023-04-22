#include <HAL/GPIO.hpp>
#include <rp2040/GPIO/GPIO.hpp>
#include <rp2040/GPIO/user_IO.hpp>

#include <iostream>
#include <new>
#include <typeinfo>

using FUNCSEL_bits = decltype(reg::CTRL::FUNCSEL)::storage_type;

std::weak_ptr<user_IO> initialize() {
  std::clog.rdbuf(nullptr);
  std::clog << "initialize called.\n";
  using namespace std::placeholders;

  auto handle = std::make_shared<GPIO>(); // This will allocate the pointer that
                                          // we are assigning our weak ptr to.
                                          // But It's fine I think.

  // Set handlers for every CTRL reg in the block.
  for (GPIO::pin_number pin = 0; pin < GPIO::get_num_pins(); pin++) {
    reg::CTRL &ctrl = get_control_register(*handle, pin);

    auto handlers = FUNCSEL_bits::effect_handlers();
    handlers.on_read = [](auto read_value) { std::cout << "CTRL register is read from.\n";};
    handlers.on_write = [](auto , const auto&) { std::cout << "CTRL reg written to.\n"; };
    FUNCSEL_bits::set_effect_handlers(&ctrl, handlers);
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