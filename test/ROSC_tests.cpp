#include <HAL/clock_control.hpp>
#include <gtest/gtest.h>
#include <rp2040/time/ROSC.hpp>

TEST(ROSC_tests, setting_frequency_while_clock_disabled_fails) {
  auto &handle = ROSC::get();
  handle.CTRL.ENABLE = reg::ROSC::CTRL::ENABLE_states::disabled;
  auto result =
      handle.set_frequency_Hz(ROSC::get_frequencies_by_power_stage().front());
  ASSERT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), clock_error::code::disabled);
}

TEST(ROSC_tests, set_frequency_applies_powerstage_correctly) {
  // Get the clock and ensure that it is enabled.
  auto &handle = ROSC::get();
  handle.CTRL.ENABLE = reg::ROSC::CTRL::ENABLE_states::enabled;

  // Set the frequency to the first sample.
  for (auto input_frequency : ROSC::get_frequencies_by_power_stage()) {
    auto output_frequency = handle.set_frequency_Hz(input_frequency);
    ASSERT_TRUE(output_frequency.has_value());
    EXPECT_EQ(input_frequency, output_frequency.value());

    auto new_frequency = handle.get_frequency_Hz();
    ASSERT_TRUE(new_frequency.has_value());
    EXPECT_EQ(new_frequency.value(), input_frequency);
  };
}

TEST(ROSC_tests, set_frequency_applies_divisor_change_correctly) {
  auto &handle = ROSC::get();
  // Use back to ensure that any multiple of input frequency changes div.
  // (i.e. does not pick a close match found in the table.)
  const auto input_frequency = ROSC::get_frequencies_by_power_stage().back();
  constexpr auto divisor_prefix = 0xaa0;
  constexpr auto default_divisor = 31;

  auto new_divisor = 16;
  auto changed_frequency = input_frequency * default_divisor / new_divisor;
  auto result_frequency = handle.set_frequency_Hz(changed_frequency);
  EXPECT_EQ(changed_frequency, result_frequency.value());
  EXPECT_EQ(handle.DIV.divisor - divisor_prefix, new_divisor);
  auto gotten_frequency = handle.get_frequency_Hz().value();
  EXPECT_EQ(gotten_frequency, changed_frequency);

  new_divisor = 1;
  changed_frequency = input_frequency * default_divisor / new_divisor;
  result_frequency = handle.set_frequency_Hz(changed_frequency);
  EXPECT_EQ(changed_frequency, result_frequency.value());
  EXPECT_EQ(handle.DIV.divisor - divisor_prefix, new_divisor);
  gotten_frequency = handle.get_frequency_Hz().value();
  EXPECT_EQ(gotten_frequency, changed_frequency);
}