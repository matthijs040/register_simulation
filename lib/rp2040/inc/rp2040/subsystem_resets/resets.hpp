#pragma once

#include "registers/resets.hpp"
#include <HAL/simulatable_peripheral.hpp>
#include <cstdint>
#include <type_traits>

class resets : public simulatable_peripheral<resets, reg::mock> {
public:
  reg::RESET RESET;
  reg::WDSEL WDSEL;
  reg::RESET_DONE RESET_DONE;

  ~resets();

private:
  resets(/* args */);

  static constexpr std::array base_addresses = {0x4000c000};

  void init_UART_reset_handlers();

  void init_UART_reset_done_handlers();

  void init_SPI_reset_handlers();

  void init_SPI_reset_done_handlers();

  void initialize_effect_handlers(std::size_t);

  friend simulatable_peripheral<resets, reg::mock>;
};
