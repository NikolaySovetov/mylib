add_library(fortests fortests.cpp)
set(TEST_MESSAGE ON)
configure_file(configured.h.in configured/configured.h)
target_include_directories(fortests PUBLIC .
                                   PRIVATE ${CMAKE_CURRENT_BINARY_DIR})



