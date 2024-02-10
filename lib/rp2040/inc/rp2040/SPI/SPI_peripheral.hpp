#pragma once

#include "registers/SPI.hpp"
#include <HAL/simulated_peripheral.hpp>
#include <cstdint>
#include <rp2040/shared_types.hpp>
#include <system/fixed_capacity_queue.hpp>
#include <type_traits>

constexpr size_t num_SPI_peripherals = 2;

class SPI_peripheral {
public:
  static constexpr uintptr_t base_address_0 = 0x4003c000;
  static constexpr uintptr_t base_address_1 = 0x40040000;

  reg::SPI::SSPCR0 SSPCR0;
  reg::SPI::SSPCR1 SSPCR1;
  reg::SPI::SSPDR SSPDR;
  reg::SPI::SSPSR SSPSR;
  reg::SPI::SSPCPSR SSPCPSR;
  reg::SPI::SSPIMSC SSPIMSC;
  reg::SPI::SSPRIS SSPRIS;
  reg::SPI::SSPMIS SSPMIS;
  reg::SPI::SSPICR SSPICR;
  reg::SPI::SSPDMACR SSPDMACR;

  // The two literal values here are, in order, the offset-addresses of
  // SSPPERIPHID0 and SSPDMACR. The addition after that is to take into account
  // the space taken by SSPDMACR at its offset address.
  const std::array<uint8_t, 0xFE0 - 0x024 + sizeof(SSPDMACR)> padding_;

  reg::SPI::SSPPERIPHID0 SSPPERIPHID0;
  reg::SPI::SSPPERIPHID1 SSPPERIPHID1;
  reg::SPI::SSPPERIPHID2 SSPPERIPHID2;
  reg::SPI::SSPPERIPHID3 SSPPERIPHID3;

  reg::SPI::SSPPCELLID0 SSPPCELLID0;
  reg::SPI::SSPPCELLID1 SSPPCELLID1;
  reg::SPI::SSPPCELLID2 SSPPCELLID2;
  reg::SPI::SSPPCELLID3 SSPPCELLID3;

  enum class ID : std::size_t { first, second };

  static inline SPI_peripheral &get(ID which) noexcept {
    auto &instance = handles.at(std::to_underlying(which));
    if (instance)
      return *instance;

    instance = new (which) SPI_peripheral();
    if constexpr (reg::mock)
      instance->initialize_SPI_handlers(which);
    return *instance;
  }

  ~SPI_peripheral() = default;
  void operator delete(void *addr) {
    for (auto *handle : handles)
      if (handle == addr)
        handle = nullptr;
  }

private:
  static inline std::array<SPI_peripheral *, num_SPI_peripherals> handles;

  SPI_peripheral(/* args */) : padding_(){};
  void *operator new(std::size_t, SPI_peripheral::ID which) {
    using base = simulated_peripheral<SPI_peripheral>;
    if constexpr (reg::mock)
      return base::operator new(std::to_underlying(which));
    else {
      switch (which) {
      case SPI_peripheral::ID::first:
        return std::bit_cast<SPI_peripheral *>(base_address_0);
      case SPI_peripheral::ID::second:
        return std::bit_cast<SPI_peripheral *>(base_address_1);
      }
      assert(false && "Invalid SPI-peripheral-ID given.");
    }
  }

  void initialize_DR_handlers(SPI_peripheral::ID which) {
    using data_type = decltype(reg::SPI::SSPDR::DATA)::simulated_type;

    struct SPI_buffer {
      fixed_capacity_queue<uint16_t, 8> TX_FIFO;
      fixed_capacity_queue<uint16_t, 8> RX_FIFO;
    };

    static std::array<SPI_buffer, SPI_peripheral::handles.size()> buffers;
    auto &buffer = buffers.at(std::to_underlying(which));
    auto &handle = SPI_peripheral::get(which);

    auto data_handlers = data_type::effect_handlers();
    data_handlers.on_read = [&handle, &buffer](const data_type::stored_bits &) {
      using periph_type = simulated_peripheral<SPI_peripheral>;

      if (buffer.RX_FIFO.empty())
        // Doing nothing here will keep the old value.
        // Should it be cleared or is the clearing of "RNE" enough?
        return;

      auto &RX_data = buffer.RX_FIFO.front().value().get();
      // Replace the data in the transfer register.
      periph_type::acquire_field(handle.SSPDR.DATA) = RX_data;
      // Then shift the active index in the static FIFO.
      buffer.RX_FIFO.pop();

      // Also, if the static FIFO is/becomes empty by this read,
      // Set the FIFO empty flag in the "Flags Register"
      if (buffer.RX_FIFO.empty())
        periph_type::acquire_field(handle.SSPSR.RNE) = reg::state::cleared;

      // And, regardless of the state of the FIFO before. It certainly isn't
      // full now.
      periph_type::acquire_field(handle.SSPSR.RFF) = reg::state::cleared;
    };

    data_handlers.on_write = [&handle, &buffer](
                                 data_type::stored_bits,
                                 const data_type::stored_bits &after_write) {
      // If the loopback-enable register is set don't buffer.
      // Just send it into the same UART's Receive FIFO.
      if (handle.SSPCR1.LBM == reg::state::set) {
        if (handle.SSPSR.RFF == reg::state::set)
          return;

        // TODO: Write to RX buffer.
        return;
      }

      // Copy over the data to transfer to the TX_FIFO.
      if (buffer.TX_FIFO.size() < buffer.TX_FIFO.capacity()) {
        buffer.TX_FIFO.push(after_write);
      }

      // Also, if the FIFO is/becomes full by this write,
      // Set the FIFO full flag in the "Flags Register"
      if (buffer.TX_FIFO.size() == buffer.TX_FIFO.capacity()) {
        simulated_peripheral<SPI_peripheral>::acquire_field(handle.SSPSR.TNF) =
            reg::state::cleared;
      }
    };

    data_type::set_effect_handlers(&handle.SSPDR, data_handlers);
  }

  void initialize_SPI_handlers(SPI_peripheral::ID which) {
    initialize_DR_handlers(which);
  }
};
