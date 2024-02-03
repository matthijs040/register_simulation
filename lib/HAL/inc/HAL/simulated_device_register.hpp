#pragma once

#include "device_register.hpp"

#include <bit>
#include <functional>
#include <iostream>
#include <map>

template <typename field_type, typename storage_type>
class simulated_device_register {
public:
  simulated_device_register() {}

  simulated_device_register(storage_type initial_value)
      : value(initial_value) {}
  // ---------------- Accessors ----------------

  operator storage_type() const {
    // Perform a copy before a potential read handler is called.
    // Read handlers can mutate the (to be) observed memory.
    auto ret = value;
    on_read();
    return ret;
  }

  void operator=(const storage_type &v) {
    on_read();
    const auto old_value = value;
    value = v;
    on_write(old_value);
  }

  // ---------------- Effect handler coupling ----------------
  inline void on_read() const {
    if (auto func = get_read_handler(this))
      func(value);
  }

  inline void on_write(storage_type before_write) const {
    if (auto func = get_write_handler(this))
      func(before_write, value);
  }

  // ---------------- Effect handler logic ----------------

  using read_handler = std::function<void(const field_type &)>;
  using write_handler = std::function<void(field_type, const field_type &)>;
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

  using stored_type = storage_type;
  using stored_bits = field_type;

private:
  stored_type value;
  friend effect_handlers;
};
