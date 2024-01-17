#include <HAL/GPIO.hpp>
#include <cstdio>
#include <gtest/gtest.h>
#include <rp2040/SPI/SPI_handle.hpp>
#include <rp2040/SPI/SPI_peripheral.hpp>

#include <cstring>

constexpr SPI::pins default_pins = SPI::pins{0, 3, 1, 2};

TEST(SPI_tests, SPI_handle_with_valid_configuration_will_initialize) {
  auto periph = SPI_peripheral::get(SPI_peripheral::ID::first);
  auto handle =
      rp2040_SPI(default_pins, SPI::mode::Motorola, SPI::role::main, true);
  ASSERT_EQ(handle.initialization_result, error::standard_value::success);
}

TEST(SPI_tests, SPI_handle_with_invalid_pins_will_error) {
  auto periph = SPI_peripheral::get(SPI_peripheral::ID::first);
  // The pins here are invalid as the TX and RX pins are swapped.
  const auto invalid_pins = SPI::pins{3, 0, 1, 2};

  auto handle =
      rp2040_SPI(invalid_pins, SPI::mode::Motorola, SPI::role::main, true);
  ASSERT_EQ(handle.initialization_result,
            error::standard_value::invalid_argument);
}

TEST(SPI_tests, SPI_handle_will_not_initialize_if_already_active) {
  auto periph = SPI_peripheral::get(SPI_peripheral::ID::first);

  auto first_handle =
      rp2040_SPI(default_pins, SPI::mode::Motorola, SPI::role::main, true);
  ASSERT_EQ(first_handle.initialization_result, error::standard_value::success);

  auto second_handle =
      rp2040_SPI(default_pins, SPI::mode::Motorola, SPI::role::main, true);
  ASSERT_EQ(second_handle.initialization_result,
            error::standard_value::resource_unavailable_try_again);
}

TEST(SPI_tests, SPI_handle_can_initialize_two_seperate_handles) {
  constexpr auto SPI1_pins = default_pins;
  auto first_handle =
      rp2040_SPI(SPI1_pins, SPI::mode::Motorola, SPI::role::main, true);
  ASSERT_EQ(first_handle.initialization_result, error::standard_value::success);

  constexpr auto SPI2_pins = SPI::pins{8, 11, 9, 10};
  auto second_handle =
      rp2040_SPI(SPI2_pins, SPI::mode::Motorola, SPI::role::main, true);
  ASSERT_EQ(second_handle.initialization_result,
            error::standard_value::success);
}

TEST(SPI_tests, SPI_handle_clears_resources_and_reinitializes) {
  {
    auto handle =
        rp2040_SPI(default_pins, SPI::mode::Motorola, SPI::role::main, true);
  }
  auto handle =
      rp2040_SPI(default_pins, SPI::mode::Motorola, SPI::role::main, true);
  ASSERT_EQ(handle.initialization_result, error::standard_value::success);
}

template <typename T>
concept character_type = requires(T a) {
  { std::is_integral_v<T>() };
};

template <character_type T> std::size_t string_length(const T *data) {
  std::size_t index = 0;
  if (!data)
    return index;

  while (data[index] != 0)
    index++;

  return index;
}

TEST(SPI_tests, loopback_transfer_succeeds) {
  auto handle =
      rp2040_SPI(default_pins, SPI::mode::Motorola, SPI::role::main, true);

  const char *data = "Hello world!";
  const auto str_len = std::strlen(data);
  auto string_view =
      std::span<const uint8_t>(std::bit_cast<const uint8_t *>(data), str_len);
  auto transmit_result = handle.send(string_view);
  ASSERT_EQ(transmit_result, error::standard_value::success);
  ASSERT_EQ(*(string_view.data()), *(string_view.end()));

  constexpr int8_t val = -1;
  static_assert(std::bit_cast<const uint8_t>(val) == uint8_t{UINT8_MAX});
}
