#include <HAL/GPIO.hpp>
#include <HAL/device_register.hpp>
#include <gtest/gtest.h>

TEST(GPIO_tests, linked_GPIO_impl_has_pins) {
  EXPECT_GT(GPIO::get_num_pins(), 0);
}

TEST(GPIO_tests, GPIO_pins_are_initially_not_reserved) {
  GPIO::pin_number pin = 0;
  auto handle = GPIO(pin);
  EXPECT_NE(handle.get_pin_mode(), GPIO::mode::reserved);
}

TEST(GPIO_tests, correct_mode_is_returned_when_set) {
  GPIO::pin_number pin = 0;
  auto handle = GPIO(pin);

  handle.set_pin_mode(GPIO::mode::output_only);
  EXPECT_EQ(handle.get_pin_mode(), GPIO::mode::output_only);
  handle.set_pin_mode(GPIO::mode::input_only);
  EXPECT_EQ(handle.get_pin_mode(), GPIO::mode::input_only);
  handle.set_pin_mode(GPIO::mode::input_and_output);
  EXPECT_EQ(handle.get_pin_mode(), GPIO::mode::input_and_output);
  handle.set_pin_mode(GPIO::mode::disabled);
  EXPECT_EQ(handle.get_pin_mode(), GPIO::mode::disabled);
}

TEST(GPIO_tests, setting_state_with_wrong_modes_is_rejected) {
  GPIO::pin_number pin = 0;
  auto handle = GPIO(pin);

  handle.set_pin_mode(GPIO::mode::input_only);
  EXPECT_EQ(handle.set_pin_state(GPIO::state::high),
            std::errc::operation_not_permitted);
  EXPECT_EQ(handle.set_pin_state(GPIO::state::low),
            std::errc::operation_not_permitted);

  handle.set_pin_mode(GPIO::mode::disabled);
  EXPECT_EQ(handle.set_pin_state(GPIO::state::high),
            std::errc::operation_not_permitted);
  EXPECT_EQ(handle.set_pin_state(GPIO::state::low),
            std::errc::operation_not_permitted);
}

TEST(GPIO_tests, setting_state_with_correct_modes_is_accepted) {

  GPIO::pin_number pin = 0;
    auto handle = GPIO(pin);

  handle.set_pin_mode(GPIO::mode::output_only);
  EXPECT_EQ(handle.set_pin_state(GPIO::state::high), std::error_code());
  EXPECT_EQ(handle.get_pin_state(), GPIO::state::high);
  EXPECT_EQ(handle.set_pin_state(GPIO::state::low), std::error_code());
  EXPECT_EQ(handle.get_pin_state(), GPIO::state::low);

  if (handle.set_pin_state(GPIO::state::floating) == std::error_code())
    EXPECT_EQ(handle.get_pin_state(), GPIO::state::floating);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
