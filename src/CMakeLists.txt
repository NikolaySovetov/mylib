set(DISABLE_ALL_TESTS OFF)

add_subdirectory(00_testlib)
add_subdirectory(01_memory)
add_subdirectory(02_list)
add_subdirectory(03_pair)

find_package(Curses REQUIRED )

add_executable(testexec testexec.cpp)

target_link_libraries(testexec PRIVATE fortests
                               PRIVATE unique_ptr
                               PRIVATE shared_ptr
                               PRIVATE list
                               PRIVATE pair)
                           
