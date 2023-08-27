add_library(pair pair_lib.cpp)

set(TEST_ON ON)
configure_file(configured.h.in configured/inconfigured.h )
target_include_directories(pair PUBLIC .
                                PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(pair PRIVATE unique_ptr)
                                
if (${TEST_ON}) 
    target_link_libraries(pair PRIVATE fortests)
endif()
