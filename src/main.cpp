#include <HAL/GPIO.hpp>
#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <iostream>
#include <utility>
#include "application.hpp"

constexpr uint8_t LED_pin = PICO_DEFAULT_LED_PIN;

int main(int, char const *[])
{
  if (!stdio_init_all())
    return EXIT_FAILURE;

  auto handle = GPIO(LED_pin);
  if (handle.initialization_result)
  {
    std::cerr << "LED pin failed to initialize with error: " << handle.initialization_result << '\n';
    return EXIT_FAILURE;
  }

  auto application_instance = application(handle);
  application_instance.run();

  return EXIT_SUCCESS;
}
