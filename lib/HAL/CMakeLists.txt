project(HAL)

add_library(HAL STATIC)
target_include_directories(HAL PUBLIC inc)
set_target_properties(HAL PROPERTIES CXX_STANDARD 23)
target_compile_definitions(HAL PUBLIC USE_SIMULATED_REGISTERS=true)
