#pragma once
#include <rp2040/shared_types.hpp>
#include <HAL/bitfield.hpp>

namespace reg {

union CPUID {
  CPUID() {}
  enum class processor : register_integral { core_0 = 0, core_1 = 1 };
  bitfield<processor, 0, 1, reg::mock> core_ID;
};

union GPIO_IN {
  GPIO_IN() {}
  const bitfield<reg::state, 0, 1, reg::mock> GPIO_0;
  const bitfield<reg::state, 1, 1, reg::mock> GPIO_1;
  const bitfield<reg::state, 2, 1, reg::mock> GPIO_2;
  const bitfield<reg::state, 3, 1, reg::mock> GPIO_3;
  const bitfield<reg::state, 4, 1, reg::mock> GPIO_4;
  const bitfield<reg::state, 5, 1, reg::mock> GPIO_5;
  const bitfield<reg::state, 6, 1, reg::mock> GPIO_6;
  const bitfield<reg::state, 7, 1, reg::mock> GPIO_7;
  const bitfield<reg::state, 8, 1, reg::mock> GPIO_8;
  const bitfield<reg::state, 9, 1, reg::mock> GPIO_9;
  const bitfield<reg::state, 10, 1, reg::mock> GPIO_10;
  const bitfield<reg::state, 11, 1, reg::mock> GPIO_11;
  const bitfield<reg::state, 12, 1, reg::mock> GPIO_12;
  const bitfield<reg::state, 13, 1, reg::mock> GPIO_13;
  const bitfield<reg::state, 14, 1, reg::mock> GPIO_14;
  const bitfield<reg::state, 15, 1, reg::mock> GPIO_15;
  const bitfield<reg::state, 16, 1, reg::mock> GPIO_16;
  const bitfield<reg::state, 17, 1, reg::mock> GPIO_17;
  const bitfield<reg::state, 18, 1, reg::mock> GPIO_18;
  const bitfield<reg::state, 19, 1, reg::mock> GPIO_19;
  const bitfield<reg::state, 20, 1, reg::mock> GPIO_20;
  const bitfield<reg::state, 21, 1, reg::mock> GPIO_21;
  const bitfield<reg::state, 22, 1, reg::mock> GPIO_22;
  const bitfield<reg::state, 23, 1, reg::mock> GPIO_23;
  const bitfield<reg::state, 24, 1, reg::mock> GPIO_24;
  const bitfield<reg::state, 25, 1, reg::mock> GPIO_25;
  const bitfield<reg::state, 26, 1, reg::mock> GPIO_26;
  const bitfield<reg::state, 27, 1, reg::mock> GPIO_27;
  const bitfield<reg::state, 28, 1, reg::mock> GPIO_28;
  const bitfield<reg::state, 29, 1, reg::mock> GPIO_29;
};

union GPIO_HI_IN {
  GPIO_HI_IN() {}

  const bitfield<reg::state, 0, 1, reg::mock> QSPI_0;
  const bitfield<reg::state, 1, 1, reg::mock> QSPI_1;
  const bitfield<reg::state, 2, 1, reg::mock> QSPI_2;
  const bitfield<reg::state, 3, 1, reg::mock> QSPI_3;
  const bitfield<reg::state, 4, 1, reg::mock> QSPI_4;
  const bitfield<reg::state, 5, 1, reg::mock> QSPI_5;
};

union GPIO_OUT {
  GPIO_OUT() {}
  bitfield<reg::state, 0, 1, reg::mock> GPIO_0;
  bitfield<reg::state, 1, 1, reg::mock> GPIO_1;
  bitfield<reg::state, 2, 1, reg::mock> GPIO_2;
  bitfield<reg::state, 3, 1, reg::mock> GPIO_3;
  bitfield<reg::state, 4, 1, reg::mock> GPIO_4;
  bitfield<reg::state, 5, 1, reg::mock> GPIO_5;
  bitfield<reg::state, 6, 1, reg::mock> GPIO_6;
  bitfield<reg::state, 7, 1, reg::mock> GPIO_7;
  bitfield<reg::state, 8, 1, reg::mock> GPIO_8;
  bitfield<reg::state, 9, 1, reg::mock> GPIO_9;
  bitfield<reg::state, 10, 1, reg::mock> GPIO_10;
  bitfield<reg::state, 11, 1, reg::mock> GPIO_11;
  bitfield<reg::state, 12, 1, reg::mock> GPIO_12;
  bitfield<reg::state, 13, 1, reg::mock> GPIO_13;
  bitfield<reg::state, 14, 1, reg::mock> GPIO_14;
  bitfield<reg::state, 15, 1, reg::mock> GPIO_15;
  bitfield<reg::state, 16, 1, reg::mock> GPIO_16;
  bitfield<reg::state, 17, 1, reg::mock> GPIO_17;
  bitfield<reg::state, 18, 1, reg::mock> GPIO_18;
  bitfield<reg::state, 19, 1, reg::mock> GPIO_19;
  bitfield<reg::state, 20, 1, reg::mock> GPIO_20;
  bitfield<reg::state, 21, 1, reg::mock> GPIO_21;
  bitfield<reg::state, 22, 1, reg::mock> GPIO_22;
  bitfield<reg::state, 23, 1, reg::mock> GPIO_23;
  bitfield<reg::state, 24, 1, reg::mock> GPIO_24;
  bitfield<reg::state, 25, 1, reg::mock> GPIO_25;
  bitfield<reg::state, 26, 1, reg::mock> GPIO_26;
  bitfield<reg::state, 27, 1, reg::mock> GPIO_27;
  bitfield<reg::state, 28, 1, reg::mock> GPIO_28;
  bitfield<reg::state, 29, 1, reg::mock> GPIO_29;
};

union GPIO_OUT_SET {
  GPIO_OUT_SET() {}
  bitfield<reg::state, 0, 1, reg::mock> GPIO_0;
  bitfield<reg::state, 1, 1, reg::mock> GPIO_1;
  bitfield<reg::state, 2, 1, reg::mock> GPIO_2;
  bitfield<reg::state, 3, 1, reg::mock> GPIO_3;
  bitfield<reg::state, 4, 1, reg::mock> GPIO_4;
  bitfield<reg::state, 5, 1, reg::mock> GPIO_5;
  bitfield<reg::state, 6, 1, reg::mock> GPIO_6;
  bitfield<reg::state, 7, 1, reg::mock> GPIO_7;
  bitfield<reg::state, 8, 1, reg::mock> GPIO_8;
  bitfield<reg::state, 9, 1, reg::mock> GPIO_9;
  bitfield<reg::state, 10, 1, reg::mock> GPIO_10;
  bitfield<reg::state, 11, 1, reg::mock> GPIO_11;
  bitfield<reg::state, 12, 1, reg::mock> GPIO_12;
  bitfield<reg::state, 13, 1, reg::mock> GPIO_13;
  bitfield<reg::state, 14, 1, reg::mock> GPIO_14;
  bitfield<reg::state, 15, 1, reg::mock> GPIO_15;
  bitfield<reg::state, 16, 1, reg::mock> GPIO_16;
  bitfield<reg::state, 17, 1, reg::mock> GPIO_17;
  bitfield<reg::state, 18, 1, reg::mock> GPIO_18;
  bitfield<reg::state, 19, 1, reg::mock> GPIO_19;
  bitfield<reg::state, 20, 1, reg::mock> GPIO_20;
  bitfield<reg::state, 21, 1, reg::mock> GPIO_21;
  bitfield<reg::state, 22, 1, reg::mock> GPIO_22;
  bitfield<reg::state, 23, 1, reg::mock> GPIO_23;
  bitfield<reg::state, 24, 1, reg::mock> GPIO_24;
  bitfield<reg::state, 25, 1, reg::mock> GPIO_25;
  bitfield<reg::state, 26, 1, reg::mock> GPIO_26;
  bitfield<reg::state, 27, 1, reg::mock> GPIO_27;
  bitfield<reg::state, 28, 1, reg::mock> GPIO_28;
  bitfield<reg::state, 29, 1, reg::mock> GPIO_29;
};

union GPIO_OUT_CLR {
  GPIO_OUT_CLR() {}
  bitfield<reg::state, 0, 1, reg::mock> GPIO_0;
  bitfield<reg::state, 1, 1, reg::mock> GPIO_1;
  bitfield<reg::state, 2, 1, reg::mock> GPIO_2;
  bitfield<reg::state, 3, 1, reg::mock> GPIO_3;
  bitfield<reg::state, 4, 1, reg::mock> GPIO_4;
  bitfield<reg::state, 5, 1, reg::mock> GPIO_5;
  bitfield<reg::state, 6, 1, reg::mock> GPIO_6;
  bitfield<reg::state, 7, 1, reg::mock> GPIO_7;
  bitfield<reg::state, 8, 1, reg::mock> GPIO_8;
  bitfield<reg::state, 9, 1, reg::mock> GPIO_9;
  bitfield<reg::state, 10, 1, reg::mock> GPIO_10;
  bitfield<reg::state, 11, 1, reg::mock> GPIO_11;
  bitfield<reg::state, 12, 1, reg::mock> GPIO_12;
  bitfield<reg::state, 13, 1, reg::mock> GPIO_13;
  bitfield<reg::state, 14, 1, reg::mock> GPIO_14;
  bitfield<reg::state, 15, 1, reg::mock> GPIO_15;
  bitfield<reg::state, 16, 1, reg::mock> GPIO_16;
  bitfield<reg::state, 17, 1, reg::mock> GPIO_17;
  bitfield<reg::state, 18, 1, reg::mock> GPIO_18;
  bitfield<reg::state, 19, 1, reg::mock> GPIO_19;
  bitfield<reg::state, 20, 1, reg::mock> GPIO_20;
  bitfield<reg::state, 21, 1, reg::mock> GPIO_21;
  bitfield<reg::state, 22, 1, reg::mock> GPIO_22;
  bitfield<reg::state, 23, 1, reg::mock> GPIO_23;
  bitfield<reg::state, 24, 1, reg::mock> GPIO_24;
  bitfield<reg::state, 25, 1, reg::mock> GPIO_25;
  bitfield<reg::state, 26, 1, reg::mock> GPIO_26;
  bitfield<reg::state, 27, 1, reg::mock> GPIO_27;
  bitfield<reg::state, 28, 1, reg::mock> GPIO_28;
  bitfield<reg::state, 29, 1, reg::mock> GPIO_29;
};

union GPIO_OUT_XOR {
  GPIO_OUT_XOR() {}
  bitfield<reg::state, 0, 1, reg::mock> GPIO_0;
  bitfield<reg::state, 1, 1, reg::mock> GPIO_1;
  bitfield<reg::state, 2, 1, reg::mock> GPIO_2;
  bitfield<reg::state, 3, 1, reg::mock> GPIO_3;
  bitfield<reg::state, 4, 1, reg::mock> GPIO_4;
  bitfield<reg::state, 5, 1, reg::mock> GPIO_5;
  bitfield<reg::state, 6, 1, reg::mock> GPIO_6;
  bitfield<reg::state, 7, 1, reg::mock> GPIO_7;
  bitfield<reg::state, 8, 1, reg::mock> GPIO_8;
  bitfield<reg::state, 9, 1, reg::mock> GPIO_9;
  bitfield<reg::state, 10, 1, reg::mock> GPIO_10;
  bitfield<reg::state, 11, 1, reg::mock> GPIO_11;
  bitfield<reg::state, 12, 1, reg::mock> GPIO_12;
  bitfield<reg::state, 13, 1, reg::mock> GPIO_13;
  bitfield<reg::state, 14, 1, reg::mock> GPIO_14;
  bitfield<reg::state, 15, 1, reg::mock> GPIO_15;
  bitfield<reg::state, 16, 1, reg::mock> GPIO_16;
  bitfield<reg::state, 17, 1, reg::mock> GPIO_17;
  bitfield<reg::state, 18, 1, reg::mock> GPIO_18;
  bitfield<reg::state, 19, 1, reg::mock> GPIO_19;
  bitfield<reg::state, 20, 1, reg::mock> GPIO_20;
  bitfield<reg::state, 21, 1, reg::mock> GPIO_21;
  bitfield<reg::state, 22, 1, reg::mock> GPIO_22;
  bitfield<reg::state, 23, 1, reg::mock> GPIO_23;
  bitfield<reg::state, 24, 1, reg::mock> GPIO_24;
  bitfield<reg::state, 25, 1, reg::mock> GPIO_25;
  bitfield<reg::state, 26, 1, reg::mock> GPIO_26;
  bitfield<reg::state, 27, 1, reg::mock> GPIO_27;
  bitfield<reg::state, 28, 1, reg::mock> GPIO_28;
  bitfield<reg::state, 29, 1, reg::mock> GPIO_29;
};

union GPIO_OE {
  GPIO_OE() {}
  bitfield<reg::state, 0, 1, reg::mock> GPIO_0;
  bitfield<reg::state, 1, 1, reg::mock> GPIO_1;
  bitfield<reg::state, 2, 1, reg::mock> GPIO_2;
  bitfield<reg::state, 3, 1, reg::mock> GPIO_3;
  bitfield<reg::state, 4, 1, reg::mock> GPIO_4;
  bitfield<reg::state, 5, 1, reg::mock> GPIO_5;
  bitfield<reg::state, 6, 1, reg::mock> GPIO_6;
  bitfield<reg::state, 7, 1, reg::mock> GPIO_7;
  bitfield<reg::state, 8, 1, reg::mock> GPIO_8;
  bitfield<reg::state, 9, 1, reg::mock> GPIO_9;
  bitfield<reg::state, 10, 1, reg::mock> GPIO_10;
  bitfield<reg::state, 11, 1, reg::mock> GPIO_11;
  bitfield<reg::state, 12, 1, reg::mock> GPIO_12;
  bitfield<reg::state, 13, 1, reg::mock> GPIO_13;
  bitfield<reg::state, 14, 1, reg::mock> GPIO_14;
  bitfield<reg::state, 15, 1, reg::mock> GPIO_15;
  bitfield<reg::state, 16, 1, reg::mock> GPIO_16;
  bitfield<reg::state, 17, 1, reg::mock> GPIO_17;
  bitfield<reg::state, 18, 1, reg::mock> GPIO_18;
  bitfield<reg::state, 19, 1, reg::mock> GPIO_19;
  bitfield<reg::state, 20, 1, reg::mock> GPIO_20;
  bitfield<reg::state, 21, 1, reg::mock> GPIO_21;
  bitfield<reg::state, 22, 1, reg::mock> GPIO_22;
  bitfield<reg::state, 23, 1, reg::mock> GPIO_23;
  bitfield<reg::state, 24, 1, reg::mock> GPIO_24;
  bitfield<reg::state, 25, 1, reg::mock> GPIO_25;
  bitfield<reg::state, 26, 1, reg::mock> GPIO_26;
  bitfield<reg::state, 27, 1, reg::mock> GPIO_27;
  bitfield<reg::state, 28, 1, reg::mock> GPIO_28;
  bitfield<reg::state, 29, 1, reg::mock> GPIO_29;
};

union GPIO_OE_SET {
  GPIO_OE_SET() {}
  bitfield<reg::state, 0, 1, reg::mock> GPIO_0;
  bitfield<reg::state, 1, 1, reg::mock> GPIO_1;
  bitfield<reg::state, 2, 1, reg::mock> GPIO_2;
  bitfield<reg::state, 3, 1, reg::mock> GPIO_3;
  bitfield<reg::state, 4, 1, reg::mock> GPIO_4;
  bitfield<reg::state, 5, 1, reg::mock> GPIO_5;
  bitfield<reg::state, 6, 1, reg::mock> GPIO_6;
  bitfield<reg::state, 7, 1, reg::mock> GPIO_7;
  bitfield<reg::state, 8, 1, reg::mock> GPIO_8;
  bitfield<reg::state, 9, 1, reg::mock> GPIO_9;
  bitfield<reg::state, 10, 1, reg::mock> GPIO_10;
  bitfield<reg::state, 11, 1, reg::mock> GPIO_11;
  bitfield<reg::state, 12, 1, reg::mock> GPIO_12;
  bitfield<reg::state, 13, 1, reg::mock> GPIO_13;
  bitfield<reg::state, 14, 1, reg::mock> GPIO_14;
  bitfield<reg::state, 15, 1, reg::mock> GPIO_15;
  bitfield<reg::state, 16, 1, reg::mock> GPIO_16;
  bitfield<reg::state, 17, 1, reg::mock> GPIO_17;
  bitfield<reg::state, 18, 1, reg::mock> GPIO_18;
  bitfield<reg::state, 19, 1, reg::mock> GPIO_19;
  bitfield<reg::state, 20, 1, reg::mock> GPIO_20;
  bitfield<reg::state, 21, 1, reg::mock> GPIO_21;
  bitfield<reg::state, 22, 1, reg::mock> GPIO_22;
  bitfield<reg::state, 23, 1, reg::mock> GPIO_23;
  bitfield<reg::state, 24, 1, reg::mock> GPIO_24;
  bitfield<reg::state, 25, 1, reg::mock> GPIO_25;
  bitfield<reg::state, 26, 1, reg::mock> GPIO_26;
  bitfield<reg::state, 27, 1, reg::mock> GPIO_27;
  bitfield<reg::state, 28, 1, reg::mock> GPIO_28;
  bitfield<reg::state, 29, 1, reg::mock> GPIO_29;
};

union GPIO_OE_CLR {
  GPIO_OE_CLR() {}
  bitfield<reg::state, 0, 1, reg::mock> GPIO_0;
  bitfield<reg::state, 1, 1, reg::mock> GPIO_1;
  bitfield<reg::state, 2, 1, reg::mock> GPIO_2;
  bitfield<reg::state, 3, 1, reg::mock> GPIO_3;
  bitfield<reg::state, 4, 1, reg::mock> GPIO_4;
  bitfield<reg::state, 5, 1, reg::mock> GPIO_5;
  bitfield<reg::state, 6, 1, reg::mock> GPIO_6;
  bitfield<reg::state, 7, 1, reg::mock> GPIO_7;
  bitfield<reg::state, 8, 1, reg::mock> GPIO_8;
  bitfield<reg::state, 9, 1, reg::mock> GPIO_9;
  bitfield<reg::state, 10, 1, reg::mock> GPIO_10;
  bitfield<reg::state, 11, 1, reg::mock> GPIO_11;
  bitfield<reg::state, 12, 1, reg::mock> GPIO_12;
  bitfield<reg::state, 13, 1, reg::mock> GPIO_13;
  bitfield<reg::state, 14, 1, reg::mock> GPIO_14;
  bitfield<reg::state, 15, 1, reg::mock> GPIO_15;
  bitfield<reg::state, 16, 1, reg::mock> GPIO_16;
  bitfield<reg::state, 17, 1, reg::mock> GPIO_17;
  bitfield<reg::state, 18, 1, reg::mock> GPIO_18;
  bitfield<reg::state, 19, 1, reg::mock> GPIO_19;
  bitfield<reg::state, 20, 1, reg::mock> GPIO_20;
  bitfield<reg::state, 21, 1, reg::mock> GPIO_21;
  bitfield<reg::state, 22, 1, reg::mock> GPIO_22;
  bitfield<reg::state, 23, 1, reg::mock> GPIO_23;
  bitfield<reg::state, 24, 1, reg::mock> GPIO_24;
  bitfield<reg::state, 25, 1, reg::mock> GPIO_25;
  bitfield<reg::state, 26, 1, reg::mock> GPIO_26;
  bitfield<reg::state, 27, 1, reg::mock> GPIO_27;
  bitfield<reg::state, 28, 1, reg::mock> GPIO_28;
  bitfield<reg::state, 29, 1, reg::mock> GPIO_29;
};

union GPIO_OE_XOR {
  GPIO_OE_XOR() {}
  bitfield<reg::state, 0, 1, reg::mock> GPIO_0;
  bitfield<reg::state, 1, 1, reg::mock> GPIO_1;
  bitfield<reg::state, 2, 1, reg::mock> GPIO_2;
  bitfield<reg::state, 3, 1, reg::mock> GPIO_3;
  bitfield<reg::state, 4, 1, reg::mock> GPIO_4;
  bitfield<reg::state, 5, 1, reg::mock> GPIO_5;
  bitfield<reg::state, 6, 1, reg::mock> GPIO_6;
  bitfield<reg::state, 7, 1, reg::mock> GPIO_7;
  bitfield<reg::state, 8, 1, reg::mock> GPIO_8;
  bitfield<reg::state, 9, 1, reg::mock> GPIO_9;
  bitfield<reg::state, 10, 1, reg::mock> GPIO_10;
  bitfield<reg::state, 11, 1, reg::mock> GPIO_11;
  bitfield<reg::state, 12, 1, reg::mock> GPIO_12;
  bitfield<reg::state, 13, 1, reg::mock> GPIO_13;
  bitfield<reg::state, 14, 1, reg::mock> GPIO_14;
  bitfield<reg::state, 15, 1, reg::mock> GPIO_15;
  bitfield<reg::state, 16, 1, reg::mock> GPIO_16;
  bitfield<reg::state, 17, 1, reg::mock> GPIO_17;
  bitfield<reg::state, 18, 1, reg::mock> GPIO_18;
  bitfield<reg::state, 19, 1, reg::mock> GPIO_19;
  bitfield<reg::state, 20, 1, reg::mock> GPIO_20;
  bitfield<reg::state, 21, 1, reg::mock> GPIO_21;
  bitfield<reg::state, 22, 1, reg::mock> GPIO_22;
  bitfield<reg::state, 23, 1, reg::mock> GPIO_23;
  bitfield<reg::state, 24, 1, reg::mock> GPIO_24;
  bitfield<reg::state, 25, 1, reg::mock> GPIO_25;
  bitfield<reg::state, 26, 1, reg::mock> GPIO_26;
  bitfield<reg::state, 27, 1, reg::mock> GPIO_27;
  bitfield<reg::state, 28, 1, reg::mock> GPIO_28;
  bitfield<reg::state, 29, 1, reg::mock> GPIO_29;
};

union GPIO_HI_OUT {
  GPIO_HI_OUT() {}
  bitfield<reg::state, 0, 1, reg::mock> QSPI_0;
  bitfield<reg::state, 1, 1, reg::mock> QSPI_1;
  bitfield<reg::state, 2, 1, reg::mock> QSPI_2;
  bitfield<reg::state, 3, 1, reg::mock> QSPI_3;
  bitfield<reg::state, 4, 1, reg::mock> QSPI_4;
  bitfield<reg::state, 5, 1, reg::mock> QSPI_5;
};

union GPIO_HI_SET {
  GPIO_HI_SET() {}
  bitfield<reg::state, 0, 1, reg::mock> QSPI_0;
  bitfield<reg::state, 1, 1, reg::mock> QSPI_1;
  bitfield<reg::state, 2, 1, reg::mock> QSPI_2;
  bitfield<reg::state, 3, 1, reg::mock> QSPI_3;
  bitfield<reg::state, 4, 1, reg::mock> QSPI_4;
  bitfield<reg::state, 5, 1, reg::mock> QSPI_5;
};

union GPIO_HI_CLR {
  GPIO_HI_CLR() {}
  bitfield<reg::state, 0, 1, reg::mock> QSPI_0;
  bitfield<reg::state, 1, 1, reg::mock> QSPI_1;
  bitfield<reg::state, 2, 1, reg::mock> QSPI_2;
  bitfield<reg::state, 3, 1, reg::mock> QSPI_3;
  bitfield<reg::state, 4, 1, reg::mock> QSPI_4;
  bitfield<reg::state, 5, 1, reg::mock> QSPI_5;
};

union GPIO_HI_XOR {
  GPIO_HI_XOR() {}
  bitfield<reg::state, 0, 1, reg::mock> QSPI_0;
  bitfield<reg::state, 1, 1, reg::mock> QSPI_1;
  bitfield<reg::state, 2, 1, reg::mock> QSPI_2;
  bitfield<reg::state, 3, 1, reg::mock> QSPI_3;
  bitfield<reg::state, 4, 1, reg::mock> QSPI_4;
  bitfield<reg::state, 5, 1, reg::mock> QSPI_5;
};

union GPIO_HI_OE {
  GPIO_HI_OE() {}
  bitfield<reg::state, 0, 1, reg::mock> QSPI_0;
  bitfield<reg::state, 1, 1, reg::mock> QSPI_1;
  bitfield<reg::state, 2, 1, reg::mock> QSPI_2;
  bitfield<reg::state, 3, 1, reg::mock> QSPI_3;
  bitfield<reg::state, 4, 1, reg::mock> QSPI_4;
  bitfield<reg::state, 5, 1, reg::mock> QSPI_5;
};

union GPIO_HI_OE_SET {
  GPIO_HI_OE_SET() {}
  bitfield<reg::state, 0, 1, reg::mock> QSPI_0;
  bitfield<reg::state, 1, 1, reg::mock> QSPI_1;
  bitfield<reg::state, 2, 1, reg::mock> QSPI_2;
  bitfield<reg::state, 3, 1, reg::mock> QSPI_3;
  bitfield<reg::state, 4, 1, reg::mock> QSPI_4;
  bitfield<reg::state, 5, 1, reg::mock> QSPI_5;
};

union GPIO_HI_OE_CLR {
  GPIO_HI_OE_CLR() {}
  bitfield<reg::state, 0, 1, reg::mock> QSPI_0;
  bitfield<reg::state, 1, 1, reg::mock> QSPI_1;
  bitfield<reg::state, 2, 1, reg::mock> QSPI_2;
  bitfield<reg::state, 3, 1, reg::mock> QSPI_3;
  bitfield<reg::state, 4, 1, reg::mock> QSPI_4;
  bitfield<reg::state, 5, 1, reg::mock> QSPI_5;
};

union GPIO_HI_OE_XOR {
  GPIO_HI_OE_XOR() {}
  bitfield<reg::state, 0, 1, reg::mock> QSPI_0;
  bitfield<reg::state, 1, 1, reg::mock> QSPI_1;
  bitfield<reg::state, 2, 1, reg::mock> QSPI_2;
  bitfield<reg::state, 3, 1, reg::mock> QSPI_3;
  bitfield<reg::state, 4, 1, reg::mock> QSPI_4;
  bitfield<reg::state, 5, 1, reg::mock> QSPI_5;
};

union FIFO_ST {
  FIFO_ST() {}
  bitfield<reg::state, 0, 1, reg::mock> ROE; // Read On Empty. Ignored b, reg::mocky FIFO.
  bitfield<reg::state, 1, 1, reg::mock> WOF; // Written On Full? Ignored b, reg::mocky FIFO.

  // Ready (i.e. has space for more data; Is not full)
  const bitfield<reg::state, 2, 1, reg::mock> RDY;
  // VaLiD (i.e. has data to read; Is not empty)
  const bitfield<reg::state, 3, 1, reg::mock> VLD;
};

union FIFO_WR {
  FIFO_WR() {}
  register_storage<reg::mock> value;
};

union FIFO_RD {
  FIFO_RD() {}
  register_storage<reg::mock> value;
};

union SPINLOCK_ST {
  SPINLOCK_ST() {}
  enum class spinlock_state : bool { locked = true, unlocked = false };
  bitfield<spinlock_state, 0, 1, reg::mock> lock_0;
  bitfield<spinlock_state, 1, 1, reg::mock> lock_1;
  bitfield<spinlock_state, 2, 1, reg::mock> lock_2;
  bitfield<spinlock_state, 3, 1, reg::mock> lock_3;
  bitfield<spinlock_state, 4, 1, reg::mock> lock_4;
  bitfield<spinlock_state, 5, 1, reg::mock> lock_5;
  bitfield<spinlock_state, 6, 1, reg::mock> lock_6;
  bitfield<spinlock_state, 7, 1, reg::mock> lock_7;
  bitfield<spinlock_state, 8, 1, reg::mock> lock_8;
  bitfield<spinlock_state, 9, 1, reg::mock> lock_9;
  bitfield<spinlock_state, 10, 1, reg::mock> lock_10;
  bitfield<spinlock_state, 11, 1, reg::mock> lock_11;
  bitfield<spinlock_state, 12, 1, reg::mock> lock_12;
  bitfield<spinlock_state, 13, 1, reg::mock> lock_13;
  bitfield<spinlock_state, 14, 1, reg::mock> lock_14;
  bitfield<spinlock_state, 15, 1, reg::mock> lock_15;
  bitfield<spinlock_state, 16, 1, reg::mock> lock_16;
  bitfield<spinlock_state, 17, 1, reg::mock> lock_17;
  bitfield<spinlock_state, 18, 1, reg::mock> lock_18;
  bitfield<spinlock_state, 19, 1, reg::mock> lock_19;
  bitfield<spinlock_state, 20, 1, reg::mock> lock_20;
  bitfield<spinlock_state, 21, 1, reg::mock> lock_21;
  bitfield<spinlock_state, 22, 1, reg::mock> lock_22;
  bitfield<spinlock_state, 23, 1, reg::mock> lock_23;
  bitfield<spinlock_state, 24, 1, reg::mock> lock_24;
  bitfield<spinlock_state, 25, 1, reg::mock> lock_25;
  bitfield<spinlock_state, 26, 1, reg::mock> lock_26;
  bitfield<spinlock_state, 27, 1, reg::mock> lock_27;
  bitfield<spinlock_state, 28, 1, reg::mock> lock_28;
  bitfield<spinlock_state, 29, 1, reg::mock> lock_29;
  bitfield<spinlock_state, 30, 1, reg::mock> lock_30;
  bitfield<spinlock_state, 31, 1, reg::mock> lock_31;
};

union DIV_UDIVIDEND {
  DIV_UDIVIDEND() {}
  register_storage<reg::mock> value;
};

union DIV_UDIVISOR {
  DIV_UDIVISOR() {}
  register_storage<reg::mock> value;
};

union DIV_SDIVIDEND {
  DIV_SDIVIDEND() {}
  register_storage<reg::mock> value;
};

union DIV_SDIVISOR {
  DIV_SDIVISOR() {}
  register_storage<reg::mock> value;
};

union DIV_QUOTIENT {
  DIV_QUOTIENT() {}
  register_storage<reg::mock> value;
};

union DIV_REMAINDER {
  DIV_REMAINDER() {}
  register_storage<reg::mock> value;
};

union DIV_CSR {
  DIV_CSR() {}
  const bitfield<reg::state, 0, 1, reg::mock> READY;
  const bitfield<reg::state, 1, 1, reg::mock> DIRTY;
};

union INTERP0_ACCUM0 {
  INTERP0_ACCUM0() {}
  register_storage<reg::mock> value;
};

union INTERP0_ACCUM1 {
  INTERP0_ACCUM1() {}
  register_storage<reg::mock> value;
};

union INTERP0_BASE0 {
  INTERP0_BASE0() {}
  register_storage<reg::mock> value;
};

union INTERP0_BASE1 {
  INTERP0_BASE1() {}
  register_storage<reg::mock> value;
};

union INTERP0_BASE2 {
  INTERP0_BASE2() {}
  register_storage<reg::mock> value;
};

union INTERP0_POP_LANE0 {
  INTERP0_POP_LANE0() {}
  const register_storage<reg::mock> value;
};

union INTERP0_POP_LANE1 {
  INTERP0_POP_LANE1() {}
  const register_storage<reg::mock> value;
};

union INTERP0_POP_FULL {
  INTERP0_POP_FULL() {}
  const register_storage<reg::mock> value;
};

union INTERP0_PEEK_LANE0 {
  INTERP0_PEEK_LANE0() {}
  const register_storage<reg::mock> value;
};

union INTERP0_PEEK_LANE1 {
  INTERP0_PEEK_LANE1() {}
  const register_storage<reg::mock> value;
};

union INTERP0_PEEK_FULL {
  INTERP0_PEEK_FULL() {}
  const register_storage<reg::mock> value;
};

union INTERP0_CTRL_LANE0 {
  INTERP0_CTRL_LANE0() {}
  register_storage<reg::mock> SHIFT;
  register_storage<reg::mock> MASK_LSB;
  register_storage<reg::mock> MASK_MSB;
  bitfield<reg::state, 15, 1, reg::mock> SIGNED;
  bitfield<reg::state, 16, 1, reg::mock> CROSS_INPUT;
  bitfield<reg::state, 17, 1, reg::mock> CROSS_RESULT;
  bitfield<reg::state, 18, 1, reg::mock> ADD_RAW;
  register_storage<reg::mock> FORCE_MSB;
  bitfield<reg::state, 21, 1, reg::mock> BLEND;
  const bitfield<reg::state, 23, 1, reg::mock> OVERF0;
  const bitfield<reg::state, 24, 1, reg::mock> OVERF1;
  const bitfield<reg::state, 25, 1, reg::mock> OVERF;
};

union INTERP0_CTRL_LANE1 {
  INTERP0_CTRL_LANE1() {}
  register_storage<reg::mock> SHIFT;
  register_storage<reg::mock> MASK_LSB;
  register_storage<reg::mock> MASK_MSB;
  bitfield<reg::state, 15, 1, reg::mock> SIGNED;
  bitfield<reg::state, 16, 1, reg::mock> CROSS_INPUT;
  bitfield<reg::state, 17, 1, reg::mock> CROSS_RESULT;
  bitfield<reg::state, 18, 1, reg::mock> ADD_RAW;
  register_storage<reg::mock> FORCE_MSB;
};

union INTERP0_ACCUM0_ADD {
  INTERP0_ACCUM0_ADD() :value(0) {}
  register_storage<reg::mock> value;
};

union INTERP0_ACCUM1_ADD {
  INTERP0_ACCUM1_ADD() {}
  register_storage<reg::mock> value;
};

union INTERP0_BASE_1AND0 {
  INTERP0_BASE_1AND0() {}
  register_storage<reg::mock> value;
};

union INTERP1_ACCUM0 {
  INTERP1_ACCUM0() {}
  register_storage<reg::mock> value;
};

union INTERP1_ACCUM1 {
  INTERP1_ACCUM1() {}
  register_storage<reg::mock> value;
};

union INTERP1_BASE0 {
  INTERP1_BASE0() {}
  register_storage<reg::mock> value;
};

union INTERP1_BASE1 {
  INTERP1_BASE1() {}
  register_storage<reg::mock> value;
};

union INTERP1_BASE2 {
  INTERP1_BASE2() {}
  register_storage<reg::mock> value;
};

union INTERP1_POP_LANE0 {
  INTERP1_POP_LANE0() {}
  const register_storage<reg::mock> value;
};

union INTERP1_POP_LANE1 {
  INTERP1_POP_LANE1() {}
  const register_storage<reg::mock> value;
};

union INTERP1_POP_FULL {
  INTERP1_POP_FULL() {}
  const register_storage<reg::mock> value;
};

union INTERP1_PEEK_LANE0 {
  INTERP1_PEEK_LANE0() {}
  const register_storage<reg::mock> value;
};

union INTERP1_PEEK_LANE1 {
  INTERP1_PEEK_LANE1() {}
  const register_storage<reg::mock> value;
};

union INTERP1_PEEK_FULL {
  INTERP1_PEEK_FULL() {}
  const register_storage<reg::mock> value;
};

union INTERP1_CTRL_LANE0 {
  INTERP1_CTRL_LANE0() {}
  const bitfield<reg::state, 25, 1, reg::mock> OVERF;
  const bitfield<reg::state, 24, 1, reg::mock> OVERF1;
  const bitfield<reg::state, 23, 1, reg::mock> OVERF0;
  bitfield<reg::state, 22, 1, reg::mock> CLAMP;
  register_storage<reg::mock> FORCE_MSB;
  bitfield<reg::state, 18, 1, reg::mock> ADD_RAW;
  bitfield<reg::state, 17, 1, reg::mock> CROSS_RESULT;
  bitfield<reg::state, 16, 1, reg::mock> CROSS_INPUT;
  bitfield<reg::state, 15, 1, reg::mock> SIGNED;
  register_storage<reg::mock> MASK_MSB;
  register_storage<reg::mock> MASK_LSB;
  register_storage<reg::mock> SHIFT;
};

union INTERP1_CTRL_LANE1 {
  INTERP1_CTRL_LANE1() {}
  register_storage<reg::mock> FORCE_MSB;
  bitfield<reg::state, 18, 1, reg::mock> ADD_RAW;
  bitfield<reg::state, 17, 1, reg::mock> CROSS_RESULT;
  bitfield<reg::state, 16, 1, reg::mock> CROSS_INPUT;
  bitfield<reg::state, 15, 1, reg::mock> SIGNED;
  register_storage<reg::mock> MASK_MSB;
  register_storage<reg::mock> MASK_LSB;
  register_storage<reg::mock> SHIFT;
};

union INTERP1_ACCUM0_ADD {
  INTERP1_ACCUM0_ADD() {}
  register_storage<reg::mock> value;
};

union INTERP1_ACCUM1_ADD {
  INTERP1_ACCUM1_ADD() {}
  register_storage<reg::mock> value;
};

union INTERP1_ACCUM1_AND0 {
  INTERP1_ACCUM1_AND0() {}
  register_storage<reg::mock> value;
};

union SPINLOCK {
  SPINLOCK() {}
  register_storage<reg::mock> value;
};

} // namespace reg
