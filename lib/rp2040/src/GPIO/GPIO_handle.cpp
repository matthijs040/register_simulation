#include <rp2040/GPIO/GPIO_handle.hpp>

GPIO_handle::GPIO_handle()
    : gpio(std::make_shared<user_IO>()), pads(std::make_shared<pad_control>()) {
}

void *GPIO_handle::operator new(std::size_t) { return storage.data(); }

void GPIO_handle::operator delete(void *adr) {
  static_cast<GPIO_handle *>(adr)->~GPIO_handle();
  storage.fill(nullptr);
};

