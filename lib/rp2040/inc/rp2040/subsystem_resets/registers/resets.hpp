#pragma once

#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {

union RESET {
  RESET() {}

  reg::field<reg::state, 24, 1> USBCTRL;
  reg::field<reg::state, 23, 1> UART1;
  reg::field<reg::state, 22, 1> UART0;
  reg::field<reg::state, 21, 1> TIMER;
  reg::field<reg::state, 20, 1> TBMAN;
  reg::field<reg::state, 19, 1> SYSINFO;
  reg::field<reg::state, 18, 1> SYSCFG;
  reg::field<reg::state, 17, 1> SPI1;
  reg::field<reg::state, 16, 1> SPI0;
  reg::field<reg::state, 15, 1> RTC;
  reg::field<reg::state, 14, 1> PWM;
  reg::field<reg::state, 13, 1> PLL_USB;
  reg::field<reg::state, 12, 1> PLL_SYS;
  reg::field<reg::state, 11, 1> PIO1;
  reg::field<reg::state, 10, 1> PIO0;
  reg::field<reg::state, 9, 1> PADS_QSPI;
  reg::field<reg::state, 8, 1> PADS_BANK0;
  reg::field<reg::state, 7, 1> JTAG;
  reg::field<reg::state, 6, 1> IO_QSPI;
  reg::field<reg::state, 5, 1> IO_BANK0;
  reg::field<reg::state, 4, 1> I2C1;
  reg::field<reg::state, 3, 1> I2C0;
  reg::field<reg::state, 2, 1> DMA;
  reg::field<reg::state, 1, 1> BUSCTRL;
  reg::field<reg::state, 0, 1> ADC;
};

union WDSEL {
  WDSEL() {}

  reg::field<reg::state, 24, 1> USBCTRL;
  reg::field<reg::state, 23, 1> UART1;
  reg::field<reg::state, 22, 1> UART0;
  reg::field<reg::state, 21, 1> TIMER;
  reg::field<reg::state, 20, 1> TBMAN;
  reg::field<reg::state, 19, 1> SYSINFO;
  reg::field<reg::state, 18, 1> SYSCFG;
  reg::field<reg::state, 17, 1> SPI1;
  reg::field<reg::state, 16, 1> SPI0;
  reg::field<reg::state, 15, 1> RTC;
  reg::field<reg::state, 14, 1> PWM;
  reg::field<reg::state, 13, 1> PLL_USB;
  reg::field<reg::state, 12, 1> PLL_SYS;
  reg::field<reg::state, 11, 1> PIO1;
  reg::field<reg::state, 10, 1> PIO0;
  reg::field<reg::state, 9, 1> PADS_QSPI;
  reg::field<reg::state, 8, 1> PADS_BANK0;
  reg::field<reg::state, 7, 1> JTAG;
  reg::field<reg::state, 6, 1> IO_QSPI;
  reg::field<reg::state, 5, 1> IO_BANK0;
  reg::field<reg::state, 4, 1> I2C1;
  reg::field<reg::state, 3, 1> I2C0;
  reg::field<reg::state, 2, 1> DMA;
  reg::field<reg::state, 1, 1> BUSCTRL;
  reg::field<reg::state, 0, 1> ADC;
};

union RESET_DONE {
  RESET_DONE() {}

  const reg::field<reg::state, 24, 1> USBCTRL;
  const reg::field<reg::state, 23, 1> UART1;
  const reg::field<reg::state, 22, 1> UART0;
  const reg::field<reg::state, 21, 1> TIMER;
  const reg::field<reg::state, 20, 1> TBMAN;
  const reg::field<reg::state, 19, 1> SYSINFO;
  const reg::field<reg::state, 18, 1> SYSCFG;
  const reg::field<reg::state, 17, 1> SPI1;
  const reg::field<reg::state, 16, 1> SPI0;
  const reg::field<reg::state, 15, 1> RTC;
  const reg::field<reg::state, 14, 1> PWM;
  const reg::field<reg::state, 13, 1> PLL_USB;
  const reg::field<reg::state, 12, 1> PLL_SYS;
  const reg::field<reg::state, 11, 1> PIO1;
  const reg::field<reg::state, 10, 1> PIO0;
  const reg::field<reg::state, 9, 1> PADS_QSPI;
  const reg::field<reg::state, 8, 1> PADS_BANK0;
  const reg::field<reg::state, 7, 1> JTAG;
  const reg::field<reg::state, 6, 1> IO_QSPI;
  const reg::field<reg::state, 5, 1> IO_BANK0;
  const reg::field<reg::state, 4, 1> I2C1;
  const reg::field<reg::state, 3, 1> I2C0;
  const reg::field<reg::state, 2, 1> DMA;
  const reg::field<reg::state, 1, 1> BUSCTRL;
  const reg::field<reg::state, 0, 1> ADC;
};

} // namespace reg