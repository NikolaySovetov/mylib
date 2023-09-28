//#include "unique_configured.h"
#include "allocator_config.hpp"
#include "allocator_lib.hpp"
#include <iostream>
#include <exception>

#ifdef ALLOCATOR_TEST
#include <string>
#include <typeinfo>
#include "fortests.hpp" 
    mylib::tests::MsSettings allocator_set{mylib::tests::Color::white, "\t>> allocator"};
#endif

namespace mylib {

allocator::allocator() {
#ifdef ALLOCATOR_TEST 
    tests::informator.PrintMess(allocator_set, {"() created\n"}); 
#endif
}

template<typename T>
inline T* allocator::allocate() {
#ifdef ALLOCATOR_TEST 
    const char* allocator_bytes_number = std::to_string(sizeof(T)).c_str();
    tests::informator.PrintMess(allocator_set, {": allocate ", allocator_bytes_number, 
                                                " bytes for \"", typeid(T).name(),"\"\n"}); 
#endif

    std::byte* raw_mem = nullptr;
    try {
        raw_mem = new std::byte[sizeof(T)];
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        throw;
    }
    return reinterpret_cast<T*>(raw_mem);
}

template<typename T>
inline T* allocator::allocate(size_t objects_num) {
#ifdef ALLOCATOR_TEST 
    const char* allocator_bytes_number = std::to_string(sizeof(T) * objects_num).c_str();
    const char* allocator_instantiations_number = std::to_string(objects_num).c_str();
    tests::informator.PrintMess(allocator_set, 
                                {": allocate ", allocator_bytes_number, 
                                 " bytes for ", allocator_instantiations_number,
                                 " instantiations of \"", typeid(T).name(), "\"\n"}); 
#endif

    std::byte* raw_mem = nullptr;
    try {
        raw_mem = new std::byte[sizeof(T) * objects_num];
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        throw;
    }
    return reinterpret_cast<T*>(raw_mem);
}

template<typename T>
inline void allocator::deallocate(T* ptr) {
#ifdef ALLOCATOR_TEST 
    const char* allocator_bytes_number = std::to_string(sizeof(T)).c_str();
    tests::informator.PrintMess(allocator_set, {": deallocate ", allocator_bytes_number, " bytes\n"}); 
#endif

    std::byte* raw_mem = reinterpret_cast<std::byte*>(ptr);
    delete[] raw_mem;
}

template<typename T>
inline void allocator::construct(void* ptr) {
    try {
        new (ptr) T();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';

    }
}

template<typename T, typename... Args> 
inline void allocator::construct(void* ptr, Args&... args) {
    try {
        new (ptr) T(args...);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';

    }
}

template<typename T>
inline void allocator::destroy(T* ptr) {
    ptr.~T();
}


}// mylib

