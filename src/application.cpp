#include "application.hpp"
#include <functional>
#include <iostream>

#include <cstring>
#include <span>

#include <pico/stdlib.h>
#include <hardware/clocks.h>

#include <rp2040/time/clocks.hpp>
#include <rp2040/GPIO/user_IO.hpp>

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

void application::attach_ROSC()
{
    auto &pin_handle = user_IO::get();
    if (pin_handle.GPIO21_CTRL.FUNCSEL != reg::CTRL::FUNCSEL_states::disabled)
    {
        std::cerr << "Pin to expose clock signal on is occupied.\n";
        return;
    }
    pin_handle.GPIO21_CTRL.FUNCSEL = reg::CTRL::FUNCSEL_states::Clock_GPIO;

    auto &clock_handle = clocks::get();
    clock_handle.CLK_GPOUT0_CTRL.AUXSRC = reg::CLK_GPOUT_CTRL::AUXSRC_states::rosc_clksrc;
    clock_handle.CLK_GPOUT0_DIV.INT = 1u;
    clock_handle.CLK_GPOUT0_DIV.FRAC = 0u;
    clock_handle.CLK_GPOUT0_CTRL.ENABLE = reg::state::enabled;
}

void application::detach_clock()
{
    // Detach by making clock index " clk_gpout* " sourceless?
    // Cannot do that. Each allowed source value is a clock signal.
    // Just disable the output.
    auto &clock_handle = clocks::get();
    clock_handle.CLK_GPOUT0_CTRL.ENABLE = reg::state::disabled;
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
                                     named_function{"LED.get", std::bind(&application::get_LED_state, this)},
                                     named_function{"CLK.attach.ROSC", std::bind(&application::attach_ROSC, this)},
                                     named_function{"CLK.detach", std::bind(&application::detach_clock, this)}})
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
