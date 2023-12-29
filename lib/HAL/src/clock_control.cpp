#include <HAL/clock_control.hpp>

template <>
error_code error_code::make_error_code(clock_control::errc e) noexcept {
  static struct : error_category {
    virtual const char *name() const noexcept override {
      return "Clock control";
    }
    virtual const char* message(int code) const noexcept override {
      switch (static_cast<clock_control::errc>(code)) {
      case clock_control::errc::success:
        return "Success";
      case clock_control::errc::disabled:
        return "Clock disabled";
      case clock_control::errc::invalid_configuration:
        return "Clock in invalid state";
      case clock_control::errc::name_not_found:
        return "Clock not found";
      case clock_control::errc::busy:
        return "Clock irresponsive";
      case clock_control::errc::invalid_pin:
        return "Invalid clock-pin";
      }
      return "Unknown";
    }
  } category;

  return error_code(static_cast<int>(e), category);
}