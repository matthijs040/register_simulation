cmake_minimum_required(VERSION 3.25)

# Pull in SDK (must be before project)
set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lib ${CMAKE_CURRENT_BINARY_DIR}/lib)

project(application)

pico_sdk_init()
add_executable(main main.cpp application.cpp)

target_link_libraries(main PRIVATE HAL rp2040_impl pico_stdlib)
target_compile_options(main PRIVATE -Og)
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
pico_add_extra_outputs(main)

# 365kB with USB as output.
# 352kB with UART as output.

set_target_properties(main PROPERTIES CXX_STANDARD 23)


add_executable(UART_snippet UART_snippet.cpp)

# include(CheckIPOSupported)
# check_ipo_supported(RESULT supported OUTPUT error)
# if( supported )
# message(STATUS "IPO / LTO enabled")
#     set_target_properties(UART_snippet PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
# else()
#     message(STATUS "IPO / LTO not supported: <${error}>")
# endif()

target_link_libraries(UART_snippet PRIVATE HAL rp2040_impl pico_stdlib)
target_compile_options(UART_snippet PRIVATE -Og -g)
set_target_properties(UART_snippet PROPERTIES CXX_STANDARD 23)
pico_add_extra_outputs(UART_snippet)