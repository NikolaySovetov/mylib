#include "vector_config.hpp"
#include "vector_lib.hpp"
#include <iostream>

#ifdef VECTOR_TEST
#include "fortests.hpp"
#include <typeinfo>
    mylib::tests::MsSettings vector_set {mylib::tests::Color::green, ">> vector"};
#endif

namespace mylib {

template<typename T>
struct vector_data_type {
    T* arr;
    size_t capacity;
    size_t size;
};

template<typename T>
void vector<T>::reallocation(T* new_arr) {
    size_t count {0};
    try {
        for (size_t i {0}; i < vector_data.size; ++i) {
            new (new_arr + i) 
                T(typename std::conditional<std::is_move_constructible_v<T>, 
                                            T&&, const T&>::type (*(vector_data.arr + i)));
            ++count;
        }
    }
    catch(const std::exception& e) {
        for (size_t i {count};; --i) {
            new (vector_data.arr + i) 
                T(typename std::conditional<std::is_move_constructible_v<T>, 
                                            T&&, const T&>::type (*(new_arr + i)));
        }

        for (size_t i {0}; i < count; ++i) {
            new_arr[i].~T();
        }

        delete[] reinterpret_cast<std::byte*>(new_arr);

        std::cerr << e.what() << '\n';
        throw;
    }

    for (size_t i {0}; i < vector_data.size; ++i) {
        vector_data.arr[i].~T();
    }
    delete[] reinterpret_cast<std::byte*>(vector_data.arr);
    vector_data.arr = new_arr;
}

template<typename T>
void vector<T>::reserve(size_t new_cap) {
#ifdef VECTOR_RESERVE_TEST    
#include <string>   
    const char* ch_cap = std::to_string(new_cap).c_str();
    mylib::tests::MsSettings vector_reserve_set {mylib::tests::Color::green, ""};    
    tests::informator.PrintMess(vector_reserve_set, 
        {" ---->strart reserve ",  ch_cap, " places of objects \n"}); 
#endif

    if (new_cap < vector_data.capacity) return;

    std::byte* raw_mem = nullptr;
    try{
        raw_mem = new std::byte[sizeof(T) * new_cap]; //TODO: get new arr from allocator
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n'; //TODO: log
        throw;
    }
    reallocation(reinterpret_cast<T*>(raw_mem));
    vector_data.capacity = new_cap;

#ifdef VECTOR_RESERVE_TEST    
    tests::informator.PrintMess(vector_reserve_set, 
        {"      finish reserved ",  ch_cap, " places of objects <-----\n"}); 
#endif

}    

template<typename T>
vector<T>::vector(): vector_data{nullptr, 0, 0} {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( type: ", typeid(this->vector_data.arr).name(), " ) created\n"}); 
#endif
    reserve(1);
}

template<typename T>
vector<T>::vector(size_t sz, const T& t): vector_data{nullptr, 0, 0} {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( type: ", typeid(this->vector_data.arr).name(), " ) created\n"}); 
#endif

    if (sz != 0) {
        //std::byte* raw_memory = new std::byte[sizeof(T) * sz]; //TODO: allocator, strong-safety
        //vector_data.arr = reinterpret_cast<T*>(raw_memory);
        reserve(sz);
        for (size_t i {0}; i < sz; ++i) {
            new (vector_data.arr + i) T(t);           
        }
        vector_data.size = sz;    
    } 
}

template<typename T>
vector<T>::vector(std::initializer_list<T> list): vector_data{nullptr, 0, 0} {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( std::init_list<T>: ", typeid(this->vector_data.arr).name(), " ) created\n"}); 
#endif

    reserve(list.size());
    const T* arr = list.begin();
    for (size_t i {0}; i < list.size(); ++i) {
        new (vector_data.arr + i) T(arr[i]);
    }    
    vector_data.size = list.size(); 
}

template<typename T>
vector<T>::~vector() {
    for (size_t i {0}; i < vector_data.size; ++i) {
        vector_data.arr[i].~T(); 
    }
    std::byte* raw_memory = reinterpret_cast<std::byte*>(vector_data.arr);
    delete[] raw_memory;

#ifdef VECTOR_TEST 
    tests::informator.PrintMess(vector_set, 
        {"( type: ", typeid(this->vector_data.arr).name(), " ) destroyed\n"}); 
#endif
}

template<typename T>
template<typename... Args>
void vector<T>::emplace_back(Args&... args) {
    if (vector_data.size == vector_data.capacity) {
        reserve(vector_data.capacity * 2);
    }

    try {   //TODO: for allocator 
        new (vector_data.arr + vector_data.size) T(std::forward<Args>(args)...);
        ++vector_data.size;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        throw;
    }
}

template<typename T>
void vector<T>::push_back(const T& arg) {
    emplace_back(arg);
}

template<typename T>
void vector<T>::push_back(T&& arg) {
    emplace_back(arg);
}

}   // mylib