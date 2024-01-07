#pragma once

#include "error_category.hpp"
#include "standard_category.hpp"
#include <utility>

namespace error {

template <typename error_value>
struct is_error_value : public std::false_type {};

template <>
struct is_error_value<error::standard_value> : public std::true_type {};

class code;
template <typename T> code make_code(T ec) noexcept;

class code {
private:
  int value_;
  const error::category *category;

public:
  code() noexcept
      : value_(std::to_underlying(error::standard_value::success)),
        category(&standard_category::get()) {}

  code(int set_code, error::category &cat) : value_(set_code), category(&cat) {}

  code(const code &other) : value_(other.value_), category(other.category) {}

  /**
   * @brief Helper function that allows error codes to be implicitly constructed
   * from externally provided types. This is done by calling
   * error::make_code(...). Forwarding the provided value and type.
   * Expecting the caller to have implemented an overload for that custom type.
   *
   * @tparam ec
   * @tparam std::enable_if_t<is_error_value<ec>::value>
   */
  template <typename ec,
            typename std::enable_if_t<is_error_value<ec>::value, bool> = true>
  code(ec error) noexcept {
    *this = make_code(error);
  }

  code &operator=(const code &other) {
    value_ = other.value_;
    category = other.category;
    return *this;
  };

  operator bool() const noexcept { return value_ != 0; }

  bool operator==(const code &other) const noexcept {
    return &category == &(other.category) && value_ == other.value_;
  }

  const char *message() const noexcept { return category->message(value_); }

  const char *name() const noexcept { return category->name(); }

  int value() const noexcept { return value_; }

  void clear() noexcept { *this = error::code(); }
};

inline code make_code(error::standard_value val) noexcept {
  return code(std::to_underlying(val), standard_category::get());
}

} // namespace error