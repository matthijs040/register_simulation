#include <cstdlib>

#include <rp2040/SPI/SPI_handle.hpp>

enum class MCP2515_SPI_instruction : std::uint8_t {
  RESET = 0b11000000,
  READ = 0b00000011,
  READ_RX_BUFFER = 0b0010000,
  WRITE = 0b00000010,
  LOAD_TX_BUFFER = 0b01000000,
  REQUEST_TO_SEND = 0b10000000,
  READ_STATUS = 0b10100000,
  RX_STATUS = 0b10110000,
  BIT_MODIFY = 0b00000101,
};

enum class MCP2515_SPI_address : std::uint8_t {
  CANSTAT = 0b00001110,
};

/**
 * @brief This snippet assumes an MCP2515-IC is connected to the rp2040's SPI0
 * peripheral.
 */
int main() {
  volatile bool debugger_attached = false;
  while (!debugger_attached) {
  }

  auto handle = rp2040_SPI(
      SPI::pins{
          .receive_pin = 16,
          .transmit_pin = 19,
          .chip_select_pin = 17,
          .clock_pin = 18,
      },
      SPI::mode::TI_synchronous, SPI::role::main, SPI::bitrate{9600}, false);

  if (handle.initialization_result != error::standard_value::success)
    return EXIT_FAILURE;

  // Data is transferred MSB first and LSB last.
  // Data is latched on rising edge of SCLK.
  // Data should be transitioned on falling edge of SCLK.
  // Max frequency of SCLK is 1MHz.

  // First byte contains the SPI address. The following byte(s) contain(s) the
  // SPI data. The first bit of the first byte contains the Read/Write bit and
  // indicates a Read (1) or Write (0) operation. The following 7 bits contain
  // the Register Address. In case of a multi-byte Read/Write, data is two or
  // more bytes.

  const uint8_t data_to_send[] = {1,2,3,4,5,6,7,8,9,10};

  // const uint8_t CANSTAT_read_request[] = {
  //     std::to_underlying(MCP2515_SPI_instruction::READ),
  //     std::to_underlying(MCP2515_SPI_address::CANSTAT)};
  std::span<const uint8_t> sent_bytes = data_to_send;
  auto result = handle.send(sent_bytes);

  if (result != error::standard_value::success)
    return EXIT_FAILURE;

  uint8_t RX_buffer[4] = {};
  std::span<uint8_t> received_bytes = RX_buffer;
  result = handle.receive(received_bytes);
  // while (result == SPI::error_code::receive_buffer_empty && received_bytes.empty()) {
  //   std::span<uint8_t> received_bytes = RX_buffer;
  //   result = handle.receive(received_bytes);
  // }

  if (result != error::standard_value::success)
    return EXIT_FAILURE;

  // The buffer should be truncated to 1 byte (?)
  // As CANSTAT is only one byte in size?
  if (received_bytes.empty())
    return EXIT_FAILURE;

  std::printf("CANSTAT is: '%u'", received_bytes.front());

  return EXIT_SUCCESS;
}
