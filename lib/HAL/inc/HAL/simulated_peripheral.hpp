#pragma once
#include "bitfield.hpp"
#include "simulated_device_register.hpp"
#include <array>
#include <type_traits>

template <class Peripheral> class simulated_peripheral {
public:
  void *operator new(std::size_t) {
    for (auto i = 0; i < simulated_register_storage.size(); i++)
      set_effect_handlers(&simulated_register_storage.at(i), register_effects_storage.at(i));
    return base_address;
  }

  void operator delete(void *addr) {
    static_cast<Peripheral *>(addr)->~Peripheral();
  }

private:
  static_assert(sizeof(register_integral) ==
                sizeof(simulated_device_register<register_integral>));
  // static_assert(std::is_layout_compatible_v<register_integral,
  // simulated_device_register<register_integral>>);

  static inline const std::size_t register_count = sizeof(Peripheral) / sizeof(register_integral);
  static inline std::array<simulated_device_register<register_integral>, register_count> simulated_register_storage;
  static inline std::array<effect_handlers, register_count> register_effects_storage;
  static inline constexpr auto base_address = simulated_register_storage.data();
};
