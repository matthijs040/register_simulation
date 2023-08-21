cmake_minimum_required(VERSION 3.26)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lib ${CMAKE_CURRENT_BINARY_DIR}/lib)
project(unit_tests)
include(CTest)

add_executable(GPIO_tests GPIO_tests.cpp)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
if( supported )
message(STATUS "IPO / LTO enabled")
    set_target_properties(GPIO_tests PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()

target_compile_options(GPIO_tests PRIVATE -fprofile-arcs -ftest-coverage)
target_link_options(GPIO_tests PRIVATE -lgcov --coverage)
target_link_libraries(GPIO_tests PRIVATE rp2040_impl GTest::gtest_main)
set_target_properties(GPIO_tests PROPERTIES CXX_STANDARD 23)

add_test(NAME run_GPIO_tests COMMAND GPIO_tests)

add_executable(clock_control_tests clock_control_tests.cpp)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
if( supported )
message(STATUS "IPO / LTO enabled")
    set_target_properties(clock_control_tests PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()

target_compile_options(clock_control_tests PRIVATE -fprofile-arcs -ftest-coverage)
target_link_options(clock_control_tests PRIVATE -lgcov --coverage)
target_link_libraries(clock_control_tests PRIVATE rp2040_impl GTest::gtest_main)
set_target_properties(clock_control_tests PROPERTIES CXX_STANDARD 23)

add_test(NAME run_clock_control_tests COMMAND clock_control_tests)

