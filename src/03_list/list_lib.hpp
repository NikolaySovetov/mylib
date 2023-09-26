#pragma once
#include "base_iterator.hpp"
#include <cstddef>

namespace mylib {

template<typename T>
struct list_data_type;

template<typename T>
class list {
private:
    list_data_type<T> list_data;

public:
    list();
    list(size_t size, const T& t = T());
    list(const std::initializer_list<T>& list);        
    list(const list& other);
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
    void reserve(size_t new_cap);
    size_t size() const;
    bool empty() const;
};


}   // mylib
