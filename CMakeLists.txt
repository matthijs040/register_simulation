cmake_minimum_required(VERSION 3.26)
project(register_mocking)

add_executable(main main.cpp gpio.cpp)
set_target_properties(main PROPERTIES CXX_STANDARD 23)
