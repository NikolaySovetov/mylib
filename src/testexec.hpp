#pragma once
#include <iostream>
#include <type_traits>
#include <initializer_list>
#include "allocator.hpp"

//template<typename T>
template<typename T, typename... Args>
T* test_get_ptr(Args&... args) {
    std::byte* raw_mem = new std::byte[sizeof(T)];
    T* ptr_obj = reinterpret_cast<T*>(raw_mem);
    new (ptr_obj) T(std::forward<Args>(args)...);  
    std::cout << sizeof...(args) << '\n';
    return ptr_obj;
}

// *** simple allocator ***
/* template<typename T>
inline T* allocate() {
    std::byte* raw_mem = nullptr;
    try {
        raw_mem = new std::byte[sizeof(T)];
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return reinterpret_cast<T*>(raw_mem);
}

template<typename T>
inline void deallocate(T* ptr) {
    std::byte* raw_mem = reinterpret_cast<std::byte*>(ptr);
    delete[] raw_mem;
}

template<typename T> // Po Type, Construct Type 
inline void construct(void* ptr) {
    try {
        new (ptr) T();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';

    }
}

template<typename T, typename... Args> // Return Type, Construct Type 
inline void construct(void* ptr, Args&... args) {
    try {
        new (ptr) T(args...);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';

    }
}

template<typename T>
inline void destroy(T* ptr) {
    ptr.~T();
}
 */

// *** test_list ***
template<typename T>
struct test_list_data_type {
public:
    mylib::allocator* alloc;
    struct base_node_type {
        base_node_type* next;
        base_node_type* prev;
    
        base_node_type(): prev{nullptr}, next{nullptr} {}
    };     
    struct node_type : public base_node_type {
        T object;

        template<typename... Args>
        node_type(Args&... args): base_node_type(), object(std::forward<Args>(args)...) {
        }
    };         

    base_node_type* base_node;     
    size_t size;

protected:
    inline void insetr_first_node(node_type* new_node) {
        new_node->next = base_node;
        new_node->prev = base_node;
        base_node->next = new_node;
        base_node->prev = new_node;
        ++size;
    }

    inline void insert_back(node_type* new_node) {
        if (size == 0) {
            insetr_first_node(new_node);        
        } else {
            base_node_type* ptr = base_node->prev;
            base_node->prev = new_node;
            new_node->next = base_node;
            new_node->prev = ptr;
            ptr->next = new_node;
            ++size;
        }
    }

    inline void insert_front(node_type* new_node) {
        if (size == 0) {
            insetr_first_node(new_node);        
        } else {
            base_node_type* ptr = base_node->next;
            base_node->next = new_node;
            new_node->next = ptr;
            new_node->prev = base_node;
            ptr->prev = new_node;
            ++size;
        }
    }

public: 
    test_list_data_type(mylib::allocator* a = &(mylib::def_allocator)): size{0} {     
        base_node = alloc->allocate<base_node_type>();
        alloc->construct<base_node_type>(base_node);
    }

    template<typename... Args>
    void emplace_back(Args&... args) {
        node_type* new_node = alloc->allocate<node_type>();
        alloc->construct<node_type, Args...>(new_node, args...);        
        insert_back(new_node);
    }

    template<typename... Args>
    void emplace_front(Args&... args) {
        node_type* new_node = alloc->allocate<node_type>();
        alloc->construct<node_type, Args...>(new_node, args...);        
        insert_front(new_node);
    }

    void push_back(const T& obj) {
        emplace_back(obj);
    }

    void push_back(T&& obj) {
        emplace_back(obj);
    }

    void push_front(const T& obj) {
        emplace_front(obj);
    }

    void push_front(T&& obj) {
        emplace_front(obj);
    }

    size_t sz() const {
        return size;
    }

    base_node_type* get_base() {
        return base_node;
    }

    node_type* get_node(base_node_type* base) {
        return static_cast<node_type*>(base);           
    }
};



