#pragma once
#include "shared_types.hpp"
#include <HAL/bitfield.hpp>

namespace reg {
union STATUS {
  STATUS() {}
  bitfield<reg::state, 26, 1> IRQTOPROC;
  bitfield<reg::state, 24, 1> IRQFROMPAD;
  bitfield<reg::state, 19, 1> INTOPERI;
  bitfield<reg::state, 17, 1> INFROMPAD;
  bitfield<reg::state, 13, 1> OETOPAD;
  bitfield<reg::state, 12, 1> OEFROMPERI;
  bitfield<reg::state, 9, 1> OUTTOPAD;
  bitfield<reg::state, 8, 1> OUTFROMPERI;
};

union CTRL {
  CTRL() : FUNCSEL(FUNCSEL_states::disabled) {}

  enum class IRQOVER_states : register_integral {
    unaffected,
    inverted,
    driven_low,
    driven_high
  };
  bitfield<IRQOVER_states, 28, 2> IRQOVER;

  enum class INOVER_states : register_integral {
    unaffected,
    inverted,
    driven_low,
    driven_high
  };
  bitfield<INOVER_states, 16, 2> INOVER;

  enum class OEOVER_states : register_integral {
    FUNCSEL_defined,
    inverse_FUNCSEL_defined,
    disabled,
    enabled,
  };
  bitfield<OEOVER_states, 12, 2> OEOVER;

  enum class OUTOVER_states : register_integral {
    FUNCSEL_defined,
    inverse_FUNCSEL_defined,
    driven_low,
    driven_high,
  };
  bitfield<OUTOVER_states, 8, 2> OUTOVER;

  enum class FUNCSEL_states : register_integral {
    XIP,
    SPI,
    UART,
    I2C,
    PWM,
    SIO,
    PIO0,
    PIO1,
    Clock_GPIO,
    USB,
    disabled = 0x1F
  };
  bitfield<FUNCSEL_states, 0, 5> FUNCSEL;
};
} // namespace reg
