#pragma once
#include "bitfield.hpp"
#include "simulated_device_register.hpp"
#include <array>
#include <type_traits>

template <class Peripheral, std::size_t num_peripherals = 1>
class simulated_peripheral {
public:
  void *operator new(std::size_t, std::size_t index = 0) {
    assert(index < num_peripherals);
    return base_address + (sizeof(Peripheral) * index);
  }

  void operator delete(void *addr) {
    static_cast<Peripheral *>(addr)->~Peripheral();
  }

  enum class stub : register_integral {};
  static_assert(num_peripherals > 0);
  static_assert(sizeof(register_integral) == sizeof(bitfield<stub, 2, 2, true>));
  // static_assert(std::is_layout_compatible_v< register_integral,
  // simulated_device_register<register_integral>>);

  static inline const std::size_t register_count =
      sizeof(Peripheral) / sizeof(register_integral) * num_peripherals;
  static inline std::array<simulated_device_register<register_integral>,
                           register_count>
      simulated_register_storage;
  static inline constexpr auto base_address = simulated_register_storage.data();
};
