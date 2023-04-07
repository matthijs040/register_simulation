#include "gpio.hpp"
#include <iostream>

std::weak_ptr<gpio> gpio::storage_handle = std::weak_ptr<gpio>();

gpio::gpio()
{
    // TODO: reset registers to enabled but cleared state.
    std::cout << "constructed\n";
}

gpio::~gpio()
{
    // TODO: Set gpio to lowest power state. 
    std::cout << "destructed\n";
}

