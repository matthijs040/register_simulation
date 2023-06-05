#include <HAL/GPIO.hpp>
#include <cstdlib>
#include <iostream>
#include <pico/stdlib.h>
#include <utility>

int main(int argc, char const *argv[]) {
  const auto LED_pin = PICO_DEFAULT_LED_PIN;

  auto instance = GPIO(LED_pin);
  if (instance.initialization_result)
    return EXIT_FAILURE;

  auto mode = instance.get_pin_mode();
  auto error = instance.set_pin_mode(GPIO::mode::output_only);
  if (error)
    return EXIT_FAILURE;

  while (true) {
    auto error = instance.set_pin_state(
        instance.get_pin_state() == GPIO::state::high ? GPIO::state::low
                                                      : GPIO::state::high);
    if (error)
      return EXIT_FAILURE;
    sleep_ms(1000);
  }
  return EXIT_SUCCESS;
}
