#pragma once
#include <HAL/GPIO.hpp>
#include <array>
#include <functional>

using named_function = std::pair<const char *, std::function<void(void)>>;


class application
{
public:
    application(GPIO& LED_handle);
    ~application();

    void run();

private:
    GPIO& LED_handle;

    void enable_LED();
    void disable_LED();
    void get_LED_state();

    std::array<named_function, 3> RPCs;

};

