#pragma once

#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {
union UARTDR {
  UARTDR() {}

  const bitfield<reg::state, 11, 1, reg::mock> overrun_error;
  const bitfield<reg::state, 10, 1, reg::mock> break_error;
  const bitfield<reg::state, 9, 1, reg::mock> parity_error;
  const bitfield<reg::state, 8, 1, reg::mock> framing_error;
  bitfield<uint8_t, 0, 8, reg::mock> data;
};

union UARTRSR {
  UARTRSR() {}

  bitfield<reg::state, 3, 1, reg::mock> overrun_error;
  bitfield<reg::state, 2, 1, reg::mock> break_error;
  bitfield<reg::state, 1, 1, reg::mock> parity_error;
  bitfield<reg::state, 0, 1, reg::mock> framing_error;
};

union UARTFR {
  UARTFR() {}
  const bitfield<reg::state, 8, 1, reg::mock> ring_indicator;
  const bitfield<reg::state, 7, 1, reg::mock> transmit_FIFO_empty;
  const bitfield<reg::state, 6, 1, reg::mock> receive_FIFO_full;
  const bitfield<reg::state, 5, 1, reg::mock> transmit_FIFO_full;
  const bitfield<reg::state, 4, 1, reg::mock> receive_FIFO_empty;
  const bitfield<reg::state, 3, 1, reg::mock> BUSY;
  const bitfield<reg::state, 2, 1, reg::mock> data_carrier_detect;
  const bitfield<reg::state, 1, 1, reg::mock> data_set_ready;
  const bitfield<reg::state, 0, 1, reg::mock> clear_to_send;
};

union UARTILPR {
  UARTILPR() {}
  bitfield<uint8_t, 0, 8, reg::mock> ILPDVSR;
};

union UARTIBRD {
  UARTIBRD() {}
  bitfield<uint16_t, 0, 16, reg::mock> BAUD_DIVINT;
};

union UARTFBRD {
  UARTFBRD() {}
  bitfield<uint8_t, 0, 6, reg::mock> BAUD_DIVFRAC;
};

union UARTLCR_H {
  UARTLCR_H() {}
  bitfield<reg::state, 7, 1, reg::mock> SPS;

  enum class WLEN_states {
    data_bits_8 = 0b11,
    data_bits_7 = 0b10,
    data_bits_6 = 0b01,
    data_bits_5 = 0b00
  };
  bitfield<WLEN_states, 5, 2, reg::mock> WLEN;
  bitfield<reg::state, 4, 1, reg::mock> FEN;
  bitfield<reg::state, 3, 1, reg::mock> STP2;
  bitfield<reg::state, 2, 1, reg::mock> EPS;
  bitfield<reg::state, 1, 1, reg::mock> PEN;
  bitfield<reg::state, 0, 1, reg::mock> BRK;
};

union UARTCR {
  UARTCR() {}
  bitfield<reg::state, 15, 1, reg::mock> CTSEN;
  bitfield<reg::state, 14, 1, reg::mock> RTSEN;
  bitfield<reg::state, 13, 1, reg::mock> OUT2;
  bitfield<reg::state, 12, 1, reg::mock> OUT1;
  bitfield<reg::state, 11, 1, reg::mock> RTS;
  bitfield<reg::state, 10, 1, reg::mock> DTR;
  bitfield<reg::state, 9, 1, reg::mock> RXE;
  bitfield<reg::state, 8, 1, reg::mock> TXE;
  bitfield<reg::state, 7, 1, reg::mock> LBE;
  bitfield<reg::state, 2, 1, reg::mock> SIRLP;
  bitfield<reg::state, 1, 1, reg::mock> SIREN;
  bitfield<reg::state, 0, 1, reg::mock> UARTEN;
};

union UARTIFLS {
  UARTIFLS() {}

  enum class RXIFLSEL_states {
    eighth_full = 0b000,
    fourth_full = 0b001,
    half_full = 0b010,
    three_quarters_full = 0b011,
    seven_eighths_full = 0b100
  };
  bitfield<RXIFLSEL_states, 3, 3, reg::mock> RXIFLSEL;

  enum class TXIFLSEL_states {
    eighth_full = 0b000,
    fourth_full = 0b001,
    half_full = 0b010,
    three_quarters_full = 0b011,
    seven_eighths_full = 0b100
  };
  bitfield<RXIFLSEL_states, 0, 3, reg::mock> TXIFLSEL;
};

union UARTIMSC {
  UARTIMSC() {}

  bitfield<reg::state, 10, 1, reg::mock> OEIM;
  bitfield<reg::state, 9, 1, reg::mock> BEIM;
  bitfield<reg::state, 8, 1, reg::mock> PEIM;
  bitfield<reg::state, 7, 1, reg::mock> FEIM;
  bitfield<reg::state, 6, 1, reg::mock> RTIM;
  bitfield<reg::state, 5, 1, reg::mock> TXIM;
  bitfield<reg::state, 4, 1, reg::mock> RXIM;
  bitfield<reg::state, 3, 1, reg::mock> DSRMIM;
  bitfield<reg::state, 2, 1, reg::mock> DCDMIM;
  bitfield<reg::state, 1, 1, reg::mock> CTSMIM;
  bitfield<reg::state, 0, 1, reg::mock> RIMIM;
};

union UARTRIS {
  UARTRIS() {}
  const bitfield<reg::state, 10, 1, reg::mock> OERIS;
  const bitfield<reg::state, 9, 1, reg::mock> BERIS;
  const bitfield<reg::state, 8, 1, reg::mock> PERIS;
  const bitfield<reg::state, 7, 1, reg::mock> FERIS;
  const bitfield<reg::state, 6, 1, reg::mock> RTRIS;
  const bitfield<reg::state, 5, 1, reg::mock> TXRIS;
  const bitfield<reg::state, 4, 1, reg::mock> RXRIS;
  const bitfield<reg::state, 3, 1, reg::mock> DSRRMIS;
  const bitfield<reg::state, 2, 1, reg::mock> DCDRMIS;
  const bitfield<reg::state, 1, 1, reg::mock> CTSRMIS;
  const bitfield<reg::state, 0, 1, reg::mock> RIRMIS;
};

union UARTMIS {
  UARTMIS() {}
  const bitfield<reg::state, 10, 1, reg::mock> OEMIS;
  const bitfield<reg::state, 9, 1, reg::mock> BEMIS;
  const bitfield<reg::state, 8, 1, reg::mock> PEMIS;
  const bitfield<reg::state, 7, 1, reg::mock> FEMIS;
  const bitfield<reg::state, 6, 1, reg::mock> RTMIS;
  const bitfield<reg::state, 5, 1, reg::mock> TXMIS;
  const bitfield<reg::state, 4, 1, reg::mock> RXMIS;
  const bitfield<reg::state, 3, 1, reg::mock> DSRMMIS;
  const bitfield<reg::state, 2, 1, reg::mock> DCDMMIS;
  const bitfield<reg::state, 1, 1, reg::mock> CTSMMIS;
  const bitfield<reg::state, 0, 1, reg::mock> RIMMIS;
};

union UARTICR {
  UARTICR() {}

  bitfield<reg::state, 10, 1, reg::mock> OEIC;
  bitfield<reg::state, 9, 1, reg::mock> BEIC;
  bitfield<reg::state, 8, 1, reg::mock> PEIC;
  bitfield<reg::state, 7, 1, reg::mock> FEIC;
  bitfield<reg::state, 6, 1, reg::mock> RTIC;
  bitfield<reg::state, 5, 1, reg::mock> TXIC;
  bitfield<reg::state, 4, 1, reg::mock> RXIC;
  bitfield<reg::state, 3, 1, reg::mock> DSRMIC;
  bitfield<reg::state, 2, 1, reg::mock> DCDIC;
  bitfield<reg::state, 1, 1, reg::mock> CTSIC;
  bitfield<reg::state, 0, 1, reg::mock> RIIC;
};

union UARTDMACR {
  UARTDMACR() {}
  bitfield<reg::state, 2, 1, reg::mock> DMAONERR;
  bitfield<reg::state, 1, 1, reg::mock> TXDMAE;
  bitfield<reg::state, 0, 1, reg::mock> RXDMAE;
};

union UARTPERIPHID0 {
  UARTPERIPHID0() {}
  const bitfield<uint8_t, 0, 8, reg::mock> PARTNUMBER0;
};

union UARTPERIPHID1 {
  UARTPERIPHID1() {}
  const bitfield<uint8_t, 4, 4, reg::mock> DESIGNER0;
  const bitfield<uint8_t, 0, 4, reg::mock> PARTNUMBER1;
};

union UARTPERIPHID2 {
  UARTPERIPHID2() {}
  const bitfield<uint8_t, 4, 4, reg::mock> REVISION;
  const bitfield<uint8_t, 0, 4, reg::mock> DESIGNER1;
};

union UARTPERIPHID3 {
  UARTPERIPHID3() {}
  const bitfield<uint8_t, 0, 8, reg::mock> CONFIGURATION;
};

union UARTPCELLID0 {
  UARTPCELLID0() {}
  const bitfield<uint8_t, 0, 8, reg::mock> PCELLID0;
};

union UARTPCELLID1 {
  UARTPCELLID1() {}
  const bitfield<uint8_t, 0, 8, reg::mock> PCELLID1;
};

union UARTPCELLID2 {
  UARTPCELLID2() {}
  const bitfield<uint8_t, 0, 8, reg::mock> PCELLID2;
};

union UARTPCELLID3 {
  UARTPCELLID3() {}
  const bitfield<uint8_t, 0, 8, reg::mock> PCELLID3;
};
} // namespace reg