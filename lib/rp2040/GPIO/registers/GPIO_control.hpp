#pragma once
#include <HAL/bitfield.hpp>

namespace reg {
union STATUS {
  STATUS() {}
  bitfield<26, 1> IRQTOPROC;
  bitfield<24, 1> IRQFROMPAD;
  bitfield<19, 1> INTOPERI;
  bitfield<17, 1> INFROMPAD;
  bitfield<13, 1> OETOPAD;
  bitfield<12, 1> OEFROMPERI;
  bitfield<9, 1> OUTTOPAD;
  bitfield<8, 1> OUTFROMPERI;
};

union CTRL {
  CTRL() : FUNCSEL(0x1F) {}

  enum class IRQOVER_states : register_integral {
    unaffected,
    inverted,
    driven_low,
    driven_high
  };
  bitfield<28, 2> IRQOVER;

  enum class INOVER_states : register_integral {
    unaffected,
    inverted,
    driven_low,
    driven_high
  };
  bitfield<16, 2> INOVER;

  enum class OEOVER_states : register_integral {
    FUNCSEL_defined,
    inverse_FUNCSEL_defined,
    disabled,
    enabled,
  };
  bitfield<12, 2> OEOVER;

  enum class OUTOVER_states : register_integral {
    FUNCSEL_defined,
    inverse_FUNCSEL_defined,
    driven_low,
    driven_high,
  };
  bitfield<8, 2> OUTOVER;

  enum class FUNCSEL_states : register_integral {
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
  bitfield<0, 5> FUNCSEL;
};
} // namespace reg
