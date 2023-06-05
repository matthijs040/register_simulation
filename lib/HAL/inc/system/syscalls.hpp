#pragma once
#include <cinttypes>
#include <cstdint>

extern "C" int getentropy(void* buffer, std::size_t length);