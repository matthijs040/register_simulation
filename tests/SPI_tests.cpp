#include <HAL/GPIO.hpp>
#include <gtest/gtest.h>
#include <rp2040/SPI/SPI_peripheral.hpp>

TEST(SPI_tests, SPI_can_construct) {
  auto handle = SPI_peripheral::get(SPI_peripheral::ID::first);
}