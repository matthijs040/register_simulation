#include <rp2040/time/clocks.hpp>
#include <bit>
#include <concepts>

clocks::clocks() {
  // TODO maybe? Terrified of writing the initializer list for this.
  // Would not want to bork the system and resuscutation clocks.
  // That would hard-brick the chip.

  // Might just want to leave this one hardware-initialized.
  // Unless I *really* find a reason to override these.
}

clocks::~clocks() {}
