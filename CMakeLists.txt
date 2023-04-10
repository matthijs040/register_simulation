cmake_minimum_required(VERSION 3.26)
project(register_mocking)

add_subdirectory(lib/HAL)
add_subdirectory(lib/rp2040)
add_subdirectory(src)
add_subdirectory(test)