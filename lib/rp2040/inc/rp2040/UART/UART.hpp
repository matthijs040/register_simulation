#pragma once

#include "registers/UART.hpp"
#include <HAL/simulated_peripheral.hpp>
#include <cstdint>
#include <type_traits>
#include <rp2040/shared_types.hpp>

static constexpr std::size_t num_UART_peripherals = 2;

class UART
    : std::conditional<reg::mock,
                       simulated_peripheral<UART, num_UART_peripherals>, void> {
public:
  static constexpr uintptr_t base_address_0 = 0x40034000;
  static constexpr uintptr_t base_address_1 = 0x40038000;

  reg::UARTDR UARTDR;
  reg::UARTRSR UARTRSR;
  reg::UARTFR UARTFR;
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
  reg::UARTPERIPHID0 UARTPERIPHID0;
  reg::UARTPERIPHID1 UARTPERIPHID1;
  reg::UARTPERIPHID2 UARTPERIPHID2;
  reg::UARTPERIPHID3 UARTPERIPHID3;
  reg::UARTPCELLID0 UARTPCELLID0;
  reg::UARTPCELLID1 UARTPCELLID1;
  reg::UARTPCELLID2 UARTPCELLID2;
  reg::UARTPCELLID3 UARTPCELLID3;

  enum class ID : std::size_t { first, second };
  static UART &get(ID which) noexcept;
  ~UART();
  void operator delete(void *addr);

private:
  UART(/* args */);
  void *operator new(std::size_t, UART::ID which);
};