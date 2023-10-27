#include <rp2040/GPIO/SIO.hpp>
#include <concepts>

SIO::~SIO() {}

SIO::SIO() {}

void SIO::operator delete(void *addr) { static_cast<SIO *>(addr)->~SIO(); }

void *SIO::operator new(size_t size) {
  if constexpr (reg::mock)
    return simulated_peripheral<SIO>::operator new(size);
  return reinterpret_cast<SIO *>(base_address);
}

SIO &SIO::get() noexcept {
  static SIO *handle;
  if (handle)
    return *handle;
  return *(handle = new SIO());
}

std::error_code SIO::set_pin_OE(GPIO::pin_number number,
                                reg::state state) noexcept {
  auto result = std::expected<reg::state, std::error_code>();
  switch (number) {
  case 0:
    GPIO_OE_SET.GPIO_0 = state;
    break;
  case 1:
    GPIO_OE_SET.GPIO_1 = state;
    break;
  case 2:
    GPIO_OE_SET.GPIO_2 = state;
    break;
  case 3:
    GPIO_OE_SET.GPIO_3 = state;
    break;
  case 4:
    GPIO_OE_SET.GPIO_4 = state;
    break;
  case 5:
    GPIO_OE_SET.GPIO_5 = state;
    break;
  case 6:
    GPIO_OE_SET.GPIO_6 = state;
    break;
  case 7:
    GPIO_OE_SET.GPIO_7 = state;
    break;
  case 8:
    GPIO_OE_SET.GPIO_8 = state;
    break;
  case 9:
    GPIO_OE_SET.GPIO_9 = state;
    break;
  case 10:
    GPIO_OE_SET.GPIO_10 = state;
    break;
  case 11:
    GPIO_OE_SET.GPIO_11 = state;
    break;
  case 12:
    GPIO_OE_SET.GPIO_12 = state;
    break;
  case 13:
    GPIO_OE_SET.GPIO_13 = state;
    break;
  case 14:
    GPIO_OE_SET.GPIO_14 = state;
    break;
  case 15:
    GPIO_OE_SET.GPIO_15 = state;
    break;
  case 16:
    GPIO_OE_SET.GPIO_16 = state;
    break;
  case 17:
    GPIO_OE_SET.GPIO_17 = state;
    break;
  case 18:
    GPIO_OE_SET.GPIO_18 = state;
    break;
  case 19:
    GPIO_OE_SET.GPIO_19 = state;
    break;
  case 20:
    GPIO_OE_SET.GPIO_20 = state;
    break;
  case 21:
    GPIO_OE_SET.GPIO_21 = state;
    break;
  case 22:
    GPIO_OE_SET.GPIO_22 = state;
    break;
  case 23:
    GPIO_OE_SET.GPIO_23 = state;
    break;
  case 24:
    GPIO_OE_SET.GPIO_24 = state;
    break;
  case 25:
    GPIO_OE_SET.GPIO_25 = state;
    break;
  case 26:
    GPIO_OE_SET.GPIO_26 = state;
    break;
  case 27:
    GPIO_OE_SET.GPIO_27 = state;
    break;
  case 28:
    GPIO_OE_SET.GPIO_28 = state;
    break;
  case 29:
    GPIO_OE_SET.GPIO_29 = state;
    break;
  default:
    return std::make_error_code(std::errc::invalid_argument);
  }
  return std::error_code();
}

std::expected<reg::state, std::error_code>
SIO::get_pin_OE(GPIO::pin_number number) const noexcept {
  auto result = std::expected<reg::state, std::error_code>();
  switch (number) {
  case 0:
    return result = GPIO_OE_SET.GPIO_0;
  case 1:
    return result = GPIO_OE_SET.GPIO_1;
  case 2:
    return result = GPIO_OE_SET.GPIO_2;
  case 3:
    return result = GPIO_OE_SET.GPIO_3;
  case 4:
    return result = GPIO_OE_SET.GPIO_4;
  case 5:
    return result = GPIO_OE_SET.GPIO_5;
  case 6:
    return result = GPIO_OE_SET.GPIO_6;
  case 7:
    return result = GPIO_OE_SET.GPIO_7;
  case 8:
    return result = GPIO_OE_SET.GPIO_8;
  case 9:
    return result = GPIO_OE_SET.GPIO_9;
  case 10:
    return result = GPIO_OE_SET.GPIO_10;
  case 11:
    return result = GPIO_OE_SET.GPIO_11;
  case 12:
    return result = GPIO_OE_SET.GPIO_12;
  case 13:
    return result = GPIO_OE_SET.GPIO_13;
  case 14:
    return result = GPIO_OE_SET.GPIO_14;
  case 15:
    return result = GPIO_OE_SET.GPIO_15;
  case 16:
    return result = GPIO_OE_SET.GPIO_16;
  case 17:
    return result = GPIO_OE_SET.GPIO_17;
  case 18:
    return result = GPIO_OE_SET.GPIO_18;
  case 19:
    return result = GPIO_OE_SET.GPIO_19;
  case 20:
    return result = GPIO_OE_SET.GPIO_20;
  case 21:
    return result = GPIO_OE_SET.GPIO_21;
  case 22:
    return result = GPIO_OE_SET.GPIO_22;
  case 23:
    return result = GPIO_OE_SET.GPIO_23;
  case 24:
    return result = GPIO_OE_SET.GPIO_24;
  case 25:
    return result = GPIO_OE_SET.GPIO_25;
  case 26:
    return result = GPIO_OE_SET.GPIO_26;
  case 27:
    return result = GPIO_OE_SET.GPIO_27;
  case 28:
    return result = GPIO_OE_SET.GPIO_28;
  case 29:
    return result = GPIO_OE_SET.GPIO_29;
  default:
    return result = std::unexpected(
               std::make_error_code(std::errc::invalid_argument));
  }
}
