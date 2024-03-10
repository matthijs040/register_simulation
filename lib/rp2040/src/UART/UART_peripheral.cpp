#include <HAL/UART.hpp>
#include <map>
#include <rp2040/UART/UART.hpp>
#include <system/fixed_capacity_queue.hpp>

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

std::array<UART_FIFOs, num_UARTs> &get_FIFO_storage() {
  static std::array<UART_FIFOs, num_UARTs> instance;
  return instance;
}

void UART::write_to_UART(std::size_t which, uint8_t data) {

  auto &FIFOs = get_FIFO_storage()[which];
  FIFOs.write_to_RX_FIFO(data);

  // Clear the receive-FIFO-empty flag in case the FIFO has been empty.
  acquire_field(UARTFR.receive_FIFO_empty) = reg::state::cleared;

  // Also, set receive-full flag if the RX fifo is at capacity.
  acquire_field(UARTFR.receive_FIFO_full) =
      FIFOs.RX_FIFO.size() == FIFO_size + shift_register_size
          ? reg::state::set
          : reg::state::cleared;
}

void UART::flush_UART_FIFOs(std::size_t which) {
  UART_FIFOs &buffer = get_FIFO_storage()[which];
  buffer.flush_FIFOs();

  acquire_field(UARTFR.receive_FIFO_empty) = reg::state::set;
  acquire_field(UARTFR.receive_FIFO_full) = reg::state::cleared;
  acquire_field(UARTFR.transmit_FIFO_empty) = reg::state::set;
  acquire_field(UARTFR.transmit_FIFO_full) = reg::state::cleared;
}

void UART::init_UARTDR_handlers(reg::UARTDR &data_register, std::size_t which) {
  if constexpr(!reg::mock)
    std::unreachable();

  using data_type = decltype(reg::UARTDR::data)::stored_type;

  UART_FIFOs &buffer = get_FIFO_storage()[which];

  auto data_handlers = data_type::effect_handlers();
  data_handlers.on_read = [this, &buffer](const data_type::field_type &) {
    // Replace the data in the transfer register.
    if (!buffer.RX_FIFO.empty()) {
      UART_FIFOs::RX_entry &RX_data = buffer.RX_FIFO.front().value().get();

      acquire_field(UARTDR.overrun_error) =
          RX_data.overrun_error ? reg::state::set : reg::state::cleared;
      acquire_field(UARTDR.parity_error) =
          RX_data.parity_error ? reg::state::set : reg::state::cleared;
      acquire_field(UARTDR.framing_error) =
          RX_data.framing_error ? reg::state::set : reg::state::cleared;
      acquire_field(UARTDR.data) = RX_data.data;

      // Then shift the active index in the static FIFO.
      buffer.RX_FIFO.pop();
    }

    // Also, if the static FIFO is/becomes empty by this read,
    // Set the FIFO empty flag in the "Flags Register"
    if (buffer.RX_FIFO.empty()) {
      acquire_field(UARTFR.receive_FIFO_empty) = reg::state::set;
    }
  };

  data_handlers.on_write = [this, which,
                            &buffer](data_type::field_type,
                                     const data_type::field_type &after_write) {
    // If the LoopBack-Enable register is set don't buffer.
    // Just send it into the same UART's Receive FIFO.
    if (UARTCR.LBE == reg::state::set) {
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
      acquire_field(UARTFR.transmit_FIFO_full) = reg::state::set;
    }
  };

  data_type::set_effect_handlers(&data_register, data_handlers);
}

void UART::initialize_effect_handlers(std::size_t which) {
  init_UARTDR_handlers(UARTDR, which);
}

UART::~UART() {}

UART::UART() : padding__0{}, padding__1{}, padding__2{} {}
