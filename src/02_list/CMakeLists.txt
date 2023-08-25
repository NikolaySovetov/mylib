add_library(list list_lib.cpp)

set(TEST_ON ON)
set(INTERNAL_TEST_ON ON)

configure_file(configured.h.in configured/configured.h)
target_include_directories(list PUBLIC .  
                                      PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(list PRIVATE shared_ptr
                           PRIVATE unique_ptr)
                                      
if (${TEST_ON})                                      
    target_link_libraries(list PRIVATE fortests)
endif()
