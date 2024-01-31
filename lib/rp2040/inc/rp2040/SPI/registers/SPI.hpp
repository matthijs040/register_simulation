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
  bitfield<uint8_t, 8, 8, reg::mock> SCR;
  bitfield<reg::state, 7, 1, reg::mock> SPH;
  bitfield<reg::state, 6, 1, reg::mock> SPO;

  enum class FRF_states {
    Motorola_format = 0b00,
    Texas_Instruments_format = 0b01,
    National_Microwire_format = 0b10,
  };

  bitfield<FRF_states, 4, 2, reg::mock> FRF;

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
  bitfield<DSS_states, 0, 4, reg::mock> DSS;
};

union SSPCR1 {
  SSPCR1() {}

  bitfield<reg::state, 3, 1, reg::mock> SOD;
  bitfield<reg::state, 2, 1, reg::mock> MS;
  bitfield<reg::state, 1, 1, reg::mock> SSE;
  bitfield<reg::state, 0, 1, reg::mock> LBM;
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
  bitfield<uint16_t, 0, 16, reg::mock> DATA;

  static void read_handler() {}
};

union SSPSR {
  SSPSR() {}

  const bitfield<reg::state, 4, 1, reg::mock> BSY;
  const bitfield<reg::state, 3, 1, reg::mock> RFF;
  const bitfield<reg::state, 2, 1, reg::mock> RNE;
  const bitfield<reg::state, 1, 1, reg::mock> TNF;
  const bitfield<reg::state, 0, 1, reg::mock> TFE;
};

union SSPCPSR {
  SSPCPSR() {}

  /**
   * @brief Clock prescale divisor. Must be an even number from 2-
   * 254, depending on the frequency of SSPCLK. The least
   * significant bit always returns zero on reads.
   */
  bitfield<uint8_t, 0, 8, reg::mock> CPSDVSR;
};

union SSPIMSC {
  SSPIMSC() {}

  bitfield<reg::state, 3, 1, reg::mock> TXIM;
  bitfield<reg::state, 2, 1, reg::mock> RXIM;
  bitfield<reg::state, 1, 1, reg::mock> RTIM;
  bitfield<reg::state, 0, 1, reg::mock> RORIM;
};

union SSPRIS {
  SSPRIS() {}

  const bitfield<reg::state, 3, 1, reg::mock> TXRIS;
  const bitfield<reg::state, 2, 1, reg::mock> RXRIS;
  const bitfield<reg::state, 1, 1, reg::mock> RTRIS;
  const bitfield<reg::state, 0, 1, reg::mock> RORRIS;
};

union SSPMIS {
  SSPMIS() {}

  const bitfield<reg::state, 3, 1, reg::mock> TXMIS;
  const bitfield<reg::state, 2, 1, reg::mock> RXMIS;
  const bitfield<reg::state, 1, 1, reg::mock> RTMIS;
  const bitfield<reg::state, 0, 1, reg::mock> RORMIS;
};

union SSPICR {
  SSPICR() {}

  bitfield<reg::state, 1, 1, reg::mock> RTIC;
  bitfield<reg::state, 0, 1, reg::mock> RORIC;
};

union SSPDMACR {
  SSPDMACR() {}

  bitfield<reg::state, 1, 1, reg::mock> TXDMAE;
  bitfield<reg::state, 0, 1, reg::mock> RXDMAE;
};

union SSPPERIPHID0 {
  SSPPERIPHID0() {}

  const bitfield<uint8_t, 0, 8, reg::mock> PARTNUMBER0;
};

union SSPPERIPHID1 {
  SSPPERIPHID1() {}

  const bitfield<uint8_t, 4, 4, reg::mock> DESIGNER0;
  const bitfield<uint8_t, 0, 4, reg::mock> PARTNUMBER1;
};

union SSPPERIPHID2 {
  SSPPERIPHID2() {}

  const bitfield<uint8_t, 4, 4, reg::mock> REVISION;
  const bitfield<uint8_t, 0, 4, reg::mock> DESIGNER1;
};

union SSPPERIPHID3 {
  SSPPERIPHID3() {}

  const bitfield<uint8_t, 0, 8, reg::mock> CONFIGURATION;
};

union SSPPCELLID0 {
  SSPPCELLID0() {}

  const bitfield<uint8_t, 0, 8, reg::mock> cell_ID;
};

union SSPPCELLID1 {
  SSPPCELLID1() {}

  const bitfield<uint8_t, 0, 8, reg::mock> cell_ID;
};

union SSPPCELLID2 {
  SSPPCELLID2() {}

  const bitfield<uint8_t, 0, 8, reg::mock> cell_ID;
};

union SSPPCELLID3 {
  SSPPCELLID3() {}

  const bitfield<uint8_t, 0, 8, reg::mock> cell_ID;
};

} // namespace SPI
} // namespace reg