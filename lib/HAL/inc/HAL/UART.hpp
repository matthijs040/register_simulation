#pragma once

#include "GPIO.hpp"
#include <expected>
#include <span>

namespace HAL {
  
class UART {
public:
  const struct pins {
    GPIO::pin_number RX;
    GPIO::pin_number TX;
  } used_pins;
  const std::size_t used_baudrate;

  const std::error_code initialization_result;

  UART(pins pins_to_use, std::size_t baudrate);
  ~UART();

  std::expected<std::size_t, std::error_code>
  send(const std::span<uint8_t> data);

  std::expected<std::size_t, std::error_code> receive(std::span<uint8_t> data);
};

} // namespace HAL
