#pragma once

namespace error {
class category {
public:
  constexpr virtual const char *name() const noexcept = 0;
  constexpr virtual const char *message(int code) const noexcept = 0;
  ~category() = default;
};

} // namespace error
