#include <HAL/UART.hpp>
#include <map>
#include <rp2040/UART/UART.hpp>
#include <system/fixed_capacity_queue.hpp>

static std::array<UART *, num_UART_peripherals> handles;

constexpr std::size_t FIFO_size = 32;
constexpr std::size_t shift_register_size = 1;
struct UART_FIFOs {
  struct RX_entry {
    uint8_t data;
    bool overrun_error;
    bool break_error;
    bool parity_error;
    bool framing_error;
  };

  fixed_capacity_queue<RX_entry, FIFO_size + shift_register_size> RX_FIFO;
  fixed_capacity_queue<uint8_t, FIFO_size + shift_register_size> TX_FIFO;

  UART_FIFOs() : RX_FIFO(), TX_FIFO() {}

  void flush_FIFOs() {
    RX_FIFO.clear();
    TX_FIFO.clear();
  }

  void write_to_RX_FIFO(uint8_t data) {
    // Drop the data if the RX FIFO and shift-register both have data.
    if (RX_FIFO.size() == FIFO_size + shift_register_size)
      return;

    // Otherwise, push data, but add the overflow flag if this is the final
    // entry.
    RX_FIFO.push(
        RX_entry{data, RX_FIFO.size() == FIFO_size, false, false, false});
  }
};

std::array<UART_FIFOs, num_UART_peripherals> &get_FIFO_storage() {
  static std::array<UART_FIFOs, num_UART_peripherals> instance;
  return instance;
}

void write_to_UART(UART::ID which, uint8_t data) {

  auto &FIFOs = get_FIFO_storage()[std::to_underlying(which)];
  FIFOs.write_to_RX_FIFO(data);

  auto &handle = UART::get(which);
  // Clear the receive-FIFO-empty flag in case the FIFO has been empty.
  simulated_peripheral<UART>::acquire_field(handle.UARTFR.receive_FIFO_empty) =
      reg::state::cleared;

  // Also, set receive-full flag if the RX fifo is at capacity.
  simulated_peripheral<UART>::acquire_field(handle.UARTFR.receive_FIFO_full) =
      FIFOs.RX_FIFO.size() == FIFO_size + shift_register_size
          ? reg::state::set
          : reg::state::cleared;
}

void flush_UART_FIFOs(UART::ID which) {
  UART_FIFOs &buffer = get_FIFO_storage()[std::to_underlying(which)];
  buffer.flush_FIFOs();

  auto &handle = UART::get(which);
  simulated_peripheral<UART>::acquire_field(handle.UARTFR.receive_FIFO_empty) =
      reg::state::set;
  simulated_peripheral<UART>::acquire_field(handle.UARTFR.receive_FIFO_full) =
      reg::state::cleared;
  simulated_peripheral<UART>::acquire_field(handle.UARTFR.transmit_FIFO_empty) =
      reg::state::set;
  simulated_peripheral<UART>::acquire_field(handle.UARTFR.transmit_FIFO_full) =
      reg::state::cleared;
}

void init_UARTDR_handlers(reg::UARTDR &data_register, UART::ID which) {
  using data_type = decltype(reg::UARTDR::data);

  UART_FIFOs &buffer = get_FIFO_storage()[std::to_underlying(which)];

  auto data_handlers = data_type::sim_storage::effect_handlers();
  data_handlers.on_read = [which, &buffer](const data_type::stored_bits &) {
    auto &handle = UART::get(which);

    // Replace the data in the transfer register.
    if (!buffer.RX_FIFO.empty()) {
      UART_FIFOs::RX_entry &RX_data = buffer.RX_FIFO.front().value().get();

      simulated_peripheral<UART>::acquire_field(handle.UARTDR.overrun_error) =
          RX_data.overrun_error ? reg::state::set : reg::state::cleared;
      simulated_peripheral<UART>::acquire_field(handle.UARTDR.parity_error) =
          RX_data.parity_error ? reg::state::set : reg::state::cleared;
      simulated_peripheral<UART>::acquire_field(handle.UARTDR.framing_error) =
          RX_data.framing_error ? reg::state::set : reg::state::cleared;
      simulated_peripheral<UART>::acquire_field(handle.UARTDR.data) =
          RX_data.data;

      // Then shift the active index in the static FIFO.
      buffer.RX_FIFO.pop();
    }

    // Also, if the static FIFO is/becomes empty by this read,
    // Set the FIFO empty flag in the "Flags Register"
    if (buffer.RX_FIFO.empty()) {
      simulated_peripheral<UART>::acquire_field(
          handle.UARTFR.receive_FIFO_empty) = reg::state::set;
    }
  };

  data_handlers.on_write =
      [which, &buffer](data_type::stored_bits,
                       const data_type::stored_bits &after_write) {
        auto &handle = UART::get(which);

        // If the LoopBack-Enable register is set don't buffer.
        // Just send it into the same UART's Receive FIFO.
        if (UART::get(which).UARTCR.LBE == reg::state::set) {
          write_to_UART(which, after_write);
          return;
        }

        // Copy over the data to transfer to the TX_FIFO.
        if (buffer.TX_FIFO.size() < FIFO_size) {
          buffer.TX_FIFO.push(after_write);
        }

        // Also, if the FIFO is/becomes full by this write,
        // Set the FIFO full flag in the "Flags Register"
        const bool at_capacity = buffer.TX_FIFO.size() == FIFO_size;
        if (at_capacity) {
          simulated_peripheral<UART>::acquire_field(
              handle.UARTFR.transmit_FIFO_full) = reg::state::set;
        }
      };

  data_type::sim_storage::set_effect_handlers(&data_register, data_handlers);
}

void initialize_UART_handlers(UART &handle, UART::ID which) {
  init_UARTDR_handlers(handle.UARTDR, which);
}

UART &UART::get(UART::ID which) noexcept {
  auto &instance = handles.at(std::to_underlying(which));
  if (instance)
    return *instance;

  instance = new (which) UART();
  if constexpr (reg::mock)
    initialize_UART_handlers(*instance, which);
  return *instance;
}

UART::~UART() {}

void UART::operator delete(void *ptr) {
  for (auto *handle : handles)
    if (handle == ptr)
      handle = nullptr;
}
UART::UART() : padding__0{}, padding__1{}, padding__2{} {}

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