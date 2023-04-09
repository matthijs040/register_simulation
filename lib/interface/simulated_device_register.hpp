#pragma once

#include "device_register.hpp"
#include <functional>

#include <map>

class simulated_device_register
{
    public:
    using effect_handler = std::function<void(register_integral)>;

    simulated_device_register();
    simulated_device_register(const register_integral initial_value);
    ~simulated_device_register(); 

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

    operator register_integral() const;
    void operator=(register_integral v);

    register_integral operator|=(register_mask v);

    register_integral operator&=(register_mask v);

    register_integral operator&(register_mask v) const;

    static void set_effect_handlers(simulated_device_register const*to_assign, effect_handlers const &effects);

private:
    register_integral value;
    using handler_table = std::map<simulated_device_register const *, effect_handlers>;
    static handler_table register_effects;
};
