#include <HAL/GPIO.hpp>
#include <HAL/UART.hpp>
#include <cstring>
#include <gtest/gtest.h>
#include <numeric>

constexpr HAL::UART::format default_format = {HAL::UART::parity::none,
                                              HAL::UART::stop_bits::one,
                                              HAL::UART::data_bits::eight};

constexpr auto default_baudrate = 9600;
constexpr auto default_pins = HAL::UART::pins{1, 0};
constexpr auto rp2040_UART_FIFO_size = 32U;

template <typename T1, typename T2, typename T3>
constexpr bool is_within(T1 val, T2 min, T3 max) {
  return val <= max && val >= min;
}

TEST(UART_tests, UART_initializes_when_given_valid_pins) {
  constexpr auto baudrate = 115200;
  constexpr auto allowed_error = 5;
  HAL::UART instance = HAL::UART(default_pins, baudrate, default_format, false);
  error::code init_result = instance.initialization_result;
  EXPECT_EQ(init_result, error::code());
  EXPECT_TRUE(is_within(instance.used_baudrate, baudrate - allowed_error,
                        baudrate + allowed_error));
}

TEST(UART_tests, UART_fails_to_initialize_given_invalid_pins) {

  constexpr auto invalid_pins = HAL::UART::pins{0, 1};

  HAL::UART instance =
      HAL::UART(invalid_pins, default_baudrate, default_format, false);
  EXPECT_EQ(instance.initialization_result,
            HAL::UART_error::code::unsupported_pin_configuration);
}

TEST(UART_tests, UART_fails_to_initialize_given_invalid_stop_bits_config) {
  constexpr HAL::UART::format invalid_stop_bits = {
      HAL::UART::parity::none, HAL::UART::stop_bits::one_and_a_half,
      HAL::UART::data_bits::eight};

  HAL::UART instance =
      HAL::UART(default_pins, default_baudrate, invalid_stop_bits, false);
  EXPECT_EQ(instance.initialization_result,
            HAL::UART_error::code::invalid_format_configuration);
}

TEST(UART_tests, UART_fails_to_initialize_given_invalid_data_bits_config) {
  constexpr HAL::UART::format invalid_data_bits = {HAL::UART::parity::none,
                                                   HAL::UART::stop_bits::one,
                                                   HAL::UART::data_bits::nine};
  HAL::UART instance =
      HAL::UART(default_pins, default_baudrate, invalid_data_bits, false);
  EXPECT_EQ(instance.initialization_result,
            HAL::UART_error::code::invalid_format_configuration);
}

TEST(UART_tests, UART_cleans_its_pin_reservations_after_destruction) {
  {
    HAL::UART stub =
        HAL::UART(default_pins, default_baudrate, default_format, false);

    // Trying to acquire a GPIO handle on the UART's receive pin should fail
    // here...
    GPIO instance = GPIO(default_pins.RX);
    EXPECT_EQ(instance.initialization_result,
              error::standard_value::device_or_resource_busy);
  }

  // ...And be valid here.
  GPIO instance = GPIO(default_pins.RX);
  EXPECT_EQ(instance.initialization_result, {});
}

TEST(UART_tests, a_transmitted_character_is_put_in_the_right_transmit_FIFO) {
  HAL::UART instance =
      HAL::UART(default_pins, default_baudrate, default_format, false);

  uint8_t data = 42;
  error::code ec;
  auto result = instance.send({&data, sizeof(data)}, ec);

  EXPECT_EQ(result, 1);
}

TEST(UART_tests, transmitting_more_than_TX_FIFO_size_bytes_returns_FIFO_size) {

  std::array<uint8_t, rp2040_UART_FIFO_size * 2> data;
  std::iota(data.begin(), data.end(), 0);

  HAL::UART instance =
      HAL::UART(default_pins, default_baudrate, default_format, false);

  error::code ec;
  auto result = instance.send(data, ec);
  EXPECT_EQ(result, rp2040_UART_FIFO_size);
}

TEST(UART_tests, single_byte_loopback_transfer_succeeds) {
  std::array<uint8_t, 1> sent_data{69U};
  HAL::UART instance =
      HAL::UART(default_pins, default_baudrate, default_format, true);
  error::code ec;

  auto result = instance.send(sent_data, ec);
  ASSERT_EQ(result, sent_data.size());

  std::array<uint8_t, rp2040_UART_FIFO_size> received_data;
  result = instance.receive(received_data, ec);
  ASSERT_EQ(result, sent_data.size());

  for (const auto &byte : sent_data)
    EXPECT_EQ(byte, received_data.at(&byte - &sent_data.front()));
}

TEST(UART_tests, multi_byte_loopback_transfer_succeeds) {
  const char *sent_data = "Hello world!";
  auto sent_data_view = std::span<const uint8_t>(
      std::bit_cast<const uint8_t *>(sent_data), std::strlen(sent_data));
  HAL::UART instance =
      HAL::UART(default_pins, default_baudrate, default_format, true);

  error::code ec;

  auto result = instance.send(sent_data_view, ec);
  ASSERT_EQ(result, sent_data_view.size());

  std::array<uint8_t, rp2040_UART_FIFO_size> received_data;
  result = instance.receive(received_data, ec);
  ASSERT_EQ(result, sent_data_view.size());

  EXPECT_EQ(std::strncmp(sent_data,
                         std::bit_cast<const char *>(received_data.data()),
                         sent_data_view.size()),
            0);
}