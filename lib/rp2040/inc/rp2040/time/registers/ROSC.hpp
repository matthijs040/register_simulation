#pragma once
#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {
namespace ROSC {
// Ring Oscillator control
union CTRL {
  enum class ENABLE_states : register_integral {
    enabled = 0xd1e,
    disabled = 0xfab
  };
  bitfield<ENABLE_states, 12, 12> ENABLE;

  enum class FREQ_RANGE_states : register_integral {
    low = 0xfa4,
    medium = 0xfa5,
    high = 0xfa7,
    too_high = 0xfa6,
  };
  bitfield<FREQ_RANGE_states, 0, 12> FREQ_RANGE;

  CTRL() : ENABLE{ENABLE_states::enabled} {
    FREQ_RANGE = {FREQ_RANGE_states::low};
  }
};

enum class PASSWD_states { apply = 0x9696, reset = 0 };

enum class drive_strength : register_integral {
  default_strength = 0,
  double_strength = 1,
  triple_strength = 3,
  quadruple_strength = 7,
};

// Ring Oscillator frequency control A
union FREQA {
  bitfield<PASSWD_states, 16, 16> PASSWD;
  bitfield<drive_strength, 12, 3> DS3;
  bitfield<drive_strength, 8, 3> DS2;
  bitfield<drive_strength, 4, 3> DS1;
  bitfield<drive_strength, 0, 3> DS0;

  FREQA() {}
};

// Ring Oscillator frequency control B
union FREQB {
  FREQB() {}
  bitfield<PASSWD_states, 16, 16> PASSWD;
  bitfield<drive_strength, 12, 3> DS7;
  bitfield<drive_strength, 8, 3> DS6;
  bitfield<drive_strength, 4, 3> DS5;
  bitfield<drive_strength, 0, 3> DS4;
};
// Ring Oscillator pause control
union DORMANT {
  enum class DORMANT_states : register_integral {
    dormant = 0x636f6d61,
    awake = 0x77616b65,
  };
  bitfield<DORMANT_states, 0, 32> state;
  DORMANT() : state(DORMANT_states::awake) {}
};
// Controls the output divider
union DIV {
  bitfield<register_integral, 0, 12> divisor;
  DIV() : divisor(16) {}
};
// Controls the phase shifted output
union PHASE {
  PHASE() {}
  enum class PASSWD_states {
    apply = 0xaa,
    reset = 0,
  };
  bitfield<PASSWD_states, 4, 8> PASSWD;
  bitfield<reg::state, 3, 1> ENABLE;
  bitfield<reg::state, 2, 1> FLIP;
  bitfield<register_integral, 0, 2> SHIFT;
};
// Ring Oscillator Status
union STATUS {
  STATUS() {}
  bitfield<reg::state, 31, 1> STABLE;
  bitfield<reg::state, 24, 1> BADWRITE;
  bitfield<reg::state, 16, 1> DIV_RUNNING;
  bitfield<reg::state, 12, 1> ENABLED;
};
// Returns a 1 bit random value
union RANDOMBIT {
  RANDOMBIT() {}
  bitfield<reg::state, 0, 1> value;
};

// A down counter running at the ROSC frequency which counts to zero and stops.
union COUNT {
  COUNT() {}
  bitfield<register_integral, 0, 8> value;
};
} // namespace ROSC
} // namespace reg