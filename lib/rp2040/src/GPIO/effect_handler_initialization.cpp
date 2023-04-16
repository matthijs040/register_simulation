#include <HAL/simulated_device_register.hpp>

#include <rp2040/GPIO/GPIO.hpp>

#include <iostream>

class initializer {
  public:
  initializer();
  ~initializer();
};

void on_CTRL_register_write() {
  // If any of the <functionality>OVER(ride) registers are changed from 0;
  // The STATUS register must show these overrides.
  // If any of the overrides state that the input / outputs are inverted, the
  // STATUS-read handler must invert those bits.
}

void on_CTRL_register_read(register_integral read_value) {
  // Nothing implicitly happens when a CTRL register is read.
}

initializer::initializer() { 
  std::ios_base::Init();
  std::clog << "effect handler is initialized.\n"; 
}

initializer instance = initializer();