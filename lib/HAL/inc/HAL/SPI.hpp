#pragma once

#include "system/error_code.hpp"
#include <HAL/GPIO.hpp>
#include <span>

namespace SPI {

struct pins {
  GPIO::pin_number clock_pin;
  GPIO::pin_number chip_select_pin;
  GPIO::pin_number transmit_pin;
  GPIO::pin_number receive_pin;
};

enum class mode { Motorola, TI_synchronous, Microwire };

enum class role { main, sub };

template <typename Impl> class handle {
public:
  const error::code initialization_result;
  const SPI::pins used_pins;
  const SPI::mode used_mode;
  const SPI::role used_role;
  const bool loopback_enabled;

  handle(error::code initialization_result, SPI::pins pins_to_use,
         SPI::mode mode_to_use, SPI::role role_to_have, bool enable_loopback)
      : initialization_result(initialization_result), used_pins(pins_to_use),
        used_mode(mode_to_use), used_role(role_to_have),
        loopback_enabled(enable_loopback) {}

  ~handle() = default;

  error::code send(std::span<const uint16_t> &bytes_to_transfer) {
    if (initialization_result)
      return initialization_result;
    return static_cast<Impl &>(*this).send(bytes_to_transfer);
  }

  error::code receive(std::span<uint16_t> &bytes_read) {
    if (initialization_result)
      return initialization_result;
    return static_cast<Impl &>(*this).receive(bytes_read);
  }
};
} // namespace SPI
