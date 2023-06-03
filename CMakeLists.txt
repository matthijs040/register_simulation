cmake_minimum_required(VERSION 3.26)

# Pull in SDK (must be before project)
set(PICO_SDK_FETCH_FROM_GIT on)
include(src/pico_sdk_import.cmake)
pico_sdk_init()
project(register_mocking)

if(NOT DEFINED CMAKE_CROSSCOMPILING)
    add_compile_options(-fprofile-arcs -ftest-coverage)
    add_link_options(-lgcov --coverage)
    include(CTest)
endif()

add_subdirectory(lib/HAL)
add_subdirectory(lib/rp2040)
add_subdirectory(src)

if(NOT DEFINED CMAKE_CROSSCOMPILING)
add_subdirectory(test)
endif()