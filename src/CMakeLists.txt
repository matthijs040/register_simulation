project(application C CXX ASM)
include(pico_sdk_import.cmake)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
pico_sdk_init()

add_executable(main main.cpp)

pico_enable_stdio_usb(main 0)
pico_enable_stdio_uart(main 1)
pico_add_extra_outputs(main)

target_link_libraries(main pico_stdlib rp2040_impl)
set_target_properties(main PROPERTIES CXX_STANDARD 23)