project(HAL)

add_library(HAL STATIC src/simulated_device_register.cpp src/syscalls.cpp )

target_include_directories(HAL PUBLIC inc)
set_target_properties(HAL PROPERTIES CXX_STANDARD 23)

message(CHECK_START "Checking if we are crosscompiling: ")
if(DEFINED CMAKE_CROSSCOMPILING)
    message(CHECK_PASS "true")
    set(use_simulated_registers false)
else()
    message(CHECK_PASS "false")
    set(use_simulated_registers true)
endif()

target_compile_definitions(HAL PUBLIC USE_SIMULATED_REGISTERS=${use_simulated_registers})
link_libraries(HAL)
