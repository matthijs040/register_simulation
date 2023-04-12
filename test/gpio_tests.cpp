#include <HAL/GPIO.hpp>
#include <gtest/gtest.h>

TEST(GPIO_tests, linked_GPIO_impl_has_pins) {
  EXPECT_GT(GPIO::get_num_pins(), 0);
}

TEST(GPIO_tests, GPIO_pin_is_initially_disabled) {
    auto handle = GPIO();
    EXPECT_EQ(handle.get_pin_mode(0), GPIO::mode::disabled);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
