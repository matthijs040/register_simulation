#pragma once

#include "registers/SPI.hpp"
#include <cstdint>
#include <HAL/simulatable_peripheral.hpp>
#include <rp2040/shared_types.hpp>
#include <rp2040/subsystem_resets/resets.hpp>
#include <system/fixed_capacity_queue.hpp>
#include <type_traits>

constexpr std::size_t num_SPI_peripherals = 2;
class SPI_peripheral : public simulatable_peripheral<SPI_peripheral, reg::mock,
                                                     num_SPI_peripherals> {
public:
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

  enum ID : std::size_t { first, second };

  ~SPI_peripheral() = default;

private:
  SPI_peripheral(/* args */) : padding_(){};

  void initialize_DR_handlers(SPI_peripheral::ID which) {
    using data_type = decltype(reg::SPI::SSPDR::DATA)::stored_type;

    struct SPI_buffer {
      fixed_capacity_queue<uint16_t, 8> TX_FIFO;
      fixed_capacity_queue<uint16_t, 8> RX_FIFO;
    };

    static std::array<SPI_buffer, num_SPI_peripherals> buffers;
    auto &buffer = buffers.at(std::to_underlying(which));
    auto &handle = get(std::to_underlying(which));

    auto data_handlers = data_type::effect_handlers();
    data_handlers.on_read = [this, &buffer](const data_type::field_type &) {
      if (buffer.RX_FIFO.empty())
        // Doing nothing here will keep the old value.
        // Should it be cleared or is the clearing of "RNE" enough?
        return;

      auto &RX_data = buffer.RX_FIFO.front().value().get();
      // Replace the data in the transfer register.
      acquire_field(SSPDR.DATA) = RX_data;
      // Then shift the active index in the static FIFO.
      buffer.RX_FIFO.pop();

      // Also, if the static FIFO is/becomes empty by this read,
      // Set the FIFO empty flag in the "Flags Register"
      if (buffer.RX_FIFO.empty())
        acquire_field(SSPSR.RNE) = reg::state::cleared;

      // And, regardless of the state of the FIFO before. It certainly isn't
      // full now.
      acquire_field(SSPSR.RFF) = reg::state::cleared;
    };

    data_handlers.on_write =
        [this, &buffer](data_type::field_type,
                        const data_type::field_type &after_write) {
          // If the loopback-enable register is set don't buffer.
          // Just send it into the same SPI_handle's Receive FIFO.
          auto loopback_enabled = SSPCR1.LBM;
          std::cout << "loopback is: "
                    << (loopback_enabled == reg::state::set ? "enabled\n"
                                                            : "disabled\n");
          if (loopback_enabled == reg::state::set) {
            if (SSPSR.RFF == reg::state::set)
              return;

            std::clog << "entering in loopback RX_FIFO.\n";

            // TODO: Write to RX buffer.
            buffer.RX_FIFO.push(after_write);

            acquire_field(SSPSR.RNE) = reg::state::set;

            if (buffer.RX_FIFO.full())
              acquire_field(SSPSR.RFF) = reg::state::set;
            return;
          }

          std::clog << "Buffering in TX_FIFO.\n";
          // Copy over the data to transfer to the TX_FIFO.
          if (!buffer.TX_FIFO.full()) {
            buffer.TX_FIFO.push(after_write);
          }

          // Also, if the FIFO is/becomes full by this write,
          // Set the FIFO full flag in the "Flags Register"
          if (buffer.TX_FIFO.full()) {
            acquire_field(SSPSR.TNF) = reg::state::cleared;
          }
        };

    data_type::set_effect_handlers(&handle.SSPDR, data_handlers);
  }

  void initialize_effect_handlers(std::size_t which) {
    initialize_DR_handlers(static_cast<SPI_peripheral::ID>(which));
  }

  static constexpr std::array base_addresses = {0x4003c000, 0x40040000};

  friend simulatable_peripheral<SPI_peripheral, reg::mock, num_SPI_peripherals>;
  friend resets;
};
