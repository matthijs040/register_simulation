#pragma once

#include "registers/SPI.hpp"
#include <HAL/simulated_peripheral.hpp>
#include <rp2040/shared_types.hpp>

class SPI_peripheral
    : public std::conditional_t<reg::mock,
                                simulated_peripheral<SPI_peripheral, 2>, void> {
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

  SPI_peripheral(/* args */);
  ~SPI_peripheral();
};

SPI_peripheral::SPI_peripheral(/* args */) : padding_() {}

SPI_peripheral::~SPI_peripheral() {}
