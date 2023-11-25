#include <HAL/UART.hpp>

std::error_code
HAL::UART_error::make_error_code(HAL::UART_error::code e) noexcept {
  static const struct : std::error_category {
    virtual const char *name() const noexcept override { return "UART"; }
    virtual std::string message(int code) const override {
      switch (static_cast<HAL::UART_error::code>(code)) {
      case HAL::UART_error::code::success:
        return "Success";
      case HAL::UART_error::code::unsupported_pin_configuration:
        return "Unsupported pin configuration";
      case HAL::UART_error::code::unsupported_parity_configuration:
        return "Unsupported parity configuration";
      case HAL::UART_error::code::invalid_format_configuration:
        return "Invalid format configuration";
      case HAL::UART_error::code::receive_buffer_overflown:
        return "Receive buffer overflown";
      case HAL::UART_error::code::parity_error_in_received_data:
        return "Parity error in received data";
      case HAL::UART_error::code::format_error_in_received_data:
        return "Format error in received data";
      }
      return "Unknown";
    }
  } category;
  return std::error_code(static_cast<int>(e), category);
}