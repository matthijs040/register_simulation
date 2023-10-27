#include <bit>
#include <concepts>
#include <rp2040/subsystem_resets/resets.hpp>

resets &resets::get() noexcept {
  static resets *instance;
  if (!instance)
    instance = new resets();
  return *instance;
}

resets::~resets() {}

void resets::operator delete(void *) {}

resets::resets(/* args */) {}

void *resets::operator new(std::size_t size) {
  if constexpr (reg::mock)
    return simulated_peripheral<resets>::operator new(size);
  return std::bit_cast<resets *>(base_address);
}