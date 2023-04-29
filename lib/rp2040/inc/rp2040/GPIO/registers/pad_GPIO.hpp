#pragma once
#include "shared_types.hpp"
#include <HAL/bitfield.hpp>

namespace reg {

union VOLTAGE_SELECT {

  enum class VOLTAGE_SELECT_states { volts_3_3, volts_1_8 };
  VOLTAGE_SELECT(VOLTAGE_SELECT_states state) : voltage_select(state) {}
  bitfield<VOLTAGE_SELECT_states, 0, 1> voltage_select;
};

union GPIO {
  GPIO(register_integral initial_values) : full_register(initial_values) {}
  bitfield<reg::state, 7, 1> OD;
  bitfield<reg::state, 6, 1> IE;
  bitfield<reg::state, 4, 2> DRIVE;
  bitfield<reg::state, 3, 1> PUE;
  bitfield<reg::state, 2, 1> PDE;
  bitfield<reg::state, 1, 1> SCHMITT;
  bitfield<reg::state, 0, 1> SLEWFAST;
private:
  register_integral full_register;
};

} // namespace reg