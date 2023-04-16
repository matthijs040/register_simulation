#pragma once
#include "registers.hpp"
#include <HAL/GPIO.hpp>

extern reg::CTRL &get_control_register(const GPIO &handle,
                                       GPIO::pin_number pin);

extern reg::STATUS &get_status_register(const GPIO &handle,
                                        GPIO::pin_number pin);

extern reg::GPIO &get_pad_register(const GPIO &handle, GPIO::pin_number pin);