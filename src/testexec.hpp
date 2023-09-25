#pragma once
#include <iostream>
#include <type_traits>

//template<typename T>
template<typename T, typename... Args>
T* get_ptr(Args&... args) {
    std::byte* raw_mem = new std::byte[sizeof(T)];
    T* ptr_obj = reinterpret_cast<T*>(raw_mem);
    new (ptr_obj) T(std::forward<Args>(args)...);  
    std::cout << sizeof...(args) << '\n';
    return ptr_obj;
}

template<typename T>
class test_iterator {
private:
    T* it;

public:
    test_iterator();
    //test_iterator(const T&);
    test_iterator(const test_iterator&);
    test_iterator& operator=(const test_iterator&);
    test_iterator(test_iterator&&);
    test_iterator& operator=(test_iterator&&);
    virtual ~test_iterator();

    virtual void operator++(int);
    virtual bool operator!=(const test_iterator&) const;
    virtual void operator=(const T&);
    virtual T get() const;
    virtual test_iterator begin();
    virtual test_iterator end();
};

template<typename T>
test_iterator<T>::test_iterator(): it {nullptr} {
}

//template<typename T>
//test_iterator<T>::test_iterator(const T& obj): it {&obj} {
//}

template<typename T>
test_iterator<T>::test_iterator(const test_iterator& other): it {other.it} {
}

template<typename T>
test_iterator<T>& test_iterator<T>::operator=(const test_iterator& other) {
    if (this != &other) {
        it = nullptr;
        it = other.it;
    }
    return *this;
}

template<typename T>
test_iterator<T>::test_iterator(test_iterator&& other): it {other.it} {
    other.it = nullptr;
}

template<typename T>
test_iterator<T>& test_iterator<T>::operator=(test_iterator&& other) {
    if (this != &other) {
        it = nullptr;
        it = other.it;
        other.it = nullptr;
    }
    return *this;
}

template<typename T>
test_iterator<T>::~test_iterator() {
    it = nullptr;
}

template<typename T>
void test_iterator<T>::operator++(int) {
    it + 1;
}

template<typename T>
bool test_iterator<T>::operator!=(const test_iterator& other) const {
    return this != &other;
}

template<typename T>
void test_iterator<T>::operator=(const T& obj) {
    *(this->it) = obj;
}

template<typename T>
T test_iterator<T>::get() const {
    return *(this->it);
}

template<typename T>
test_iterator<T> test_iterator<T>::begin() {
    return *this;
} 

template<typename T>
test_iterator<T> test_iterator<T>::end() {
    return *(this + 1);        
} 

template<typename T>
class test_input_iterator : virtual public test_iterator<T> {
};


