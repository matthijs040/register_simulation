#pragma once

#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {

union RESET {
  RESET() {}

  bitfield<reg::state, 24, 1> USBCTRL;
  bitfield<reg::state, 23, 1> UART1;
  bitfield<reg::state, 22, 1> UART0;
  bitfield<reg::state, 21, 1> TIMER;
  bitfield<reg::state, 20, 1> TBMAN;
  bitfield<reg::state, 19, 1> SYSINFO;
  bitfield<reg::state, 18, 1> SYSCFG;
  bitfield<reg::state, 17, 1> SPI1;
  bitfield<reg::state, 16, 1> SPI0;
  bitfield<reg::state, 15, 1> RTC;
  bitfield<reg::state, 14, 1> PWM;
  bitfield<reg::state, 13, 1> PLL_USB;
  bitfield<reg::state, 12, 1> PLL_SYS;
  bitfield<reg::state, 11, 1> PIO1;
  bitfield<reg::state, 10, 1> PIO0;
  bitfield<reg::state, 9, 1> PADS_QSPI;
  bitfield<reg::state, 8, 1> PADS_BANK0;
  bitfield<reg::state, 7, 1> JTAG;
  bitfield<reg::state, 6, 1> IO_QSPI;
  bitfield<reg::state, 5, 1> IO_BANK0;
  bitfield<reg::state, 4, 1> I2C1;
  bitfield<reg::state, 3, 1> I2C0;
  bitfield<reg::state, 2, 1> DMA;
  bitfield<reg::state, 1, 1> BUSCTRL;
  bitfield<reg::state, 0, 1> ADC;
};

union WDSEL {
  WDSEL() {}

  bitfield<reg::state, 24, 1> USBCTRL;
  bitfield<reg::state, 23, 1> UART1;
  bitfield<reg::state, 22, 1> UART0;
  bitfield<reg::state, 21, 1> TIMER;
  bitfield<reg::state, 20, 1> TBMAN;
  bitfield<reg::state, 19, 1> SYSINFO;
  bitfield<reg::state, 18, 1> SYSCFG;
  bitfield<reg::state, 17, 1> SPI1;
  bitfield<reg::state, 16, 1> SPI0;
  bitfield<reg::state, 15, 1> RTC;
  bitfield<reg::state, 14, 1> PWM;
  bitfield<reg::state, 13, 1> PLL_USB;
  bitfield<reg::state, 12, 1> PLL_SYS;
  bitfield<reg::state, 11, 1> PIO1;
  bitfield<reg::state, 10, 1> PIO0;
  bitfield<reg::state, 9, 1> PADS_QSPI;
  bitfield<reg::state, 8, 1> PADS_BANK0;
  bitfield<reg::state, 7, 1> JTAG;
  bitfield<reg::state, 6, 1> IO_QSPI;
  bitfield<reg::state, 5, 1> IO_BANK0;
  bitfield<reg::state, 4, 1> I2C1;
  bitfield<reg::state, 3, 1> I2C0;
  bitfield<reg::state, 2, 1> DMA;
  bitfield<reg::state, 1, 1> BUSCTRL;
  bitfield<reg::state, 0, 1> ADC;
};

union RESET_DONE {
  RESET_DONE() {}

  const bitfield<reg::state, 24, 1> USBCTRL;
  const bitfield<reg::state, 23, 1> UART1;
  const bitfield<reg::state, 22, 1> UART0;
  const bitfield<reg::state, 21, 1> TIMER;
  const bitfield<reg::state, 20, 1> TBMAN;
  const bitfield<reg::state, 19, 1> SYSINFO;
  const bitfield<reg::state, 18, 1> SYSCFG;
  const bitfield<reg::state, 17, 1> SPI1;
  const bitfield<reg::state, 16, 1> SPI0;
  const bitfield<reg::state, 15, 1> RTC;
  const bitfield<reg::state, 14, 1> PWM;
  const bitfield<reg::state, 13, 1> PLL_USB;
  const bitfield<reg::state, 12, 1> PLL_SYS;
  const bitfield<reg::state, 11, 1> PIO1;
  const bitfield<reg::state, 10, 1> PIO0;
  const bitfield<reg::state, 9, 1> PADS_QSPI;
  const bitfield<reg::state, 8, 1> PADS_BANK0;
  const bitfield<reg::state, 7, 1> JTAG;
  const bitfield<reg::state, 6, 1> IO_QSPI;
  const bitfield<reg::state, 5, 1> IO_BANK0;
  const bitfield<reg::state, 4, 1> I2C1;
  const bitfield<reg::state, 3, 1> I2C0;
  const bitfield<reg::state, 2, 1> DMA;
  const bitfield<reg::state, 1, 1> BUSCTRL;
  const bitfield<reg::state, 0, 1> ADC;
};

} // namespace reg