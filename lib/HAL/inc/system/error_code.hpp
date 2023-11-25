#pragma once

template <class Category> class error_category {
public:
  constexpr const char *name() const noexcept {
    return static_cast<const Category *>(this)->name();
  }
  constexpr const char *message(int code) const noexcept {
    const char *msg = static_cast<const Category *>(this)->message(code);
    return msg ? msg : "invalid enumeration.";
  }

  constexpr error_category(){};
  ~error_category() = default;
};

class error_code {
private:
  int code_;
  const char *name_;
  const char *message_;
  const void *category_identifier;

public:
  constexpr error_code() noexcept
      : code_(0), name_(nullptr), message_(nullptr),
        category_identifier(nullptr) {}

  template <class T>
  constexpr error_code(int set_code, const error_category<T> &category)
      : code_(set_code), name_(category.name()),
        message_(category.message(code_)), category_identifier(&category) {}

  constexpr operator bool() const noexcept { return code_ != 0; }

  constexpr const char *message() const noexcept { return message_; }

  constexpr const char *name() const noexcept { return name_; }

  constexpr int code() const noexcept { return code_; }

  constexpr void clear() noexcept { code_ = 0; }
};
