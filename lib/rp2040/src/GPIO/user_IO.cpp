#include <rp2040/GPIO/user_IO.hpp>

std::weak_ptr<user_IO> user_IO::storage_handle = std::weak_ptr<user_IO>();

user_IO::user_IO() {
  // TODO: reset registers to enabled but cleared state.
}

user_IO::~user_IO() {
  // TODO: Set gpio to lowest power state.
}