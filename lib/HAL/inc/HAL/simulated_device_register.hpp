#pragma once

#include "device_register.hpp"
#include <any>
#include <functional>
#include <map>

using read_handler = std::function<void(register_integral)>;
using write_handler = std::function<void(register_integral, register_integral)>;

struct effect_handlers {
  read_handler on_read;
  write_handler on_write;
};

extern void set_effect_handlers(const void *const to_assign,
                                effect_handlers const &effects);
extern read_handler get_read_handler(const void *const register_location);
extern write_handler get_write_handler(const void *const register_location);

template <class Underlying> class simulated_device_register {
public:
  simulated_device_register() {}
  ~simulated_device_register() {}

  inline void on_read(register_integral read_value) const {
    if (auto func = get_read_handler(this))
      func(read_value);
  }

  inline void on_write(register_integral before_write,
                       register_integral after_write) const {
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

private:
  register_integral value;
  friend effect_handlers;
};
