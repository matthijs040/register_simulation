#pragma once

#include "device_register.hpp"

#include <bit>
#include <functional>
#include <iostream>
#include <map>

template <class Underlying> class simulated_device_register {
public:
  simulated_device_register() {}

  simulated_device_register(Underlying initial_value) : value(initial_value) {}
  // ---------------- Accessors ----------------

  operator register_integral() const {
    // Perform a copy before a potential read handler is called.
    // Read handlers can mutate the (to be) observed memory.
    auto ret = *std::bit_cast<const register_integral *>(&value);
    on_read();
    return ret;
  }

  void operator=(Underlying v) {
    on_read();
    const auto old_value = static_cast<Underlying>(value);
    value = v;
    on_write(old_value);
  }

  // ---------------- Effect handler coupling ----------------
  inline void on_read() const {
    if (auto func = get_read_handler(this))
      func(value);
  }

  inline void on_write(Underlying before_write) const {
    if (auto func = get_write_handler(this))
      func(before_write, value);
  }

  // ---------------- Effect handler logic ----------------

  using read_handler = std::function<void(const Underlying &)>;
  using write_handler = std::function<void(Underlying, const Underlying &)>;
  struct effect_handlers {
    read_handler on_read;
    write_handler on_write;
  };
  using handler_table = std::map<const void *const, effect_handlers>;

  static handler_table &register_effects() {
    static handler_table table;
    return table;
  };

  static void set_effect_handlers(const void *const to_assign,
                                  effect_handlers const effects) {
    register_effects()[to_assign] = effects;
  }

  read_handler get_read_handler(const void *register_location) const {
    if (register_effects().contains(register_location))
      if (auto func = register_effects().at(register_location).on_read)
        return func;
    return nullptr;
  }

  write_handler get_write_handler(const void *const register_location) const {
    if (register_effects().contains(register_location))
      if (auto func = register_effects().at(register_location).on_write)
        return func;
    return nullptr;
  }

private:
  Underlying value;
  friend effect_handlers;
};
