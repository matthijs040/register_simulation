#pragma once
#include "registers.hpp"
#include <HAL/GPIO.hpp>

extern reg::CTRL &get_control_register(GPIO::pin_number pin);

extern reg::STATUS &get_status_register(GPIO::pin_number pin);

extern reg::GPIO &get_pad_register(GPIO::pin_number pin);

extern error::code reserve_pin(GPIO::pin_number pin, reg::CTRL::FUNCSEL_states desired_function);