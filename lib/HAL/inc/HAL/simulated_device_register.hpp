#pragma once

#include "device_register.hpp"
#include <any>
#include <functional>
#include <map>

template <class Underlying> class simulated_device_register {
public:
  using read_handler = std::function<void(register_integral)>;
  using write_handler =
      std::function<void(register_integral, register_integral)>;

  simulated_device_register() {}
  ~simulated_device_register() {}

  struct effect_handlers {
    read_handler on_read;
    write_handler on_write;

    // To directly write to private "value" without triggering effects.
    friend simulated_device_register;
  };

  inline register_integral simulated_device_register::value() const {
    const auto val = reinterpret_cast<const register_integral *>(this);
    return val;
  }

  inline void on_read() const {
    if (register_effects.contains(this))
      if (auto func = register_effects.at(this).on_read)
        func(value());
  }

  inline void on_write() const {
    if (register_effects.contains(this))
      if (auto func = register_effects.at(this).on_write)
        func(value());
  }

  operator register_integral() const {
    on_read(value());
    return value();
  }

  void operator=(register_integral v) {
    on_read(value());
    const auto old_value = value();
    static_cast<Underlying *>(this)->operator=(v);
    on_write(old_value, value());
  }

  void set_effect_handlers(void *to_assign, effect_handlers const &effects) {
    register_effects[to_assign] = effects;
  }

private:
  using handler_table = std::map<void *, effect_handlers>;
  static inline handler_table register_effects;
};
