#include <HAL/GPIO.hpp>
#include <HAL/device_register.hpp>
#include <gtest/gtest.h>

TEST(GPIO_tests, linked_GPIO_impl_has_pins) {
  EXPECT_GT(GPIO::get_num_pins(), 0);
}

TEST(GPIO_tests, GPIO_pins_are_initially_not_reserved) {
  auto handle = GPIO();

  GPIO::pin_number pin = 0;
  EXPECT_NE(handle.get_pin_mode(pin++), GPIO::mode::reserved);
}

TEST(GPIO_tests, setting_pins_as_output_reads_them_back_as_such) {
  auto handle = GPIO();

  GPIO::pin_number pin = 0;
  handle.set_pin_mode(pin, GPIO::mode::output_only);
  const GPIO::mode mode = handle.get_pin_mode(pin);
  EXPECT_EQ(mode, GPIO::mode::output_only);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
