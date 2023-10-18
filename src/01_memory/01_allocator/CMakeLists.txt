add_library(allocator allocator_lib.cpp)

set(ALLOCATOR_TEST ON)
set(ALLOCATOR_STATISTICS ON)

if (${DISABLE_ALL_TESTS})
    set(ALLOCATOR_TEST OFF)
    set(ALLOCATOR_STATISTICS OFF)
endif()

configure_file(allocator_config.h.in allocator_config.hpp)
target_include_directories(allocator PUBLIC .
                                     PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

if (${ALLOCATOR_TEST})                                      
    target_link_libraries(allocator PRIVATE fortests)
endif()

