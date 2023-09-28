add_library(unique_ptr unique_ptr_lib.cpp)

set(UNIQUE_TEST ON)

if (${DISABLE_ALL_TESTS})
    set(UNIQUE_TEST OFF)
endif()

configure_file(unique_config.h.in unique_config.hpp)
target_include_directories(unique_ptr PUBLIC .
                                      PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

if (${UNIQUE_TEST})                                      
    target_link_libraries(unique_ptr PRIVATE fortests)
endif()

