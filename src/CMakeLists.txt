add_executable(main main.cpp)
target_link_libraries(main PRIVATE rp2040_impl)
set_target_properties(main PROPERTIES CXX_STANDARD 23)