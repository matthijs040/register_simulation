#pragma once
#include "device_register.hpp"
#include <memory>
#include "simulated_peripheral.hpp"

struct rp2040_gpio : std::conditional<in_test_mode, simulated_peripheral<rp2040_gpio>, void>
{
    ~rp2040_gpio();
    void operator delete(void *){};

private:
    rp2040_gpio();

    void *operator new(std::size_t) { return reinterpret_cast<rp2040_gpio *>(base_address); }

    static constexpr uintptr_t base_address = 0x40014000;
    static std::weak_ptr<rp2040_gpio> storage_handle;

    // To force users to use make_shared for initialization.
    friend std::shared_ptr<rp2040_gpio> std::make_shared<rp2040_gpio>();

    // Start of non-static member variables:
    device_register GPIO0_STATUSGPIO;   // status
    device_register GPIO0_CTRLGPIO;     // control including function select and overrides.
    device_register GPIO1_STATUSGPIO;   // status
    device_register GPIO1_CTRLGPIO;     // control including function select and overrides.
    device_register GPIO2_STATUSGPIO;   // status
    device_register GPIO2_CTRLGPIO;     // control including function select and overrides.
    device_register GPIO3_STATUSGPIO;   // status
    device_register GPIO3_CTRLGPIO;     // control including function select and overrides.
    device_register GPIO4_STATUSGPIO;   // status
    device_register GPIO4_CTRLGPIO;     // control including function select and overrides.
    device_register GPIO5_STATUSGPIO;   // status
    device_register GPIO5_CTRLGPIO;     /// control including function select and overrides.
    device_register PIO5_CTRLGPIO;      // control including function select and overrides.
    device_register GPIO6_STATUSGPIO;   // status
    device_register GPIO6_CTRLGPIO;     // control including function select and overrides.
    device_register GPIO7_STATUSGPIO;   // status
    device_register GPIO7_CTRLGPIO;     // control including function select and overrides.
    device_register GPIO8_STATUSGPIO;   // status
    device_register GPIO8_CTRLGPIO;     // control including function select and overrides.
    device_register GPIO9_STATUSGPIO;   // status
    device_register GPIO9_CTRLGPIO;     // control including function select and overrides.
    device_register GPIO10_STATUSGPIO;  // status
    device_register GPIO10_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO11_STATUSGPIO;  // status
    device_register GPIO11_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO12_STATUSGPIO;  // status
    device_register GPIO12_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO13_STATUSGPIO;  // status
    device_register GPIO13_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO14_STATUSGPIO;  // status
    device_register GPIO14_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO15_STATUSGPIO;  // status
    device_register GPIO15_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO16_STATUSGPIO;  // status
    device_register GPIO16_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO17_STATUSGPIO;  // status
    device_register GPIO17_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO18_STATUSGPIO;  // status
    device_register GPIO18_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO19_STATUSGPIO;  // status
    device_register GPIO19_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO20_STATUSGPIO;  // status
    device_register GPIO20_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO21_STATUSGPIO;  // status
    device_register GPIO21_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO22_STATUSGPIO;  // status
    device_register GPIO22_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO23_STATUSGPIO;  // status
    device_register GPIO23_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO24_STATUSGPIO;  // status
    device_register GPIO24_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO25_STATUSGPIO;  // status
    device_register GPIO25_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO26_STATUSGPIO;  // status
    device_register GPIO26_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO27_STATUSGPIO;  // status
    device_register GPIO27_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO28_STATUSGPIO;  // status
    device_register GPIO28_CTRLGPIO;    // control including function select and overrides.
    device_register GPIO29_STATUSGPIO;  // status
    device_register GPIO29_CTRLGPIO;    // control including function select and overrides.
    device_register INTR0;              // Raw Interrupts
    device_register INTR1;              // Raw Interrupts
    device_register INTR2;              // Raw Interrupts
    device_register INTR3;              // Raw Interrupts
    device_register PROC0_INTE0;        // Interrupt Enable for proc0
    device_register PROC0_INTE1;        // Interrupt Enable for proc0
    device_register PROC0_INTE2;        // Interrupt Enable for proc0
    device_register PROC0_INTE3;        // Interrupt Enable for proc0
    device_register PROC0_INTF0;        // Interrupt Force for proc0
    device_register PROC0_INTF1;        // Interrupt Force for proc0
    device_register PROC0_INTF2;        // Interrupt Force for proc0
    device_register PROC0_INTF3;        // Interrupt Force for proc0
    device_register PROC0_INTS0;        // Interrupt status after masking & forcing for proc0
    device_register PROC0_INTS1;        // Interrupt status after masking & forcing for proc0
    device_register PROC0_INTS2;        // Interrupt status after masking & forcing for proc0
    device_register PROC0_INTS3;        // Interrupt status after masking & forcing for proc0
    device_register PROC1_INTE0;        // Interrupt Enable for proc1
    device_register PROC1_INTE1;        // Interrupt Enable for proc1
    device_register PROC1_INTE2;        // Interrupt Enable for proc1
    device_register PROC1_INTE3;        // Interrupt Enable for proc1
    device_register PROC1_INTF0;        // Interrupt Force for proc1
    device_register PROC1_INTF1;        // Interrupt Force for proc1
    device_register PROC1_INTF2;        // Interrupt Force for proc1
    device_register PROC1_INTF3;        // Interrupt Force for proc1
    device_register PROC1_INTS0;        // Interrupt status after masking & forcing for proc1
    device_register PROC1_INTS1;        // Interrupt status after masking & forcing for proc1
    device_register PROC1_INTS2;        // Interrupt status after masking & forcing for proc1
    device_register PROC1_INTS3;        // Interrupt status after masking & forcing for proc1
    device_register DORMANT_WAKE_INTE0; // Interrupt Enable for dormant_wake
    device_register DORMANT_WAKE_INTE1; // Interrupt Enable for dormant_wake
    device_register DORMANT_WAKE_INTE2; // Interrupt Enable for dormant_wake
    device_register DORMANT_WAKE_INTE3; // Interrupt Enable for dormant_wake
    device_register DORMANT_WAKE_INTF0; // Interrupt Force for dormant_wake
    device_register DORMANT_WAKE_INTF1; // Interrupt Force for dormant_wake
    device_register DORMANT_WAKE_INTF2; // Interrupt Force for dormant_wake
    device_register DORMANT_WAKE_INTF3; // Interrupt Force for dormant_wake
    device_register DORMANT_WAKE_INTS0; // Interrupt status after masking & forcing for dormant_wake
    device_register DORMANT_WAKE_INTS1; // Interrupt status after masking & forcing for dormant_wake
    device_register DORMANT_WAKE_INTS2; // Interrupt status after masking & forcing for dormant_wake
    device_register DORMANT_WAKE_INTS3; // Interrupt status after masking & forcing for dormant_wake
};

template <>
inline std::shared_ptr<rp2040_gpio> std::make_shared<rp2040_gpio>()
{
    if (const auto ptr = rp2040_gpio::storage_handle.lock())
        return ptr;
    const auto ptr = std::shared_ptr<rp2040_gpio>(new rp2040_gpio());
    rp2040_gpio::storage_handle = ptr;
    return ptr;
}