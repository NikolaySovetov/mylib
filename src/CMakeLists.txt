add_subdirectory(00_testlib)
add_subdirectory(01_memory)

add_executable(testexec testexec.cpp)
target_link_libraries(testexec PRIVATE fortests
                               PRIVATE unique_ptr)