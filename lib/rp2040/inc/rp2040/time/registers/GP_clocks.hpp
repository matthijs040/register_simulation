#pragma once

#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {
union CLK_GPOUT_CTRL {
  CLK_GPOUT_CTRL() {}
  bitfield<reg::state, 20, 1> NUDGE;
  bitfield<register_integral, 16, 2> PHASE;
  bitfield<reg::state, 12, 1> DC50;
  bitfield<reg::state, 11, 1> ENABLE;
  bitfield<reg::state, 10, 1> KILL;

  enum class AUXSRC_states : register_integral {
    clksrc_pll_sys = 0x0,
    clksrc_gpin0 = 0x1,
    clksrc_gpin1 = 0x2,
    clksrc_pll_usb = 0x3,
    rosc_clksrc = 0x4,
    xosc_clksrc = 0x5,
    clk_sys = 0x6,
    clk_usb = 0x7,
    clk_adc = 0x8,
    clk_rtc = 0x9,
    clk_ref = 0xA,
  };
  bitfield<AUXSRC_states, 5, 4> AUXSRC;
};

union CLK_GPOUT_DIV {
  CLK_GPOUT_DIV() {}
  /** @brief Integer component of the divisor, 0 → divide by 2^16. */
  bitfield<register_integral, 8, 24> INT;
  /** @brief Fractional component of the divisor. */
  bitfield<register_integral, 0, 8> FRAC;
};

union CLK_GPOUT_SELECTED {
  CLK_GPOUT_SELECTED() {}
  /**
   * @brief GPOUT-clocks only have an "auxilliary selection register".
   * Thus, their true selected source is hardwired to 0x1. (clksrc_clk_ref_aux)
   */
  bitfield<register_integral, 0, 32> SELECTED;
};

union CLK_REF_CTRL {

  enum class AUXSRC_states : register_integral {
    clksrc_pll_usb = 0x0,
    clksrc_gpin0 = 0x1,
    clksrc_gpin1 = 0x2,
  };
  bitfield<AUXSRC_states, 5, 4> AUXSRC;

  enum class SRC_states : register_integral {
    rosc_clksrc_ph = 0x0,
    clksrc_clk_ref_aux = 0x1,
    xosc_clksrc = 0x2,
  };
  bitfield<SRC_states, 0, 2> SRC;

  CLK_REF_CTRL() : SRC(SRC_states::rosc_clksrc_ph) {}
};

union CLK_REF_DIV {
  CLK_REF_DIV() {}
  bitfield<register_integral, 2, 8> INT;
};
union CLK_REF_SELECTED {
  CLK_REF_SELECTED() {}
  /**
   * @brief The glitchless multiplexer does not switch instantaneously (to avoid
   * glitches), so software should poll this register to wait for the switch to
   * complete. This register contains one decoded bit for each of the clock
   * sources enumerated in the CTRL SRC field. At most one of these bits will be
   * set at any time, indicating that clock is currently present at the output
   * of the glitchless mux. Whilst switching is in progress, this register may
   * briefly show all-0s.
   */
  bitfield<register_integral, 0, 32> selected_source;
};

union CLK_SYS_CTRL {
  CLK_SYS_CTRL() {}
  enum class AUXSRC_states : register_integral {
    clksrc_pll_sys = 0x0,
    clksrc_pll_usb = 0x1,
    rosc_clksrc = 0x2,
    xosc_clksrc = 0x3,
    clksrc_gpin0 = 0x4,
    clksrc_gpin1 = 0x5,
  };
  bitfield<AUXSRC_states, 5, 3> AUXSRC;

  enum class SRC_states : register_integral {
    clk_ref = 0x0,
    clksrc_clk_sys_aux = 0x1
  };
  bitfield<SRC_states, 0, 1> SRC;
};

union CLK_SYS_DIV {
  CLK_SYS_DIV() {}
  /** @brief Integer component of the divisor, 0 → divide by 2^16. */
  bitfield<register_integral, 8, 24> INT;
  /** @brief Fractional component of the divisor. */
  bitfield<register_integral, 0, 8> FRAC;
};

union CLK_SYS_SELECTED {
  CLK_SYS_SELECTED() {}
  bitfield<register_integral, 0, 32> selected_source;
};

union CLK_PERI_CTRL {
  CLK_PERI_CTRL() {}
  bitfield<reg::state, 11, 1> ENABLE;
  bitfield<reg::state, 10, 1> KILL;

  enum class AUXSRC_states : register_integral {
    clk_sys = 0x0,
    clksrc_pll_sys = 0x1,
    clksrc_pll_usb = 0x2,
    rosc_clksrc_ph = 0x3,
    xosc_clksrc = 0x4,
    clksrc_gpin0 = 0x5,
    clksrc_gpin1 = 0x6,
  };
  bitfield<AUXSRC_states, 5, 3> AUXSRC;
};
union CLK_PERI_SELECTED {
  CLK_PERI_SELECTED() {}
  bitfield<register_integral, 0, 32> selected_source;
};
union CLK_USB_CTRL {
  CLK_USB_CTRL() {}
  bitfield<reg::state, 20, 1> NUDGE;
  bitfield<register_integral, 16, 2> PHASE;
  bitfield<reg::state, 11, 1> ENABLE;
  bitfield<reg::state, 10, 1> KILL;

  enum class AUXSRC_states : register_integral {
    clksrc_pll_usb = 0x0,
    clksrc_pll_sys = 0x1,
    rosc_clksrc_ph = 0x2,
    xosc_clksrc = 0x3,
    clksrc_gpin0 = 0x4,
    clksrc_gpin1 = 0x5,
  };
  bitfield<AUXSRC_states, 5, 3> AUXSRC;
};
union CLK_USB_DIV {
  CLK_USB_DIV() {}
  bitfield<register_integral, 2, 8> INT;
};

union CLK_USB_SELECTED {
  CLK_USB_SELECTED() {}
  bitfield<register_integral, 0, 32> selected_source;
};

union CLK_ADC_CTRL {
  CLK_ADC_CTRL() {}
  bitfield<reg::state, 20, 1> NUDGE;
  bitfield<register_integral, 16, 2> PHASE;
  bitfield<reg::state, 11, 1> ENABLE;
  bitfield<reg::state, 10, 1> KILL;

  enum class AUXSRC_states : register_integral {
    clksrc_pll_usb = 0x0,
    clksrc_pll_sys = 0x1,
    rosc_clksrc_ph = 0x2,
    xosc_clksrc = 0x3,
    clksrc_gpin0 = 0x4,
    clksrc_gpin1 = 0x5,
  };
  bitfield<AUXSRC_states, 5, 3> AUXSRC;
};

union CLK_ADC_DIV {
  CLK_ADC_DIV() {}
  bitfield<register_integral, 2, 8> INT;
};

union CLK_ADC_SELECTED {
  CLK_ADC_SELECTED() {}
  bitfield<register_integral, 0, 32> selected_source;
};

union CLK_RTC_CTRL {
  CLK_RTC_CTRL() {}
  bitfield<reg::state, 20, 1> NUDGE;
  bitfield<register_integral, 16, 2> PHASE;
  bitfield<reg::state, 11, 1> ENABLE;
  bitfield<reg::state, 10, 1> KILL;

  enum class AUXSRC_states : register_integral {
    clksrc_pll_usb = 0x0,
    clksrc_pll_sys = 0x1,
    rosc_clksrc_ph = 0x2,
    xosc_clksrc = 0x3,
    clksrc_gpin0 = 0x4,
    clksrc_gpin1 = 0x5,
  };
  bitfield<AUXSRC_states, 5, 3> AUXSRC;
};

union CLK_RTC_DIV {
  CLK_RTC_DIV() {}
  /** @brief Integer component of the divisor, 0 → divide by 2^16. */
  bitfield<register_integral, 8, 24> INT;
  /** @brief Fractional component of the divisor. */
  bitfield<register_integral, 0, 8> FRAC;
};

union CLK_RTC_SELECTED {
  CLK_RTC_SELECTED() {}
  bitfield<register_integral, 0, 32> selected_source;
};

union CLK_SYS_RESUS_CTRL {
  CLK_SYS_RESUS_CTRL() {}
  bitfield<reg::state, 16, 1> CLEAR;
  bitfield<reg::state, 12, 1> FRCE;
  bitfield<reg::state, 8, 1> ENABLE;
  /**
   * @brief This is expressed as a number of clk_ref cycles
   * and must be >= 2x clk_ref_freq/min_clk_tst_freq
   */
  bitfield<register_integral, 0, 8> TIMEOUT;
};

union CLK_SYS_RESUS_STATUS {
  CLK_SYS_RESUS_STATUS() {}
  bitfield<reg::state, 0, 1> RESUSSED;
};

union FC0_REF_KHZ {
  FC0_REF_KHZ() {}
  bitfield<register_integral, 0, 20> reference_frequency;
};

union FC0_MIN_KHZ {
  FC0_MIN_KHZ() {}
  /**
   * @brief Minimum pass frequency in kHz. This is optional. Set to 0 if you are
   * not using the pass/fail flags.
   */
  bitfield<register_integral, 0, 25> minimum_pass_frequency;
};

union FC0_MAX_KHZ {
  FC0_MAX_KHZ() {}
  /**
   * @brief Maximum pass frequency in kHz. This is optional. Set to 0 if you are
   * not using the pass/fail flags.
   */
  bitfield<register_integral, 0, 25> maximum_pass_frequency;
};

union FC0_DELAY {
  FC0_DELAY() {}
  /**
   * @brief Delays the start of frequency counting to allow the mux to settle.
   * Delay is measured in multiples of the reference clock period
   */
  bitfield<register_integral, 0, 3> mux_settle_delay;
};

union FC0_INTERVAL {
  FC0_INTERVAL() {}
  /**
   * @brief The test interval is 0.98us * 2**interval.
   * but let’s call it 1us * 2^interval
   * The default gives a test interval of 250us
   *
   */
  bitfield<register_integral, 0, 3> frequency_test_interval;
};

union FC0_SRC {
  FC0_SRC() {}
  enum class Clocks {
    none = 0x00,
    pll_sys_clksrc_primary = 0x01,
    pll_usb_clksrc_primary = 0x02,
    rosc_clksrc = 0x03,
    rosc_clksrc_ph = 0x04,
    xosc_clksrc = 0x05,
    clksrc_gpin0 = 0x06,
    clksrc_gpin1 = 0x07,
    clk_ref = 0x08,
    clk_sys = 0x09,
    clk_peri = 0x0a,
    clk_usb = 0x0b,
    clk_adc = 0x0c,
    clk_rtc = 0x0d,
  };

  bitfield<Clocks, 0, 8> clock_to_frequency_count;
};

union FC0_STATUS {
  FC0_STATUS() {}
  bitfield<reg::state, 28, 1> DIED;
  bitfield<reg::state, 24, 1> FAST;
  bitfield<reg::state, 20, 1> SLOW;
  bitfield<reg::state, 16, 1> FAIL;
  bitfield<reg::state, 12, 1> WAITING;
  bitfield<reg::state, 8, 1> RUNNING;
  bitfield<reg::state, 4, 1> DONE;
  bitfield<reg::state, 0, 1> PASS;
};

#ifdef KHZ
#undef KHZ
#endif

union FC0_RESULT {
  FC0_RESULT() {}
  bitfield<register_integral, 5, 25> KHZ;
  bitfield<register_integral, 0, 5> FRAC;
};

union WAKE_EN0 {
  WAKE_EN0() {}
  bitfield<reg::state, 31, 1> CLK_SYS_SRAM3;
  bitfield<reg::state, 30, 1> CLK_SYS_SRAM2;
  bitfield<reg::state, 29, 1> CLK_SYS_SRAM1;
  bitfield<reg::state, 28, 1> CLK_SYS_SRAM0;
  bitfield<reg::state, 27, 1> CLK_SYS_SPI1;
  bitfield<reg::state, 26, 1> CLK_PERI_SPI1;
  bitfield<reg::state, 25, 1> CLK_SYS_SPI0;
  bitfield<reg::state, 24, 1> CLK_PERI_SPI0;
  bitfield<reg::state, 23, 1> CLK_SYS_SIO;
  bitfield<reg::state, 22, 1> CLK_SYS_RTC;
  bitfield<reg::state, 21, 1> CLK_RTC_RTC;
  bitfield<reg::state, 20, 1> CLK_SYS_ROSC;
  bitfield<reg::state, 19, 1> CLK_SYS_ROM;
  bitfield<reg::state, 18, 1> CLK_SYS_RESETS;
  bitfield<reg::state, 17, 1> CLK_SYS_PWM;
  bitfield<reg::state, 16, 1> CLK_SYS_PSM;
  bitfield<reg::state, 15, 1> CLK_SYS_PLL_USB;
  bitfield<reg::state, 14, 1> CLK_SYS_PLL_SYS;
  bitfield<reg::state, 13, 1> CLK_SYS_PIO1;
  bitfield<reg::state, 12, 1> CLK_SYS_PIO0;
  bitfield<reg::state, 11, 1> CLK_SYS_PADS;
  bitfield<reg::state, 10, 1> CLK_SYS_VREG_AND_CHIP_RESET;
  bitfield<reg::state, 9, 1> CLK_SYS_JTAG;
  bitfield<reg::state, 8, 1> CLK_SYS_IO;
  bitfield<reg::state, 7, 1> CLK_SYS_I2C1;
  bitfield<reg::state, 6, 1> CLK_SYS_I2C0;
  bitfield<reg::state, 5, 1> CLK_SYS_DMA;
  bitfield<reg::state, 4, 1> CLK_SYS_BUSFABRIC;
  bitfield<reg::state, 3, 1> CLK_SYS_BUSCTRL;
  bitfield<reg::state, 2, 1> CLK_SYS_ADC;
  bitfield<reg::state, 1, 1> CLK_ADC_ADC;
  bitfield<reg::state, 0, 1> CLK_SYS_CLOCKS;
};

union WAKE_EN1 {
  WAKE_EN1() {}
  bitfield<reg::state, 14, 1> CLK_SYS_XOSC;
  bitfield<reg::state, 13, 1> CLK_SYS_XIP;
  bitfield<reg::state, 12, 1> CLK_SYS_WATCHDOG;
  bitfield<reg::state, 11, 1> CLK_USB_USBCTRL;
  bitfield<reg::state, 10, 1> CLK_SYS_USBCTRL;
  bitfield<reg::state, 9, 1> CLK_SYS_UART1;
  bitfield<reg::state, 8, 1> CLK_PERI_UART1;
  bitfield<reg::state, 7, 1> CLK_SYS_UART0;
  bitfield<reg::state, 6, 1> CLK_PERI_UART0;
  bitfield<reg::state, 5, 1> CLK_SYS_TIMER;
  bitfield<reg::state, 4, 1> CLK_SYS_TBMAN;
  bitfield<reg::state, 3, 1> CLK_SYS_SYSINFO;
  bitfield<reg::state, 2, 1> CLK_SYS_SYSCFG;
  bitfield<reg::state, 1, 1> CLK_SYS_SRAM5;
  bitfield<reg::state, 0, 1> CLK_SYS_SRAM4;
};

union SLEEP_EN0 {
  SLEEP_EN0() {}
  bitfield<reg::state, 31, 1> CLK_SYS_SRAM3;
  bitfield<reg::state, 30, 1> CLK_SYS_SRAM2;
  bitfield<reg::state, 29, 1> CLK_SYS_SRAM1;
  bitfield<reg::state, 28, 1> CLK_SYS_SRAM0;
  bitfield<reg::state, 27, 1> CLK_SYS_SPI1;
  bitfield<reg::state, 26, 1> CLK_PERI_SPI1;
  bitfield<reg::state, 25, 1> CLK_SYS_SPI0;
  bitfield<reg::state, 24, 1> CLK_PERI_SPI0;
  bitfield<reg::state, 23, 1> CLK_SYS_SIO;
  bitfield<reg::state, 22, 1> CLK_SYS_RTC;
  bitfield<reg::state, 21, 1> CLK_RTC_RTC;
  bitfield<reg::state, 20, 1> CLK_SYS_ROSC;
  bitfield<reg::state, 19, 1> CLK_SYS_ROM;
  bitfield<reg::state, 18, 1> CLK_SYS_RESETS;
  bitfield<reg::state, 17, 1> CLK_SYS_PWM;
  bitfield<reg::state, 16, 1> CLK_SYS_PSM;
  bitfield<reg::state, 15, 1> CLK_SYS_PLL_USB;
  bitfield<reg::state, 14, 1> CLK_SYS_PLL_SYS;
  bitfield<reg::state, 13, 1> CLK_SYS_PIO1;
  bitfield<reg::state, 12, 1> CLK_SYS_PIO0;
  bitfield<reg::state, 11, 1> CLK_SYS_PADS;
  bitfield<reg::state, 10, 1> CLK_SYS_VREG_AND_CHIP_RESET;
  bitfield<reg::state, 9, 1> CLK_SYS_JTAG;
  bitfield<reg::state, 8, 1> CLK_SYS_IO;
  bitfield<reg::state, 7, 1> CLK_SYS_I2C1;
  bitfield<reg::state, 6, 1> CLK_SYS_I2C0;
  bitfield<reg::state, 5, 1> CLK_SYS_DMA;
  bitfield<reg::state, 4, 1> CLK_SYS_BUSFABRIC;
  bitfield<reg::state, 3, 1> CLK_SYS_BUSCTRL;
  bitfield<reg::state, 2, 1> CLK_SYS_ADC;
  bitfield<reg::state, 1, 1> CLK_ADC_ADC;
  bitfield<reg::state, 0, 1> CLK_SYS_CLOCKS;
};

union SLEEP_EN1 {
  SLEEP_EN1() {}
  bitfield<reg::state, 14, 1> CLK_SYS_XOSC;
  bitfield<reg::state, 13, 1> CLK_SYS_XIP;
  bitfield<reg::state, 12, 1> CLK_SYS_WATCHDOG;
  bitfield<reg::state, 11, 1> CLK_USB_USBCTRL;
  bitfield<reg::state, 10, 1> CLK_SYS_USBCTRL;
  bitfield<reg::state, 9, 1> CLK_SYS_UART1;
  bitfield<reg::state, 8, 1> CLK_PERI_UART1;
  bitfield<reg::state, 7, 1> CLK_SYS_UART0;
  bitfield<reg::state, 6, 1> CLK_PERI_UART0;
  bitfield<reg::state, 5, 1> CLK_SYS_TIMER;
  bitfield<reg::state, 4, 1> CLK_SYS_TBMAN;
  bitfield<reg::state, 3, 1> CLK_SYS_SYSINFO;
  bitfield<reg::state, 2, 1> CLK_SYS_SYSCFG;
  bitfield<reg::state, 1, 1> CLK_SYS_SRAM5;
  bitfield<reg::state, 0, 1> CLK_SYS_SRAM4;
};

union ENABLED0 {
  ENABLED0() {}
  bitfield<reg::state, 31, 1> CLK_SYS_SRAM3;
  bitfield<reg::state, 30, 1> CLK_SYS_SRAM2;
  bitfield<reg::state, 29, 1> CLK_SYS_SRAM1;
  bitfield<reg::state, 28, 1> CLK_SYS_SRAM0;
  bitfield<reg::state, 27, 1> CLK_SYS_SPI1;
  bitfield<reg::state, 26, 1> CLK_PERI_SPI1;
  bitfield<reg::state, 25, 1> CLK_SYS_SPI0;
  bitfield<reg::state, 24, 1> CLK_PERI_SPI0;
  bitfield<reg::state, 23, 1> CLK_SYS_SIO;
  bitfield<reg::state, 22, 1> CLK_SYS_RTC;
  bitfield<reg::state, 21, 1> CLK_RTC_RTC;
  bitfield<reg::state, 20, 1> CLK_SYS_ROSC;
  bitfield<reg::state, 19, 1> CLK_SYS_ROM;
  bitfield<reg::state, 18, 1> CLK_SYS_RESETS;
  bitfield<reg::state, 17, 1> CLK_SYS_PWM;
  bitfield<reg::state, 16, 1> CLK_SYS_PSM;
  bitfield<reg::state, 15, 1> CLK_SYS_PLL_USB;
  bitfield<reg::state, 14, 1> CLK_SYS_PLL_SYS;
  bitfield<reg::state, 13, 1> CLK_SYS_PIO1;
  bitfield<reg::state, 12, 1> CLK_SYS_PIO0;
  bitfield<reg::state, 11, 1> CLK_SYS_PADS;
  bitfield<reg::state, 10, 1> CLK_SYS_VREG_AND_CHIP_RESET;
  bitfield<reg::state, 9, 1> CLK_SYS_JTAG;
  bitfield<reg::state, 8, 1> CLK_SYS_IO;
  bitfield<reg::state, 7, 1> CLK_SYS_I2C1;
  bitfield<reg::state, 6, 1> CLK_SYS_I2C0;
  bitfield<reg::state, 5, 1> CLK_SYS_DMA;
  bitfield<reg::state, 4, 1> CLK_SYS_BUSFABRIC;
  bitfield<reg::state, 3, 1> CLK_SYS_BUSCTRL;
  bitfield<reg::state, 2, 1> CLK_SYS_ADC;
  bitfield<reg::state, 1, 1> CLK_ADC_ADC;
  bitfield<reg::state, 0, 1> CLK_SYS_CLOCKS;
};

union ENABLED1 {
  ENABLED1() {}
  bitfield<reg::state, 14, 1> CLK_SYS_XOSC;
  bitfield<reg::state, 13, 1> CLK_SYS_XIP;
  bitfield<reg::state, 12, 1> CLK_SYS_WATCHDOG;
  bitfield<reg::state, 11, 1> CLK_USB_USBCTRL;
  bitfield<reg::state, 10, 1> CLK_SYS_USBCTRL;
  bitfield<reg::state, 9, 1> CLK_SYS_UART1;
  bitfield<reg::state, 8, 1> CLK_PERI_UART1;
  bitfield<reg::state, 7, 1> CLK_SYS_UART0;
  bitfield<reg::state, 6, 1> CLK_PERI_UART0;
  bitfield<reg::state, 5, 1> CLK_SYS_TIMER;
  bitfield<reg::state, 4, 1> CLK_SYS_TBMAN;
  bitfield<reg::state, 3, 1> CLK_SYS_SYSINFO;
  bitfield<reg::state, 2, 1> CLK_SYS_SYSCFG;
  bitfield<reg::state, 1, 1> CLK_SYS_SRAM5;
  bitfield<reg::state, 0, 1> CLK_SYS_SRAM4;
};

union INTR {
  INTR() {}
  bitfield<reg::state, 0, 1> CLK_SYS_RESUS;
};

union INTE {
  INTE() {}
  bitfield<reg::state, 0, 1> CLK_SYS_RESUS;
};
union INTF {
  INTF() {}
  bitfield<reg::state, 0, 1> CLK_SYS_RESUS;
};
union INTS {
  INTS() {}
  bitfield<reg::state, 0, 1> CLK_SYS_RESUS;
};

} // namespace reg
