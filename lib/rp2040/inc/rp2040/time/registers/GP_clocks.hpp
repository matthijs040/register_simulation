#pragma once

#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {
union CLK_GPOUT0_CTRL {
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

} // namespace reg
