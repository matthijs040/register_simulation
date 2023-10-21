#pragma once
#include <HAL/GPIO.hpp>
#include <array>
#include <functional>
#include <variant>

using named_function = std::pair<const char *, std::function<void(const char*)>>;

class application
{
public:
    application(GPIO& LED_handle);
    ~application();

    void run();

private:
    GPIO& LED_handle;

    void enable_LED(const char* stub = "");
    void disable_LED(const char* stub = "");
    void get_LED_state(const char* stub = "");


    void attach_ROSC(const char* stub = "");
    void attach_sys(const char* stub = "");
    void detach_clock(const char* stub = "");
    void set_ROSC_state(const char* state);
    void set_ROSC_devisor(const char* devisor);

    std::array<named_function, 8> RPCs;

};

