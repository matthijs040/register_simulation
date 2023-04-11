#pragma once
#include "IO.hpp"
#include "pad_control.hpp"
#include <array>

class IO_register_blocks {
private:
  IO_register_blocks()
      : gpio(std::make_shared<IO>()), pads(std::make_shared<pad_control>()) {}
  void *operator new(std::size_t) { return storage.data(); }
  static std::array<std::shared_ptr<void>, 2> storage;
  static std::weak_ptr<IO_register_blocks> handle;
  friend std::shared_ptr<IO_register_blocks>
  std::make_shared<IO_register_blocks>();

public:
  std::shared_ptr<IO> gpio;
  std::shared_ptr<pad_control> pads;

  ~IO_register_blocks();
  void operator delete(void *);
};

template <>
std::shared_ptr<IO_register_blocks> std::make_shared<IO_register_blocks>() {
  auto ptr = std::shared_ptr<IO_register_blocks>();
  if (ptr = IO_register_blocks::handle.lock())
    return ptr;
  ptr = std::shared_ptr<IO_register_blocks>(new IO_register_blocks());
  ::new (ptr.get()) IO_register_blocks();
}