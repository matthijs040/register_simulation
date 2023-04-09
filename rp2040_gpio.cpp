#include "rp2040_gpio.hpp"
#include "gpio.hpp"

#include <iostream>

std::weak_ptr<rp2040_gpio> rp2040_gpio::storage_handle = std::weak_ptr<rp2040_gpio>();

rp2040_gpio::rp2040_gpio()
{
    // TODO: reset registers to enabled but cleared state.
    std::cout << "constructed impl\n";
}

rp2040_gpio::~rp2040_gpio()
{
    // TODO: Set gpio to lowest power state.
    std::cout << "destructed impl\n";
}

gpio::gpio()
    : impl_handle(std::make_shared<rp2040_gpio>())
{
    std::cout << "constructed wrapper\n";
}

gpio::~gpio()
{
    std::cout << "destructed wrapper\n";
}

constexpr std::size_t gpio::get_num_pins() noexcept
{
    return 5u;
}

bool gpio::is_pin_reserved(pin_number number) const noexcept
{
    if (number > get_num_pins() - 1)
        return true;
    return false;
}

void gpio::set_pin_mode(pin_number number, gpio::mode_t mode)
{
}