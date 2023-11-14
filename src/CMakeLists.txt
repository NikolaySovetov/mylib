set(DISABLE_ALL_TESTS OFF)

add_subdirectory(00_testlib         )
add_subdirectory(01_memory          )
add_subdirectory(02_iterator        )
add_subdirectory(03_initializer_list)
add_subdirectory(04_list            )
add_subdirectory(05_pair            )
add_subdirectory(06_vector          )

find_package(Curses REQUIRED )

add_executable(testexec testexec.cpp)

target_link_libraries(testexec PRIVATE fortests
                               PRIVATE allocator 
                               PRIVATE unique_ptr
                               PRIVATE shared_ptr
                               PRIVATE initializer_list
                               PRIVATE base_iterator
                               PRIVATE list
                               PRIVATE pair
                               PRIVATE vector)
                               
                           
