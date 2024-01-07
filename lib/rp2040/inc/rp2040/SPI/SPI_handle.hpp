#pragma once

#include <HAL/SPI.hpp>
#include <optional>
#include <rp2040/GPIO/GPIO.hpp>
#include <rp2040/SPI/SPI_peripheral.hpp>
#include <rp2040/shared_types.hpp>
#include <rp2040/subsystem_resets/resets.hpp>
#include <system/error_code.hpp>

class rp2040_SPI : public SPI::handle<rp2040_SPI> {
public:
  rp2040_SPI(SPI::pins pins_to_use, SPI::mode mode_to_use);
  ~rp2040_SPI();

  error::code send(std::span<const uint16_t> &bytes_to_transfer);

  error::code receive(std::span<uint16_t> &bytes_read);

private:
  error::code initialize(SPI::pins pins_to_use, SPI::mode mode_to_use);

  std::optional<SPI_peripheral::ID>
  get_peripheral_handle_for_pins(const SPI::pins &pins);

  error::code reserve_pins(const SPI::pins &pins_to_use);
};

std::optional<SPI_peripheral::ID>
rp2040_SPI::get_peripheral_handle_for_pins(const SPI::pins &pins) {
  if ((pins.receive_pin == 0 || pins.receive_pin == 4 ||
       pins.receive_pin == 16 || pins.receive_pin == 20) &&
      (pins.transmit_pin == 3 || pins.transmit_pin == 7 ||
       pins.transmit_pin == 19 || pins.transmit_pin == 23) &&
      (pins.chip_select_pin == 1 || pins.chip_select_pin == 5 ||
       pins.chip_select_pin == 17 || pins.chip_select_pin == 21) &&
      (pins.clock_pin == 2 || pins.clock_pin == 6 || pins.clock_pin == 18 ||
       pins.clock_pin == 22)) {
    return SPI_peripheral::ID::first;
  }
  if ((pins.receive_pin == 8 || pins.receive_pin == 12 ||
       pins.receive_pin == 24 || pins.receive_pin == 28) &&
      (pins.transmit_pin == 11 || pins.transmit_pin == 15 ||
       pins.transmit_pin == 27) &&
      (pins.chip_select_pin == 9 || pins.chip_select_pin == 13 ||
       pins.chip_select_pin == 25 || pins.chip_select_pin == 29) &&
      (pins.clock_pin == 10 || pins.clock_pin == 14 || pins.clock_pin == 26)) {
    return SPI_peripheral::ID::second;
  }
  return std::nullopt;
}

error::code rp2040_SPI::reserve_pins(const SPI::pins &pins_to_use) {
  if (get_peripheral_handle_for_pins(pins_to_use) == std::nullopt)
    return error::code(error::standard_value::invalid_argument);

  if (GPIO::is_pin_reserved(pins_to_use.receive_pin) ||
      GPIO::is_pin_reserved(pins_to_use.transmit_pin) ||
      GPIO::is_pin_reserved(pins_to_use.chip_select_pin) ||
      GPIO::is_pin_reserved(pins_to_use.clock_pin)) {
    return error::code(error::standard_value::resource_unavailable_try_again);
  }

  reserve_pin(pins_to_use.receive_pin, reg::CTRL::FUNCSEL_states::SPI);
  reserve_pin(pins_to_use.transmit_pin, reg::CTRL::FUNCSEL_states::SPI);
  reserve_pin(pins_to_use.chip_select_pin, reg::CTRL::FUNCSEL_states::SPI);
  reserve_pin(pins_to_use.clock_pin, reg::CTRL::FUNCSEL_states::SPI);

  return {};
}

void clear_pin_reservations(SPI::pins pins) {
  get_control_register(pins.receive_pin).FUNCSEL =
      reg::CTRL::FUNCSEL_states::disabled;
  get_control_register(pins.transmit_pin).FUNCSEL =
      reg::CTRL::FUNCSEL_states::disabled;
  get_control_register(pins.chip_select_pin).FUNCSEL =
      reg::CTRL::FUNCSEL_states::disabled;
  get_control_register(pins.clock_pin).FUNCSEL =
      reg::CTRL::FUNCSEL_states::disabled;
}

void reset_peripheral(SPI_peripheral::ID ID) {
  auto &HW_reset = resets::get();
  switch (ID) {
  case SPI_peripheral::ID::first:
    HW_reset.RESET.SPI0 = reg::state::enabled;
    HW_reset.RESET.SPI0 = reg::state::cleared;
    while (HW_reset.RESET_DONE.SPI0 == reg::state::cleared) {
    }

    break;
  case SPI_peripheral::ID::second:
    HW_reset.RESET.SPI1 = reg::state::enabled;
    HW_reset.RESET.SPI1 = reg::state::cleared;
    while (HW_reset.RESET_DONE.SPI1 == reg::state::cleared) {
    }

    break;
  }
}

void set_format(SPI_peripheral &handle, SPI::mode mode) {
  switch (mode) {
  case SPI::mode::Motorola:
    handle.SSPCR0.FRF = reg::SPI::SSPCR0::FRF_states::Motorola_format;
    break;
  case SPI::mode::TI_synchronous:
    handle.SSPCR0.FRF = reg::SPI::SSPCR0::FRF_states::Texas_Instruments_format;
    break;
  case SPI::mode::Microwire:
    handle.SSPCR0.FRF = reg::SPI::SSPCR0::FRF_states::National_Microwire_format;
    break;
  }
}

error::code rp2040_SPI::initialize(SPI::pins pins_to_use,
                                   SPI::mode mode_to_use) {

  if (auto error_ocurred = reserve_pins(pins_to_use))
    return error_ocurred;

  const auto ID = get_peripheral_handle_for_pins(pins_to_use).value();
  auto periph = SPI_peripheral::get(ID);
  if (periph.SSPCR1.SSE == reg::state::set) {
    clear_pin_reservations(pins_to_use);
    return error::standard_value::resource_unavailable_try_again;
  }
  reset_peripheral(ID);

  return {};
}

rp2040_SPI::rp2040_SPI(SPI::pins pins_to_use, SPI::mode mode_to_use)
    : SPI::handle<rp2040_SPI>(initialize(pins_to_use, mode_to_use), pins_to_use,
                              mode_to_use) {}

rp2040_SPI::~rp2040_SPI() {
  if (initialization_result)
    return;
  clear_pin_reservations(used_pins);
}

error::code rp2040_SPI::send(std::span<const uint16_t> &bytes_to_transfer) {
  (void)bytes_to_transfer;
  return {};
}

error::code rp2040_SPI::receive(std::span<uint16_t> &bytes_read) {
  (void)bytes_read;
  return {};
}
