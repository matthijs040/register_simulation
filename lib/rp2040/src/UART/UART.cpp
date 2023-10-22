#include <HAL/UART.hpp>
#include <concepts>
#include <rp2040/UART/UART.hpp>

UART &UART::get(UART::ID which) noexcept {
  static std::array<UART *, num_UART_peripherals> handles;
  auto instance = handles.at(std::to_underlying(which));
  if (!instance)
    instance = new (which) UART();
  return *instance;
}
UART::~UART() {}
void UART::operator delete(void *) {}

UART::UART() {}

void *UART::operator new(std::size_t, UART::ID which) {
  using base = simulated_peripheral<UART>;
  if constexpr (std::derived_from<UART, base>)
    return base::operator new(std::to_underlying(which));
  else {
    switch (which) {
    case UART::ID::first:
      return std::bit_cast<UART *>(base_address_0);
    case UART::ID::second:
      return std::bit_cast<UART *>(base_address_1);
    }
    std::abort();
  }
}

std::error_code initialize(HAL::UART::pins) { return {}; }

HAL::UART::UART(UART::pins pins_to_use, std::size_t baudrate)
    : used_pins(pins_to_use), used_baudrate(baudrate),
      initialization_result(initialize(pins_to_use)) {}

HAL::UART::~UART() {}

std::expected<std::size_t, std::error_code>
HAL::UART::send(const std::span<uint8_t>) {
  return 0u;
}

std::expected<std::size_t, std::error_code>
HAL::UART::receive(std::span<uint8_t>) {
  return 0u;
}