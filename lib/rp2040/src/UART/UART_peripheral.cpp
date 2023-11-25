#include <HAL/UART.hpp>
#include <map>
#include <rp2040/UART/UART.hpp>

static std::array<UART *, num_UART_peripherals> handles;

constexpr std::size_t FIFO_size = 32;
struct UART_FIFOs {
  std::array<uint8_t, FIFO_size> RX_FIFO{};
  size_t RX_index{};
  std::array<uint8_t, FIFO_size> TX_FIFO{};
  size_t TX_index{};
};

void init_UARTDR_handlers(reg::UARTDR &data_register, UART::ID which) {
  using data_type = decltype(reg::UARTDR::data);

  static std::map<void *, UART_FIFOs> FIFO_storage;

  auto data_handlers = data_type::sim_storage::effect_handlers();
  data_handlers.on_read = [which, &buffer = FIFO_storage[&data_register]](
                              const data_type::stored_bits &) {
    auto &UARTFR_storage =
        simulated_peripheral<UART>::simulated_register_storage.at(
            std::to_underlying(which) * sizeof(UART) +
            offsetof(UART, UART::UARTFR) / sizeof(UART::UARTFR));

    auto &UARTDR_storage =
        simulated_peripheral<UART>::simulated_register_storage.at(
            std::to_underlying(which) * sizeof(UART) +
            offsetof(UART, UART::UARTDR) / sizeof(UART::UARTDR));

    // Replace the data in the transfer register.
    if (buffer.RX_index) {
      // Do this by assigning the present state...
      UARTDR_storage =
          (UARTDR_storage
           // ... "AND-ed" with the inverse of the shifted data-bitfield ...
           & ~(decltype(reg::UARTDR::data)::max
               << decltype(reg::UARTDR::data)::offset))
          // ... and "OR-ed" with the new state of the data from the FIFO.
          | (buffer.RX_FIFO[buffer.RX_index]
             << decltype(reg::UARTDR::data)::offset);

      // Then shift the active index in the static FIFO.
      buffer.RX_index--;
    }

    // Also, if the static FIFO is/becomes empty by this read,
    // Set the FIFO empty flag in the "Flags Register"
    if (buffer.RX_index == 0) {
      UARTFR_storage = UARTFR_storage |
                       std::to_underlying(reg::state::set)
                           << decltype(reg::UARTFR::receive_FIFO_empty)::offset;
    }
  };

  data_handlers.on_write = [which, &buffer = FIFO_storage[&data_register]](
                               data_type::stored_bits,
                               const data_type::stored_bits &after_write) {
    auto &UARTFR_storage =
        simulated_peripheral<UART>::simulated_register_storage.at(
            std::to_underlying(which) * sizeof(UART) +
            (offsetof(UART, UART::UARTFR) / sizeof(UART::UARTFR)));

    // Copy over the data to transfer to the TX_FIFO.
    if (buffer.TX_index < buffer.TX_FIFO.size()) {
      buffer.TX_FIFO[buffer.TX_index] = after_write;
      buffer.TX_index++;
    }

    // Also, if the FIFO is/becomes full by this write,
    // Set the FIFO full flag in the "Flags Register"
    if (buffer.TX_index >= buffer.TX_FIFO.size()) {
      UARTFR_storage = UARTFR_storage |
                       std::to_underlying(reg::state::set)
                           << decltype(reg::UARTFR::transmit_FIFO_full)::offset;
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