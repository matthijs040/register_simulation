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

  UART(pins pins_to_use, std::uint32_t baudrate);
  ~UART();

  std::expected<std::size_t, std::error_code>
  send(const std::span<uint8_t> data);

  std::expected<std::size_t, std::error_code> receive(std::span<uint8_t> data);
};

} // namespace HAL
