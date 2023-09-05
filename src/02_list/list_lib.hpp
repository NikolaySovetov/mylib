#pragma once
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

    class const_iterator;
    const const_iterator cbegin() const;
    const const_iterator cend() const;     
 
    
};


}   // mylib
