#include <HAL/simulated_device_register.hpp>

using handler_table = std::map<const void *const, effect_handlers>;
static handler_table register_effects = handler_table();

void set_effect_handlersset_effect_handlers(const void *const to_assign,
                                            effect_handlers const &effects) {
  register_effects[to_assign] = effects;
}

read_handler get_read_handler(const void *const register_location) {
  if (register_effects.contains(register_location))
    if (auto func = register_effects.at(register_location).on_read)
      return func;
  return nullptr;
}

write_handler get_write_handler(const void *const register_location) {
  if (register_effects.contains(register_location))
    if (auto func = register_effects.at(register_location).on_write)
      return func;
  return nullptr;
}
