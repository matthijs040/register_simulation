#include "application.hpp"
#include <functional>
#include <iostream>

#include <cstring>
#include <span>

#include <pico/stdlib.h>

using named_function = std::pair<const char *, std::function<void(void)>>;

void application::enable_LED()
{
    if (LED_handle.initialization_result)
    {
        std::cout << "initializing the LED failed with error: " << LED_handle.initialization_result.message() << '\n';
        return;
    }

    auto error = LED_handle.set_pin_mode(GPIO::mode::output_only);
    if (error)
    {
        std::cout << "Setting pin mode to output failed with error: " << error.message() << '\n';
        return;
    }
    error = LED_handle.set_pin_state(GPIO::state::high);
    if (error)
    {
        std::cout << "Setting the pin state to high failed with error: " << error.message() << '\n';
        return;
    }

    const char *state = LED_handle.get_pin_state() == GPIO::state::high ? "high" : "low";
    std::cout << "LED state is now: " << state << "\n";
}

void application::disable_LED()
{
    LED_handle.set_pin_mode(GPIO::mode::output_only);
    LED_handle.set_pin_state(GPIO::state::low);
    std::cout << "Set LED low.\n";
}

void application::get_LED_state()
{
    const char *state = LED_handle.get_pin_state() == GPIO::state::high ? "high" : "low";
    std::cout << "LED state is: " << state << '\n';
}

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

application::application(GPIO &LED_handle_)
    : LED_handle(LED_handle_), RPCs({named_function{"LED.set.high", std::bind(&application::enable_LED, this)},
                                     named_function{"LED.set.low", std::bind(&application::disable_LED, this)},
                                     named_function{"LED.get", std::bind(&application::get_LED_state, this)}})
{
}

application::~application()
{
}

void application::run()
{
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

        const auto found = std::find_if(RPCs.begin(), RPCs.end(), [line](named_function fn)
                                        { return std::strlen(line.data()) == std::strlen(fn.first) && std::strcmp(line.data(), fn.first) == 0; });

        if (found != RPCs.end())
            found->second();
    }
}
