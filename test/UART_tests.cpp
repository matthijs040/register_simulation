#include <HAL/UART.hpp>
#include <gtest/gtest.h>

TEST(UART_tests, UART_initializes)
{
    using namespace HAL;
    UART instance = UART( UART::pins{1,2}, 9600);
}