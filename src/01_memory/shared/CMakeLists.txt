add_library(shared_ptr shared_ptr_lib.cpp)
set(SHARED_TEST OFF)

configure_file(shared_config.h.in shared_config.hpp)
target_include_directories(shared_ptr PUBLIC .
                                      PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

if (${SHARED_TEST})
    target_link_libraries(shared_ptr PRIVATE fortests)
endif()

