#pragma once

#include <chrono>
#include <cstdint>
#include <ranges>
#include <ratio>
#include <system_error>
#include <expected>

namespace clock_error {
  enum class code {
    success = 0,
    name_not_found,
    disabled,
    invalid_configuration,
    busy
  };

  std::error_code make_error_code(clock_error::code e) noexcept;
}

class clock_control {
public:
  using kiloHertz = unsigned long long;
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
};

namespace std {
template <> struct is_error_code_enum<clock_error::code> : true_type {};

} // namespace std
