cmake_minimum_required(VERSION 3.26)
project(register_mocking)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-fprofile-arcs -ftest-coverage -Og)
    add_link_options(-lgcov --coverage)
    include(CTest)
endif()

add_subdirectory(lib/HAL)
add_subdirectory(lib/rp2040)
add_subdirectory(src)
add_subdirectory(test)