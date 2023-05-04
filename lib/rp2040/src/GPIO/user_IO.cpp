#include <rp2040/GPIO/user_IO.hpp>

std::weak_ptr<user_IO> user_IO::storage_handle = std::weak_ptr<user_IO>();

user_IO::user_IO() {
  // TODO: reset registers to enabled but cleared state.
}

user_IO::~user_IO() {
  // TODO: Set gpio to lowest power state.
}

void user_IO::operator delete(void *addr) {
  static_cast<user_IO *>(addr)->~user_IO();
};

void *user_IO::operator new(std::size_t size) {
  return USE_SIMULATED_REGISTERS
             ? simulated_peripheral<user_IO>::operator new(size)
             : reinterpret_cast<user_IO *>(base_address);
}