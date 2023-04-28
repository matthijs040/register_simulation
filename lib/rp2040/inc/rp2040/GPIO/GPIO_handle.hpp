#pragma once
#include "pad_control.hpp"
#include "user_IO.hpp"
#include <array>

class GPIO_handle {
private:
  GPIO_handle()
      : gpio(std::make_shared<user_IO>()),
        pads(std::make_shared<pad_control>()) {}
  void *operator new(std::size_t) { return storage.data(); }
  static inline std::array<std::shared_ptr<void>, 2> storage;
  static inline std::weak_ptr<GPIO_handle> handle;
  friend std::shared_ptr<GPIO_handle> std::make_shared<GPIO_handle>();

public:
  std::shared_ptr<user_IO> gpio;
  std::shared_ptr<pad_control> pads;

  ~GPIO_handle(){};
  void operator delete(void *adr) {
    static_cast<GPIO_handle *>(adr)->~GPIO_handle();
  };
};

template <> std::shared_ptr<GPIO_handle> std::make_shared<GPIO_handle>() {
  auto ptr = GPIO_handle::handle.lock();
  if (ptr)
    return ptr;
  ptr = std::shared_ptr<GPIO_handle>(new GPIO_handle());
  ::new (ptr.get()) GPIO_handle();

  return ptr;
}