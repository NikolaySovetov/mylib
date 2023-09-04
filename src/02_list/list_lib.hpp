#pragma once
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"

namespace mylib {

template<typename T>
struct list_data_type;

template<typename T>
class list {
private:
    list_data_type<T> list_data;

public:
    list();
    list(const T& obj);
    list(T&& obj);
    list(const list&);
    list& operator=(const list&);
    list(list&&);
    list& operator=(list&&);
    ~list() = default;
    void push_back(const T& obj);
    void push_back(T&& obj);
    void pop_back(const T& obj);
    void pop_back(T&& obj);
    T* front() const;
    bool empty() const;
    const size_t size() const;
    
    class iterator;
    iterator begin() const;         // need exeption if list_data is empty
    const iterator& end() const;    // need exeption if list_data is empty
        
};


}   // mylib
