#include <HAL/gpio.hpp>
#include <gtest/gtest.h>

TEST(gpio_tests, linked_gpio_impl_has_pins) {
  EXPECT_GT(gpio::get_num_pins(), 0);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
