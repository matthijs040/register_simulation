#pragma once

#include <HAL/bitfield.hpp>
#include <rp2040/shared_types.hpp>

namespace reg {
union UARTDR {
  UARTDR() {}

  const reg::field<reg::state, 11, 1> overrun_error;
  const reg::field<reg::state, 10, 1> break_error;
  const reg::field<reg::state, 9, 1> parity_error;
  const reg::field<reg::state, 8, 1> framing_error;
  reg::field<uint8_t, 0, 8> data;
};

union UARTRSR {
  UARTRSR() {}

  reg::field<reg::state, 3, 1> overrun_error;
  reg::field<reg::state, 2, 1> break_error;
  reg::field<reg::state, 1, 1> parity_error;
  reg::field<reg::state, 0, 1> framing_error;
};

union UARTFR {
  UARTFR() {}
  const reg::field<reg::state, 8, 1> ring_indicator;
  const reg::field<reg::state, 7, 1> transmit_FIFO_empty;
  const reg::field<reg::state, 6, 1> receive_FIFO_full;
  const reg::field<reg::state, 5, 1> transmit_FIFO_full;
  const reg::field<reg::state, 4, 1> receive_FIFO_empty;
  const reg::field<reg::state, 3, 1> BUSY;
  const reg::field<reg::state, 2, 1> data_carrier_detect;
  const reg::field<reg::state, 1, 1> data_set_ready;
  const reg::field<reg::state, 0, 1> clear_to_send;
};

union UARTILPR {
  UARTILPR() {}
  reg::field<uint8_t, 0, 8> ILPDVSR;
};

union UARTIBRD {
  UARTIBRD() {}
  reg::field<uint16_t, 0, 16> BAUD_DIVINT;
};

union UARTFBRD {
  UARTFBRD() {}
  reg::field<uint8_t, 0, 6> BAUD_DIVFRAC;
};

union UARTLCR_H {
  UARTLCR_H() {}
  reg::field<reg::state, 7, 1> SPS;

  enum class WLEN_states {
    data_bits_8 = 0b11,
    data_bits_7 = 0b10,
    data_bits_6 = 0b01,
    data_bits_5 = 0b00
  };
  reg::field<WLEN_states, 5, 2> WLEN;
  reg::field<reg::state, 4, 1> FEN;
  reg::field<reg::state, 3, 1> STP2;
  reg::field<reg::state, 2, 1> EPS;
  reg::field<reg::state, 1, 1> PEN;
  reg::field<reg::state, 0, 1> BRK;
};

union UARTCR {
  UARTCR() {}
  reg::field<reg::state, 15, 1> CTSEN;
  reg::field<reg::state, 14, 1> RTSEN;
  reg::field<reg::state, 13, 1> OUT2;
  reg::field<reg::state, 12, 1> OUT1;
  reg::field<reg::state, 11, 1> RTS;
  reg::field<reg::state, 10, 1> DTR;
  reg::field<reg::state, 9, 1> RXE;
  reg::field<reg::state, 8, 1> TXE;
  reg::field<reg::state, 7, 1> LBE;
  reg::field<reg::state, 2, 1> SIRLP;
  reg::field<reg::state, 1, 1> SIREN;
  reg::field<reg::state, 0, 1> UARTEN;
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
  reg::field<RXIFLSEL_states, 3, 3> RXIFLSEL;

  enum class TXIFLSEL_states {
    eighth_full = 0b000,
    fourth_full = 0b001,
    half_full = 0b010,
    three_quarters_full = 0b011,
    seven_eighths_full = 0b100
  };
  reg::field<RXIFLSEL_states, 0, 3> TXIFLSEL;
};

union UARTIMSC {
  UARTIMSC() {}

  reg::field<reg::state, 10, 1> OEIM;
  reg::field<reg::state, 9, 1> BEIM;
  reg::field<reg::state, 8, 1> PEIM;
  reg::field<reg::state, 7, 1> FEIM;
  reg::field<reg::state, 6, 1> RTIM;
  reg::field<reg::state, 5, 1> TXIM;
  reg::field<reg::state, 4, 1> RXIM;
  reg::field<reg::state, 3, 1> DSRMIM;
  reg::field<reg::state, 2, 1> DCDMIM;
  reg::field<reg::state, 1, 1> CTSMIM;
  reg::field<reg::state, 0, 1> RIMIM;
};

union UARTRIS {
  UARTRIS() {}
  const reg::field<reg::state, 10, 1> OERIS;
  const reg::field<reg::state, 9, 1> BERIS;
  const reg::field<reg::state, 8, 1> PERIS;
  const reg::field<reg::state, 7, 1> FERIS;
  const reg::field<reg::state, 6, 1> RTRIS;
  const reg::field<reg::state, 5, 1> TXRIS;
  const reg::field<reg::state, 4, 1> RXRIS;
  const reg::field<reg::state, 3, 1> DSRRMIS;
  const reg::field<reg::state, 2, 1> DCDRMIS;
  const reg::field<reg::state, 1, 1> CTSRMIS;
  const reg::field<reg::state, 0, 1> RIRMIS;
};

union UARTMIS {
  UARTMIS() {}
  const reg::field<reg::state, 10, 1> OEMIS;
  const reg::field<reg::state, 9, 1> BEMIS;
  const reg::field<reg::state, 8, 1> PEMIS;
  const reg::field<reg::state, 7, 1> FEMIS;
  const reg::field<reg::state, 6, 1> RTMIS;
  const reg::field<reg::state, 5, 1> TXMIS;
  const reg::field<reg::state, 4, 1> RXMIS;
  const reg::field<reg::state, 3, 1> DSRMMIS;
  const reg::field<reg::state, 2, 1> DCDMMIS;
  const reg::field<reg::state, 1, 1> CTSMMIS;
  const reg::field<reg::state, 0, 1> RIMMIS;
};

union UARTICR {
  UARTICR() {}

  reg::field<reg::state, 10, 1> OEIC;
  reg::field<reg::state, 9, 1> BEIC;
  reg::field<reg::state, 8, 1> PEIC;
  reg::field<reg::state, 7, 1> FEIC;
  reg::field<reg::state, 6, 1> RTIC;
  reg::field<reg::state, 5, 1> TXIC;
  reg::field<reg::state, 4, 1> RXIC;
  reg::field<reg::state, 3, 1> DSRMIC;
  reg::field<reg::state, 2, 1> DCDIC;
  reg::field<reg::state, 1, 1> CTSIC;
  reg::field<reg::state, 0, 1> RIIC;
};

union UARTDMACR {
  UARTDMACR() {}
  reg::field<reg::state, 2, 1> DMAONERR;
  reg::field<reg::state, 1, 1> TXDMAE;
  reg::field<reg::state, 0, 1> RXDMAE;
};

union UARTPERIPHID0 {
  UARTPERIPHID0() {}
  const reg::field<uint8_t, 0, 8> PARTNUMBER0;
};

union UARTPERIPHID1 {
  UARTPERIPHID1() {}
  const reg::field<uint8_t, 4, 4> DESIGNER0;
  const reg::field<uint8_t, 0, 4> PARTNUMBER1;
};

union UARTPERIPHID2 {
  UARTPERIPHID2() {}
  const reg::field<uint8_t, 4, 4> REVISION;
  const reg::field<uint8_t, 0, 4> DESIGNER1;
};

union UARTPERIPHID3 {
  UARTPERIPHID3() {}
  const reg::field<uint8_t, 0, 8> CONFIGURATION;
};

union UARTPCELLID0 {
  UARTPCELLID0() {}
  const reg::field<uint8_t, 0, 8> PCELLID0;
};

union UARTPCELLID1 {
  UARTPCELLID1() {}
  const reg::field<uint8_t, 0, 8> PCELLID1;
};

union UARTPCELLID2 {
  UARTPCELLID2() {}
  const reg::field<uint8_t, 0, 8> PCELLID2;
};

union UARTPCELLID3 {
  UARTPCELLID3() {}
  const reg::field<uint8_t, 0, 8> PCELLID3;
};
} // namespace reg