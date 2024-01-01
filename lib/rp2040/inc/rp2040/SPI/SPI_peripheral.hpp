#pragma once

#include "registers/SPI.hpp"
#include <HAL/simulated_peripheral.hpp>
#include <cstdint>
#include <rp2040/shared_types.hpp>
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
  static SPI_peripheral &get(ID which) noexcept;
  ~SPI_peripheral();
  void operator delete(void *addr);

private:
  SPI_peripheral(/* args */);
  void *operator new(std::size_t, SPI_peripheral::ID which);
};

SPI_peripheral::SPI_peripheral(/* args */) : padding_() {}

SPI_peripheral::~SPI_peripheral() {}

static inline std::array<SPI_peripheral *, num_SPI_peripherals> handles;

void initialize_SPI_handlers(SPI_peripheral &handle, SPI_peripheral::ID which) {
}

SPI_peripheral &SPI_peripheral::get(SPI_peripheral::ID which) noexcept {
  auto &instance = handles.at(std::to_underlying(which));
  if (instance)
    return *instance;

  instance = new (which) SPI_peripheral();
  if constexpr (reg::mock)
    initialize_SPI_handlers(*instance, which);
  return *instance;
}

void SPI_peripheral::operator delete(void *ptr) {
  for (auto *handle : handles)
    if (handle == ptr)
      handle = nullptr;
}

void *SPI_peripheral::operator new(std::size_t, SPI_peripheral::ID which) {
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
    std::abort();
  }
}