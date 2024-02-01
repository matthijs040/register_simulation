#include <bit>
#include <concepts>
#include <rp2040/SPI/SPI_peripheral.hpp>
#include <rp2040/UART/UART.hpp>
#include <rp2040/subsystem_resets/resets.hpp>

extern void flush_UART_FIFOs(UART::ID which);

void init_SPI_reset_handlers() {
  auto &handle = resets::get();
  using SPI0 = decltype(reg::RESET::SPI0)::stored_type;
  auto SPI0_handlers = SPI0::effect_handlers();
  SPI0_handlers.on_write = [&handle](SPI0::stored_bits before,
                                     const SPI0::stored_bits &after_write) {
    if (before == reg::state::cleared && after_write == reg::state::set) {
      // Force de/con-structor calls by delete and re-get().
      delete &SPI_peripheral::get(SPI_peripheral::ID::first);
      SPI_peripheral::get(SPI_peripheral::ID::first);

      simulated_peripheral<resets>::acquire_field(handle.RESET_DONE.SPI0) =
          reg::state::set;
    }
  };
  SPI0::set_effect_handlers(&handle.RESET.SPI0, SPI0_handlers);

  using SPI1 = decltype(reg::RESET::SPI1)::stored_type;
  auto SPI1_handlers = SPI1::effect_handlers();
  SPI1_handlers.on_write = [&handle](SPI1::stored_bits before,
                                     const SPI1::stored_bits &after_write) {
    if (before == reg::state::cleared && after_write == reg::state::set) {
      // Force de/con-structor calls by delete and re-get().
      delete &SPI_peripheral::get(SPI_peripheral::ID::second);
      SPI_peripheral::get(SPI_peripheral::ID::second);

      simulated_peripheral<resets>::acquire_field(handle.RESET_DONE.SPI1) =
          reg::state::set;
    }
  };
  SPI1::set_effect_handlers(&handle.RESET.SPI1, SPI1_handlers);
}

void init_SPI_reset_done_handlers() {
  auto &handle = resets::get();
  using SPI0 = decltype(reg::RESET_DONE::SPI0)::stored_type;
  auto SPI0_handlers = SPI0::effect_handlers();
  SPI0_handlers.on_read = [&handle](const SPI0::stored_bits &read_bits) {
    if (read_bits == reg::state::cleared)
      return;

    simulated_peripheral<resets>::acquire_field(handle.RESET.SPI0) =
        reg::state::cleared;
    simulated_peripheral<resets>::acquire_field(handle.RESET_DONE.SPI0) =
        reg::state::set;
  };
  SPI0::set_effect_handlers(&handle.RESET_DONE.SPI0,
                                         SPI0_handlers);

  using SPI1 = decltype(reg::RESET_DONE::SPI1)::stored_type;
  auto SPI1_handlers = SPI1::effect_handlers();
  SPI1_handlers.on_read = [&handle](const SPI1::stored_bits &read_bits) {
    if (read_bits == reg::state::set) {
      simulated_peripheral<resets>::acquire_field(handle.RESET_DONE.SPI1) =
          reg::state::cleared;
    }
  };
  SPI1::set_effect_handlers(&handle.RESET_DONE.SPI1,
                                         SPI1_handlers);
}

void init_UART_reset_handlers() {
  auto &handle = resets::get();
  using UART0 = decltype(reg::RESET::UART0)::stored_type;
  auto UART0_handlers = UART0::effect_handlers();
  UART0_handlers.on_write = [&handle](UART0::stored_bits before,
                                      const UART0::stored_bits &after_write) {
    if (before == reg::state::cleared && after_write == reg::state::set) {
      // Force de/con-structor calls by delete and re-get().
      delete &UART::get(UART::ID::first);
      UART::get(UART::ID::first);

      flush_UART_FIFOs(UART::ID::first);
      simulated_peripheral<resets>::acquire_field(handle.RESET_DONE.UART0) =
          reg::state::set;
    }
  };
  UART0::set_effect_handlers(&handle.RESET.UART0, UART0_handlers);

  using UART1 = decltype(reg::RESET::UART1)::stored_type;
  auto UART1_handlers = UART1::effect_handlers();
  UART1_handlers.on_write = [&handle](UART1::stored_bits before,
                                      const UART1::stored_bits &after_write) {
    if (before == reg::state::cleared && after_write == reg::state::set) {
      // Force de/con-structor calls by delete and re-get().
      delete &UART::get(UART::ID::second);
      UART::get(UART::ID::second);

      flush_UART_FIFOs(UART::ID::second);
      simulated_peripheral<resets>::acquire_field(handle.RESET_DONE.UART1) =
          reg::state::set;
    }
  };
  UART1::set_effect_handlers(&handle.RESET.UART1, UART1_handlers);
}

void init_UART_reset_done_handlers() {
  auto &handle = resets::get();
  using UART0 = decltype(reg::RESET_DONE::UART0)::stored_type;
  auto UART0_handlers = UART0::effect_handlers();
  UART0_handlers.on_read = [&handle](const UART0::stored_bits &read_bits) {
    if (read_bits == reg::state::cleared)
      return;

    simulated_peripheral<resets>::acquire_field(handle.RESET.UART0) =
        reg::state::cleared;
    simulated_peripheral<resets>::acquire_field(handle.RESET_DONE.UART0) =
        reg::state::set;
  };
  UART0::set_effect_handlers(&handle.RESET_DONE.UART0,
                                          UART0_handlers);

  using UART1 = decltype(reg::RESET_DONE::UART1)::stored_type;
  auto UART1_handlers = UART1::effect_handlers();
  UART1_handlers.on_read = [&handle](const UART1::stored_bits &read_bits) {
    if (read_bits == reg::state::set) {
      simulated_peripheral<resets>::acquire_field(handle.RESET_DONE.UART1) =
          reg::state::cleared;
    }
  };
  UART1::set_effect_handlers(&handle.RESET_DONE.UART1,
                                          UART1_handlers);
}

void init_reset_handlers() {
  init_UART_reset_handlers();
  init_SPI_reset_handlers();
}

void init_reset_done_handlers() {
  init_UART_reset_done_handlers();
  init_SPI_reset_done_handlers();
}

void init_resets_handlers() {
  // Set handlers for every CTRL reg in the block.
  init_reset_handlers();
  init_reset_done_handlers();
}

resets &resets::get() noexcept {
  static resets *instance;
  if (instance)
    return *instance;

  instance = new resets();
  if constexpr (reg::mock)
    init_resets_handlers();

  return *instance;
}

resets::~resets() {}

void resets::operator delete(void *) {}

resets::resets(/* args */) {}

void *resets::operator new(std::size_t size) {
  if constexpr (reg::mock)
    return simulated_peripheral<resets>::operator new(size);

  return std::bit_cast<resets *>(base_address);
}