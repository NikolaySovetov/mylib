add_library(base_iterator iterator_lib.cpp)

set(ITERATOR_TEST ON)

if (${DISABLE_ALL_TESTS})
    set(ITERATOR_TEST OFF)
endif()

configure_file(iterator_config.h.in iterator_config.hpp)
target_include_directories(base_iterator PUBLIC .  
                                         PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
                                      
if (${ITERATOR_TEST})                                      
    target_link_libraries(base_iterator PRIVATE fortests)
endif()
