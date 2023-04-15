project(HAL)

add_library(HAL STATIC
    inc/HAL/bitfield.hpp 
    inc/HAL/GPIO.hpp 
    inc/HAL/simulated_device_register.hpp 
    inc/HAL/simulated_peripheral.hpp
    src/simulated_device_register.cpp )

target_include_directories(HAL PUBLIC inc)
# set_target_properties(HAL PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(HAL PROPERTIES CXX_STANDARD 23)
target_compile_definitions(HAL PUBLIC USE_SIMULATED_REGISTERS=true)
