#include <HAL/UART.hpp>
#include <concepts>
#include <rp2040/GPIO/GPIO.hpp>
#include <rp2040/UART/UART.hpp>
#include <rp2040/subsystem_resets/resets.hpp>
#include <rp2040/time/ROSC.hpp>
#include <rp2040/time/clocks.hpp>

UART &UART::get(UART::ID which) noexcept {
  static std::array<UART *, num_UART_peripherals> handles;
  auto instance = handles.at(std::to_underlying(which));
  if (!instance)
    instance = new (which) UART();
  return *instance;
}
UART::~UART() {}
void UART::operator delete(void *) {}

UART::UART() {}

void *UART::operator new(std::size_t, UART::ID which) {
  using base = simulated_peripheral<UART>;
  if constexpr (reg::mock)
    return base::operator new(std::to_underlying(which));
  else {
    switch (which) {
    case UART::ID::first:
      return std::bit_cast<UART *>(base_address_0);
    case UART::ID::second:
      return std::bit_cast<UART *>(base_address_1);
    }
    std::abort();
  }
}

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

  if (auto error = reserve_pin(pins.CTS.value(), reg::CTRL::FUNCSEL_states::UART)) {
    clear_pin_reservations(pins, 2);
    return error;
  }
  if (auto error = reserve_pin(pins.RTS.value(), reg::CTRL::FUNCSEL_states::UART)) {
    clear_pin_reservations(pins, 3);
    return error;
  }

  return {};
}

bool has_additional_control_flow(HAL::UART::pins pins) {
  return pins.CTS.has_value() && pins.RTS.has_value();
}

constexpr std::optional<UART::ID> get_ID_by_pins(HAL::UART::pins pins) {
  std::optional<UART::ID> ret = {};
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

std::error_code initialize(HAL::UART::pins &pins, std::uint32_t &baudrate) {
  if (baudrate == 0)
    return std::make_error_code(std::errc::invalid_argument);

  auto ID = get_ID_by_pins(pins);
  // Combination of pins do not map to one peripheral.
  // Reject initialization.
  if (ID == std::nullopt)
    return std::make_error_code(std::errc::invalid_argument);

  if (auto error = set_reserved_pins(pins))
    return error;

  reset_peripheral(*ID);

  // Use the ROSC as the peripheral clock source.
  clocks::get().CLK_PERI_CTRL.ENABLE = reg::state::enabled;
  clocks::get().CLK_PERI_CTRL.AUXSRC =
      reg::CLK_PERI_CTRL::AUXSRC_states::rosc_clksrc_ph;
  // Obtain the frequency or abort if that fails.
  auto frequency = ROSC::get().get_frequency_Hz();
  if (frequency.error())
    return frequency.error();

  UART &handle = UART::get(ID.value());
  // get the used baudrate as out-param to write to the class member.
  baudrate = set_baudrate(handle, baudrate, frequency.value());

  return {};
}

HAL::UART::UART(UART::pins pins_to_use, std::uint32_t baudrate)
    : initialization_result(initialize(pins_to_use, baudrate)),
      used_pins(pins_to_use), used_baudrate(baudrate) {}

HAL::UART::~UART() {
  clear_pin_reservations(used_pins,
                         has_additional_control_flow(used_pins) ? 4 : 2);
}

std::expected<std::size_t, std::error_code>
HAL::UART::send(const std::span<uint8_t>) {
  return 0u;
}

std::expected<std::size_t, std::error_code>
HAL::UART::receive(std::span<uint8_t>) {
  return 0u;
}