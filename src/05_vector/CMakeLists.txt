add_library(vector vector_lib.cpp)

set(VECTOR_TEST ON)
set(VECTOR_RESERVE_TEST ON)
set(VECTOR_ITERATOR_TEST ON)

if (NOT ${VECTOR_TEST})
    set(VECTOR_RESERVE_TEST OFF)
    set(VECTOR_ITERATOR_TEST OFF)
endif()

if (${DISABLE_ALL_TESTS})
    set(VECTOR_TEST OFF)
    set(VECTOR_RESERVE_TEST OFF)
    set(VECTOR_ITERATOR_TEST OFF)
endif()


configure_file(vector_config.h.in vector_config.hpp)
target_include_directories(vector PUBLIC .
                                  PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(vector PUBLIC base_iterator)                                  

if (${VECTOR_TEST}) 
    target_link_libraries(vector PRIVATE fortests)
endif()

target_link_libraries(vector PRIVATE allocator
                             PRIVATE base_iterator)
