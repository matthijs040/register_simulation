#pragma once

#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <type_traits>

constexpr std::size_t min_instances = 1;
template <class peripheral_type, bool enable_storage,
          size_t num_peripherals = min_instances>
class simulatable_peripheral {
public:
  static constexpr peripheral_type &get(std::size_t which = 0) noexcept {
    assert(which < num_peripherals);

    peripheral_type *&handle = get_handles().at(which);
    if (handle)
      return *handle;
    handle = new (get_storage_ptr(which)) peripheral_type;

    if constexpr (enable_storage)
      static_cast<peripheral_type *>(handle)->initialize_effect_handlers(which);

    return *handle;
  }

  ~simulatable_peripheral() {}

protected:
  simulatable_peripheral() {}

  template <typename field_type>
  constexpr auto &acquire_field(const field_type &given_field) {

    static_assert(sizeof(field_type) <= sizeof(std::uintptr_t));
    const std::uintptr_t field_addr =
        std::bit_cast<const std::uintptr_t>(&given_field);
    auto &field_storage = get_storage();
    const std::uintptr_t begin =
        std::bit_cast<const std::uintptr_t>(field_storage.data());
    const std::uintptr_t end =
        std::bit_cast<const std::uintptr_t>(begin + field_storage.size());
    assert(field_addr >= begin && field_addr < end);

    const off_t field_offset = field_addr - begin;

    // This conversion is made to ensure reads or writes on the acquired field
    // do not trigger effect handlers.
    using stored_bits = field_type::stored_type::field_type;
    return *std::bit_cast<stored_bits *>(begin + field_offset);
  }

  static peripheral_type &reset_instance(std::size_t which) {
    peripheral_type *&handle = get_handles().at(which);

    // In case first-time initialization is done through a "reset"-call...
    if (!handle) {
      handle = new (get_storage_ptr(which)) peripheral_type;

      // ...we only have to construct and ensure that initialize_effect_handlers is called.
      if constexpr (enable_storage)
        static_cast<peripheral_type *>(handle)->initialize_effect_handlers(
            which);
      return *handle;
    }

    // In the regular case. We just de- and re-construct.
    handle->~peripheral_type();
    handle = new (get_storage_ptr(which)) peripheral_type;
    return *handle;
  }

private:
  static constexpr auto &get_handles() {
    static std::array<peripheral_type *, num_peripherals> handles;
    return handles;
  }

  static constexpr auto &get_storage() {
    static std::array<std::byte, sizeof(peripheral_type) * num_peripherals>
        storage;
    return storage;
  }

  static constexpr auto get_storage_ptr(std::size_t which) {
    if constexpr (enable_storage)
      return get_storage().data() + (which * sizeof(peripheral_type));
    else {

      static_assert(peripheral_type::base_addresses.size() == num_peripherals,
                    "Every peripheral requires a base-address.");

      const std::uintptr_t physical_address =
          peripheral_type::base_addresses.at(which);
      return std::bit_cast<void *>(physical_address);
    }
  }
};