#pragma once
#include "pad_control.hpp"
#include "user_IO.hpp"
#include <array>

class GPIO_handle {
private:
  GPIO_handle();

  void *operator new(std::size_t);
  static inline std::array<std::shared_ptr<void>, 2> storage;
  static std::weak_ptr<GPIO_handle> handle;

public:
  std::shared_ptr<user_IO> gpio;
  std::shared_ptr<pad_control> pads;

  void operator delete(void *adr);
  friend std::shared_ptr<GPIO_handle> std::make_shared<GPIO_handle>();
};

template <> inline std::shared_ptr<GPIO_handle> std::make_shared<GPIO_handle>() {
  auto ptr = GPIO_handle::handle.lock();
  if (ptr)
    return ptr;
  ptr = std::shared_ptr<GPIO_handle>(new GPIO_handle());
  ::new (ptr.get()) GPIO_handle();

  return ptr;
}