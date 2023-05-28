#include <HAL/GPIO.hpp>
#include <cstdlib>
#include <iostream>
#include <pico/stdlib.h>
#include <utility>

int main(int argc, char const *argv[]) {
  const auto LED_pin = PICO_DEFAULT_LED_PIN;

  auto instance = GPIO(LED_pin);
  std::cout << "initialization-result was: " << instance.initialization_result
            << "\n";

  if (instance.initialization_result)
    return EXIT_FAILURE;

  const auto mode = instance.get_pin_mode();
  std::cout << "pre-GPIO_init() mode: " << std::to_underlying(mode) << "\n";
  gpio_init(LED_pin);
  std::cout << "pre-GPIO_init() mode: " << std::to_underlying(mode) << "\n";

  // gpio_set_dir(LED_pin, GPIO_OUT);
  // while (true) {
  //   gpio_put(LED_pin, true);
  //   std::cout << "high: " << std::to_underlying(instance.get_pin_state())
  //             << "\n";
  //   sleep_ms(250);
  //   gpio_put(LED_pin, false);
  //   std::cout << "low: " << std::to_underlying(instance.get_pin_state())
  //             << "\n";
  //   sleep_ms(250);
  // }
  return EXIT_SUCCESS;
}
