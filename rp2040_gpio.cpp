#include "rp2040_gpio.hpp"
#include <iostream>

std::weak_ptr<rp2040_gpio> rp2040_gpio::storage_handle = std::weak_ptr<rp2040_gpio>();

rp2040_gpio::rp2040_gpio()
{
    // TODO: reset registers to enabled but cleared state.
    std::cout << "constructed\n";
}

rp2040_gpio::~rp2040_gpio()
{
    // TODO: Set gpio to lowest power state. 
    std::cout << "destructed\n";
}

