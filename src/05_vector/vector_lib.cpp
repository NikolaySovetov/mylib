#include "vector_config.hpp"
#include "vector_lib.hpp"
#include <typeinfo>
#include <type_traits>
#include <iostream>

#ifdef VECTOR_TEST
#include "fortests.hpp"
    mylib::tests::MsSettings vector_set {mylib::tests::Color::green, ">> vector"};
    mylib::tests::MsSettings vector_reallov_set {mylib::tests::Color::green, "\t"};
#endif

namespace mylib {

template<typename T>
void vector<T>::realloc(T* new_arr, size_t new_cap) noexcept {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_reallov_set, {"--- start reallocation\n"}); 
#endif

    size_t success_count {0};
    
    /*  try to reallocation an object by copy constructor of the object if possible,
        if it not possible will move the object  */
    try {
        for (; success_count < v_size; ++success_count) {
            alloc.construct<T>(new_arr + success_count, 
                typename std::conditional<std::is_copy_constructible_v<T>,
                                          const T&, T&&>::type(v_arr[success_count])); 
        }
    }    
    catch(const std::exception& e) {
        std::cerr << "error: vector<" << typeid(T).name() << ">: fault reallocation\n";

        handle_fault_realloc(new_arr, new_cap, success_count,
            typename std::conditional<std::is_copy_constructible_v<T>,
                                      const T&, T&&>::type(v_arr[success_count]));
        return;                               
    }

    for (size_t i {0}; i < v_size; ++i) {
        alloc.destroy<T>(v_arr + i);
    }
    alloc.deallocate<T>(v_arr, v_capacity);
    v_arr = new_arr;
    v_capacity = new_cap;

#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_reallov_set, {"    finish reallocation ---\n"}); 
#endif

}

template<typename T>
void vector<T>::handle_fault_realloc(T* new_arr, size_t new_capacity,
                                         size_t success_count, const T&) noexcept {
    for (size_t i {0}; i < success_count; ++i) {
        alloc.destroy<T>(new_arr + i);
    }
    alloc.deallocate<T>(new_arr, new_capacity);
    std::cerr << "vector restored.\n";
}

template<typename T>
void vector<T>::handle_fault_realloc(T* new_arr, size_t new_capacity,
                                         size_t success_count, T&&) noexcept {

    /*  destroy and deallocate old array */                                            
    for (size_t i {0}; i < v_size; ++i) {
        alloc.destroy<T>(v_arr + i);
    }
    alloc.deallocate<T>(v_arr, v_capacity);
    
    v_arr = new_arr;
    v_capacity = new_capacity;
    v_size = success_count;

    std::cerr << "partial restore\n";
}

template<typename T>
void vector<T>::copy_from(const T* arr, size_t size) {
    size_t count {0};

    try {
        for (; count < size; ++count) {
            alloc.construct<T>(v_arr + count, *(arr + count));
        }
    }
    catch (const std::exception& e) {
        for (size_t i {0}; i < count; ++i) {
            alloc.destroy<T>(v_arr + i);
        }
        alloc.deallocate<T>(v_arr, v_capacity);
        throw;
    }
}

template<typename T>
void vector<T>::destroy_arr() noexcept {

    for (size_t i {0}; i < v_size; ++i) {
        alloc.destroy<T>(v_arr + i);
    }
    alloc.deallocate<T>(v_arr, v_capacity);

    v_arr = nullptr;
    v_capacity = 0;
    v_size = 0; 
}

template<typename T>
vector<T>::vector(const mylib::allocator& a) noexcept
: v_size {0}, v_capacity {0}, v_arr {nullptr}, alloc {a} {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( type: ", typeid(T).name(), " ) created\n"}); 
#endif
}

template<typename T>
vector<T>::vector(size_t size, const T& t, const mylib::allocator& a) noexcept
: v_size {0}, v_capacity {0}, v_arr {nullptr}, alloc {a} {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( type: ", typeid(T).name(), " ) created\n"}); 
#endif

    size_t count {0};

    try {
        reserve(size);
        for (; count < size; ++count) {
            alloc.construct<T>(v_arr + count, t);
        }
    }
    catch (const std::bad_alloc& e) {
        return;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        for (size_t i {0}; i < count; ++i) {
            alloc.destroy<T>(v_arr + i);  
        }
        alloc.deallocate<T>(v_arr, size);

        std::cerr << "error: vector<" << typeid(T).name() << ">: can't construct container\n";
        return;
    }
    v_size = size;
}

template<typename T>
vector<T>::vector(const std::initializer_list<T>& list, const mylib::allocator& a) noexcept
: v_size {0}, v_capacity {0}, v_arr {nullptr}, alloc {a} {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( list< type: ", typeid(T).name(), "> ) created\n"}); 
#endif

    size_t new_size = list.size();   

    try {
        reserve(new_size);
        copy_from(list.begin(), new_size);
    }
    catch (const std::bad_alloc& e) {
        return;
    }
    catch(const std::exception& e) {
        std::cerr << "error: vector<" << typeid(T).name() << ">: can't construct container\n";
        return;
    }
    
    v_size = new_size;
}

template<typename T>
vector<T>::vector(const vector& other) noexcept
: v_size {0}, v_capacity {0}, v_arr {nullptr}, alloc {other.alloc} {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"< type: ", typeid(T).name(), ">() copied\n"}); 
#endif

    try {
        reserve(other.v_capacity);
        copy_from(other.v_arr, other.v_size);
    }
    catch (const std::bad_alloc& e) {
        return;
    }
    catch(const std::exception& e) {
        std::cerr << "error: vector<" << typeid(T).name() << ">: can't copy container\n";
        return;
    }
    
    v_size = other.v_size;
}

template<typename T>
vector<T>& vector<T>::operator=(const vector& other) noexcept {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( < type: ", typeid(T).name(), ">() =copied\n"}); 
#endif

    if (this == &other) {
        return *this;
    }
    alloc.~allocator();
    alloc = other.alloc;
    destroy_arr();

    try {
        reserve(other.v_capacity);
        copy_from(other.v_arr, other.v_size);
    }
    catch(const std::exception& e) {
        std::cerr << "error: vector<" << typeid(T).name() << ">: can't copy container\n";
    }
    v_size = other.v_size;
    return *this;
}

template<typename T>
vector<T>::vector(vector&& other) noexcept
: v_size {0}, v_capacity {0}, v_size {0}, alloc {std::move(other.alloc)}  {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"< type: ", typeid(T).name(), ">() moved\n"}); 
#endif

    v_arr = other.v_arr; 
    v_capacity = other.v_capacity; 
    v_size = other.v_size; 

    other.v_arr = nullptr;    
    other.v_capacity = 0;
    other.v_size = 0;
}

template<typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( < type: ", typeid(T).name(), ">() =moved\n"}); 
#endif

    if (this == &other) {
        return *this;
    }
    destroy_arr();
    alloc = std::move(other.alloc);

    v_arr = other.v_arr; 
    v_capacity = other.v_capacity; 
    v_size = other.v_size; 

    other.v_arr = nullptr;    
    other.v_capacity = 0;
    other.v_size = 0;

    return *this;
}

template<typename T>
vector<T>::~vector() {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( type: ", typeid(T).name(), " ) destroyed\n"}); 
#endif

    destroy_arr();
}

template<typename T>
template<typename... Args>
void vector<T>::emplace_back(Args&&... args) {
    if (v_size == v_capacity) {
        (v_capacity == 0) ? reserve(1)
                                      : reserve(v_capacity * 2);  
    }
    try {
        alloc.construct<T>(v_arr + v_size, 
                           std::forward<Args>(args)...);                           
    }
    catch(const std::exception& e) {
        std::cerr << "error: vector<" << typeid(T).name() << ">: can't add object\n";
    }
    
    ++v_size;
}

template<typename T>
void vector<T>::push_back(const T& t) {
    emplace_back(t);
}

template<typename T>
void vector<T>::push_back(T&& t) {
    emplace_back(std::move(t));
}

template<typename T>
void vector<T>::pop_back() {
    if (v_size != 0) {
        --v_size;
        alloc.destroy<T>(v_arr + v_size);
    }
}

template<typename T>
void vector<T>::reserve(size_t new_cap) {
    if (new_cap < v_capacity) {
        return;
    }
    T* new_arr = nullptr;
    
    try {
        new_arr = alloc.allocate<T>(new_cap);
    }
    catch(const std::exception& e) {
        std::cerr << "error: vector<" << typeid(T).name() << ">: can't allocate memory\n";
        throw;
    }

    realloc(new_arr, new_cap);
}

template<typename T>
size_t vector<T>::size() const {
    return v_size;
}

template<typename T>
size_t vector<T>::capacity() const {
    return v_capacity;
}

template<typename T>
bool vector<T>::empty() const {
    return v_size == 0;
}

template<typename T>
vector<T>::iterator::iterator(T* ptr): it {ptr} {    
}

template<typename T>
bool vector<T>::iterator::operator!=(const vector<T>::iterator& other) const {    
    return it != other.it;
}

template<typename T>
void vector<T>::iterator::operator++() {    
    ++it;
}

template<typename T>
T& vector<T>::iterator::operator*() const {    
    return *it;
}

template<typename T>
T* vector<T>::iterator::operator->() const {    
    return it;
}

template<typename T>
typename vector<T>::iterator vector<T>::begin() const {    
    return iterator(v_arr);
}

template<typename T>
typename vector<T>::iterator vector<T>::end() const {    
    return iterator(v_arr + v_size);
}


}   // mylib


