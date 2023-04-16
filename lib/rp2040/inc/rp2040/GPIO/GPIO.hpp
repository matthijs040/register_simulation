#pragma once
#include "registers.hpp"
#include <HAL/GPIO.hpp>

extern inline reg::CTRL &get_control_register(const GPIO &handle,
                                              GPIO::pin_number pin);

extern inline reg::STATUS &get_status_register(const GPIO &handle,
                                               GPIO::pin_number pin);

extern inline reg::GPIO &get_pad_register(const GPIO &handle,
                                          GPIO::pin_number pin);