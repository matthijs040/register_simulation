#pragma once

#include <bit>
#include <functional>
#include <iostream>
#include <map>

template <typename field_type_, typename stored_type_, bool enable_handlers>
class simulated_device_register {
public:
  using field_type = field_type_;
  using stored_type = stored_type_;

  simulated_device_register() {}

  simulated_device_register(stored_type initial_value) : value(initial_value) {}
  // ---------------- Accessors ----------------

  operator stored_type() const {
    if constexpr (enable_handlers)
      on_read();
    return value;
  }

  template <typename T> void assign_as(const T &v, std::size_t shift) {
    const auto old_value = value;
    *(std::bit_cast<T *>(&value) + shift) = v;
    if constexpr (enable_handlers)
      on_write(old_value);
  }

  void operator=(const stored_type &v) {
    const auto old_value = value;
    value = v;
    if constexpr (enable_handlers)
      on_write(old_value);
  }

  // ---------------- Effect handler logic ----------------

  using read_handler = std::function<void(const field_type &)>;
  using write_handler = std::function<void(field_type, const field_type &)>;
  struct effect_handlers {
    read_handler on_read;
    write_handler on_write;
  };
  using handler_table = std::map<const void *const, effect_handlers>;

  static void set_effect_handlers(const void *const to_assign,
                                  effect_handlers const effects) {
    if constexpr (enable_handlers)
      register_effects()[to_assign] = effects;
  }

private:
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

  // ---------------- Effect handler coupling ----------------
  inline void on_read() const {
    if (auto func = get_read_handler(this))
      func(value);
  }

  inline void on_write(stored_type before_write) const {
    if (auto func = get_write_handler(this))
      func(before_write, value);
  }

  static handler_table &register_effects() {
    static handler_table table;
    return table;
  };

  stored_type value;
  friend effect_handlers;
};
