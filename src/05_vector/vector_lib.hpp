#pragma once
#include "base_iterator.hpp"
#include "allocator.hpp"
#include "base_iterator.hpp"
#include <cstddef>
#include <initializer_list>
#include <type_traits>

namespace mylib {

template<typename T>
class vector {
private:
    struct vector_data_type {
        size_t m_size;
        size_t m_capacity;
        T* arr;

        vector_data_type();
    } vector_data;

    mylib::allocator* const alloc;

private:
    void realloc(T* new_arr);
    void destroy_if_fault_realloc(T*, T*, const T&);
    void destroy_if_fault_realloc(T*, T*, T&&);

public:
    vector(mylib::allocator* alloc = &def_allocator);
    vector(size_t size, const T& t = T(), 
           mylib::allocator* alloc = &def_allocator);
    vector(const std::initializer_list<T>& list);        
    vector(const vector& other);
    vector& operator=(const vector& other);
    vector(vector&& other);
    vector& operator=(vector&& other);
    ~vector();

    template<typename... Args>
    void emplace_back(Args&... args);
    void push_back(const T& arg);
    void push_back(T&& arg);
    void pop_back();
    void reserve(size_t new_cap);
    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    typedef base_iterator<vector_data_type, T*, T&> iterator;    
    iterator begin() const;
    iterator end() const;
};

}   // mylib