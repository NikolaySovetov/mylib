#include "initializer_list_lib.hpp"

namespace mylib {

template<typename T>
initializer_list<T>::~initializer_list() {
    if (il_arr) {
        for (size_t i {0}; i < il_size; ++i) {
            alloc.destroy<T>(il_arr + i);
        }
        alloc.deallocate<T>(il_arr, il_capacity);
    }
    il_size = 0;
    il_capacity = 0;
}

template<typename T>
template<typename... Args>
    initializer_list<T>::initializer_list(Args&&... args)
: il_size{0}, il_arr{nullptr}, alloc{mylib::allocator()} { 

    il_capacity = sizeof...(args);
    il_arr = alloc.allocate<T>(il_capacity);
    ([&] {alloc.construct<T>(il_arr + il_size, std::forward<Args>(args)); 
          ++il_size;} (), ...);        
}

template<typename T>
T* initializer_list<T>::data() const {
    return il_arr;
} 

template<typename T>
void initializer_list<T>::reset() {
    il_arr = nullptr;
    il_size = 0;
    il_capacity = 0;
} 

template<typename T>
size_t initializer_list<T>::size() const {
    return il_size;
}


} //mylib


