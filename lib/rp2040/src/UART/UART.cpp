#include <HAL/UART.hpp>
#include <concepts>
#include <rp2040/GPIO/GPIO.hpp>
#include <rp2040/UART/UART.hpp>
#include <rp2040/subsystem_resets/resets.hpp>
#include <rp2040/time/ROSC.hpp>
#include <rp2040/time/clocks.hpp>


void clear_pin_reservations(HAL::UART::pins pins,
                            std::size_t num_pins_reserved) {
  if (num_pins_reserved > 0)
    get_control_register(pins.RX).FUNCSEL = reg::CTRL::FUNCSEL_states::disabled;
  if (num_pins_reserved > 1)
    get_control_register(pins.TX).FUNCSEL = reg::CTRL::FUNCSEL_states::disabled;
  if (num_pins_reserved > 2)
    get_control_register(pins.RTS.value()).FUNCSEL =
        reg::CTRL::FUNCSEL_states::disabled;
  if (num_pins_reserved > 3)
    get_control_register(pins.CTS.value()).FUNCSEL =
        reg::CTRL::FUNCSEL_states::disabled;
}

std::error_code set_reserved_pins(HAL::UART::pins pins) {
  if (auto error = reserve_pin(pins.RX, reg::CTRL::FUNCSEL_states::UART)) {
    clear_pin_reservations(pins, 0);
    return error;
  }
  if (auto error = reserve_pin(pins.TX, reg::CTRL::FUNCSEL_states::UART)) {
    clear_pin_reservations(pins, 1);
    return error;
  }
  if (!pins.CTS.has_value() || !pins.RTS.has_value())
    return {};

  if (auto error =
          reserve_pin(pins.CTS.value(), reg::CTRL::FUNCSEL_states::UART)) {
    clear_pin_reservations(pins, 2);
    return error;
  }
  if (auto error =
          reserve_pin(pins.RTS.value(), reg::CTRL::FUNCSEL_states::UART)) {
    clear_pin_reservations(pins, 3);
    return error;
  }

  return {};
}

constexpr bool has_additional_control_flow(HAL::UART::pins pins) {
  return pins.CTS.has_value() && pins.RTS.has_value();
}

constexpr std::optional<UART::ID> get_ID_by_pins(HAL::UART::pins pins) {
  std::optional<UART::ID> ret = std::nullopt;
  if (pins.RX == 1 || pins.RX == 13 || pins.RX == 17 || pins.RX == 29)
    if (pins.TX == 0 || pins.TX == 12 || pins.TX == 16 || pins.TX == 28)
      ret = UART::ID::first;

  if (pins.RX == 5 || pins.RX == 9 || pins.RX == 21 || pins.RX == 25)
    if (pins.TX == 4 || pins.TX == 8 || pins.TX == 16 || pins.TX == 28)
      ret = UART::ID::second;

  if (!has_additional_control_flow(pins))
    return ret;
  if (!ret)
    return ret;

  switch (*ret) {
  case UART::ID::first: {
    if ((*pins.CTS != 2 && *pins.CTS != 14 && *pins.CTS != 18) &&
        (*pins.RTS != 3 && *pins.RTS != 15 && *pins.RTS != 19))
      return ret = std::nullopt;
    return ret;
  }
  case UART::ID::second: {
    if ((*pins.CTS != 2 && *pins.CTS != 14 && *pins.CTS != 18) &&
        (*pins.RTS != 3 && *pins.RTS != 15 && *pins.RTS != 19))
      return ret = std::nullopt;
    return ret;
  }
  }
  return ret;
}

void reset_peripheral(UART::ID ID) {
  auto &HW_reset = resets::get();
  switch (ID) {
  case UART::ID::first:
    HW_reset.RESET.UART0 = reg::state::enabled;
    while (HW_reset.RESET_DONE.UART0 == reg::state::cleared) {
    }
    break;
  case UART::ID::second:
    HW_reset.RESET.UART1 = reg::state::enabled;
    while (HW_reset.RESET_DONE.UART1 == reg::state::cleared) {
    }
    break;
  }
}

uint32_t set_baudrate(UART &handle, uint32_t baudrate,
                      std::uint32_t clock_rate_Hz) {
  assert(baudrate);

  uint32_t baud_rate_div = (8 * clock_rate_Hz / baudrate);
  uint32_t baud_ibrd = baud_rate_div >> 7;
  uint32_t baud_fbrd;

  if (baud_ibrd == 0) {
    baud_ibrd = 1;
    baud_fbrd = 0;
  } else if (baud_ibrd >= 65535) {
    baud_ibrd = 65535;
    baud_fbrd = 0;
  } else {
    baud_fbrd = ((baud_rate_div & 0x7f) + 1) / 2;
  }

  handle.UARTFBRD.BAUD_DIVFRAC = baud_fbrd;
  handle.UARTIBRD.BAUD_DIVINT = baud_ibrd;

  // PL011 needs a (dummy) LCR_H write to latch in the divisors.
  // We don't want to actually change LCR_H contents here.
  handle.UARTLCR_H.BRK = reg::state::disabled;

  // See datasheet
  return (4 * clock_rate_Hz) / (64 * baud_ibrd + baud_fbrd);
}

std::error_code set_format(UART &handle,
                           const HAL::UART::format &format_to_apply) {
  if (format_to_apply.used_data_bits == HAL::UART::data_bits::nine ||
      format_to_apply.used_stop_bits == HAL::UART::stop_bits::one_and_a_half)
    return HAL::UART_error::code::invalid_format_configuration;

  switch (format_to_apply.used_data_bits) {
  case HAL::UART::data_bits::five:
    handle.UARTLCR_H.WLEN = reg::UARTLCR_H::WLEN_states::data_bits_5;
    break;
  case HAL::UART::data_bits::six:
    handle.UARTLCR_H.WLEN = reg::UARTLCR_H::WLEN_states::data_bits_6;
    break;
  case HAL::UART::data_bits::seven:
    handle.UARTLCR_H.WLEN = reg::UARTLCR_H::WLEN_states::data_bits_7;
    break;
  case HAL::UART::data_bits::eight:
    handle.UARTLCR_H.WLEN = reg::UARTLCR_H::WLEN_states::data_bits_8;
    break;
  case HAL::UART::data_bits::nine:
    // Should be caught by input if-statement
    break;
  }

  switch (format_to_apply.used_parity) {
  case HAL::UART::parity::none:
    handle.UARTLCR_H.PEN = reg::state::disabled;
    break;
  case HAL::UART::parity::even:
    handle.UARTLCR_H.EPS = reg::state::set;
    handle.UARTLCR_H.PEN = reg::state::enabled;
    break;
  case HAL::UART::parity::odd:
    handle.UARTLCR_H.EPS = reg::state::cleared;
    handle.UARTLCR_H.PEN = reg::state::enabled;
    break;
  }

  switch (format_to_apply.used_stop_bits) {
  case HAL::UART::stop_bits::one:
    handle.UARTLCR_H.STP2 = reg::state::cleared;
    break;
  case HAL::UART::stop_bits::one_and_a_half:
  // Should be caught by input if-statement
  case HAL::UART::stop_bits::two:
    handle.UARTLCR_H.STP2 = reg::state::set;
  }
  return {};
}

HAL::UART::format get_format(const ::UART &handle) {
  return HAL::UART::format{
      handle.UARTLCR_H.PEN == reg::state::disabled ? HAL::UART::parity::none
      : handle.UARTLCR_H.EPS == reg::state::set    ? HAL::UART::parity::even
                                                   : HAL::UART::parity::odd,

      handle.UARTLCR_H.STP2 == reg::state::set ? HAL::UART::stop_bits::two
                                               : HAL::UART::stop_bits::one,

      handle.UARTLCR_H.WLEN == reg::UARTLCR_H::WLEN_states::data_bits_5
          ? HAL::UART::data_bits::five
      : handle.UARTLCR_H.WLEN == reg::UARTLCR_H::WLEN_states::data_bits_6
          ? HAL::UART::data_bits::six
      : handle.UARTLCR_H.WLEN == reg::UARTLCR_H::WLEN_states::data_bits_7
          ? HAL::UART::data_bits::seven
          : HAL::UART::data_bits::eight};
}

std::error_code initialize(HAL::UART::pins &pins, std::uint32_t &baudrate,
                           const HAL::UART::format &format_to_use) {
  if (baudrate == 0)
    return std::make_error_code(std::errc::invalid_argument);

  auto ID = get_ID_by_pins(pins);
  // Combination of pins do not map to one peripheral.
  // Reject initialization.
  if (ID == std::nullopt)
    return HAL::UART_error::code::unsupported_pin_configuration;

  if (auto error = set_reserved_pins(pins))
    return error;

  reset_peripheral(*ID);

  // Use the ROSC as the peripheral clock source.
  clocks::get().CLK_PERI_CTRL.ENABLE = reg::state::enabled;
  clocks::get().CLK_PERI_CTRL.AUXSRC =
      reg::CLK_PERI_CTRL::AUXSRC_states::rosc_clksrc_ph;
  // Obtain the frequency or abort if that fails.
  auto frequency = ROSC::get().get_frequency_Hz();
  if (!frequency.has_value())
    return frequency.error();

  UART &handle = UART::get(ID.value());
  // get the used baudrate as out-param to write to the class member.
  baudrate = set_baudrate(handle, baudrate, frequency.value());

  // Clearing the pin reservation if this error occurs will be handled by the
  // destructor.
  auto error = set_format(handle, format_to_use);
  if (error)
    return error;

  // Enable the FIFO's used for buffering bytes in transfer.
  handle.UARTLCR_H.FEN = reg::state::enabled;

  // Enable the peripheral.
  handle.UARTCR.TXE = reg::state::enabled;
  handle.UARTCR.RXE = reg::state::enabled;
  handle.UARTCR.UARTEN = reg::state::enabled;

  // Enable DMA.
  handle.UARTDMACR.TXDMAE = reg::state::enabled;
  handle.UARTDMACR.RXDMAE = reg::state::enabled;

  return std::error_code();
}

HAL::UART::UART(UART::pins pins_to_use, std::uint32_t baudrate,
                format format_to_use)
    : initialization_result(initialize(pins_to_use, baudrate, format_to_use)),
      used_pins(pins_to_use), used_baudrate(baudrate),
      used_format(format_to_use) {}

HAL::UART::~UART() {
  clear_pin_reservations(used_pins,
                         has_additional_control_flow(used_pins) ? 4 : 2);
}

std::expected<std::size_t, std::error_code>
HAL::UART::send(const std::span<uint8_t> data) {
  if (initialization_result)
    return std::unexpected(initialization_result);
  if (data.empty())
    return 0U;

  auto &handle = ::UART::get(get_ID_by_pins(used_pins).value());
  for (const auto &byte : data) {
    if (handle.UARTFR.transmit_FIFO_full == reg::state::set)
      return &byte - &data.front();

    handle.UARTDR.data = byte;
  }

  return data.size();
}

std::expected<std::size_t, std::error_code>
HAL::UART::receive(std::span<uint8_t> data) {
  if (data.empty())
    return 0U;

  if (initialization_result)
    return std::unexpected(initialization_result);

  auto &handle = ::UART::get(get_ID_by_pins(used_pins).value());
  if (handle.UARTFR.receive_FIFO_empty == reg::state::set)
    return (data = std::span<uint8_t>()).size();

  std::error_code transfer_error;

  for (uint8_t &byte : data) {

    // Check for errors in received data before performing the read.
    // This is because e.g. the Overrun-error bit clears when the FIFO is read
    // from.
    if (handle.UARTDR.overrun_error == reg::state::set)
      transfer_error = HAL::UART_error::code::receive_buffer_overflown;
    if (handle.UARTDR.parity_error == reg::state::set)
      transfer_error = HAL::UART_error::code::parity_error_in_received_data;
    if (handle.UARTDR.framing_error == reg::state::set ||
        handle.UARTDR.break_error == reg::state::set)
      transfer_error = HAL::UART_error::code::format_error_in_received_data;

    // Read the data byte.
    byte = handle.UARTDR.data;

    if (handle.UARTFR.receive_FIFO_empty == reg::state::set) {
      // Change the caller's buffer to data that actually changed.
      return transfer_error ? std::unexpected(transfer_error)
                            : std::expected<std::size_t, std::error_code>(
                                  &byte - &data.front());
    }
  }

  return transfer_error
             ? std::unexpected(transfer_error)
             : std::expected<std::size_t, std::error_code>(data.size());
}

HAL::UART::format HAL::UART::get_active_format() const noexcept {
  auto ID = get_ID_by_pins(used_pins);
  if (!ID.has_value())
    return {};
  auto &handle = ::UART::get(ID.value());
  return get_format(handle);
}