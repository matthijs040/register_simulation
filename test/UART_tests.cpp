#include <HAL/GPIO.hpp>
#include <HAL/UART.hpp>
#include <gtest/gtest.h>

constexpr HAL::UART::format default_format = {HAL::UART::parity::none,
                                              HAL::UART::stop_bits::one,
                                              HAL::UART::data_bits::eight};

constexpr auto default_baudrate = 9600;
constexpr auto default_pins = HAL::UART::pins{1, 0};

template <typename T1, typename T2, typename T3>
constexpr bool is_within(T1 val, T2 min, T3 max) {
  return val <= max && val >= min;
}

TEST(UART_tests, UART_initializes_when_given_valid_pins) {
  constexpr auto baudrate = 115200;
  constexpr auto allowed_error = 5;
  HAL::UART instance = HAL::UART(default_pins, baudrate, default_format);
  std::error_code init_result = instance.initialization_result;
  EXPECT_EQ(init_result, std::error_code());
  EXPECT_TRUE(is_within(instance.used_baudrate, baudrate - allowed_error,
                        baudrate + allowed_error));
}

TEST(UART_tests, UART_fails_to_initialize_given_invalid_pins) {

  constexpr auto invalid_pins = HAL::UART::pins{0, 1};

  HAL::UART instance =
      HAL::UART(invalid_pins, default_baudrate, default_format);
  EXPECT_EQ(instance.initialization_result,
            HAL::UART_error::code::unsupported_pin_configuration);
}

TEST(UART_tests, UART_fails_to_initialize_given_invalid_stop_bits_config) {
  constexpr HAL::UART::format invalid_stop_bits = {
      HAL::UART::parity::none, HAL::UART::stop_bits::one_and_a_half,
      HAL::UART::data_bits::eight};

  HAL::UART instance =
      HAL::UART(default_pins, default_baudrate, invalid_stop_bits);
  EXPECT_EQ(instance.initialization_result,
            HAL::UART_error::code::invalid_format_configuration);
}

TEST(UART_tests, UART_fails_to_initialize_given_invalid_data_bits_config) {
  constexpr HAL::UART::format invalid_data_bits = {HAL::UART::parity::none,
                                                   HAL::UART::stop_bits::one,
                                                   HAL::UART::data_bits::nine};
  HAL::UART instance =
      HAL::UART(default_pins, default_baudrate, invalid_data_bits);
  EXPECT_EQ(instance.initialization_result,
            HAL::UART_error::code::invalid_format_configuration);
}

TEST(UART_tests, UART_cleans_its_pin_reservations_after_destruction) {
  {
    HAL::UART stub = HAL::UART(default_pins, default_baudrate, default_format);

    // Trying to acquire a GPIO handle on the UART's receive pin should fail
    // here...
    GPIO instance = GPIO(default_pins.RX);
    EXPECT_EQ(instance.initialization_result,
              std::errc::device_or_resource_busy);
  }

  // ...And be valid here.
  GPIO instance = GPIO(default_pins.RX);
  EXPECT_EQ(instance.initialization_result, std::error_code());
}

TEST(UART_tests, a_transmitted_character_is_put_in_the_right_transmit_FIFO) {
  HAL::UART instance =
      HAL::UART(default_pins, default_baudrate, default_format);

  uint8_t data = 42;
  auto result = instance.send({&data, sizeof(data)});

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 1);
}

TEST(UART_tests, transmitting_more_than_TX_FIFO_size_bytes_returns_FIFO_size) {
  constexpr auto TX_FIFO_size = 32U;
  std::array<uint8_t, TX_FIFO_size + 1> data;

  HAL::UART instance =
      HAL::UART(default_pins, default_baudrate, default_format);

  auto result = instance.send(data);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), TX_FIFO_size);
}