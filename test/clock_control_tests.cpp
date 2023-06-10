#include <HAL/clock_control.hpp>
#include <HAL/device_register.hpp>

#include <gtest/gtest.h>

TEST(timer_tests, given_clock_control_has_clocks) {
    EXPECT_GT(clock_control::get_num_clock_sources(), 0);
}