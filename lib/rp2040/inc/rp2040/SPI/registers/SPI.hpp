#pragma once

#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {
namespace SPI {

union SSPCR0 {
  SSPCR0(){};

  /**
   * @brief Serial clock rate. The value SCR is used to generate the
   * transmit and receive bit rate of the PrimeCell SSP. The bit
   * rate is: F SSPCLK CPSDVSR x (1+SCR) where CPSDVSR is
   * an even value from 2-254, programmed through the
   * SSPCPSR register and SCR is a value from 0-255.
   */
  reg::field<uint8_t, 8, 8> SCR;
  reg::field<reg::state, 7, 1> SPH;
  reg::field<reg::state, 6, 1> SPO;

  enum class FRF_states {
    Motorola_format = 0b00,
    Texas_Instruments_format = 0b01,
    National_Microwire_format = 0b10,
  };

  reg::field<FRF_states, 4, 2> FRF;

  enum class DSS_states {
    data_bits_4 = 0b0011,
    data_bits_5 = 0b0100,
    data_bits_6 = 0b0101,
    data_bits_7 = 0b0110,
    data_bits_8 = 0b0111,
    data_bits_9 = 0b1000,
    data_bits_10 = 0b1001,
    data_bits_11 = 0b1010,
    data_bits_12 = 0b1011,
    data_bits_13 = 0b1100,
    data_bits_14 = 0b1101,
    data_bits_15 = 0b1110,
    data_bits_16 = 0b1111,
  };
  reg::field<DSS_states, 0, 4> DSS;
};

union SSPCR1 {
  SSPCR1() {}

  reg::field<reg::state, 3, 1> SOD;
  reg::field<reg::state, 2, 1> MS;
  reg::field<reg::state, 1, 1> SSE;
  reg::field<reg::state, 0, 1> LBM;
};

union SSPDR {
  SSPDR() {}

  /**
   * @brief Transmit/Receive FIFO: Read Receive FIFO. Write
   * Transmit FIFO. You must right-justify data when the
   * PrimeCell SSP is programmed for a data size that is less
   * than 16 bits. Unused bits at the top are ignored by
   * transmit logic. The receive logic automatically right-
   * justified.
   */
  reg::field<uint16_t, 0, 16> DATA;

  static void read_handler() {}
};

union SSPSR {
  SSPSR() {}

  const reg::field<reg::state, 4, 1> BSY;
  const reg::field<reg::state, 3, 1> RFF;
  const reg::field<reg::state, 2, 1> RNE;
  const reg::field<reg::state, 1, 1> TNF;
  const reg::field<reg::state, 0, 1> TFE;
};

union SSPCPSR {
  SSPCPSR() {}

  /**
   * @brief Clock prescale divisor. Must be an even number from 2-
   * 254, depending on the frequency of SSPCLK. The least
   * significant bit always returns zero on reads.
   */
  reg::field<uint8_t, 0, 8> CPSDVSR;
};

union SSPIMSC {
  SSPIMSC() {}

  reg::field<reg::state, 3, 1> TXIM;
  reg::field<reg::state, 2, 1> RXIM;
  reg::field<reg::state, 1, 1> RTIM;
  reg::field<reg::state, 0, 1> RORIM;
};

union SSPRIS {
  SSPRIS() {}

  const reg::field<reg::state, 3, 1> TXRIS;
  const reg::field<reg::state, 2, 1> RXRIS;
  const reg::field<reg::state, 1, 1> RTRIS;
  const reg::field<reg::state, 0, 1> RORRIS;
};

union SSPMIS {
  SSPMIS() {}

  const reg::field<reg::state, 3, 1> TXMIS;
  const reg::field<reg::state, 2, 1> RXMIS;
  const reg::field<reg::state, 1, 1> RTMIS;
  const reg::field<reg::state, 0, 1> RORMIS;
};

union SSPICR {
  SSPICR() {}

  reg::field<reg::state, 1, 1> RTIC;
  reg::field<reg::state, 0, 1> RORIC;
};

union SSPDMACR {
  SSPDMACR() {}

  reg::field<reg::state, 1, 1> TXDMAE;
  reg::field<reg::state, 0, 1> RXDMAE;
};

union SSPPERIPHID0 {
  SSPPERIPHID0() {}

  const reg::field<uint8_t, 0, 8> PARTNUMBER0;
};

union SSPPERIPHID1 {
  SSPPERIPHID1() {}

  const reg::field<uint8_t, 4, 4> DESIGNER0;
  const reg::field<uint8_t, 0, 4> PARTNUMBER1;
};

union SSPPERIPHID2 {
  SSPPERIPHID2() {}

  const reg::field<uint8_t, 4, 4> REVISION;
  const reg::field<uint8_t, 0, 4> DESIGNER1;
};

union SSPPERIPHID3 {
  SSPPERIPHID3() {}

  const reg::field<uint8_t, 0, 8> CONFIGURATION;
};

union SSPPCELLID0 {
  SSPPCELLID0() {}

  const reg::field<uint8_t, 0, 8> cell_ID;
};

union SSPPCELLID1 {
  SSPPCELLID1() {}

  const reg::field<uint8_t, 0, 8> cell_ID;
};

union SSPPCELLID2 {
  SSPPCELLID2() {}

  const reg::field<uint8_t, 0, 8> cell_ID;
};

union SSPPCELLID3 {
  SSPPCELLID3() {}

  const reg::field<uint8_t, 0, 8> cell_ID;
};

} // namespace SPI
} // namespace reg