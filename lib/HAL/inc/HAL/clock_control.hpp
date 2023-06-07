#pragma once

#include <chrono>
#include <cstdint>
#include <ratio>
#include <system_error>

class clock_control {
public:
  using kiloHertz = unsigned long long;

  kiloHertz get_current_frequency() const noexcept;

  std::error_code set_current_frequency(kiloHertz value) noexcept;

  std::error_code sleep_for(std::chrono::nanoseconds) const noexcept;

  const std::error_code initialization_result;

  clock_control();
  ~clock_control();
};