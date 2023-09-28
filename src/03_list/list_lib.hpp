#pragma once

#include "allocator.hpp"
#include "base_iterator.hpp"
#include <cstddef>
#include <initializer_list>

namespace mylib {

template<typename T>
struct list_data_type;

template<typename T>
class list {
private:
    list_data_type<T> list_data;

public:
    list(mylib::allocator* alloc = &mylib::def_allocator);
    list(size_t size, const T& t = T(), mylib::allocator* alloc = &mylib::def_allocator);
    list(const std::initializer_list<T>& init_list, mylib::allocator* alloc = &mylib::def_allocator);        
    list(const list& other, mylib::allocator* alloc = &mylib::def_allocator);
    list& operator=(const list& other);
    list(list&& other);
    list& operator=(list&& other);
    ~list();

    template<typename... Args>
    void emplace_back(Args&... args);
    void push_back(const T& arg);
    void push_back(T&& arg);
    void front_back(const T& arg);
    void front_back(T&& arg);
    void pop_back();
    void front_back();
    size_t size() const;
    bool empty() const;
};


}   // mylib
