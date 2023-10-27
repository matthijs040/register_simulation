#include <HAL/UART.hpp>
#include <gtest/gtest.h>

TEST(UART_tests, UART_initializes_when_given_valid_pins)
{
    GTEST_SKIP();
    using namespace HAL;
    UART instance = UART( UART::pins{1,0}, 9600);
}

TEST(UART_tests, UART_fails_to_initialize_given_invalid_pins)
{
    GTEST_SKIP();
}