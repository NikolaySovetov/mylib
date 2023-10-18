#pragma once
#include "allocator.hpp"
#include "base_iterator.hpp"
#include <cstddef>
#include <initializer_list>

namespace mylib {

template<typename T>
class vector {
private:
    size_t v_size;
    size_t v_capacity;
    T*     v_arr;
    
    mylib::allocator alloc;

private:
    void realloc(T* new_arr, size_t new_capacity) noexcept; 
    void handle_fault_realloc(T* new_arr, size_t new_capacity, 
                                  size_t success_count, const T&) noexcept;
    void handle_fault_realloc(T* new_arr, size_t new_capacity, 
                                  size_t success_count, T&&) noexcept;
    void copy_from(const T* arr, size_t size);
    void destroy_arr() noexcept;

public:
    vector(const mylib::allocator& alloc = mylib::allocator()) noexcept;
    vector(size_t size, const T& t = T(), 
           const mylib::allocator& alloc = mylib::allocator()) noexcept;
    vector(const std::initializer_list<T>& list,        
           const mylib::allocator& alloc = mylib::allocator()) noexcept;
    vector(const vector& other) noexcept;
    vector& operator=(const vector& other) noexcept;
    vector(vector&& other) noexcept;
    vector& operator=(vector&& other) noexcept;
    ~vector();

    template<typename... Args>
    void emplace_back(Args&&... args);
    void push_back(const T& arg);
    void push_back(T&& arg);
    void pop_back();
    void reserve(size_t new_cap);
    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    class iterator: public base_iterator<T, T*, T&> {
    private:
        T* it;

    public:
        explicit iterator(T* ptr);
        bool operator!=(const iterator& other) const;
        void operator++() override;   
        T& operator*() const override;
        T* operator->() const override;
    };

    iterator begin() const;
    iterator end() const;
};

}   // mylib