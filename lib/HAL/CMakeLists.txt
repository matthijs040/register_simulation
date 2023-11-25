project(HAL)

add_library(HAL STATIC src/simulated_device_register.cpp src/syscalls.cpp src/clock_control.cpp src/UART.cpp)
target_include_directories(HAL PUBLIC inc)
set_target_properties(HAL PROPERTIES CXX_STANDARD 23)
target_compile_options(HAL PRIVATE -Og -g)

