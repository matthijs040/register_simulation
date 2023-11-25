#pragma once

#include "GPIO.hpp"
#include <expected>
#include <optional>
#include <span>

namespace HAL {

class UART {
public:
  const std::error_code initialization_result;
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

  UART(pins pins_to_use, std::uint32_t baudrate, format format);
  ~UART();

  std::expected<std::size_t, std::error_code>
  send(const std::span<uint8_t> data);

  std::expected<std::size_t, std::error_code> receive(std::span<uint8_t> data);

  format get_active_format() const noexcept;
};

} // namespace HAL
