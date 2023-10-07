#include <HAL/GPIO.hpp>
#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <iostream>
#include <utility>
#include <charconv>
#include <cstring>
#include <functional>
#include <variant>
#include <chrono>

constexpr uint8_t LED_pin = PICO_DEFAULT_LED_PIN;

void enable_LED_pin()
{
  auto instance = GPIO(LED_pin);
  if (instance.initialization_result)
  {
    std::cout << "initializing the LED failed with error: " << instance.initialization_result.message() << '\n';
    return;
  }

  auto error = instance.set_pin_mode(GPIO::mode::output_only);
  if (error)
  {
    std::cout << "Setting pin mode to output failed with error: " << error.message() << '\n';
    return;
  }
  error = instance.set_pin_state(GPIO::state::high);
  if (error)
  {
    std::cout << "Setting the pin state to high failed with error: " << error.message() << '\n';
    return;
  }

  const char *state = instance.get_pin_state() == GPIO::state::high ? "high" : "low";
  std::cout << "LED state is now: " << state << "\n";
}

void disable_LED_pin()
{
  auto instance = GPIO(LED_pin);
  instance.set_pin_mode(GPIO::mode::output_only);
  instance.set_pin_state(GPIO::state::low);
  std::cout << "Set LED low.\n";
}

void get_LED_state()
{
  auto instance = GPIO(LED_pin);
  const char *state = instance.get_pin_state() == GPIO::state::high ? "high" : "low";
  std::cout << "LED state is: " << state << '\n';
}

using named_function = std::pair<const char *, std::function<void(void)>>;

static const std::array functions = {
    named_function{"LED.set.high", std::bind(enable_LED_pin)},
    named_function{"LED.set.low", std::bind(disable_LED_pin)},
    named_function{"LED.get", std::bind(get_LED_state)}};

void get_string(std::span<char> data)
{
  std::size_t index = 0;
  while (index < data.size())
  {
    int character = 0;
    while ((character = getchar_timeout_us(1)) == PICO_ERROR_TIMEOUT)
      sleep_ms(1);
    std::cout << static_cast<char>(character);
    std::cout.flush();

    if (character == '\n' || character == '\r')
      break;
    data[index++] = character & 0xFF;
  }
}

int main(int, char const *[])
{
  if (!stdio_init_all())
    return EXIT_FAILURE;

  while (true)
  {
    constexpr size_t max_command_size = 30;
    char storage[max_command_size] = {};
    std::memset(storage, '\0', sizeof(storage));

    std::cout << "Enter command." << std::endl;
    std::span<char> line = {storage, sizeof(storage)};
    get_string(line.subspan(0, line.size() - 1));
    line.back() = '\0';

    std::cout << "gotten line: '" << line.data() << "'" << std::endl;

    const auto found = std::find_if(functions.begin(), functions.end(), [line](named_function fn)
                                    { return std::strlen(line.data()) == std::strlen(fn.first) && std::strcmp(line.data(), fn.first) == 0; });

    if (found != functions.end())
      found->second();
  }
  return EXIT_SUCCESS;
}
