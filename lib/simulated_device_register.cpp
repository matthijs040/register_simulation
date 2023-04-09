#include "simulated_device_register.hpp"
#include "device_register.hpp"

simulated_device_register::handler_table simulated_device_register::register_effects;

bool simulated_device_register::simulated_device_register::operator<(const simulated_device_register &other) const
{
    return this->value < other.value;
}

inline void simulated_device_register::on_read() const
{
    if (register_effects.contains(this))
        register_effects.at(this).on_read(value);
}

inline void simulated_device_register::on_write() const
{
    if (register_effects.contains(this))
        register_effects.at(this).on_write(value);
}

simulated_device_register::operator std::uint32_t() const
{
    on_read();
    return value;
}

void simulated_device_register::operator=(uint32_t v)
{
    value = v;
    on_write();
}

std::uint32_t simulated_device_register::operator|=(std::uint32_t v)
{
    on_read();
    value |= v;
    on_write();
    return value;
}

std::uint32_t simulated_device_register::operator&=(std::uint32_t v)
{
    on_read();
    value &= v;
    on_write();
    return value;
}

void simulated_device_register::set_effect_handlers(simulated_device_register const*to_assign, effect_handlers const &effects)
{
    register_effects.at(to_assign) = effects;
}