project(lib)

add_library(rp2040_impl STATIC 
    src/GPIO/GPIO.cpp 
    src/GPIO/user_IO.cpp 
    src/GPIO/pad_control.cpp )

target_compile_options(rp2040_impl PRIVATE -Wall -Wextra -Wpedantic -Werror)
set_target_properties(rp2040_impl PROPERTIES CXX_STANDARD 23)
target_link_libraries(rp2040_impl PUBLIC HAL)
target_include_directories(rp2040_impl PUBLIC inc)