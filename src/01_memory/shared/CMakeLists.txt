add_library(shared_ptr shared_ptr_lib.cpp)
set(SHARED_TEST ON)
set(ONE_TAB   OFF)
set(TWO_TAB   ON)
set(THREE_TAB OFF)


configure_file(configured.h.in configured/sharedconfig.h)
target_include_directories(shared_ptr PUBLIC .
                                      PUBLIC ${CMAKE_CURRENT_BINARY_DIR})