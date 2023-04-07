#pragma once
#include "types.hpp"
#include <array>

template <typename Peripheral>
struct simulated_peripheral
{
    void *operator new(std::size_t)
    {
        for (auto i = 0; i < simulated_register_storage.size(); i++)
            DeviceRegister::set_effect_handlers(&simulated_register_storage.at(i), register_effects_storage.at(i));
        return simulated_register_storage.data();
    }

    void operator delete(void *) {}

private:
    static_assert(std::is_layout_compatible_v<device_register, DeviceRegister>());
    static_assert(sizeof(device_register) == sizeof(DeviceRegister));

    static const auto register_count = sizeof(Peripheral) / sizeof(device_register);
    static std::array<DeviceRegister, register_count> simulated_register_storage;
    static std::array<const DeviceRegister::effect_handlers, register_count> register_effects_storage;
};
