#pragma once

#include "device_register.hpp"
#include <any>
#include <functional>
#include <map>

template <class Underlying> class simulated_device_register {
public:
  simulated_device_register() {}
  ~simulated_device_register() {}

  inline void on_read(Underlying &read_value) const {
    if (auto func = get_read_handler(this))
      func(read_value);
  }

  inline void on_write(Underlying before_write, Underlying &after_write) const {
    if (auto func = get_write_handler(this))
      func(before_write, after_write);
  }

  operator register_integral() const {
    on_read(value);
    return value;
  }

  void operator=(register_integral v) {
    on_read(value);
    const auto old_value = value;
    static_cast<Underlying *>(this)->operator=(v);
    on_write(old_value, value);
  }

  using read_handler = std::function<void(Underlying &)>;
  using write_handler = std::function<void(Underlying, Underlying &)>;
  struct effect_handlers {
    read_handler on_read;
    write_handler on_write;
  };
  using handler_table = std::map<const void *const, effect_handlers>;
  static inline handler_table register_effects;

  static void set_effect_handlers(const Underlying *const to_assign,
                                  effect_handlers const &effects) {
    register_effects[to_assign] = effects;
  }

  read_handler get_read_handler(const Underlying *const register_location) {
    if (register_effects.contains(register_location))
      if (auto func = register_effects.at(register_location).on_read)
        return func;
    return nullptr;
  }

  write_handler get_write_handler(const Underlying *const register_location) {
    if (register_effects.contains(register_location))
      if (auto func = register_effects.at(register_location).on_write)
        return func;
    return nullptr;
  }

private:
  Underlying value;
  friend effect_handlers;
};
