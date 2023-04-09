#pragma once

#include <memory>
#include <cstdint>
#include <array>

class gpio
{
    public:
    gpio();
    ~gpio();

    using pin_number = std::size_t;
    enum class mode_t
    {
        disabled,
        input_only,
        output_only,
        input_and_output
    };

    static constexpr std::size_t get_num_pins() noexcept;

    bool is_pin_reserved(pin_number number) const noexcept;

    void set_pin_mode(pin_number number, gpio::mode_t mode);

private:
    std::shared_ptr<void> impl_handle;
};
