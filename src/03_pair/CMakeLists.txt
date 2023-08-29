add_library(pair pair_lib.cpp)

set(PAIR_TEST ON)
configure_file(pair_config.h.in pair_config.hpp)
target_include_directories(pair PUBLIC .
                                PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(pair PRIVATE unique_ptr)
                                
if (${PAIR_TEST}) 
    target_link_libraries(pair PRIVATE fortests)
endif()
