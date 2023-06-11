#pragma once

#include <chrono>
#include <cstdint>
#include <ranges>
#include <ratio>
#include <system_error>

class clock_control {
public:
  using kiloHertz = unsigned long long;
  using clock_name = const char *const;

  static std::size_t get_num_clocks() noexcept;

  static std::span<clock_name> get_clock_names() noexcept;

  std::error_code get_current_frequency(kiloHertz &value) const noexcept;

  std::error_code set_current_frequency(kiloHertz value) noexcept;

  std::error_code sleep_for(std::chrono::nanoseconds) const noexcept;

  const clock_name addressed_clock;
  const std::error_code initialization_result;

  clock_control(clock_name name);
  ~clock_control();
};