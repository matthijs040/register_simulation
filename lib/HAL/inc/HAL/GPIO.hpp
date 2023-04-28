#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <system_error>

class GPIO_handle;

class GPIO {
public:
  GPIO();
  ~GPIO();

  using pin_number = std::size_t;
  enum class mode {
    disabled,
    reserved,
    input_only,
    output_only,
    input_and_output
  };

  enum class state { floating, high, low };

  static std::size_t get_num_pins() noexcept;

  bool is_pin_reserved(pin_number number) const noexcept;

  std::error_code set_pin_mode(pin_number number, GPIO::mode mode);

  GPIO::mode get_pin_mode(pin_number number);

  std::error_code set_pin_state(pin_number number, GPIO::state state);

  GPIO::state get_pin_state(pin_number number);

  std::shared_ptr<GPIO_handle> impl_handle;
};
