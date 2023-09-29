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
    list(list&& other, mylib::allocator* alloc = &mylib::def_allocator);
    list& operator=(list&& other);
    ~list();

    template<typename... Args>
        void emplace_back(Args&... args);
    template<typename... Args>
        void emplace_front(Args&... args);
    void push_back(const T& arg);
    void push_back(T&& arg);
    void push_front(const T& arg);
    void push_front(T&& arg);
    void pop_back();
    void pop_front();
    size_t size() const;
    bool empty() const;

    class iterator: virtual public base_iterator<list_data_type<T>>{   
    public:
        iterator();
        iterator(T*);
        iterator(const iterator&);
        iterator& operator=(const iterator&);
        iterator(iterator&&);
        iterator& operator=(iterator&&);
        ~iterator();

        void operator++() override;
        bool operator!=(const base_iterator<T>&) const override;
        T* operator->() const override;
        T& operator*() const override;
    };
    
    list<T>::iterator begin() const;
    list<T>::iterator end() const;
};


}   // mylib
