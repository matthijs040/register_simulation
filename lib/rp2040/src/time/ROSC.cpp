#include <HAL/clock_control.hpp>
#include <rp2040/time/ROSC.hpp>

ROSC &ROSC::get() noexcept {
  static ROSC *handle;
  if (handle)
    return *handle;
  return *(handle = new ROSC());
}

ROSC::~ROSC() {}

void ROSC::operator delete(void *addr) { static_cast<ROSC *>(addr)->~ROSC(); }

ROSC::ROSC() : CTRL() {}

void *ROSC::operator new(std::size_t size) {
  if constexpr (USE_SIMULATED_REGISTERS)
    return simulated_peripheral<ROSC>::operator new(size);
  return reinterpret_cast<ROSC *>(base_address);
}

std::expected<uint32_t, std::error_code> ROSC::get_frequency_kHz() {
  std::expected<uint32_t, std::error_code> ret;

  if (CTRL.ENABLE == reg::ROSC::CTRL::ENABLE_states::disabled) {
    std::error_code err = clock_error::code::disabled;
    ret = std::unexpected(err);
    return ret;
  }

  if (CTRL.FREQ_RANGE == reg::ROSC::CTRL::FREQ_RANGE_states::too_high) {
    ret = std::unexpected(clock_error::code::invalid_configuration);
    return ret;
  }

  ret = std::unexpected(clock_error::code::disabled);
  return ret;
}