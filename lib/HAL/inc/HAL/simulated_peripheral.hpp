#pragma once
#include <HAL/device_register.hpp>
#include <array>
#include <type_traits>

template <class Peripheral> class simulated_peripheral {
public:
  void *operator new(std::size_t) {
    for (auto i = 0; i < simulated_register_storage.size(); i++)
      simulated_device_register::set_effect_handlers(
          &simulated_register_storage.at(i), register_effects_storage.at(i));
    return simulated_register_storage.data();
  }

  void operator delete(void *addr) {
    static_cast<Peripheral *>(addr)->~Peripheral();
  }

private:
  static_assert(
      std::is_layout_compatible_v<device_register, simulated_device_register>);
  static_assert(sizeof(device_register) == sizeof(simulated_device_register));

  static const auto register_count =
      sizeof(Peripheral) / sizeof(device_register);
  static inline std::array<simulated_device_register, register_count>
      simulated_register_storage;
  static inline std::array<const simulated_device_register::effect_handlers,
                           register_count>
      register_effects_storage;
};
