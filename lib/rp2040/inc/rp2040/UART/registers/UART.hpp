#pragma once
#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {
union UARTDR {
  UARTDR() {}

  const bitfield<reg::state, 11, 1> overrun_error;
  const bitfield<reg::state, 10, 1> break_error;
  const bitfield<reg::state, 9, 1> parity_error;
  const bitfield<reg::state, 8, 1> framing_error;
  bitfield<uint8_t, 0, 8> data;
};

union UARTRSR {
  UARTRSR() {}

  bitfield<reg::state, 3, 1> overrun_error;
  bitfield<reg::state, 2, 1> break_error;
  bitfield<reg::state, 1, 1> parity_error;
  bitfield<reg::state, 0, 1> framing_error;
};

union UARTFR {
  UARTFR() {}
  const bitfield<reg::state, 8, 1> ring_indicator;
  const bitfield<reg::state, 7, 1> transmit_FIFO_empty;
  const bitfield<reg::state, 6, 1> receive_FIFO_full;
  const bitfield<reg::state, 5, 1> transmit_FIFO_full;
  const bitfield<reg::state, 4, 1> receive_FIFO_empty;
  const bitfield<reg::state, 3, 1> BUSY;
  const bitfield<reg::state, 2, 1> data_carrier_detect;
  const bitfield<reg::state, 1, 1> data_set_ready;
  const bitfield<reg::state, 0, 1> clear_to_send;
};

union UARTILPR {
  UARTILPR() {}
  bitfield<uint8_t, 0, 8> ILPDVSR;
};

union UARTIBRD {
  UARTIBRD() {}
  bitfield<uint16_t, 0, 16> BAUD_DIVINT;
};

union UARTFBRD {
  UARTFBRD() {}
  bitfield<uint8_t, 0, 6> BAUD_DIVFRAC;
};

union UARTLCR_H {
  UARTLCR_H() {}
  bitfield<reg::state, 7, 1> SPS;

  enum class WLEN_states {
    data_bits_8 = 0b11,
    data_bits_7 = 0b10,
    data_bits_6 = 0b01,
    data_bits_5 = 0b00
  };
  bitfield<WLEN_states, 5, 2> WLEN;
  bitfield<reg::state, 4, 1> FEN;
  bitfield<reg::state, 3, 1> STP2;
  bitfield<reg::state, 2, 1> EPS;
  bitfield<reg::state, 1, 1> PEN;
  bitfield<reg::state, 0, 1> BRK;
};

union UARTCR {
  UARTCR() {}
  bitfield<reg::state, 15, 1> CTSEN;
  bitfield<reg::state, 14, 1> RTSEN;
  bitfield<reg::state, 13, 1> OUT2;
  bitfield<reg::state, 12, 1> OUT1;
  bitfield<reg::state, 11, 1> RTS;
  bitfield<reg::state, 10, 1> DTR;
  bitfield<reg::state, 9, 1> RXE;
  bitfield<reg::state, 8, 1> TXE;
  bitfield<reg::state, 7, 1> LBE;
  bitfield<reg::state, 2, 1> SIRLP;
  bitfield<reg::state, 1, 1> SIREN;
  bitfield<reg::state, 0, 1> UARTEN;
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
  bitfield<RXIFLSEL_states, 3, 3> RXIFLSEL;

  enum class TXIFLSEL_states {
    eighth_full = 0b000,
    fourth_full = 0b001,
    half_full = 0b010,
    three_quarters_full = 0b011,
    seven_eighths_full = 0b100
  };
  bitfield<RXIFLSEL_states, 0, 3> TXIFLSEL;
};

union UARTIMSC {
  UARTIMSC() {}

  bitfield<reg::state, 10, 1> OEIM;
  bitfield<reg::state, 9, 1> BEIM;
  bitfield<reg::state, 8, 1> PEIM;
  bitfield<reg::state, 7, 1> FEIM;
  bitfield<reg::state, 6, 1> RTIM;
  bitfield<reg::state, 5, 1> TXIM;
  bitfield<reg::state, 4, 1> RXIM;
  bitfield<reg::state, 3, 1> DSRMIM;
  bitfield<reg::state, 2, 1> DCDMIM;
  bitfield<reg::state, 1, 1> CTSMIM;
  bitfield<reg::state, 0, 1> RIMIM;
};

union UARTRIS {
  UARTRIS() {}
  const bitfield<reg::state, 10, 1> OERIS;
  const bitfield<reg::state, 9, 1> BERIS;
  const bitfield<reg::state, 8, 1> PERIS;
  const bitfield<reg::state, 7, 1> FERIS;
  const bitfield<reg::state, 6, 1> RTRIS;
  const bitfield<reg::state, 5, 1> TXRIS;
  const bitfield<reg::state, 4, 1> RXRIS;
  const bitfield<reg::state, 3, 1> DSRRMIS;
  const bitfield<reg::state, 2, 1> DCDRMIS;
  const bitfield<reg::state, 1, 1> CTSRMIS;
  const bitfield<reg::state, 0, 1> RIRMIS;
};

union UARTMIS {
  UARTMIS() {}
  const bitfield<reg::state, 10, 1> OEMIS;
  const bitfield<reg::state, 9, 1> BEMIS;
  const bitfield<reg::state, 8, 1> PEMIS;
  const bitfield<reg::state, 7, 1> FEMIS;
  const bitfield<reg::state, 6, 1> RTMIS;
  const bitfield<reg::state, 5, 1> TXMIS;
  const bitfield<reg::state, 4, 1> RXMIS;
  const bitfield<reg::state, 3, 1> DSRMMIS;
  const bitfield<reg::state, 2, 1> DCDMMIS;
  const bitfield<reg::state, 1, 1> CTSMMIS;
  const bitfield<reg::state, 0, 1> RIMMIS;
};

union UARTICR {
  UARTICR() {}

  bitfield<reg::state, 10, 1> OEIC;
  bitfield<reg::state, 9, 1> BEIC;
  bitfield<reg::state, 8, 1> PEIC;
  bitfield<reg::state, 7, 1> FEIC;
  bitfield<reg::state, 6, 1> RTIC;
  bitfield<reg::state, 5, 1> TXIC;
  bitfield<reg::state, 4, 1> RXIC;
  bitfield<reg::state, 3, 1> DSRMIC;
  bitfield<reg::state, 2, 1> DCDIC;
  bitfield<reg::state, 1, 1> CTSIC;
  bitfield<reg::state, 0, 1> RIIC;
};

union UARTDMACR {
  UARTDMACR() {}
  bitfield<reg::state, 2, 1> DMAONERR;
  bitfield<reg::state, 1, 1> TXDMAE;
  bitfield<reg::state, 0, 1> RXDMAE;
};

union UARTPERIPHID0 {
  UARTPERIPHID0() {}
  const bitfield<uint8_t, 0, 8> PARTNUMBER0;
};

union UARTPERIPHID1 {
  UARTPERIPHID1() {}
  const bitfield<uint8_t, 4, 4> DESIGNER0;
  const bitfield<uint8_t, 0, 4> PARTNUMBER1;
};

union UARTPERIPHID2 {
  UARTPERIPHID2() {}
  const bitfield<uint8_t, 4, 4> REVISION;
  const bitfield<uint8_t, 0, 4> DESIGNER1;
};

union UARTPERIPHID3 {
  UARTPERIPHID3() {}
  const bitfield<uint8_t, 0, 8> CONFIGURATION;
};

union UARTPCELLID0 {
  UARTPCELLID0() {}
  const bitfield<uint8_t, 0, 8> PCELLID0;
};

union UARTPCELLID1 {
  UARTPCELLID1() {}
  const bitfield<uint8_t, 0, 8> PCELLID1;
};

union UARTPCELLID2 {
  UARTPCELLID2() {}
  const bitfield<uint8_t, 0, 8> PCELLID2;
};

union UARTPCELLID3 {
  UARTPCELLID3() {}
  const bitfield<uint8_t, 0, 8> PCELLID3;
};
} // namespace reg