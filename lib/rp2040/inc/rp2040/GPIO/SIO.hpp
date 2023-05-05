#pragma once

#include "registers/SIO.hpp"
#include <HAL/device_register.hpp>
#include <HAL/simulated_peripheral.hpp>
#include <memory>
#include <type_traits>
#include <HAL/GPIO.hpp>
#include <expected>
#include <system_error>

class SIO : std::conditional<USE_SIMULATED_REGISTERS, simulated_peripheral<SIO>,
                             void> {
public:
  static constexpr uintptr_t base_address = 0xd0000000;

  ~SIO();
  void operator delete(void *addr);

  std::expected<reg::state, std::error_code> get_pin_OE(GPIO::pin_number number) const noexcept;

  reg::CPUID CPUID;
  reg::GPIO_IN GPIO_IN;
  reg::GPIO_HI_IN GPIO_HI_IN;
  reg::GPIO_OUT GPIO_OUT;
  reg::GPIO_OUT_SET GPIO_OUT_SET;
  reg::GPIO_OUT_CLR GPIO_OUT_CLR;
  reg::GPIO_OUT_XOR GPIO_OUT_XOR;
  reg::GPIO_OE GPIO_OE;
  reg::GPIO_OE_SET GPIO_OE_SET;
  reg::GPIO_OE_CLR GPIO_OE_CLR;
  reg::GPIO_OE_XOR GPIO_OE_XOR;
  reg::GPIO_HI_OUT GPIO_HI_OUT;
  reg::GPIO_HI_SET GPIO_HI_SET;
  reg::GPIO_HI_CLR GPIO_HI_CLR;
  reg::GPIO_HI_XOR GPIO_HI_XOR;
  reg::GPIO_HI_OE GPIO_HI_OE;
  reg::GPIO_HI_OE_SET GPIO_HI_OE_SET;
  reg::GPIO_HI_OE_CLR GPIO_HI_OE_CLR;
  reg::GPIO_HI_OE_XOR GPIO_HI_OE_XOR;
  reg::FIFO_ST FIFO_ST;
  reg::FIFO_WR FIFO_WR;
  reg::FIFO_RD FIFO_RD;
  reg::SPINLOCK_ST SPINLOCK_ST;
  reg::DIV_UDIVIDEND DIV_UDIVIDEND;
  reg::DIV_UDIVISOR DIV_UDIVISOR;
  reg::DIV_SDIVIDEND DIV_SDIVIDEND;
  reg::DIV_SDIVISOR DIV_SDIVISOR;
  reg::DIV_QUOTIENT DIV_QUOTIENT;
  reg::DIV_REMAINDER DIV_REMAINDER;
  reg::DIV_CSR DIV_CSR;
  reg::INTERP0_ACCUM0 INTERP0_ACCUM0;
  reg::INTERP0_ACCUM1 INTERP0_ACCUM1;
  reg::INTERP0_BASE0 INTERP0_BASE0;
  reg::INTERP0_BASE1 INTERP0_BASE1;
  reg::INTERP0_BASE2 INTERP0_BASE2;
  reg::INTERP0_POP_LANE0 INTERP0_POP_LANE0;
  reg::INTERP0_POP_LANE1 INTERP0_POP_LANE1;
  reg::INTERP0_POP_FULL INTERP0_POP_FULL;
  reg::INTERP0_PEEK_LANE0 INTERP0_PEEK_LANE0;
  reg::INTERP0_PEEK_LANE1 INTERP0_PEEK_LANE1;
  reg::INTERP0_PEEK_FULL INTERP0_PEEK_FULL;
  reg::INTERP0_CTRL_LANE0 INTERP0_CTRL_LANE0;
  reg::INTERP0_CTRL_LANE1 INTERP0_CTRL_LANE1;
  reg::INTERP0_ACCUM0_ADD INTERP0_ACCUM0_ADD;
  reg::INTERP0_ACCUM1_ADD INTERP0_ACCUM1_ADD;
  reg::INTERP0_BASE_1AND0 INTERP0_BASE_1AND0;
  reg::INTERP1_ACCUM0 INTERP1_ACCUM0;
  reg::INTERP1_ACCUM1 INTERP1_ACCUM1;
  reg::INTERP1_BASE0 INTERP1_BASE0;
  reg::INTERP1_BASE1 INTERP1_BASE1;
  reg::INTERP1_BASE2 INTERP1_BASE2;
  reg::INTERP1_POP_LANE0 INTERP1_POP_LANE0;
  reg::INTERP1_POP_LANE1 INTERP1_POP_LANE1;
  reg::INTERP1_POP_FULL INTERP1_POP_FULL;
  reg::INTERP1_PEEK_LANE0 INTERP1_PEEK_LANE0;
  reg::INTERP1_PEEK_LANE1 INTERP1_PEEK_LANE1;
  reg::INTERP1_PEEK_FULL INTERP1_PEEK_FULL;
  reg::INTERP1_CTRL_LANE0 INTERP1_CTRL_LANE0;
  reg::INTERP1_CTRL_LANE1 INTERP1_CTRL_LANE1;
  reg::INTERP1_ACCUM0_ADD INTERP1_ACCUM0_ADD;
  reg::INTERP1_ACCUM1_ADD INTERP1_ACCUM1_ADD;
  reg::INTERP1_ACCUM1_AND0 INTERP1_ACCUM1_AND0;
  reg::SPINLOCK SPINLOCK;

private:
  SIO();
  void *operator new(std::size_t);

  static inline std::weak_ptr<SIO> storage_handle;
  friend std::shared_ptr<SIO> std::make_shared<SIO>();
};

template <> inline std::shared_ptr<SIO> std::make_shared<SIO>() {
  if (const auto ptr = SIO::storage_handle.lock())
    return ptr;
  auto ptr = std::shared_ptr<SIO>(new SIO());
  ::new (ptr.get()) SIO();

  SIO::storage_handle = ptr;
  return ptr;
}