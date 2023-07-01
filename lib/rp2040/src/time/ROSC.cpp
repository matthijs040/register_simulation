#include <rp2040/time/ROSC.hpp>

ROSC &ROSC::get() noexcept {
  static ROSC *handle;
  if (handle)
    return *handle;
  return *(handle = new ROSC());
}

ROSC::~ROSC() {}

void ROSC::operator delete(void *addr) {
      static_cast<ROSC *>(addr)->~ROSC();
}

ROSC::ROSC() : CTRL() {}

void *ROSC::operator new(std::size_t size) {
  if constexpr (USE_SIMULATED_REGISTERS)
    return simulated_peripheral<ROSC>::operator new(size);
  return reinterpret_cast<ROSC *>(base_address);
}