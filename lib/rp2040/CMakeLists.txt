project(lib)

add_library(rp2040_impl STATIC GPIO/GPIO.cpp GPIO/user_IO.cpp GPIO/pad_control.cpp)
set_target_properties(rp2040_impl PROPERTIES CXX_STANDARD 23)
target_link_libraries(rp2040_impl PUBLIC HAL)