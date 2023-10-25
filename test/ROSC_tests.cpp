#include <gtest/gtest.h>
#include <rp2040/time/ROSC.hpp>

TEST(ROSC_tests, set_frequency_applies_frequency_correctly) {
    // Get the clock and ensure that it is enabled.
  auto &handle = ROSC::get();
  handle.CTRL.ENABLE = reg::ROSC::CTRL::ENABLE_states::enabled;
  
  // Set the frequency to the first sample.
  auto input_frequency = ROSC::get_frequencies_by_power_stage()[2];
  auto output_frequency = handle.set_frequency_Hz(input_frequency);
  ASSERT_TRUE(output_frequency.has_value());
  EXPECT_EQ(input_frequency, output_frequency.value());
}