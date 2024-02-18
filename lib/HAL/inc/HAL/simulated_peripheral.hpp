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

    char debug_message[150];
    std::snprintf(debug_message, sizeof(debug_message),
                  "Invalid pointer given for periph type: '%s'",
                  typeid(Peripheral).name());
    const auto periph_min_address = static_cast<void *>(base_address);
    const auto periph_size = simulated_register_storage.size();
    const auto periph_max_address =
        static_cast<void *>(base_address + periph_size);
    const auto *field_storage_address = &field_address;
    assert(debug_message && field_storage_address >= periph_min_address &&
           field_storage_address < periph_max_address);

    const off_t offset =
        std::bit_cast<const reg::register_integral *>(&field_address) -
        std::bit_cast<const reg::register_integral *>(base_address);
    auto &field = simulated_register_storage.at(offset);

    using stored_bits = Bitfield::stored_type::field_type;
    auto *sub_field = std::bit_cast<stored_bits *>(&field);
    return *sub_field;
  }

private:
  enum class stub : reg::register_integral {};
  static_assert(num_peripherals > 0);
  static_assert(sizeof(reg::register_integral) ==
                sizeof(bitfield<stub, 2, 2, reg::register_integral>));

  static inline const std::size_t register_count =
      sizeof(Peripheral) / sizeof(reg::register_integral) * num_peripherals;
  static inline std::array<reg::register_integral, register_count>
      simulated_register_storage;
  static inline constexpr auto base_address = simulated_register_storage.data();
};
