#include <sys/stat.h>
#include <cstdint>
#include <cinttypes>

extern "C" int getentropy(void* buffer, std::size_t length)
{
    return 0;
}