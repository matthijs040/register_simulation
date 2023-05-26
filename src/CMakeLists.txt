project(application C CXX ASM)
add_executable(main main.cpp)

include(pico_sdk_import.cmake)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)

target_link_libraries(main pico_stdlib rp2040_impl)
set_target_properties(main PROPERTIES CXX_STANDARD 23)