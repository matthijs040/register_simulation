#include <HAL/UART.hpp>
#include <gtest/gtest.h>

template <typename T1, typename T2, typename T3>
constexpr bool is_within(T1 val, T2 min, T3 max) {
  return val <= max && val >= min;
}

TEST(UART_tests, UART_initializes_when_given_valid_pins) {
  constexpr auto baudrate = 115200;
  constexpr auto allowed_error = 5;
  HAL::UART instance = HAL::UART(HAL::UART::pins{1, 0}, baudrate);
  std::error_code init_result = instance.initialization_result;
  EXPECT_EQ(init_result, std::error_code());
  EXPECT_TRUE(is_within(instance.used_baudrate, baudrate - allowed_error,
                        baudrate + allowed_error));
}

TEST(UART_tests, UART_fails_to_initialize_given_invalid_pins) {
  HAL::UART instance = HAL::UART(HAL::UART::pins{0, 1}, 9600);
  EXPECT_EQ(instance.initialization_result, std::errc::invalid_argument);
}