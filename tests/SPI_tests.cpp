#include <HAL/GPIO.hpp>
#include <cstdio>
#include <gtest/gtest.h>
#include <rp2040/SPI/SPI_handle.hpp>
#include <rp2040/SPI/SPI_peripheral.hpp>

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
