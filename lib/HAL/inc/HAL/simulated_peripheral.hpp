#pragma once
#include "bitfield.hpp"
#include "simulated_device_register.hpp"
#include <array>
#include <type_traits>

template <class Peripheral, std::size_t num_peripherals = 1>
struct simulated_peripheral {
  void *operator new(std::size_t, std::size_t index = 0) {
    assert(index < num_peripherals);
    return base_address + (sizeof(Peripheral) * index);
  }

  void operator delete(void *addr) {
    static_cast<Peripheral *>(addr)->~Peripheral();
  }

  enum class stub : register_integral {};
  static_assert(num_peripherals > 0);
  static_assert(sizeof(register_integral) ==
                sizeof(bitfield<stub, 2, 2, register_integral>));
  // static_assert(std::is_layout_compatible_v< register_integral,
  // simulated_device_register<register_integral>>);

  static inline const std::size_t register_count =
      sizeof(Peripheral) / sizeof(register_integral) * num_peripherals;
  static inline std::array<register_integral, register_count>
      simulated_register_storage;
  static inline constexpr auto base_address = simulated_register_storage.data();

  /**
   * @brief Wrapper function that allows type-safe access to raw
   * "register_integrals" contained in "simulated_register_storage". With the
   * returned "bitfield"-type having "uses_simulated_registers" set to false,
   * bitfield will have its reads and writes directly done to the underlying
   * integral. The remaining "bitfield"-configuration will map to the field the
   * caller has provided. Ensuring that shifting and masking is correct.
   *
   * @tparam BitField bitfield-type to convert member to.
   * @return const void* address of the field to wrap in Bitfield::stored_bits.
   */
  template <typename Bitfield>
  static inline auto &acquire_field(const Bitfield &field_address) {

    const off_t offset =
        std::bit_cast<const register_integral *>(&field_address) -
        std::bit_cast<const register_integral *>(base_address);
    auto &field = simulated_register_storage.at(offset);

    using stored_bits = Bitfield::stored_type::stored_bits;
    auto *sub_field = std::bit_cast<stored_bits *>(&field);
    return *sub_field;
  }
};
