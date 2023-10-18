#pragma once

#include <chrono>
#include <cstdint>
#include <ranges>
#include <ratio>
#include <system_error>
#include <expected>
#include "GPIO.hpp"

namespace clock_error
{
  enum class code
  {
    success = 0,
    name_not_found,
    disabled,
    invalid_configuration,
    busy,
    invalid_pin,
  };

  std::error_code make_error_code(clock_error::code e) noexcept;
}

class clock_control
{
public:
  using kiloHertz = uint32_t;
  using clock_name = const char *const;

  static std::size_t get_num_clocks() noexcept;

  static std::span<clock_name> get_clock_names() noexcept;

  std::expected<kiloHertz, std::error_code> get_current_frequency() const noexcept;

  std::expected<kiloHertz, std::error_code> set_current_frequency(kiloHertz value) noexcept;

  std::error_code sleep_for(std::chrono::nanoseconds) const noexcept;

  const clock_name addressed_clock;
  const std::error_code initialization_result;

  clock_control(clock_name name);
  ~clock_control();

  /**
   * @brief If the current clock is not itself a foundational source clock.
   * e.g. It is the clock label that would provide time for a specific peripheral.
   * This function would assign the source for that peripheral.
   *
   * @param source One of the names / labels obtained from get_clock_names().
   * @return * std::error_code
   */
  std::error_code set_source(clock_name source);

  /**
   * @brief Exposes the clock signal on the given GPIO pin.
   *
   * @param pin number to expose the clock signal on.
   * @return std::error_code
   */
  std::error_code expose_signal(GPIO::pin_number pin);
};

namespace std
{
  template <>
  struct is_error_code_enum<clock_error::code> : true_type
  {
  };

} // namespace std
