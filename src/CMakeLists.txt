cmake_minimum_required(VERSION 3.26)

# Pull in SDK (must be before project)
set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)
pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lib ${CMAKE_CURRENT_BINARY_DIR}/lib)

project(application)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE HAL rp2040_impl pico_stdlib)
pico_enable_stdio_usb(main 0)
pico_enable_stdio_uart(main 1)
pico_add_extra_outputs(main)


set_target_properties(main PROPERTIES CXX_STANDARD 23)