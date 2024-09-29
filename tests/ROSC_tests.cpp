#include <HAL/clock_control.hpp>
#include <gtest/gtest.h>
#include <rp2040/time/ROSC.hpp>

TEST(ROSC_tests, setting_frequency_while_clock_disabled_fails) {
  auto &handle = ROSC::get();
  handle.CTRL.ENABLE = reg::ROSC::CTRL::ENABLE_states::disabled;

  error::code ec;

  auto result = handle.set_frequency_Hz(
      ROSC::get_frequencies_by_power_stage().front(), ec);
  EXPECT_EQ(ec, clock_control::errc::disabled);
}

TEST(ROSC_tests, set_frequency_applies_powerstage_correctly) {
  // Get the clock and ensure that it is enabled.
  auto &handle = ROSC::get();
  handle.CTRL.ENABLE = reg::ROSC::CTRL::ENABLE_states::enabled;

  error::code ec;
  // Set the frequency to the first sample.
  for (auto input_frequency : ROSC::get_frequencies_by_power_stage()) {
    auto output_frequency = handle.set_frequency_Hz(input_frequency, ec);
    EXPECT_EQ(input_frequency, output_frequency);

    auto new_frequency = handle.get_frequency_Hz(ec);
    EXPECT_EQ(new_frequency, input_frequency);
  };
}

TEST(ROSC_tests, set_frequency_applies_divisor_change_correctly) {
  error::code ec;

  auto &handle = ROSC::get();
  // Use back to ensure that any multiple of input frequency changes div.
  // (i.e. does not pick a close match found in the table.)
  const auto input_frequency = ROSC::get_frequencies_by_power_stage().back();
  constexpr auto divisor_prefix = 0xaa0;
  constexpr auto default_divisor = 31;

  auto new_divisor = 16;
  auto changed_frequency = input_frequency * default_divisor / new_divisor;
  auto result_frequency = handle.set_frequency_Hz(changed_frequency, ec);
  EXPECT_EQ(changed_frequency, result_frequency);
  EXPECT_EQ(handle.DIV.divisor - divisor_prefix, new_divisor);
  auto gotten_frequency = handle.get_frequency_Hz(ec);
  EXPECT_EQ(gotten_frequency, changed_frequency);

  new_divisor = 1;
  changed_frequency = input_frequency * default_divisor / new_divisor;
  result_frequency = handle.set_frequency_Hz(changed_frequency, ec);
  EXPECT_EQ(changed_frequency, result_frequency);
  EXPECT_EQ(handle.DIV.divisor - divisor_prefix, new_divisor);
  gotten_frequency = handle.get_frequency_Hz(ec);
  EXPECT_EQ(gotten_frequency, changed_frequency);
}