#pragma once
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"

namespace mylib {

template<typename T>
struct ListData;

template<typename T>
class list {
private:
    unique_ptr<ListData<T>> list_data;

public:
    list();
    list(const T& obj);
    list(T&& obj);
    list(const list&);
    list& operator=(const list&);
    list(list&&);
    list& operator=(list&&);
    ~list();
    void push_back(const T& obj);
    void push_back(T&& obj);
    void pop_back(const T& obj);
    void pop_back(T&& obj);
    T* front() const;
    bool empty() const;
    const size_t size() const;
    
    class iterator;
    iterator begin() const;
    iterator end() const;
        
};


}   // mylib
