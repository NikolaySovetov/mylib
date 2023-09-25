#pragma once
#include <iostream>
#include <type_traits>

//template<typename T>
template<typename T, typename... Args>
T* get_ptr(Args&... args) {
    std::byte* raw_mem = new std::byte[sizeof(T)];
    T* ptr_obj = reinterpret_cast<T*>(raw_mem);
    new (ptr_obj) T(std::forward<Args>(args)...);  
    //new (ptr_obj) T(std::forward<Args>(args...));

    std::cout << sizeof...(args) << '\n';

    return ptr_obj;
}




