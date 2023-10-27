#pragma once
#include <rp2040/shared_types.hpp>
#include <HAL/bitfield.hpp>

namespace reg {

union VOLTAGE_SELECT {

  enum class VOLTAGE_SELECT_states { volts_3_3, volts_1_8 };
  VOLTAGE_SELECT(VOLTAGE_SELECT_states state) : voltage_select(state) {}
  bitfield<VOLTAGE_SELECT_states, 0, 1, reg::mock> voltage_select;
};

union GPIO {
  GPIO(register_integral initial_values) : full_register(initial_values) {}
  bitfield<reg::state, 7, 1, reg::mock> OD;
  bitfield<reg::state, 6, 1, reg::mock> IE;
  bitfield<reg::state, 4, 2, reg::mock> DRIVE;
  bitfield<reg::state, 3, 1, reg::mock> PUE;
  bitfield<reg::state, 2, 1, reg::mock> PDE;
  bitfield<reg::state, 1, 1, reg::mock> SCHMITT;
  bitfield<reg::state, 0, 1, reg::mock> SLEWFAST;
private:
  register_integral full_register;
};

} // namespace reg