#pragma once
#include <iostream>
#include <type_traits>
#include <initializer_list>
#include "allocator.hpp"

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





