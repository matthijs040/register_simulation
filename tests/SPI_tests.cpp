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
  EXPECT_EQ(handle.initialization_result, error::standard_value::success);
  if (handle.initialization_result) {
    std::printf("Default SPI initialization failed with error: '%s'\n", handle.initialization_result.message());
  }
}