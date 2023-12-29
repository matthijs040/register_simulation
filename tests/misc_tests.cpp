#include <gtest/gtest.h>
#include <rp2040/subsystem_resets/resets.hpp>

TEST(peripheral_tests,
     direct_modification_to_mocked_read_only_storage_is_possible) {

  resets &handle = resets::get();
  ASSERT_EQ(handle.RESET_DONE.PIO0, reg::state::cleared);
  static_assert(reg::mock);
  
  auto& field = simulated_peripheral<resets>::acquire_field(handle.RESET_DONE.PIO0);
  field = reg::state::set;
  
  ASSERT_EQ(field, reg::state::set);
  ASSERT_EQ(handle.RESET_DONE.PIO0, reg::state::set);

  field = reg::state::cleared;
  ASSERT_EQ(field, reg::state::cleared);
  ASSERT_EQ(handle.RESET_DONE.PIO0, reg::state::cleared);
}

#include <system/error_code.hpp>

TEST(error_code_test, standard_error_initializes_properly)
{
  auto ec = error_code();
}