#pragma once

#include "registers/UART.hpp"
#include <cstdint>
#include <cstdlib>
#include <HAL/simulatable_peripheral.hpp>
#include <rp2040/shared_types.hpp>
#include <rp2040/subsystem_resets/resets.hpp>
#include <type_traits>

static constexpr std::size_t num_UARTs = 2;

class UART : public simulatable_peripheral<UART, reg::mock, num_UARTs> {
public:
  reg::UARTDR UARTDR;
  reg::UARTRSR UARTRSR;

  // 0x18 = 24
  // 0x4 = 4
  // Meaning that 16 bytes must be padded.
  // Taking into account the bytes taken by UARTRSR.
  const std::array<uint8_t, (0x18 - 0x8)> padding__0;
  reg::UARTFR UARTFR;
  const std::array<uint8_t, 4> padding__1;
  reg::UARTILPR UARTILPR;
  reg::UARTIBRD UARTIBRD;
  reg::UARTFBRD UARTFBRD;
  reg::UARTLCR_H UARTLCR_H;
  reg::UARTCR UARTCR;
  reg::UARTIFLS UARTIFLS;
  reg::UARTIMSC UARTIMSC;
  reg::UARTRIS UARTRIS;
  reg::UARTMIS UARTMIS;
  reg::UARTICR UARTICR;
  reg::UARTDMACR UARTDMACR;

  const std::array<uint8_t, 0xfe0 - 0x4C> padding__2;
  reg::UARTPERIPHID0 UARTPERIPHID0;
  reg::UARTPERIPHID1 UARTPERIPHID1;
  reg::UARTPERIPHID2 UARTPERIPHID2;
  reg::UARTPERIPHID3 UARTPERIPHID3;
  reg::UARTPCELLID0 UARTPCELLID0;
  reg::UARTPCELLID1 UARTPCELLID1;
  reg::UARTPCELLID2 UARTPCELLID2;
  reg::UARTPCELLID3 UARTPCELLID3;

  enum ID : std::size_t { first, second };
  ~UART();

private:
  static constexpr std::array base_addresses = {0x40034000, 0x40038000};

  UART(/* args */);

  void write_to_UART(std::size_t which, uint8_t data);

  void flush_UART_FIFOs(std::size_t which);

  void init_UARTDR_handlers(reg::UARTDR &data_register, std::size_t which);

  void initialize_effect_handlers(std::size_t);

  friend simulatable_peripheral<UART, reg::mock, num_UARTs>;
  friend resets;
};