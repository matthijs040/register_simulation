#pragma once

#include "GPIO.hpp"
#include "system/error_code.hpp"
#include <expected>
#include <optional>
#include <span>

namespace HAL {

namespace UART_error {
enum class code {
  success = 0,
  unsupported_pin_configuration,
  unsupported_parity_configuration,
  invalid_format_configuration,
  receive_buffer_overflown,
  parity_error_in_received_data,
  format_error_in_received_data,
};

} // namespace UART_error

class UART {
public:
  const error::code initialization_result;
  const struct pins {
    GPIO::pin_number RX;
    GPIO::pin_number TX;
    std::optional<GPIO::pin_number> CTS;
    std::optional<GPIO::pin_number> RTS;
  } used_pins;
  const std::uint32_t used_baudrate;

  enum class parity { none, even, odd };
  enum class stop_bits { one, one_and_a_half, two };
  enum class data_bits { five, six, seven, eight, nine };

  const struct format {
    UART::parity used_parity;
    UART::stop_bits used_stop_bits;
    UART::data_bits used_data_bits;
  } used_format;
  const bool loopback_enabled;

  UART(pins pins_to_use, std::uint32_t baudrate, format format,
       bool enable_loopback);
  ~UART();

  std::expected<std::size_t, error::code>
  send(const std::span<const uint8_t> data);

  std::expected<std::size_t, error::code> receive(std::span<uint8_t> data);

  format get_active_format() const noexcept;
};

} // namespace HAL

namespace error {

extern code make_code(HAL::UART_error::code e) noexcept;

template <>
struct is_error_value<HAL::UART_error::code> : public std::true_type {};

} // namespace error