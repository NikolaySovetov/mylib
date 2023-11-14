#pragma once
#include <cstddef>
#include "allocator.hpp"


namespace mylib {

template<typename T>
class initializer_list {
private:
    size_t il_capacity;
    size_t il_size;
    T*     il_arr;
    mylib::allocator alloc;

public:
    initializer_list() = delete;
    ~initializer_list();
    template<typename... Args>
        initializer_list(Args&&... args);
    initializer_list(const initializer_list&) = delete;
    initializer_list& operator=(const initializer_list&) = delete;
    initializer_list(initializer_list&&) = delete;
    initializer_list& operator=(initializer_list&&) = delete;

    /**TODO: 
     *  - add iterator with members begin, end, increment
     *  - add possibility to move pointers to vector and list
     */

    T* data() const;
    void reset();
    size_t size() const;
};

} //mylib

