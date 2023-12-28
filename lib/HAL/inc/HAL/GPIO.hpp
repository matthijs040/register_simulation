#pragma once

#include <array>
#include <cstdint>
#include "system/error_code.hpp"

class GPIO {
public:
  enum class state { floating, high, low };

  enum class mode {
    disabled,
    reserved,
    input_only,
    output_only,
    input_and_output
  };

  using pin_number = std::size_t;

  const pin_number acquired_pin;
  const error_code initialization_result;

  GPIO(const pin_number pin);

  ~GPIO();

  static std::size_t get_num_pins() noexcept;

  static bool is_pin_reserved(pin_number number) noexcept;

  error_code set_pin_mode(GPIO::mode mode);

  GPIO::mode get_pin_mode();

  error_code set_pin_state(GPIO::state state);

  GPIO::state get_pin_state();
};
