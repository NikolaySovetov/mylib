add_library(unique_ptr unique_ptr_lib.cpp)
set(TEST_ON ON)

configure_file(configured.h.in configured/configured.h)
target_include_directories(unique_ptr PUBLIC .  
                                      PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

if (${TEST_ON})                                      
    target_link_libraries(unique_ptr PRIVATE fortests)
endif()
