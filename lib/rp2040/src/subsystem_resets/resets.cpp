#include <bit>
#include <concepts>
#include <rp2040/SPI/SPI_peripheral.hpp>
#include <rp2040/UART/UART.hpp>
#include <rp2040/subsystem_resets/resets.hpp>

void resets::init_SPI_reset_handlers() {
  using SPI0 = decltype(reg::RESET::SPI0)::stored_type;
  auto SPI0_handlers = SPI0::effect_handlers();
  SPI0_handlers.on_write = [this](SPI0::field_type before,
                                  const SPI0::field_type &after_write) {
    if (before == reg::state::cleared && after_write == reg::state::set) {
      // Force de/con-structor calls by delete and re-get().
      delete &SPI_peripheral::get(
          static_cast<size_t>(SPI_peripheral::ID::first));
      auto &SPI_handle =
          SPI_peripheral::get(static_cast<size_t>(SPI_peripheral::ID::first));

      acquire_field(SPI_handle.SSPSR.TNF) = reg::state::set;
      acquire_field(SPI_handle.SSPSR.TFE) = reg::state::set;
      acquire_field(SPI_handle.SSPSR.RFF) = reg::state::cleared;
      acquire_field(SPI_handle.SSPSR.RNE) = reg::state::cleared;

      acquire_field(RESET.SPI0) = reg::state::cleared;
      acquire_field(RESET_DONE.SPI0) = reg::state::set;
    }
  };
  SPI0::set_effect_handlers(&RESET.SPI0, SPI0_handlers);

  using SPI1 = decltype(reg::RESET::SPI1)::stored_type;
  auto SPI1_handlers = SPI1::effect_handlers();
  SPI1_handlers.on_write = [this](SPI1::field_type before,
                                  const SPI1::field_type &after_write) {
    if (before == reg::state::cleared && after_write == reg::state::set) {
      // Force de/con-structor calls by delete and re-get().
      delete &SPI_peripheral::get(
          static_cast<size_t>(SPI_peripheral::ID::second));
      SPI_peripheral::get(static_cast<size_t>(SPI_peripheral::ID::second));

      acquire_field(RESET.SPI1) = reg::state::cleared;
      acquire_field(RESET_DONE.SPI1) = reg::state::set;
    }
  };
  SPI1::set_effect_handlers(&RESET.SPI1, SPI1_handlers);
}

void resets::init_SPI_reset_done_handlers() {
  using SPI0 = decltype(reg::RESET_DONE::SPI0)::stored_type;
  auto SPI0_handlers = SPI0::effect_handlers();
  SPI0_handlers.on_read = [this](const SPI0::field_type &read_bits) {
    if (read_bits == reg::state::cleared)
      return;

    acquire_field(RESET.SPI0) = reg::state::cleared;
    acquire_field(RESET_DONE.SPI0) = reg::state::set;
  };
  SPI0::set_effect_handlers(&RESET_DONE.SPI0, SPI0_handlers);

  using SPI1 = decltype(reg::RESET_DONE::SPI1)::stored_type;
  auto SPI1_handlers = SPI1::effect_handlers();
  SPI1_handlers.on_read = [this](const SPI1::field_type &read_bits) {
    if (read_bits == reg::state::set) {
      acquire_field(RESET_DONE.SPI1) = reg::state::cleared;
    }
  };
  SPI1::set_effect_handlers(&RESET_DONE.SPI1, SPI1_handlers);
}

void resets::init_UART_reset_handlers() {
  using UART0 = decltype(reg::RESET::UART0)::stored_type;
  auto UART0_handlers = UART0::effect_handlers();
  UART0_handlers.on_write = [this](UART0::field_type before,
                                   const UART0::field_type &after_write) {
    if (before == reg::state::cleared && after_write == reg::state::set) {
      // Force de/con-structor calls by delete and re-get().
      delete &UART::get(UART::ID::first);
      auto &handle = UART::get(UART::ID::first);

      handle.flush_UART_FIFOs(UART::ID::first);
      acquire_field(RESET_DONE.UART0) = reg::state::set;
    }
  };
  UART0::set_effect_handlers(&RESET.UART0, UART0_handlers);

  using UART1 = decltype(reg::RESET::UART1)::stored_type;
  auto UART1_handlers = UART1::effect_handlers();
  UART1_handlers.on_write = [this](UART1::field_type before,
                                   const UART1::field_type &after_write) {
    if (before == reg::state::cleared && after_write == reg::state::set) {
      // Force de/con-structor calls by delete and re-get().
      delete &UART::get(UART::ID::second);
      auto &handle = UART::get(UART::ID::second);
      
      handle.flush_UART_FIFOs(UART::ID::second);
      acquire_field(RESET_DONE.UART1) = reg::state::set;
    }
  };
  UART1::set_effect_handlers(&RESET.UART1, UART1_handlers);
}

void resets::init_UART_reset_done_handlers() {
  auto &handle = resets::get();
  using UART0 = decltype(reg::RESET_DONE::UART0)::stored_type;
  auto UART0_handlers = UART0::effect_handlers();
  UART0_handlers.on_read = [this, &handle](const UART0::field_type &read_bits) {
    if (read_bits == reg::state::cleared)
      return;

    acquire_field(handle.RESET.UART0) = reg::state::cleared;
    acquire_field(handle.RESET_DONE.UART0) = reg::state::set;
  };
  UART0::set_effect_handlers(&handle.RESET_DONE.UART0, UART0_handlers);

  using UART1 = decltype(reg::RESET_DONE::UART1)::stored_type;
  auto UART1_handlers = UART1::effect_handlers();
  UART1_handlers.on_read = [this, &handle](const UART1::field_type &read_bits) {
    if (read_bits == reg::state::set) {
      acquire_field(handle.RESET_DONE.UART1) = reg::state::cleared;
    }
  };
  UART1::set_effect_handlers(&handle.RESET_DONE.UART1, UART1_handlers);
}

void resets::initialize_effect_handlers(std::size_t) {
  init_UART_reset_handlers();
  init_SPI_reset_handlers();

  init_UART_reset_done_handlers();
  init_SPI_reset_done_handlers();
}

resets::~resets() {}

resets::resets(/* args */) {}
