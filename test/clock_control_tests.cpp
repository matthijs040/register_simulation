#include <HAL/clock_control.hpp>
#include <HAL/device_register.hpp>

#include <gtest/gtest.h>

TEST(timer_tests, given_clock_control_has_clocks) {
  EXPECT_GT(clock_control::get_num_clocks(), 0);
}

TEST(timer_tests, each_clock_has_non_empty_name) {
  const auto count = clock_control::get_num_clocks();
  auto names = clock_control::get_clock_names();

  for (const auto &name : names) {
    EXPECT_NE(name, nullptr);
    EXPECT_NE(name, "\0");
    std::clog << "clock name: " << name << '\n';
  }
}