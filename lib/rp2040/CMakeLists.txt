project(lib)

add_library(rp2040_impl STATIC gpio/IO.cpp gpio/gpio.cpp)
set_target_properties(rp2040_impl PROPERTIES CXX_STANDARD 23)
target_link_libraries(rp2040_impl PUBLIC HAL)