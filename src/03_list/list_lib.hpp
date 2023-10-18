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
    }* base_node;     

    struct node_type : public base_node_type {
        T object;

        template<typename... Args>
            node_type(Args&... args);
    };         

    mylib::allocator alloc;
    size_t m_size;

private:
    inline void base_node_init();
    template<typename... Args>
        inline node_type* construct_node(Args&&... args);
    inline void copy_nodes_from(const base_node_type* base_node);
    inline void destroy_nodes();
    inline void insetr_first_node(node_type* new_node);
    inline void insert_back(node_type* new_node);
    inline void insert_front(node_type* new_node);

public:
    list(const mylib::allocator& alloc = mylib::allocator());
    list(size_t size, const T& t = T(), 
         const mylib::allocator& alloc = mylib::allocator());
    list(const std::initializer_list<T>& init_list, 
         const mylib::allocator& alloc = mylib::allocator());        
    list(const list& other);
    list& operator=(const list& other);
    list(list&& other);
    list& operator=(list&& other);
    ~list();

    template<typename... Args>
        void emplace_back(Args&&... args);
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

    class iterator: public base_iterator<base_node_type, T*, T&> {
    private:
        base_node_type* p_node;

    public:
        explicit iterator(base_node_type* ptr);
        bool operator!=(const iterator& other) const;
        void operator++() override;   
        T& operator*() const override;
        T* operator->() const override;
    };

    iterator begin() const;
    iterator end() const;
};

}   // mylib
