#pragma once

#include "registers/GP_clocks.hpp"
#include <HAL/device_register.hpp>
#include <HAL/simulated_peripheral.hpp>
#include <type_traits>

class clocks
    : public std::conditional<reg::mock, simulated_peripheral<clocks>, void> {
public:
  static constexpr uintptr_t base_address = 0x40008000;

  static clocks &get() noexcept;

  ~clocks();
  void operator delete(void *addr);

  // Clock control, can be changed on-the-fly (except for auxsrc)
  reg::CLK_GPOUT_CTRL CLK_GPOUT0_CTRL;
  // Clock divisor, can be changed on-the-fly
  reg::CLK_GPOUT_DIV CLK_GPOUT0_DIV;
  // Indicates which SRC is currently selected by the glitchless mux (one-hot).
  reg::CLK_GPOUT_SELECTED CLK_GPOUT0_SELECTED;
  // Clock control, can be changed on-the-fly (except for auxsrc)
  reg::CLK_GPOUT_CTRL CLK_GPOUT1_CTRL;
  // Clock divisor, can be changed on-the-fly
  reg::CLK_GPOUT_DIV CLK_GPOUT1_DIV;
  // Indicates which SRC is currently selected by the glitchless mux (one-hot).
  reg::CLK_GPOUT_SELECTED CLK_GPOUT1_SELECTED;
  // Clock control, can be changed on-the-fly (except for auxsrc)
  reg::CLK_GPOUT_CTRL CLK_GPOUT2_CTRL;
  // Clock divisor, can be changed on-the-fly
  reg::CLK_GPOUT_DIV CLK_GPOUT2_DIV;
  // Indicates which SRC is currently selected by the glitchless mux (one-hot).
  reg::CLK_GPOUT_SELECTED CLK_GPOUT2_SELECTED;
  // Clock control, can be changed on-the-fly (except for auxsrc)
  reg::CLK_GPOUT_CTRL CLK_GPOUT3_CTRL;
  // Clock divisor, can be changed on-the-fly
  reg::CLK_GPOUT_DIV CLK_GPOUT3_DIV;
  // Indicates which SRC is currently selected by the glitchless mux (one-hot).
  reg::CLK_GPOUT_SELECTED CLK_GPOUT3_SELECTED;
  // Clock control, can be changed on-the-fly (except for auxsrc)
  reg::CLK_REF_CTRL CLK_REF_CTRL;
  // Clock divisor, can be changed on-the-fly
  reg::CLK_REF_DIV CLK_REF_DIV;
  // Indicates which SRC is currently selected by the glitchless mux (one-hot).
  const reg::CLK_REF_SELECTED CLK_REF_SELECTED;
  // Clock control, can be changed on-the-fly (except for auxsrc)
  reg::CLK_SYS_CTRL CLK_SYS_CTRL;
  // Clock divisor, can be changed on-the-fly
  reg::CLK_SYS_DIV CLK_SYS_DIV;
  // Indicates which SRC is currently selected by the glitchless mux (one-hot).
  reg::CLK_SYS_SELECTED CLK_SYS_SELECTED;
  // Clock control, can be changed on-the-fly (except for auxsrc)
  reg::CLK_PERI_CTRL CLK_PERI_CTRL;
  // Indicates which SRC is currently selected by the glitchless mux (one-hot).
  reg::CLK_PERI_SELECTED CLK_PERI_SELECTED;
  // Clock control, can be changed on-the-fly (except for auxsrc)
  reg::CLK_USB_CTRL CLK_USB_CTRL;
  // Clock divisor, can be changed on-the-fly
  reg::CLK_USB_DIV CLK_USB_DIV;
  // Indicates which SRC is currently selected by the glitchless mux (one-hot).
  reg::CLK_USB_SELECTED CLK_USB_SELECTED;
  // Clock control, can be changed on-the-fly (except for auxsrc)
  reg::CLK_ADC_CTRL CLK_ADC_CTRL;
  // Clock divisor, can be changed on-the-fly
  reg::CLK_ADC_DIV CLK_ADC_DIV;
  // Indicates which SRC is currently selected by the glitchless mux (one-hot).
  reg::CLK_ADC_SELECTED CLK_ADC_SELECTED;
  // Clock control, can be changed on-the-fly (except for auxsrc)
  reg::CLK_RTC_CTRL CLK_RTC_CTRL;
  // Clock divisor, can be changed on-the-fly
  reg::CLK_RTC_DIV CLK_RTC_DIV;
  // Indicates which SRC is currently selected by the glitchless mux (one-hot).
  reg::CLK_RTC_SELECTED CLK_RTC_SELECTED;
  // Control register for the resuscutation clock.
  reg::CLK_SYS_RESUS_CTRL CLK_SYS_RESUS_CTRL;
  // Status register for the resuscutation clock.
  reg::CLK_SYS_RESUS_STATUS CLK_SYS_RESUS_STATUS;
  // Reference clock frequency in kHz
  reg::FC0_REF_KHZ FC0_REF_KHZ;
  // Minimum pass frequency in kHz. This is optional. Set to 0 if you are not
  // using the pass/fail flags
  reg::FC0_MIN_KHZ FC0_MIN_KHZ;
  // Maximum pass frequency in kHz. This is optional. Set to 0x1ffffff if you
  // are not using the pass/fail flags
  reg::FC0_MAX_KHZ FC0_MAX_KHZ;
  // Delays the start of frequency counting to allow the mux to settle.  Delay
  // is measured in multiples of the reference clock period
  reg::FC0_DELAY FC0_DELAY;

  // The test interval is 0.98us * 2**interval, but let's call it 1us *
  // 2**interval. The default gives a test interval of 250us
  reg::FC0_INTERVAL FC0_INTERVAL;
  // Clock sent to frequency counter, set to 0 when not required Writing to this
  // register initiates the frequency count
  reg::FC0_SRC FC0_SRC;
  // Frequency counter status
  reg::FC0_STATUS FC0_STATUS;
  // Result of frequency measurement, only valid when status_done=1
  reg::FC0_RESULT FC0_RESULT;
  // enable clock in wake mode
  reg::WAKE_EN0 WAKE_EN0;
  // enable clock in wake mode
  reg::WAKE_EN1 WAKE_EN1;
  // enable clock in sleep mode
  reg::SLEEP_EN0 SLEEP_EN0;
  // enable clock in sleep mode
  reg::SLEEP_EN1 SLEEP_EN1;
  // indicates the state of the clock enable
  reg::ENABLED0 ENABLED0;
  // indicates the state of the clock enable
  reg::ENABLED1 ENABLED1;
  // Raw Interrupts
  reg::INTR INTR;
  // Interrupt Enable
  reg::INTE INTE;
  // Interrupt Force
  reg::INTF INTF;
  // Interrupt status after masking & forcing
  reg::INTS INTS;

private:
  clocks();
  void *operator new(std::size_t);
};