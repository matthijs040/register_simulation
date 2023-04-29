include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(rp2040_tests gpio_tests.cpp)
target_link_libraries(rp2040_tests PRIVATE rp2040_impl GTest::gtest_main)
set_target_properties(rp2040_tests PROPERTIES CXX_STANDARD 23)
add_test(NAME run_rp2040_tests COMMAND rp2040_tests)
