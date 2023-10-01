#pragma once

#include "allocator.hpp"
#include "base_iterator.hpp"
#include <cstddef>
#include <initializer_list>

namespace mylib {

template<typename T>
class list {
private:
    struct base_node_type {
        base_node_type* next;
        base_node_type* prev;   

        base_node_type();
        inline base_node_type* get_next();
        inline T* get_ptr(base_node_type*) const;
        inline T& get_ref(base_node_type*) const;
    }* base_node;     

    struct node_type : public base_node_type {
        T object;

        template<typename... Args>
            node_type(Args&... args);
    };         

    mylib::allocator* alloc;
    size_t m_size;

private:
    inline void base_node_init();
    template<typename... Args>
        inline node_type* construct_node(Args&... args);
    inline void copy_nodes_from(const base_node_type* base_node);
    inline void destroy_nodes();
    inline void insetr_first_node(node_type* new_node);
    inline void insert_back(node_type* new_node);
    inline void insert_front(node_type* new_node);

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

    typedef base_iterator<typename list<T>::base_node_type, T*, T&> iterator; 
    iterator begin();
    iterator end();
};

}   // mylib
