#pragma once
#include <rp2040/shared_types.hpp>
#include <HAL/bitfield.hpp>

namespace reg {

union VOLTAGE_SELECT {

  enum class VOLTAGE_SELECT_states { volts_3_3, volts_1_8 };
  VOLTAGE_SELECT(VOLTAGE_SELECT_states state) : voltage_select(state) {}
  reg::field<VOLTAGE_SELECT_states, 0, 1> voltage_select;
};

union GPIO {
  GPIO(register_integral initial_values) : full_register(initial_values) {}
  reg::field<reg::state, 7, 1> OD;
  reg::field<reg::state, 6, 1> IE;
  reg::field<reg::state, 4, 2> DRIVE;
  reg::field<reg::state, 3, 1> PUE;
  reg::field<reg::state, 2, 1> PDE;
  reg::field<reg::state, 1, 1> SCHMITT;
  reg::field<reg::state, 0, 1> SLEWFAST;
private:
  register_integral full_register;
};

} // namespace reg