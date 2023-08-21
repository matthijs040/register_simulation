#include <HAL/clock_control.hpp>

std::error_code clock_error::make_error_code(clock_error::code e) noexcept {
  static const struct : std::error_category {
    virtual const char *name() const noexcept override {
      return "Clock control";
    }
    virtual std::string message(int code) const override {
      switch (static_cast<clock_error::code>(code)) {
      case clock_error::code::success:
        return "Success";
        case clock_error::code::disabled:
        return "Clock disabled";
        case clock_error::code::invalid_configuration:
        return "Clock in invalid state";
        case clock_error::code::name_not_found:
        return "Clock not found";
        case clock_error::code::busy:
        return "Clock irresponsive";
      }
      return "Unknown";
    }
  } category;
  return std::error_code(static_cast<int>(e), category);
}