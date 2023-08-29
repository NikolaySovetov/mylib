add_library(list list_lib.cpp)

set(LIST_TEST ON)

configure_file(list_config.h.in list_config.hpp)
target_include_directories(list PUBLIC .  
                                PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(list PRIVATE shared_ptr
                           PRIVATE unique_ptr)
                                      
if (${LIST_TEST})                                      
    target_link_libraries(list PRIVATE fortests)
endif()
