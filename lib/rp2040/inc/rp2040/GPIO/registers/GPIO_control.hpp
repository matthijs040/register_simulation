#pragma once
#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {
union STATUS {
  STATUS() {}
  reg::field<reg::state, 26, 1> IRQTOPROC;
  reg::field<reg::state, 24, 1> IRQFROMPAD;
  reg::field<reg::state, 19, 1> INTOPERI;
  reg::field<reg::state, 17, 1> INFROMPAD;
  reg::field<reg::state, 13, 1> OETOPAD;
  reg::field<reg::state, 12, 1> OEFROMPERI;
  reg::field<reg::state, 9, 1> OUTTOPAD;
  reg::field<reg::state, 8, 1> OUTFROMPERI;
};

union CTRL {
  CTRL() : FUNCSEL(FUNCSEL_states::disabled) {}

  enum class IRQOVER_states : register_integral {
    unaffected,
    inverted,
    driven_low,
    driven_high
  };
  reg::field<IRQOVER_states, 28, 2> IRQOVER;

  enum class INOVER_states : register_integral {
    unaffected,
    inverted,
    driven_low,
    driven_high
  };
  reg::field<INOVER_states, 16, 2> INOVER;

  enum class OEOVER_states : register_integral {
    FUNCSEL_defined,
    inverse_FUNCSEL_defined,
    disabled,
    enabled,
  };
  reg::field<OEOVER_states, 12, 2> OEOVER;

  enum class OUTOVER_states : register_integral {
    FUNCSEL_defined,
    inverse_FUNCSEL_defined,
    driven_low,
    driven_high,
  };
  reg::field<OUTOVER_states, 8, 2> OUTOVER;

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
  reg::field<FUNCSEL_states, 0, 5> FUNCSEL;
};
} // namespace reg
