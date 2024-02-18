#pragma once

#include <array>
#include <cstdlib>
#include <expected>

template <typename elem_type, std::size_t capacity_>
class fixed_capacity_queue {

public:
  fixed_capacity_queue(/* args */) : storage{}, stored_elements(0) {}
  ~fixed_capacity_queue() {}

  bool pop() noexcept {
    if (empty())
      return false;

    stored_elements--;
    if (empty())
      return true;

    for (size_t i = 1; i < 1 + stored_elements; i++) {
      storage.at(i - 1) = storage.at(i);
    }
    return true;
  }

  std::expected<std::reference_wrapper<elem_type>, bool> front() noexcept {
    if (empty())
      return std::unexpected{false};
    return storage.front();
  }

  std::expected<std::reference_wrapper<const elem_type>, bool>
  front() const noexcept {
    if (empty())
      return std::unexpected{false};
    return storage.front();
  }

  bool full() const noexcept { return stored_elements == storage.size(); }

  bool empty() const noexcept { return stored_elements == 0; }

  size_t size() const noexcept { return stored_elements; }

  size_t capacity() const noexcept { return storage.size(); }

  void clear() noexcept { stored_elements = 0; }

  bool push(const elem_type &data) {
    if (full())
      return false;
    stored_elements++;
    storage.at(stored_elements - 1) = data;
    return true;
  }

  bool push(elem_type &&data) {
    if (full())
      return false;
    stored_elements++;
    storage.at(stored_elements - 1) = std::move(data);
    return true;
  }

private:
  std::array<elem_type, capacity_> storage;
  std::size_t stored_elements;
};
