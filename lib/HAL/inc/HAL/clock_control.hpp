#pragma once

#include "GPIO.hpp"
#include "system/error_code.hpp"
#include <chrono>
#include <cstdint>
#include <expected>
#include <ranges>
#include <ratio>

class clock_control {
public:
  using kiloHertz = uint32_t;
  using clock_name = const char *const;

  enum class errc : int {
    success = 0,
    name_not_found,
    disabled,
    invalid_configuration,
    busy,
    invalid_pin,
  };

  static std::size_t get_num_clocks() noexcept;

  static std::span<clock_name> get_clock_names() noexcept;

  std::expected<kiloHertz, error::code> get_current_frequency() const noexcept;

  std::expected<kiloHertz, error::code>
  set_current_frequency(kiloHertz value) noexcept;

  error::code sleep_for(std::chrono::nanoseconds) const noexcept;

  const clock_name addressed_clock;
  const error::code initialization_result;

  clock_control(clock_name name);
  ~clock_control();

  /**
   * @brief If the current clock is not itself a foundational source clock.
   * e.g. It is the clock label that would provide time for a specific
   * peripheral. This function would assign the source for that peripheral.
   *
   * @param source One of the names / labels obtained from get_clock_names().
   * @return * error::code
   */
  error::code set_source(clock_name source);

  /**
   * @brief Exposes the clock signal on the given GPIO pin.
   *
   * @param pin number to expose the clock signal on.
   * @return error::code
   */
  error::code expose_signal(GPIO::pin_number pin);
};

namespace error {

extern code make_code(clock_control::errc e) noexcept;

template <>
struct is_error_value<clock_control::errc> : public std::true_type {};

} // namespace error