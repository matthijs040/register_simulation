#pragma once

#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {

union RESET {
  RESET() {}

  bitfield<reg::state, 24, 1, reg::mock> USBCTRL;
  bitfield<reg::state, 23, 1, reg::mock> UART1;
  bitfield<reg::state, 22, 1, reg::mock> UART0;
  bitfield<reg::state, 21, 1, reg::mock> TIMER;
  bitfield<reg::state, 20, 1, reg::mock> TBMAN;
  bitfield<reg::state, 19, 1, reg::mock> SYSINFO;
  bitfield<reg::state, 18, 1, reg::mock> SYSCFG;
  bitfield<reg::state, 17, 1, reg::mock> SPI1;
  bitfield<reg::state, 16, 1, reg::mock> SPI0;
  bitfield<reg::state, 15, 1, reg::mock> RTC;
  bitfield<reg::state, 14, 1, reg::mock> PWM;
  bitfield<reg::state, 13, 1, reg::mock> PLL_USB;
  bitfield<reg::state, 12, 1, reg::mock> PLL_SYS;
  bitfield<reg::state, 11, 1, reg::mock> PIO1;
  bitfield<reg::state, 10, 1, reg::mock> PIO0;
  bitfield<reg::state, 9, 1, reg::mock> PADS_QSPI;
  bitfield<reg::state, 8, 1, reg::mock> PADS_BANK0;
  bitfield<reg::state, 7, 1, reg::mock> JTAG;
  bitfield<reg::state, 6, 1, reg::mock> IO_QSPI;
  bitfield<reg::state, 5, 1, reg::mock> IO_BANK0;
  bitfield<reg::state, 4, 1, reg::mock> I2C1;
  bitfield<reg::state, 3, 1, reg::mock> I2C0;
  bitfield<reg::state, 2, 1, reg::mock> DMA;
  bitfield<reg::state, 1, 1, reg::mock> BUSCTRL;
  bitfield<reg::state, 0, 1, reg::mock> ADC;
};

union WDSEL {
  WDSEL() {}

  bitfield<reg::state, 24, 1, reg::mock> USBCTRL;
  bitfield<reg::state, 23, 1, reg::mock> UART1;
  bitfield<reg::state, 22, 1, reg::mock> UART0;
  bitfield<reg::state, 21, 1, reg::mock> TIMER;
  bitfield<reg::state, 20, 1, reg::mock> TBMAN;
  bitfield<reg::state, 19, 1, reg::mock> SYSINFO;
  bitfield<reg::state, 18, 1, reg::mock> SYSCFG;
  bitfield<reg::state, 17, 1, reg::mock> SPI1;
  bitfield<reg::state, 16, 1, reg::mock> SPI0;
  bitfield<reg::state, 15, 1, reg::mock> RTC;
  bitfield<reg::state, 14, 1, reg::mock> PWM;
  bitfield<reg::state, 13, 1, reg::mock> PLL_USB;
  bitfield<reg::state, 12, 1, reg::mock> PLL_SYS;
  bitfield<reg::state, 11, 1, reg::mock> PIO1;
  bitfield<reg::state, 10, 1, reg::mock> PIO0;
  bitfield<reg::state, 9, 1, reg::mock> PADS_QSPI;
  bitfield<reg::state, 8, 1, reg::mock> PADS_BANK0;
  bitfield<reg::state, 7, 1, reg::mock> JTAG;
  bitfield<reg::state, 6, 1, reg::mock> IO_QSPI;
  bitfield<reg::state, 5, 1, reg::mock> IO_BANK0;
  bitfield<reg::state, 4, 1, reg::mock> I2C1;
  bitfield<reg::state, 3, 1, reg::mock> I2C0;
  bitfield<reg::state, 2, 1, reg::mock> DMA;
  bitfield<reg::state, 1, 1, reg::mock> BUSCTRL;
  bitfield<reg::state, 0, 1, reg::mock> ADC;
};

union RESET_DONE {
  RESET_DONE() {}

  const bitfield<reg::state, 24, 1, reg::mock> USBCTRL;
  const bitfield<reg::state, 23, 1, reg::mock> UART1;
  const bitfield<reg::state, 22, 1, reg::mock> UART0;
  const bitfield<reg::state, 21, 1, reg::mock> TIMER;
  const bitfield<reg::state, 20, 1, reg::mock> TBMAN;
  const bitfield<reg::state, 19, 1, reg::mock> SYSINFO;
  const bitfield<reg::state, 18, 1, reg::mock> SYSCFG;
  const bitfield<reg::state, 17, 1, reg::mock> SPI1;
  const bitfield<reg::state, 16, 1, reg::mock> SPI0;
  const bitfield<reg::state, 15, 1, reg::mock> RTC;
  const bitfield<reg::state, 14, 1, reg::mock> PWM;
  const bitfield<reg::state, 13, 1, reg::mock> PLL_USB;
  const bitfield<reg::state, 12, 1, reg::mock> PLL_SYS;
  const bitfield<reg::state, 11, 1, reg::mock> PIO1;
  const bitfield<reg::state, 10, 1, reg::mock> PIO0;
  const bitfield<reg::state, 9, 1, reg::mock> PADS_QSPI;
  const bitfield<reg::state, 8, 1, reg::mock> PADS_BANK0;
  const bitfield<reg::state, 7, 1, reg::mock> JTAG;
  const bitfield<reg::state, 6, 1, reg::mock> IO_QSPI;
  const bitfield<reg::state, 5, 1, reg::mock> IO_BANK0;
  const bitfield<reg::state, 4, 1, reg::mock> I2C1;
  const bitfield<reg::state, 3, 1, reg::mock> I2C0;
  const bitfield<reg::state, 2, 1, reg::mock> DMA;
  const bitfield<reg::state, 1, 1, reg::mock> BUSCTRL;
  const bitfield<reg::state, 0, 1, reg::mock> ADC;
};

} // namespace reg