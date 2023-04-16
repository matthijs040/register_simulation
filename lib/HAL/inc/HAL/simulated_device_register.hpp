#pragma once

#include "device_register.hpp"
#include <any>
#include <functional>
#include <map>

template <class Underlying> class simulated_device_register {
public:
  simulated_device_register(register_integral initial_value = 0)
      : value(initial_value) {}
  // ---------------- Accessors ----------------

  operator register_integral() const {
    on_read();
    return static_cast<register_integral>(value);
  }

  void operator=(register_integral v) {
    on_read();
    const auto old_value = value;
    static_cast<Underlying>(value) = v;
    on_write(old_value);
  }

  // ---------------- Effect handler coupling ----------------
  inline void on_read() const {
    const auto& read_value = *reinterpret_cast<const Underlying *>(this);
    if (auto func = get_read_handler(&read_value))
      func(read_value);
  }

  inline void on_write(Underlying before_write) const {
    const auto& after_write = *reinterpret_cast<const Underlying *>(this);
    if (auto func = get_write_handler(&after_write))
      func(before_write, after_write);
  }

  // ---------------- Effect handler logic ----------------

  using read_handler = std::function<void(const Underlying &)>;
  using write_handler = std::function<void(Underlying, const Underlying &)>;
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

  read_handler get_read_handler(const Underlying *register_location) const {
    if (register_effects.contains(register_location))
      if (auto func = register_effects.at(register_location).on_read)
        return func;
    return nullptr;
  }

  write_handler get_write_handler(const Underlying *const register_location) const {
    if (register_effects.contains(register_location))
      if (auto func = register_effects.at(register_location).on_write)
        return func;
    return nullptr;
  }

private:
  register_integral value;
  friend effect_handlers;
};
