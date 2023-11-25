#include <HAL/UART.hpp>
#include <rp2040/UART/UART.hpp>

static std::array<UART *, num_UART_peripherals> handles;

void initialize_UART_handlers()
{

}


UART &UART::get(UART::ID which) noexcept {
  auto instance = handles.at(std::to_underlying(which));
  if (!instance)
    instance = new (which) UART();

  if constexpr (reg::mock)
    initialize_UART_handlers();
  return *instance;
}
UART::~UART() {}
void UART::operator delete(void *ptr) {
  for (auto *handle : handles)
    if (handle == ptr)
      handle = nullptr;
}
UART::UART() {}

void *UART::operator new(std::size_t, UART::ID which) {
  using base = simulated_peripheral<UART>;
  if constexpr (reg::mock)
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