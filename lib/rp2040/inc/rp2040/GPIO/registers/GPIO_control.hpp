#pragma once
#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {
union STATUS {
  STATUS() {}
  bitfield<reg::state, 26, 1, reg::mock> IRQTOPROC;
  bitfield<reg::state, 24, 1, reg::mock> IRQFROMPAD;
  bitfield<reg::state, 19, 1, reg::mock> INTOPERI;
  bitfield<reg::state, 17, 1, reg::mock> INFROMPAD;
  bitfield<reg::state, 13, 1, reg::mock> OETOPAD;
  bitfield<reg::state, 12, 1, reg::mock> OEFROMPERI;
  bitfield<reg::state, 9, 1, reg::mock> OUTTOPAD;
  bitfield<reg::state, 8, 1, reg::mock> OUTFROMPERI;
};

union CTRL {
  CTRL() : FUNCSEL(FUNCSEL_states::disabled) {}

  enum class IRQOVER_states : register_integral {
    unaffected,
    inverted,
    driven_low,
    driven_high
  };
  bitfield<IRQOVER_states, 28, 2, reg::mock> IRQOVER;

  enum class INOVER_states : register_integral {
    unaffected,
    inverted,
    driven_low,
    driven_high
  };
  bitfield<INOVER_states, 16, 2, reg::mock> INOVER;

  enum class OEOVER_states : register_integral {
    FUNCSEL_defined,
    inverse_FUNCSEL_defined,
    disabled,
    enabled,
  };
  bitfield<OEOVER_states, 12, 2, reg::mock> OEOVER;

  enum class OUTOVER_states : register_integral {
    FUNCSEL_defined,
    inverse_FUNCSEL_defined,
    driven_low,
    driven_high,
  };
  bitfield<OUTOVER_states, 8, 2, reg::mock> OUTOVER;

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
  bitfield<FUNCSEL_states, 0, 5, reg::mock> FUNCSEL;
};
} // namespace reg
