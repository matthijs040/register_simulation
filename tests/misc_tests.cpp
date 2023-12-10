#include <gtest/gtest.h>
#include <rp2040/subsystem_resets/resets.hpp>

TEST(peripheral_tests,
     direct_modification_to_mocked_read_only_storage_is_possible) {

  auto &handle = resets::get();
  ASSERT_EQ(handle.RESET_DONE.PIO0, reg::state::cleared);
  static_assert(reg::mock);

  auto &upcast_handle = *std::bit_cast<simulated_peripheral<resets> *>(&handle);

  decltype(resets::RESET_DONE.PIO0)::stored_bits &field =
      upcast_handle.acquire_field<decltype(resets::RESET_DONE.PIO0)>(
          &handle.RESET_DONE);
  field = reg::state::set;
  
  ASSERT_EQ(field, reg::state::set);
  ASSERT_EQ(handle.RESET_DONE.PIO0, reg::state::set);

  field = reg::state::cleared;
  ASSERT_EQ(field, reg::state::cleared);
  ASSERT_EQ(handle.RESET_DONE.PIO0, reg::state::cleared);

}