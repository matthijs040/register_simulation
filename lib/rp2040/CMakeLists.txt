project(rp2040_HAL)

add_library(rp2040_impl STATIC 
    src/GPIO/GPIO.cpp   
    src/GPIO/user_IO.cpp 
    src/GPIO/pad_control.cpp
    src/GPIO/SIO.cpp
    src/time/clocks.cpp
    src/time/clock_control.cpp
    src/time/ROSC.cpp
    src/UART/UART.cpp
    src/UART/UART_peripheral.cpp
    src/subsystem_resets/resets.cpp)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
if( supported )
message(STATUS "IPO / LTO enabled")
    set_target_properties(rp2040_impl PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()

target_compile_options(rp2040_impl PRIVATE -Og -g -Wall -Wextra -Wpedantic -Werror)
set_target_properties(rp2040_impl PROPERTIES CXX_STANDARD 23)
target_link_libraries(rp2040_impl PUBLIC HAL)
target_include_directories(rp2040_impl PUBLIC inc)
