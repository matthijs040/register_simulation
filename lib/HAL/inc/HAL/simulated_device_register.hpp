#pragma once

#include "device_register.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <typeinfo>

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
    if (auto func = get_read_handler(this))
      func(reinterpret_cast<const Underlying &>(*this));
  }

  inline void on_write(Underlying before_write) const {
    if (auto func = get_write_handler(this))
      func(before_write, reinterpret_cast<const Underlying &>(*this));
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
                                  effect_handlers const &effects) {
    register_effects()[to_assign] = effects;
  }

  read_handler get_read_handler(const void *register_location) const {
    std::clog << "checking for read-handler in map: "
              << &simulated_device_register<Underlying>::register_effects()
              << " with type: "
              << typeid(
                     simulated_device_register<Underlying>::register_effects())
                     .name()
              << " at: " << register_location << '\n';
    if (register_effects().contains(register_location))
      if (auto func = register_effects().at(register_location).on_read)
        return func;
    return nullptr;
  }

  write_handler get_write_handler(const void *const register_location) const {
    std::clog << "checking for write-handler in map: " << &register_effects()
              << " with type: " << typeid(*this).name()
              << " at: " << register_location << '\n';
    if (register_effects().contains(register_location))
      if (auto func = register_effects().at(register_location).on_write)
        return func;
    return nullptr;
  }

private:
  register_integral value;
  friend effect_handlers;
};
