#pragma once
#include <cstdint>
#include <type_traits>
#include <assert.h>
#include <functional>
#include <map>

constexpr auto in_test_mode = true;

struct DeviceRegister
{
    using effect_handler = std::function<void(std::uint32_t)>;

    struct effect_handlers
    {
        effect_handler on_read;
        effect_handler on_write;

        // To directly write to private "value" without triggering effects.
        friend DeviceRegister;
    };

    constexpr bool operator<(const DeviceRegister &other) const noexcept
    {
        return this->value < other.value;
    }

    inline void on_read()
    {
        if (register_effects.contains(this))
            register_effects.at(this).on_read(value);
    }

    inline void on_write()
    {
        if (register_effects.contains(this))
            register_effects.at(this).on_write(value);
    }

    operator std::uint32_t()
    {
        on_read();
        return value;
    }

    void operator=(uint32_t v)
    {
        value = v;
        on_write();
    }

    std::uint32_t operator|=(std::uint32_t v)
    {
        on_read();
        value |= v;
        on_write();
        return value;
    }

    std::uint32_t operator&=(std::uint32_t v)
    {
        on_read();
        value &= v;
        on_write();
        return value;
    }

    static void set_effect_handlers(DeviceRegister* to_assign, effect_handlers const &effects)
    {
        register_effects[to_assign] = effects;
    }

private:
    std::uint32_t value;
    static std::map<DeviceRegister*, effect_handlers> register_effects;
};

// Device register becomes non-volatile while const evaluated as volatile types cannot be interacted in in constexpr functions.
// std::is_constant_evaluated() ?
using device_register = std::conditional<in_test_mode, std::uint32_t volatile, DeviceRegister>::type;