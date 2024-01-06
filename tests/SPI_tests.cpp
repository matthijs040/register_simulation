#include <HAL/GPIO.hpp>
#include <gtest/gtest.h>
#include <rp2040/SPI/SPI_handle.hpp>
#include <rp2040/SPI/SPI_peripheral.hpp>

TEST(SPI_tests, SPI_can_construct) {
  auto periph = SPI_peripheral::get(SPI_peripheral::ID::first);
  auto handle = rp2040_SPI({}, {});
}