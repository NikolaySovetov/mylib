add_library(fortests fortests.cpp)

set(PERSON_TEST ON)

if (${DISABLE_ALL_TESTS})
    set(PERSON_TEST OFF)
endif()

configure_file(fortsests_config.h.in fortsests_config.hpp)
target_include_directories(fortests PUBLIC .
                                    PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



