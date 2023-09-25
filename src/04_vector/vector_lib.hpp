#pragma once
#include <cstddef>
#include <initializer_list>

namespace mylib {

template<typename T>
struct vector_data_type;

template<typename T>
class vector {
private:
    vector_data_type<T> vector_data;

public:
    vector();
    vector(size_t size, const T& t = T());
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

};


}   // mylib