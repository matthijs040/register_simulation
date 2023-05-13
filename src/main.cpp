#include <system/syscalls.hpp>
#include <cstdlib>
#include <HAL/GPIO.hpp>


extern "C" int getentropy(void*, std::size_t) {
    return 0;
}


int main(int argc, char const *argv[])
{
    auto instance = GPIO(1);

    return EXIT_SUCCESS;
}
