#include <HAL/GPIO.hpp>
#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <iostream>
#include <utility>
#include <charconv>
#include <cstring>
#include <functional>
#include <variant>

constexpr uint8_t LED_pin = PICO_DEFAULT_LED_PIN;

void enable_LED_pin()
{
  auto instance = GPIO(LED_pin);
  instance.set_pin_mode(GPIO::mode::output_only);
  instance.set_pin_state(GPIO::state::high);
  std::cout << "Set LED high.\n";
}

void disable_LED_pin()
{
  auto instance = GPIO(LED_pin);
  instance.set_pin_mode(GPIO::mode::output_only);
  instance.set_pin_state(GPIO::state::low);
  std::cout << "Set LED low.\n";
}

using named_function = std::pair<const char *, std::function<void(void)>>;

static const std::array functions = {
    named_function{"LED.set.high", std::bind(enable_LED_pin)},
    named_function{"LED.set.low", std::bind(disable_LED_pin)}};

int main(int, char const *[])
{
  if (!stdio_init_all())
    return EXIT_FAILURE;

  while (true)
  {
    constexpr size_t max_command_size = 30;
    char read_line[max_command_size] = {};

    std::cout << "Enter command.\n";
    if (std::cin.peek() == std::char_traits<char>::eof())
    {
      sleep_ms(1000);
      continue;
    }
    std::cin.getline(read_line, max_command_size - 1);

    const auto found = std::find_if(functions.begin(), functions.end(), [read_line](named_function fn)
                                    { return std::strlen(read_line) == std::strlen(fn.first) && std::strcmp(read_line, fn.first) == 0; });

    if (found != functions.end())
      found->second();
  }
  return EXIT_SUCCESS;
}
