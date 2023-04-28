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

TEST(GPIO_tests, correct_mode_is_returned_when_set) {
  auto handle = GPIO();

  GPIO::pin_number pin = 0;
  handle.set_pin_mode(pin, GPIO::mode::output_only);
  EXPECT_EQ(handle.get_pin_mode(pin), GPIO::mode::output_only);
  handle.set_pin_mode(pin, GPIO::mode::input_only);
  EXPECT_EQ(handle.get_pin_mode(pin), GPIO::mode::input_only);
  handle.set_pin_mode(pin, GPIO::mode::input_and_output);
  EXPECT_EQ(handle.get_pin_mode(pin), GPIO::mode::input_and_output);
  handle.set_pin_mode(pin, GPIO::mode::disabled);
  EXPECT_EQ(handle.get_pin_mode(pin), GPIO::mode::disabled);
}

TEST(GPIO_tests, setting_state_with_wrong_mode_is_rejected) {}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
