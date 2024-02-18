#include <gtest/gtest.h>
#include <system/fixed_capacity_queue.hpp>

TEST(fixed_capacity_queue_tests,
     queue_stops_reporting_as_empty_after_pushing_an_element) {
  fixed_capacity_queue<int, 4> queue;
  EXPECT_TRUE(queue.empty());
  queue.push(42);
  EXPECT_FALSE(queue.empty());
  queue.pop();
  EXPECT_TRUE(queue.empty());
}

TEST(fixed_capacity_queue_tests,
     queue_stops_reporting_as_full_after_popping_an_element) {
  fixed_capacity_queue<int, 4> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);

  EXPECT_FALSE(queue.full());
  queue.push(4);
  EXPECT_TRUE(queue.full());
  queue.pop();
  EXPECT_FALSE(queue.full());
}

TEST(fixed_capacity_queue_tests, elements_are_popped_in_order_of_insertion) {

  constexpr std::size_t capacity = 4;
  std::array<int, capacity> contents;
  fixed_capacity_queue<int, capacity> queue;

  for (std::size_t ind = 0; ind < capacity; ind++)
    queue.push(ind);

  for (std::size_t ind = 0; ind < capacity; ind++) {
    EXPECT_EQ(queue.front().value(), ind);
    queue.pop();
  }
}

TEST(fixed_capacity_queue_tests, push_after_pop_still_is_last_element) {
  constexpr std::size_t capacity = 3;
  fixed_capacity_queue<int, capacity> queue;

  queue.push(1);
  queue.push(2);
  queue.push(3);

  queue.pop();
  EXPECT_EQ(queue.front().value(), 2);
  queue.push(4);
  queue.pop();
  EXPECT_EQ(queue.front().value(), 3);
  queue.pop();
  EXPECT_EQ(queue.front().value(), 4);
}