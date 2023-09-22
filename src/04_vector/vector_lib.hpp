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
    void reallocation(T* new_arr);

public:
    vector();
    vector(size_t size, const T& t = T());
    vector(std::initializer_list<T> list);        
    ~vector();

    void push_back(const T&);
    void push_back(T&&);

    template<typename... Args>
    void emplace_back(Args&... args);

    void reserve(size_t new_cap);
};


}   // mylib