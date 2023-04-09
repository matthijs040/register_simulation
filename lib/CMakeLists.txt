project(lib)

add_library(rp2040_impl STATIC rp2040_gpio.cpp simulated_device_register.cpp)
set_target_properties(rp2040_impl PROPERTIES CXX_STANDARD 23)
target_include_directories(rp2040_impl PUBLIC interface)