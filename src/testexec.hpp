#pragma once

#include <cstdarg>
#include <vector>
#include <initializer_list>
#include <typeinfo>
#include <chrono>
#include <thread>
#include <iostream>
#include <type_traits>
#include "vector.hpp"
#include "initializer_list.hpp"
//#include "allocator.hpp"

//template<typename T>
//void foo(mylib::initializer_list<T>) {
//}

template<typename T>
void foo(std::initializer_list<T>) {
}


//template<typename T>
template<typename T, typename... Args>
T* test_get_ptr(Args&... args) {
    std::byte* raw_mem = new std::byte[sizeof(T)];
    T* ptr_obj = reinterpret_cast<T*>(raw_mem);
    new (ptr_obj) T(std::forward<Args>(args)...);  
    std::cout << sizeof...(args) << '\n';
    return ptr_obj;
}

// *** simple allocator ***
/* template<typename T>
inline T* allocate() {
    std::byte* raw_mem = nullptr;
    try {
        raw_mem = new std::byte[sizeof(T)];
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return reinterpret_cast<T*>(raw_mem);
}

template<typename T>
inline void deallocate(T* ptr) {
    std::byte* raw_mem = reinterpret_cast<std::byte*>(ptr);
    delete[] raw_mem;
}

template<typename T> // Po Type, Construct Type 
inline void construct(void* ptr) {
    try {
        new (ptr) T();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';

    }
}

template<typename T, typename... Args> // Return Type, Construct Type 
inline void construct(void* ptr, Args&... args) {
    try {
        new (ptr) T(args...);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';

    }
}

template<typename T>
inline void destroy(T* ptr) {
    ptr.~T();
}
 */

// *** simple initializer_list ***
/* template<typename T>
class initializer_list {
private:    size_t il_capacity;
    size_t il_size;
    T*     il_arr;
    mylib::allocator alloc;

public:
    initializer_list() = delete;
    ~initializer_list() {
        if (il_arr) {
            for (size_t i {0}; i < il_size; ++i) {
                alloc.destroy<T>(il_arr + i);
            }
            alloc.deallocate<T>(il_arr, il_capacity);
        }
    }
    template<typename... Args>
        initializer_list(const Args&... args)
    : il_size{0}, il_arr{nullptr}, alloc{mylib::allocator()} { 
        il_capacity = sizeof...(args);
        il_arr = alloc.allocate<T>(il_capacity);

        ([&] {alloc.construct<T>(il_arr + il_size, args); 
              ++il_size;} (), ...);        
    }
    initializer_list(const initializer_list&) = delete;
    initializer_list& operator=(const initializer_list&) = delete;
    initializer_list(initializer_list&&) = delete;
    initializer_list& operator=(initializer_list&&) = delete;

    T* data() {
        return il_arr;
    } 
    void set_data(T* ptr = nullptr) {
        il_arr = ptr;
    } 
    size_t size() {
        return 0;
    }

};

 */


