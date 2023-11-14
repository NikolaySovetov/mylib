add_library(initializer_list initializer_list_lib.cpp)

set(initializer_list_TEST ON)

if (${DISABLE_ALL_TESTS})
    set(initializer_list_TEST OFF)
endif()

configure_file(initializer_list_config.h.in initializer_list_config.hpp)
target_include_directories(initializer_list PUBLIC .
                                  PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(initializer_list PUBLIC base_iterator)                                  

if (${initializer_list_TEST}) 
    target_link_libraries(initializer_list PRIVATE fortests)
endif()

target_link_libraries(initializer_list PUBLIC allocator
                                       PRIVATE base_iterator)
