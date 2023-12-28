#include <HAL/UART.hpp>
#include <bit>
#include <cstring>
#include <rp2040/UART/UART.hpp>

int main(int, char const *[]) {
  volatile bool continue_ = false;
  while (!continue_) {
  }

  constexpr auto RX_pin = 1;
  constexpr auto TX_pin = 0;
  constexpr auto baudrate = 115200;
  constexpr auto loopback_enabled = false;
  constexpr const char *data = "hello world!";

  HAL::UART::format format{HAL::UART::parity::none, HAL::UART::stop_bits::one,
                           HAL::UART::data_bits::eight};
  HAL::UART::pins pins{RX_pin, TX_pin};
  auto handle = HAL::UART(pins, baudrate, format, loopback_enabled);

  std::span<const uint8_t> payload = {std::bit_cast<const uint8_t *>(data),
                                      std::strlen(data)};
  auto send_result = handle.send(payload);

  if (!send_result.has_value())
    return EXIT_FAILURE;

  auto receive_buffer = std::array<uint8_t, 16>();
  receive_buffer.fill(0u);

  while (::UART::get(UART::ID::first).UARTFR.BUSY == reg::state::set) {
  }

  // auto receive_result = handle.receive(receive_buffer);
  //
  // if (!receive_result.has_value())
  //   return EXIT_FAILURE;
  //
  // volatile char *received_data = std::bit_cast<char
  // *>(receive_buffer.data());

  while (true) {
  }

  return EXIT_SUCCESS;
}
