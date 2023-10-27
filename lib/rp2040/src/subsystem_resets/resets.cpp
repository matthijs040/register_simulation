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
  using base = simulated_peripheral<resets>;
  if constexpr (std::is_base_of_v<base, resets>)
    return base::operator new(size);
  return std::bit_cast<resets *>(base_address);
}