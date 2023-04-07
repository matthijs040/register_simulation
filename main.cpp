#include <cstdlib>
#include "rp2040_gpio.hpp"

int main(int argc, char const *argv[])
{
    auto instance = std::make_shared<rp2040_gpio>(); 


    return EXIT_SUCCESS;
}
