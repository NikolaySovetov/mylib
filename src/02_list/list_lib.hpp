#pragma once
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"

namespace mylib {

template<typename T>
struct ListNode;

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
    shared_ptr<ListNode<T>> begin() const;
    T* end() const;
    const T* first() const;
    bool empty() const;
    const size_t size() const;

    class iterator {
    private:
        shared_ptr<ListNode<T>> current_node;

    public:
        iterator();
        iterator(const shared_ptr<ListNode<T>>&);
        iterator& operator=(const shared_ptr<ListNode<T>>&);
        iterator(shared_ptr<ListNode<T>>&&) = delete;
        iterator& operator=(shared_ptr<ListNode<T>>&&) = delete;
        const shared_ptr<ListNode<T>>& operator++();  
    };
};


}   // mylib
