#pragma once
#include <rp2040/shared_types.hpp>
#include <HAL/bitfield.hpp>

namespace reg {

union CPUID {
  CPUID() {}
  enum class processor : register_integral { core_0 = 0, core_1 = 1 };
  reg::field<processor, 0, 1> core_ID;
};

union GPIO_IN {
  GPIO_IN() {}
  const reg::field<reg::state, 0, 1> GPIO_0;
  const reg::field<reg::state, 1, 1> GPIO_1;
  const reg::field<reg::state, 2, 1> GPIO_2;
  const reg::field<reg::state, 3, 1> GPIO_3;
  const reg::field<reg::state, 4, 1> GPIO_4;
  const reg::field<reg::state, 5, 1> GPIO_5;
  const reg::field<reg::state, 6, 1> GPIO_6;
  const reg::field<reg::state, 7, 1> GPIO_7;
  const reg::field<reg::state, 8, 1> GPIO_8;
  const reg::field<reg::state, 9, 1> GPIO_9;
  const reg::field<reg::state, 10, 1> GPIO_10;
  const reg::field<reg::state, 11, 1> GPIO_11;
  const reg::field<reg::state, 12, 1> GPIO_12;
  const reg::field<reg::state, 13, 1> GPIO_13;
  const reg::field<reg::state, 14, 1> GPIO_14;
  const reg::field<reg::state, 15, 1> GPIO_15;
  const reg::field<reg::state, 16, 1> GPIO_16;
  const reg::field<reg::state, 17, 1> GPIO_17;
  const reg::field<reg::state, 18, 1> GPIO_18;
  const reg::field<reg::state, 19, 1> GPIO_19;
  const reg::field<reg::state, 20, 1> GPIO_20;
  const reg::field<reg::state, 21, 1> GPIO_21;
  const reg::field<reg::state, 22, 1> GPIO_22;
  const reg::field<reg::state, 23, 1> GPIO_23;
  const reg::field<reg::state, 24, 1> GPIO_24;
  const reg::field<reg::state, 25, 1> GPIO_25;
  const reg::field<reg::state, 26, 1> GPIO_26;
  const reg::field<reg::state, 27, 1> GPIO_27;
  const reg::field<reg::state, 28, 1> GPIO_28;
  const reg::field<reg::state, 29, 1> GPIO_29;
};

union GPIO_HI_IN {
  GPIO_HI_IN() {}

  const reg::field<reg::state, 0, 1> QSPI_0;
  const reg::field<reg::state, 1, 1> QSPI_1;
  const reg::field<reg::state, 2, 1> QSPI_2;
  const reg::field<reg::state, 3, 1> QSPI_3;
  const reg::field<reg::state, 4, 1> QSPI_4;
  const reg::field<reg::state, 5, 1> QSPI_5;
};

union GPIO_OUT {
  GPIO_OUT() {}
  reg::field<reg::state, 0, 1> GPIO_0;
  reg::field<reg::state, 1, 1> GPIO_1;
  reg::field<reg::state, 2, 1> GPIO_2;
  reg::field<reg::state, 3, 1> GPIO_3;
  reg::field<reg::state, 4, 1> GPIO_4;
  reg::field<reg::state, 5, 1> GPIO_5;
  reg::field<reg::state, 6, 1> GPIO_6;
  reg::field<reg::state, 7, 1> GPIO_7;
  reg::field<reg::state, 8, 1> GPIO_8;
  reg::field<reg::state, 9, 1> GPIO_9;
  reg::field<reg::state, 10, 1> GPIO_10;
  reg::field<reg::state, 11, 1> GPIO_11;
  reg::field<reg::state, 12, 1> GPIO_12;
  reg::field<reg::state, 13, 1> GPIO_13;
  reg::field<reg::state, 14, 1> GPIO_14;
  reg::field<reg::state, 15, 1> GPIO_15;
  reg::field<reg::state, 16, 1> GPIO_16;
  reg::field<reg::state, 17, 1> GPIO_17;
  reg::field<reg::state, 18, 1> GPIO_18;
  reg::field<reg::state, 19, 1> GPIO_19;
  reg::field<reg::state, 20, 1> GPIO_20;
  reg::field<reg::state, 21, 1> GPIO_21;
  reg::field<reg::state, 22, 1> GPIO_22;
  reg::field<reg::state, 23, 1> GPIO_23;
  reg::field<reg::state, 24, 1> GPIO_24;
  reg::field<reg::state, 25, 1> GPIO_25;
  reg::field<reg::state, 26, 1> GPIO_26;
  reg::field<reg::state, 27, 1> GPIO_27;
  reg::field<reg::state, 28, 1> GPIO_28;
  reg::field<reg::state, 29, 1> GPIO_29;
};

union GPIO_OUT_SET {
  GPIO_OUT_SET() {}
  reg::field<reg::state, 0, 1> GPIO_0;
  reg::field<reg::state, 1, 1> GPIO_1;
  reg::field<reg::state, 2, 1> GPIO_2;
  reg::field<reg::state, 3, 1> GPIO_3;
  reg::field<reg::state, 4, 1> GPIO_4;
  reg::field<reg::state, 5, 1> GPIO_5;
  reg::field<reg::state, 6, 1> GPIO_6;
  reg::field<reg::state, 7, 1> GPIO_7;
  reg::field<reg::state, 8, 1> GPIO_8;
  reg::field<reg::state, 9, 1> GPIO_9;
  reg::field<reg::state, 10, 1> GPIO_10;
  reg::field<reg::state, 11, 1> GPIO_11;
  reg::field<reg::state, 12, 1> GPIO_12;
  reg::field<reg::state, 13, 1> GPIO_13;
  reg::field<reg::state, 14, 1> GPIO_14;
  reg::field<reg::state, 15, 1> GPIO_15;
  reg::field<reg::state, 16, 1> GPIO_16;
  reg::field<reg::state, 17, 1> GPIO_17;
  reg::field<reg::state, 18, 1> GPIO_18;
  reg::field<reg::state, 19, 1> GPIO_19;
  reg::field<reg::state, 20, 1> GPIO_20;
  reg::field<reg::state, 21, 1> GPIO_21;
  reg::field<reg::state, 22, 1> GPIO_22;
  reg::field<reg::state, 23, 1> GPIO_23;
  reg::field<reg::state, 24, 1> GPIO_24;
  reg::field<reg::state, 25, 1> GPIO_25;
  reg::field<reg::state, 26, 1> GPIO_26;
  reg::field<reg::state, 27, 1> GPIO_27;
  reg::field<reg::state, 28, 1> GPIO_28;
  reg::field<reg::state, 29, 1> GPIO_29;
};

union GPIO_OUT_CLR {
  GPIO_OUT_CLR() {}
  reg::field<reg::state, 0, 1> GPIO_0;
  reg::field<reg::state, 1, 1> GPIO_1;
  reg::field<reg::state, 2, 1> GPIO_2;
  reg::field<reg::state, 3, 1> GPIO_3;
  reg::field<reg::state, 4, 1> GPIO_4;
  reg::field<reg::state, 5, 1> GPIO_5;
  reg::field<reg::state, 6, 1> GPIO_6;
  reg::field<reg::state, 7, 1> GPIO_7;
  reg::field<reg::state, 8, 1> GPIO_8;
  reg::field<reg::state, 9, 1> GPIO_9;
  reg::field<reg::state, 10, 1> GPIO_10;
  reg::field<reg::state, 11, 1> GPIO_11;
  reg::field<reg::state, 12, 1> GPIO_12;
  reg::field<reg::state, 13, 1> GPIO_13;
  reg::field<reg::state, 14, 1> GPIO_14;
  reg::field<reg::state, 15, 1> GPIO_15;
  reg::field<reg::state, 16, 1> GPIO_16;
  reg::field<reg::state, 17, 1> GPIO_17;
  reg::field<reg::state, 18, 1> GPIO_18;
  reg::field<reg::state, 19, 1> GPIO_19;
  reg::field<reg::state, 20, 1> GPIO_20;
  reg::field<reg::state, 21, 1> GPIO_21;
  reg::field<reg::state, 22, 1> GPIO_22;
  reg::field<reg::state, 23, 1> GPIO_23;
  reg::field<reg::state, 24, 1> GPIO_24;
  reg::field<reg::state, 25, 1> GPIO_25;
  reg::field<reg::state, 26, 1> GPIO_26;
  reg::field<reg::state, 27, 1> GPIO_27;
  reg::field<reg::state, 28, 1> GPIO_28;
  reg::field<reg::state, 29, 1> GPIO_29;
};

union GPIO_OUT_XOR {
  GPIO_OUT_XOR() {}
  reg::field<reg::state, 0, 1> GPIO_0;
  reg::field<reg::state, 1, 1> GPIO_1;
  reg::field<reg::state, 2, 1> GPIO_2;
  reg::field<reg::state, 3, 1> GPIO_3;
  reg::field<reg::state, 4, 1> GPIO_4;
  reg::field<reg::state, 5, 1> GPIO_5;
  reg::field<reg::state, 6, 1> GPIO_6;
  reg::field<reg::state, 7, 1> GPIO_7;
  reg::field<reg::state, 8, 1> GPIO_8;
  reg::field<reg::state, 9, 1> GPIO_9;
  reg::field<reg::state, 10, 1> GPIO_10;
  reg::field<reg::state, 11, 1> GPIO_11;
  reg::field<reg::state, 12, 1> GPIO_12;
  reg::field<reg::state, 13, 1> GPIO_13;
  reg::field<reg::state, 14, 1> GPIO_14;
  reg::field<reg::state, 15, 1> GPIO_15;
  reg::field<reg::state, 16, 1> GPIO_16;
  reg::field<reg::state, 17, 1> GPIO_17;
  reg::field<reg::state, 18, 1> GPIO_18;
  reg::field<reg::state, 19, 1> GPIO_19;
  reg::field<reg::state, 20, 1> GPIO_20;
  reg::field<reg::state, 21, 1> GPIO_21;
  reg::field<reg::state, 22, 1> GPIO_22;
  reg::field<reg::state, 23, 1> GPIO_23;
  reg::field<reg::state, 24, 1> GPIO_24;
  reg::field<reg::state, 25, 1> GPIO_25;
  reg::field<reg::state, 26, 1> GPIO_26;
  reg::field<reg::state, 27, 1> GPIO_27;
  reg::field<reg::state, 28, 1> GPIO_28;
  reg::field<reg::state, 29, 1> GPIO_29;
};

union GPIO_OE {
  GPIO_OE() {}
  reg::field<reg::state, 0, 1> GPIO_0;
  reg::field<reg::state, 1, 1> GPIO_1;
  reg::field<reg::state, 2, 1> GPIO_2;
  reg::field<reg::state, 3, 1> GPIO_3;
  reg::field<reg::state, 4, 1> GPIO_4;
  reg::field<reg::state, 5, 1> GPIO_5;
  reg::field<reg::state, 6, 1> GPIO_6;
  reg::field<reg::state, 7, 1> GPIO_7;
  reg::field<reg::state, 8, 1> GPIO_8;
  reg::field<reg::state, 9, 1> GPIO_9;
  reg::field<reg::state, 10, 1> GPIO_10;
  reg::field<reg::state, 11, 1> GPIO_11;
  reg::field<reg::state, 12, 1> GPIO_12;
  reg::field<reg::state, 13, 1> GPIO_13;
  reg::field<reg::state, 14, 1> GPIO_14;
  reg::field<reg::state, 15, 1> GPIO_15;
  reg::field<reg::state, 16, 1> GPIO_16;
  reg::field<reg::state, 17, 1> GPIO_17;
  reg::field<reg::state, 18, 1> GPIO_18;
  reg::field<reg::state, 19, 1> GPIO_19;
  reg::field<reg::state, 20, 1> GPIO_20;
  reg::field<reg::state, 21, 1> GPIO_21;
  reg::field<reg::state, 22, 1> GPIO_22;
  reg::field<reg::state, 23, 1> GPIO_23;
  reg::field<reg::state, 24, 1> GPIO_24;
  reg::field<reg::state, 25, 1> GPIO_25;
  reg::field<reg::state, 26, 1> GPIO_26;
  reg::field<reg::state, 27, 1> GPIO_27;
  reg::field<reg::state, 28, 1> GPIO_28;
  reg::field<reg::state, 29, 1> GPIO_29;
};

union GPIO_OE_SET {
  GPIO_OE_SET() {}
  reg::field<reg::state, 0, 1> GPIO_0;
  reg::field<reg::state, 1, 1> GPIO_1;
  reg::field<reg::state, 2, 1> GPIO_2;
  reg::field<reg::state, 3, 1> GPIO_3;
  reg::field<reg::state, 4, 1> GPIO_4;
  reg::field<reg::state, 5, 1> GPIO_5;
  reg::field<reg::state, 6, 1> GPIO_6;
  reg::field<reg::state, 7, 1> GPIO_7;
  reg::field<reg::state, 8, 1> GPIO_8;
  reg::field<reg::state, 9, 1> GPIO_9;
  reg::field<reg::state, 10, 1> GPIO_10;
  reg::field<reg::state, 11, 1> GPIO_11;
  reg::field<reg::state, 12, 1> GPIO_12;
  reg::field<reg::state, 13, 1> GPIO_13;
  reg::field<reg::state, 14, 1> GPIO_14;
  reg::field<reg::state, 15, 1> GPIO_15;
  reg::field<reg::state, 16, 1> GPIO_16;
  reg::field<reg::state, 17, 1> GPIO_17;
  reg::field<reg::state, 18, 1> GPIO_18;
  reg::field<reg::state, 19, 1> GPIO_19;
  reg::field<reg::state, 20, 1> GPIO_20;
  reg::field<reg::state, 21, 1> GPIO_21;
  reg::field<reg::state, 22, 1> GPIO_22;
  reg::field<reg::state, 23, 1> GPIO_23;
  reg::field<reg::state, 24, 1> GPIO_24;
  reg::field<reg::state, 25, 1> GPIO_25;
  reg::field<reg::state, 26, 1> GPIO_26;
  reg::field<reg::state, 27, 1> GPIO_27;
  reg::field<reg::state, 28, 1> GPIO_28;
  reg::field<reg::state, 29, 1> GPIO_29;
};

union GPIO_OE_CLR {
  GPIO_OE_CLR() {}
  reg::field<reg::state, 0, 1> GPIO_0;
  reg::field<reg::state, 1, 1> GPIO_1;
  reg::field<reg::state, 2, 1> GPIO_2;
  reg::field<reg::state, 3, 1> GPIO_3;
  reg::field<reg::state, 4, 1> GPIO_4;
  reg::field<reg::state, 5, 1> GPIO_5;
  reg::field<reg::state, 6, 1> GPIO_6;
  reg::field<reg::state, 7, 1> GPIO_7;
  reg::field<reg::state, 8, 1> GPIO_8;
  reg::field<reg::state, 9, 1> GPIO_9;
  reg::field<reg::state, 10, 1> GPIO_10;
  reg::field<reg::state, 11, 1> GPIO_11;
  reg::field<reg::state, 12, 1> GPIO_12;
  reg::field<reg::state, 13, 1> GPIO_13;
  reg::field<reg::state, 14, 1> GPIO_14;
  reg::field<reg::state, 15, 1> GPIO_15;
  reg::field<reg::state, 16, 1> GPIO_16;
  reg::field<reg::state, 17, 1> GPIO_17;
  reg::field<reg::state, 18, 1> GPIO_18;
  reg::field<reg::state, 19, 1> GPIO_19;
  reg::field<reg::state, 20, 1> GPIO_20;
  reg::field<reg::state, 21, 1> GPIO_21;
  reg::field<reg::state, 22, 1> GPIO_22;
  reg::field<reg::state, 23, 1> GPIO_23;
  reg::field<reg::state, 24, 1> GPIO_24;
  reg::field<reg::state, 25, 1> GPIO_25;
  reg::field<reg::state, 26, 1> GPIO_26;
  reg::field<reg::state, 27, 1> GPIO_27;
  reg::field<reg::state, 28, 1> GPIO_28;
  reg::field<reg::state, 29, 1> GPIO_29;
};

union GPIO_OE_XOR {
  GPIO_OE_XOR() {}
  reg::field<reg::state, 0, 1> GPIO_0;
  reg::field<reg::state, 1, 1> GPIO_1;
  reg::field<reg::state, 2, 1> GPIO_2;
  reg::field<reg::state, 3, 1> GPIO_3;
  reg::field<reg::state, 4, 1> GPIO_4;
  reg::field<reg::state, 5, 1> GPIO_5;
  reg::field<reg::state, 6, 1> GPIO_6;
  reg::field<reg::state, 7, 1> GPIO_7;
  reg::field<reg::state, 8, 1> GPIO_8;
  reg::field<reg::state, 9, 1> GPIO_9;
  reg::field<reg::state, 10, 1> GPIO_10;
  reg::field<reg::state, 11, 1> GPIO_11;
  reg::field<reg::state, 12, 1> GPIO_12;
  reg::field<reg::state, 13, 1> GPIO_13;
  reg::field<reg::state, 14, 1> GPIO_14;
  reg::field<reg::state, 15, 1> GPIO_15;
  reg::field<reg::state, 16, 1> GPIO_16;
  reg::field<reg::state, 17, 1> GPIO_17;
  reg::field<reg::state, 18, 1> GPIO_18;
  reg::field<reg::state, 19, 1> GPIO_19;
  reg::field<reg::state, 20, 1> GPIO_20;
  reg::field<reg::state, 21, 1> GPIO_21;
  reg::field<reg::state, 22, 1> GPIO_22;
  reg::field<reg::state, 23, 1> GPIO_23;
  reg::field<reg::state, 24, 1> GPIO_24;
  reg::field<reg::state, 25, 1> GPIO_25;
  reg::field<reg::state, 26, 1> GPIO_26;
  reg::field<reg::state, 27, 1> GPIO_27;
  reg::field<reg::state, 28, 1> GPIO_28;
  reg::field<reg::state, 29, 1> GPIO_29;
};

union GPIO_HI_OUT {
  GPIO_HI_OUT() {}
  reg::field<reg::state, 0, 1> QSPI_0;
  reg::field<reg::state, 1, 1> QSPI_1;
  reg::field<reg::state, 2, 1> QSPI_2;
  reg::field<reg::state, 3, 1> QSPI_3;
  reg::field<reg::state, 4, 1> QSPI_4;
  reg::field<reg::state, 5, 1> QSPI_5;
};

union GPIO_HI_SET {
  GPIO_HI_SET() {}
  reg::field<reg::state, 0, 1> QSPI_0;
  reg::field<reg::state, 1, 1> QSPI_1;
  reg::field<reg::state, 2, 1> QSPI_2;
  reg::field<reg::state, 3, 1> QSPI_3;
  reg::field<reg::state, 4, 1> QSPI_4;
  reg::field<reg::state, 5, 1> QSPI_5;
};

union GPIO_HI_CLR {
  GPIO_HI_CLR() {}
  reg::field<reg::state, 0, 1> QSPI_0;
  reg::field<reg::state, 1, 1> QSPI_1;
  reg::field<reg::state, 2, 1> QSPI_2;
  reg::field<reg::state, 3, 1> QSPI_3;
  reg::field<reg::state, 4, 1> QSPI_4;
  reg::field<reg::state, 5, 1> QSPI_5;
};

union GPIO_HI_XOR {
  GPIO_HI_XOR() {}
  reg::field<reg::state, 0, 1> QSPI_0;
  reg::field<reg::state, 1, 1> QSPI_1;
  reg::field<reg::state, 2, 1> QSPI_2;
  reg::field<reg::state, 3, 1> QSPI_3;
  reg::field<reg::state, 4, 1> QSPI_4;
  reg::field<reg::state, 5, 1> QSPI_5;
};

union GPIO_HI_OE {
  GPIO_HI_OE() {}
  reg::field<reg::state, 0, 1> QSPI_0;
  reg::field<reg::state, 1, 1> QSPI_1;
  reg::field<reg::state, 2, 1> QSPI_2;
  reg::field<reg::state, 3, 1> QSPI_3;
  reg::field<reg::state, 4, 1> QSPI_4;
  reg::field<reg::state, 5, 1> QSPI_5;
};

union GPIO_HI_OE_SET {
  GPIO_HI_OE_SET() {}
  reg::field<reg::state, 0, 1> QSPI_0;
  reg::field<reg::state, 1, 1> QSPI_1;
  reg::field<reg::state, 2, 1> QSPI_2;
  reg::field<reg::state, 3, 1> QSPI_3;
  reg::field<reg::state, 4, 1> QSPI_4;
  reg::field<reg::state, 5, 1> QSPI_5;
};

union GPIO_HI_OE_CLR {
  GPIO_HI_OE_CLR() {}
  reg::field<reg::state, 0, 1> QSPI_0;
  reg::field<reg::state, 1, 1> QSPI_1;
  reg::field<reg::state, 2, 1> QSPI_2;
  reg::field<reg::state, 3, 1> QSPI_3;
  reg::field<reg::state, 4, 1> QSPI_4;
  reg::field<reg::state, 5, 1> QSPI_5;
};

union GPIO_HI_OE_XOR {
  GPIO_HI_OE_XOR() {}
  reg::field<reg::state, 0, 1> QSPI_0;
  reg::field<reg::state, 1, 1> QSPI_1;
  reg::field<reg::state, 2, 1> QSPI_2;
  reg::field<reg::state, 3, 1> QSPI_3;
  reg::field<reg::state, 4, 1> QSPI_4;
  reg::field<reg::state, 5, 1> QSPI_5;
};

union FIFO_ST {
  FIFO_ST() {}
  reg::field<reg::state, 0, 1> ROE; // Read On Empty. Ignored b FIFO.
  reg::field<reg::state, 1, 1> WOF; // Written On Full? Ignored b FIFO.

  // Ready (i.e. has space for more data; Is not full)
  const reg::field<reg::state, 2, 1> RDY;
  // VaLiD (i.e. has data to read; Is not empty)
  const reg::field<reg::state, 3, 1> VLD;
};

union FIFO_WR {
  FIFO_WR() {}
  reg::type<register_integral> value;
};

union FIFO_RD {
  FIFO_RD() {}
  reg::type<register_integral> value;
};

union SPINLOCK_ST {
  SPINLOCK_ST() {}
  enum class spinlock_state : bool { locked = true, unlocked = false };
  reg::field<spinlock_state, 0, 1> lock_0;
  reg::field<spinlock_state, 1, 1> lock_1;
  reg::field<spinlock_state, 2, 1> lock_2;
  reg::field<spinlock_state, 3, 1> lock_3;
  reg::field<spinlock_state, 4, 1> lock_4;
  reg::field<spinlock_state, 5, 1> lock_5;
  reg::field<spinlock_state, 6, 1> lock_6;
  reg::field<spinlock_state, 7, 1> lock_7;
  reg::field<spinlock_state, 8, 1> lock_8;
  reg::field<spinlock_state, 9, 1> lock_9;
  reg::field<spinlock_state, 10, 1> lock_10;
  reg::field<spinlock_state, 11, 1> lock_11;
  reg::field<spinlock_state, 12, 1> lock_12;
  reg::field<spinlock_state, 13, 1> lock_13;
  reg::field<spinlock_state, 14, 1> lock_14;
  reg::field<spinlock_state, 15, 1> lock_15;
  reg::field<spinlock_state, 16, 1> lock_16;
  reg::field<spinlock_state, 17, 1> lock_17;
  reg::field<spinlock_state, 18, 1> lock_18;
  reg::field<spinlock_state, 19, 1> lock_19;
  reg::field<spinlock_state, 20, 1> lock_20;
  reg::field<spinlock_state, 21, 1> lock_21;
  reg::field<spinlock_state, 22, 1> lock_22;
  reg::field<spinlock_state, 23, 1> lock_23;
  reg::field<spinlock_state, 24, 1> lock_24;
  reg::field<spinlock_state, 25, 1> lock_25;
  reg::field<spinlock_state, 26, 1> lock_26;
  reg::field<spinlock_state, 27, 1> lock_27;
  reg::field<spinlock_state, 28, 1> lock_28;
  reg::field<spinlock_state, 29, 1> lock_29;
  reg::field<spinlock_state, 30, 1> lock_30;
  reg::field<spinlock_state, 31, 1> lock_31;
};

union DIV_UDIVIDEND {
  DIV_UDIVIDEND() {}
  reg::type<register_integral> value;
};

union DIV_UDIVISOR {
  DIV_UDIVISOR() {}
  reg::type<register_integral> value;
};

union DIV_SDIVIDEND {
  DIV_SDIVIDEND() {}
  reg::type<register_integral> value;
};

union DIV_SDIVISOR {
  DIV_SDIVISOR() {}
  reg::type<register_integral> value;
};

union DIV_QUOTIENT {
  DIV_QUOTIENT() {}
  reg::type<register_integral> value;
};

union DIV_REMAINDER {
  DIV_REMAINDER() {}
  reg::type<register_integral> value;
};

union DIV_CSR {
  DIV_CSR() {}
  const reg::field<reg::state, 0, 1> READY;
  const reg::field<reg::state, 1, 1> DIRTY;
};

union INTERP0_ACCUM0 {
  INTERP0_ACCUM0() {}
  reg::type<register_integral> value;
};

union INTERP0_ACCUM1 {
  INTERP0_ACCUM1() {}
  reg::type<register_integral> value;
};

union INTERP0_BASE0 {
  INTERP0_BASE0() {}
  reg::type<register_integral> value;
};

union INTERP0_BASE1 {
  INTERP0_BASE1() {}
  reg::type<register_integral> value;
};

union INTERP0_BASE2 {
  INTERP0_BASE2() {}
  reg::type<register_integral> value;
};

union INTERP0_POP_LANE0 {
  INTERP0_POP_LANE0() {}
  const reg::type<register_integral> value;
};

union INTERP0_POP_LANE1 {
  INTERP0_POP_LANE1() {}
  const reg::type<register_integral> value;
};

union INTERP0_POP_FULL {
  INTERP0_POP_FULL() {}
  const reg::type<register_integral> value;
};

union INTERP0_PEEK_LANE0 {
  INTERP0_PEEK_LANE0() {}
  const reg::type<register_integral> value;
};

union INTERP0_PEEK_LANE1 {
  INTERP0_PEEK_LANE1() {}
  const reg::type<register_integral> value;
};

union INTERP0_PEEK_FULL {
  INTERP0_PEEK_FULL() {}
  const reg::type<register_integral> value;
};

union INTERP0_CTRL_LANE0 {
  INTERP0_CTRL_LANE0() {}
  reg::type<register_integral> SHIFT;
  reg::type<register_integral> MASK_LSB;
  reg::type<register_integral> MASK_MSB;
  reg::field<reg::state, 15, 1> SIGNED;
  reg::field<reg::state, 16, 1> CROSS_INPUT;
  reg::field<reg::state, 17, 1> CROSS_RESULT;
  reg::field<reg::state, 18, 1> ADD_RAW;
  reg::type<register_integral> FORCE_MSB;
  reg::field<reg::state, 21, 1> BLEND;
  const reg::field<reg::state, 23, 1> OVERF0;
  const reg::field<reg::state, 24, 1> OVERF1;
  const reg::field<reg::state, 25, 1> OVERF;
};

union INTERP0_CTRL_LANE1 {
  INTERP0_CTRL_LANE1() {}
  reg::type<register_integral> SHIFT;
  reg::type<register_integral> MASK_LSB;
  reg::type<register_integral> MASK_MSB;
  reg::field<reg::state, 15, 1> SIGNED;
  reg::field<reg::state, 16, 1> CROSS_INPUT;
  reg::field<reg::state, 17, 1> CROSS_RESULT;
  reg::field<reg::state, 18, 1> ADD_RAW;
  reg::type<register_integral> FORCE_MSB;
};

union INTERP0_ACCUM0_ADD {
  INTERP0_ACCUM0_ADD() :value(0) {}
  reg::type<register_integral> value;
};

union INTERP0_ACCUM1_ADD {
  INTERP0_ACCUM1_ADD() {}
  reg::type<register_integral> value;
};

union INTERP0_BASE_1AND0 {
  INTERP0_BASE_1AND0() {}
  reg::type<register_integral> value;
};

union INTERP1_ACCUM0 {
  INTERP1_ACCUM0() {}
  reg::type<register_integral> value;
};

union INTERP1_ACCUM1 {
  INTERP1_ACCUM1() {}
  reg::type<register_integral> value;
};

union INTERP1_BASE0 {
  INTERP1_BASE0() {}
  reg::type<register_integral> value;
};

union INTERP1_BASE1 {
  INTERP1_BASE1() {}
  reg::type<register_integral> value;
};

union INTERP1_BASE2 {
  INTERP1_BASE2() {}
  reg::type<register_integral> value;
};

union INTERP1_POP_LANE0 {
  INTERP1_POP_LANE0() {}
  const reg::type<register_integral> value;
};

union INTERP1_POP_LANE1 {
  INTERP1_POP_LANE1() {}
  const reg::type<register_integral> value;
};

union INTERP1_POP_FULL {
  INTERP1_POP_FULL() {}
  const reg::type<register_integral> value;
};

union INTERP1_PEEK_LANE0 {
  INTERP1_PEEK_LANE0() {}
  const reg::type<register_integral> value;
};

union INTERP1_PEEK_LANE1 {
  INTERP1_PEEK_LANE1() {}
  const reg::type<register_integral> value;
};

union INTERP1_PEEK_FULL {
  INTERP1_PEEK_FULL() {}
  const reg::type<register_integral> value;
};

union INTERP1_CTRL_LANE0 {
  INTERP1_CTRL_LANE0() {}
  const reg::field<reg::state, 25, 1> OVERF;
  const reg::field<reg::state, 24, 1> OVERF1;
  const reg::field<reg::state, 23, 1> OVERF0;
  reg::field<reg::state, 22, 1> CLAMP;
  reg::type<register_integral> FORCE_MSB;
  reg::field<reg::state, 18, 1> ADD_RAW;
  reg::field<reg::state, 17, 1> CROSS_RESULT;
  reg::field<reg::state, 16, 1> CROSS_INPUT;
  reg::field<reg::state, 15, 1> SIGNED;
  reg::type<register_integral> MASK_MSB;
  reg::type<register_integral> MASK_LSB;
  reg::type<register_integral> SHIFT;
};

union INTERP1_CTRL_LANE1 {
  INTERP1_CTRL_LANE1() {}
  reg::type<register_integral> FORCE_MSB;
  reg::field<reg::state, 18, 1> ADD_RAW;
  reg::field<reg::state, 17, 1> CROSS_RESULT;
  reg::field<reg::state, 16, 1> CROSS_INPUT;
  reg::field<reg::state, 15, 1> SIGNED;
  reg::type<register_integral> MASK_MSB;
  reg::type<register_integral> MASK_LSB;
  reg::type<register_integral> SHIFT;
};

union INTERP1_ACCUM0_ADD {
  INTERP1_ACCUM0_ADD() {}
  reg::type<register_integral> value;
};

union INTERP1_ACCUM1_ADD {
  INTERP1_ACCUM1_ADD() {}
  reg::type<register_integral> value;
};

union INTERP1_ACCUM1_AND0 {
  INTERP1_ACCUM1_AND0() {}
  reg::type<register_integral> value;
};

union SPINLOCK {
  SPINLOCK() {}
  reg::type<register_integral> value;
};

} // namespace reg
