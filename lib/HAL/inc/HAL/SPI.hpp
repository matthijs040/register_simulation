#pragma once

#include "system/error_code.hpp"
#include <HAL/GPIO.hpp>
#include <span>

namespace SPI {

struct pins {
  GPIO::pin_number receive_pin;
  GPIO::pin_number transmit_pin;
  GPIO::pin_number chip_select_pin;
  GPIO::pin_number clock_pin;
};

enum class mode { Motorola, TI_synchronous, Microwire };

enum class role { main, sub };

enum class error_code {
  success = 0,
  transmit_buffer_full,
};

using bitrate = uint32_t;

template <typename Impl> class handle {
public:
  const error::code initialization_result;
  const SPI::pins used_pins;
  const SPI::mode used_mode;
  const SPI::role used_role;
  const SPI::bitrate used_bitrate;
  const bool loopback_enabled;

  handle(error::code initialization_result, SPI::pins pins_to_use,
         SPI::mode mode_to_use, SPI::role role_to_have,
         SPI::bitrate bitrate_to_use, bool enable_loopback)
      : initialization_result(initialization_result), used_pins(pins_to_use),
        used_mode(mode_to_use), used_role(role_to_have),
        used_bitrate(bitrate_to_use), loopback_enabled(enable_loopback) {}

  ~handle() = default;

  error::code send(std::span<const uint8_t> &bytes_to_transfer) {
    if (initialization_result)
      return initialization_result;
    return static_cast<Impl &>(*this).send(bytes_to_transfer);
  }

  error::code receive(std::span<uint8_t> &bytes_read) {
    if (initialization_result)
      return initialization_result;
    return static_cast<Impl &>(*this).receive(bytes_read);
  }
};
} // namespace SPI

namespace error {

template <> inline code make_code<SPI::error_code>(SPI::error_code e) noexcept {
  static struct : public category {
    constexpr virtual const char *name() const noexcept override {
      return "SPI";
    }
    constexpr virtual const char *message(int code) const noexcept override {
      switch (static_cast<SPI::error_code>(code)) {
      case SPI::error_code::success:
        return "Success";
      case SPI::error_code::transmit_buffer_full:
        return "Transmit buffer full";
      }
      return "Unknown";
    }
  } instance;

  return error::code(std::to_underlying(e), instance);
}

template <> struct is_error_value<SPI::error_code> : public std::true_type {};

} // namespace error