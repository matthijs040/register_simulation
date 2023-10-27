#include <HAL/UART.hpp>
#include <gtest/gtest.h>

TEST(UART_tests, UART_initializes_when_given_valid_pins)
{
    HAL::UART instance = HAL::UART( HAL::UART::pins{1,0}, 9600);
    std::error_code init_result = instance.initialization_result; 
    EXPECT_EQ(init_result, std::error_code());
}

TEST(UART_tests, UART_fails_to_initialize_given_invalid_pins)
{
    HAL::UART instance = HAL::UART( HAL::UART::pins{0,1}, 9600);
    EXPECT_EQ(instance.initialization_result, std::errc::invalid_argument);
}