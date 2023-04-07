#pragma once

#include "device_register.hpp"
#include <functional>

#include <map>

struct simulated_device_register
{
    using effect_handler = std::function<void(std::uint32_t)>;

    struct effect_handlers
    {
        effect_handler on_read;
        effect_handler on_write;

        // To directly write to private "value" without triggering effects.
        friend simulated_device_register;
    };

    bool operator<(const simulated_device_register &other) const;

    inline void on_read() const;

    inline void on_write() const;

    operator std::uint32_t() const;
    void operator=(uint32_t v);

    std::uint32_t operator|=(std::uint32_t v);

    std::uint32_t operator&=(std::uint32_t v);

    static void set_effect_handlers(simulated_device_register const*to_assign, effect_handlers const &effects);

private:
    std::uint32_t value;
    using handler_table = std::map<simulated_device_register const *, effect_handlers>;
    static handler_table register_effects;
};
