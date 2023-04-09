cmake_minimum_required(VERSION 3.26)
project(register_mocking)

add_library(rp2040_impl rp2040_gpio.cpp simulated_device_register.cpp)
set_target_properties(rp2040_impl PROPERTIES CXX_STANDARD 23)


add_executable(main main.cpp)
target_link_libraries(main PRIVATE rp2040_impl)
set_target_properties(main PROPERTIES CXX_STANDARD 23)
