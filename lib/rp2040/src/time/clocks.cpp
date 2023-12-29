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

void clocks::operator delete(void *addr) {
  static_cast<clocks *>(addr)->~clocks();
}

void *clocks::operator new(std::size_t size) {
  if constexpr (reg::mock)
    return simulated_peripheral<clocks>::operator new(size);
  return std::bit_cast<clocks *>(base_address);
}

clocks &clocks::get() noexcept {
  static clocks *handle;
  if (handle)
    return *handle;
  return *(handle = new clocks());
}