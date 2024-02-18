#include <HAL/GPIO.hpp>
#include <cstdio>
#include <gtest/gtest.h>
#include <rp2040/SPI/SPI_handle.hpp>
#include <rp2040/SPI/SPI_peripheral.hpp>

#include <cstring>

constexpr SPI::pins default_pins = SPI::pins{0, 3, 1, 2};
constexpr auto default_bitrate = 2400;

rp2040_SPI make_handle(SPI::pins pins = default_pins,
                       SPI::mode mode = SPI::mode::Motorola,
                       SPI::role role = SPI::role::main,
                       uint32_t bitrate = default_bitrate,
                       bool enable_loopback = true) {
  return rp2040_SPI(pins, mode, role, bitrate, enable_loopback);
}

TEST(SPI_tests, SPI_handle_with_valid_configuration_will_initialize) {
  auto periph =
      SPI_peripheral::get(std::to_underlying(SPI_peripheral::ID::first));
  auto handle = make_handle();
  ASSERT_EQ(handle.initialization_result, error::standard_value::success);
}

TEST(SPI_tests, SPI_handle_with_invalid_pins_will_error) {
  auto periph =
      SPI_peripheral::get(std::to_underlying(SPI_peripheral::ID::first));
  // The pins here are invalid as the TX and RX pins are swapped.
  const auto invalid_pins = SPI::pins{3, 0, 1, 2};

  auto handle = make_handle(invalid_pins);
  ASSERT_EQ(handle.initialization_result,
            error::standard_value::invalid_argument);
}

TEST(SPI_tests, SPI_handle_will_not_initialize_if_already_active) {
  auto first_handle = make_handle();
  ASSERT_EQ(first_handle.initialization_result, error::standard_value::success);

  auto second_handle = make_handle();
  ASSERT_EQ(second_handle.initialization_result,
            error::standard_value::resource_unavailable_try_again);
}

TEST(SPI_tests, SPI_handle_can_initialize_two_seperate_handles) {
  constexpr auto SPI1_pins = default_pins;
  auto first_handle = make_handle(SPI1_pins);
  ASSERT_EQ(first_handle.initialization_result, error::standard_value::success);

  constexpr auto SPI2_pins = SPI::pins{8, 11, 9, 10};
  auto second_handle = make_handle(SPI2_pins);
  ASSERT_EQ(second_handle.initialization_result,
            error::standard_value::success);
}

TEST(SPI_tests, SPI_handle_clears_resources_and_reinitializes) {
  { auto handle = make_handle(); }
  auto handle = make_handle();
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
  auto handle = make_handle();

  const uint8_t sent_data = 42;
  auto sent_view = std::span<const uint8_t>(&sent_data, sizeof(sent_data));
  auto transmit_result = handle.send(sent_view);
  ASSERT_EQ(transmit_result, error::code());

  uint8_t received_data = 0;
  auto received_view =
      std::span<uint8_t>(&received_data, sizeof(received_data));
  auto receive_result = handle.receive(received_view);
  EXPECT_EQ(transmit_result, error::code());
  EXPECT_EQ(sent_data, received_data);
}
