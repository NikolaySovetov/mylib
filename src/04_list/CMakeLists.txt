add_library(list list_lib.cpp)

set(LIST_TEST ON)

if (${DISABLE_ALL_TESTS})
    set(LIST_TEST OFF)
endif()

configure_file(list_config.h.in list_config.hpp)
target_include_directories(list PUBLIC .  
                                PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(list PRIVATE allocator
                           PRIVATE base_iterator)                                
                                
if (${LIST_TEST})                                      
    target_link_libraries(list PRIVATE fortests)
endif()
