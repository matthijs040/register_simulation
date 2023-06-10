#pragma once

#include <chrono>
#include <cstdint>
#include <ratio>
#include <system_error>
#include <ranges>

class clock_control {
public:
  using kiloHertz = unsigned long long;

  static std::size_t get_num_clock_sources() noexcept;

  static const char* const* get_clock_source_names(std::size_t& num_sources) noexcept; 

  kiloHertz get_current_frequency() const noexcept;

  std::error_code set_current_frequency(kiloHertz value) noexcept;

  std::error_code sleep_for(std::chrono::nanoseconds) const noexcept;

  const std::error_code initialization_result;

  clock_control();
  ~clock_control();
};