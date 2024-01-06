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

template <typename Impl> class handle {
public:
  const error_code initialization_result;
  const SPI::pins used_pins;
  const SPI::mode used_mode;

  handle(error_code initialization_result, SPI::pins pins_to_use,
         SPI::mode mode_to_use)
      : initialization_result(initialization_result), used_pins(pins_to_use),
        used_mode(mode_to_use) {}

  ~handle() = default;

  error_code send(std::span<const uint16_t> &bytes_to_transfer) {
    if (initialization_result)
      return initialization_result;
    return static_cast<Impl &>(*this).send(bytes_to_transfer);
  }

  error_code receive(std::span<uint16_t> &bytes_read) {
    if (initialization_result)
      return initialization_result;
    return static_cast<Impl &>(*this).receive(bytes_read);
  }
};
} // namespace SPI
