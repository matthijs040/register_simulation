#pragma once

#include <memory>
#include <cstdint>
#include <array>

class GPIO
{
    public:
    GPIO();
    ~GPIO();

    using pin_number = std::size_t;
    enum class mode
    {
        disabled,
        reserved,
        input_only,
        output_only,
        input_and_output
    };

    enum class state
    {
        floating,
        high,
        low
    };

    static std::size_t get_num_pins() noexcept;

    bool is_pin_reserved(pin_number number) const noexcept;

    void set_pin_mode(pin_number number, GPIO::mode mode);

    GPIO::mode get_pin_mode(pin_number number);

    void set_pin_state(pin_number number, GPIO::state state);

    GPIO::state get_pin_state(pin_number number);

private:
    std::shared_ptr<void> impl_handle;
};
