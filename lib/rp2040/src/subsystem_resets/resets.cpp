#include <bit>
#include <concepts>
#include <rp2040/UART/UART.hpp>
#include <rp2040/subsystem_resets/resets.hpp>

void init_reset_handlers() {
  auto &handle = resets::get();
  using UART0 = decltype(reg::RESET::UART0);
  auto UART0_handlers = UART0::sim_storage::effect_handlers();
  UART0_handlers.on_write = [](UART0::stored_bits before,
                               const UART0::stored_bits &after_write) {
    if (before == reg::state::cleared && after_write == reg::state::set) {
      // Force de/con-structor calls by delete and re-get().
      delete &UART::get(UART::ID::first);
      UART::get(UART::ID::first) // Perform a dummy write to a register to
                                 // ensure it is called.
          .UARTLCR_H.BRK = reg::state::disabled;
      auto &reset_done =
          simulated_peripheral<resets>::simulated_register_storage.at(2);
      reset_done = reset_done | std::to_underlying(reg::state::set)
                                    << decltype(reg::RESET_DONE::UART0)::offset;
    }
  };
  UART0::sim_storage::set_effect_handlers(&handle.RESET.UART0, UART0_handlers);

  using UART1 = decltype(reg::RESET::UART1);
  auto UART1_handlers = UART1::sim_storage::effect_handlers();
  UART1_handlers.on_write = [](UART1::stored_bits before,
                               const UART1::stored_bits &after_write) {
    if (before == reg::state::cleared && after_write == reg::state::set) {
      // Force de/con-structor calls by delete and re-get().
      delete &UART::get(UART::ID::first);
      UART::get(UART::ID::first) // Perform a dummy write to a register to
                                 // ensure it is called.
          .UARTLCR_H.BRK = reg::state::disabled;
      auto &reset_done =
          simulated_peripheral<resets>::simulated_register_storage.at(2);
      reset_done = reset_done | std::to_underlying(reg::state::set)
                                    << decltype(reg::RESET_DONE::UART1)::offset;
    }
  };
  UART1::sim_storage::set_effect_handlers(&handle.RESET.UART1, UART1_handlers);
}

void init_reset_done_handlers() {
  auto &handle = resets::get();
  using UART0 = decltype(reg::RESET_DONE::UART0);
  auto UART0_handlers = UART0::sim_storage::effect_handlers();
  UART0_handlers.on_read = [](const UART0::stored_bits &read_bits) {
    if (read_bits == reg::state::set) {
      auto &working_bit =
          simulated_peripheral<resets>::simulated_register_storage.at(
              offsetof(resets, resets::RESET));
      working_bit = working_bit | std::to_underlying(reg::state::cleared)
                                      << decltype(reg::RESET::UART0)::offset;
      auto &done_bit =
          simulated_peripheral<resets>::simulated_register_storage.at(2);
      done_bit = done_bit | std::to_underlying(reg::state::set)
                                << decltype(reg::RESET_DONE::UART0)::offset;
    }
  };
  UART0::sim_storage::set_effect_handlers(&handle.RESET_DONE.UART0,
                                          UART0_handlers);

  using UART1 = decltype(reg::RESET_DONE::UART1);
  auto UART1_handlers = UART1::sim_storage::effect_handlers();
  UART1_handlers.on_read = [](const UART1::stored_bits &read_bits) {
    if (read_bits == reg::state::set) {
      auto &done_read =
          simulated_peripheral<resets>::simulated_register_storage.at(
              offsetof(resets, resets::RESET_DONE));
      done_read = done_read | std::to_underlying(reg::state::cleared)
                                  << decltype(reg::RESET_DONE::UART1)::offset;
    }
  };
  UART1::sim_storage::set_effect_handlers(&handle.RESET_DONE.UART1,
                                          UART1_handlers);
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