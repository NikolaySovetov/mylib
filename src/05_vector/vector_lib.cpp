#include "vector_config.hpp"
#include "vector_lib.hpp"
#include <type_traits>
//#include <iostream>

#ifdef VECTOR_TEST
#include <typeinfo>
#include "fortests.hpp"
    mylib::tests::MsSettings vector_set {mylib::tests::Color::green, ">> vector"};
#endif

namespace mylib {

template<typename T>
struct vector_data_type {
private:
    T* arr;
    size_t capacity;
    size_t size;
    friend class vector<T>;

private:
    vector_data_type(): arr{nullptr}, capacity{0}, size{0} {        
    };
    inline void erase() {
        for (size_t i {0}; i < size; ++i) {
            arr[i].~T();
        }
        delete[] reinterpret_cast<std::byte*>(arr);
    }
    void realloc(T* new_arr, T&&) {
        size_t count {0};

        try {
            for (size_t i {0}; i < size; ++i) {
                new (new_arr + i) T(std::move(arr[i])); 
                ++count;
            }
        }
        catch(const std::exception& e) {
            for (size_t i {count};; --i) {
                new (arr + i) T(std::move(new_arr[i])); 
            }

            for (size_t i {0}; i < count; ++i) {
                new_arr[i].~T();
            }

            delete[] reinterpret_cast<std::byte*>(new_arr);

            std::cerr << e.what() << '\n';
            throw;
        }
        erase();
        arr = new_arr;
    }
    void realloc(T* new_arr, const T&) {
        size_t count {0};

        try {
            for (size_t i {0}; i < size; ++i) {
                new (new_arr + i) T(arr[i]); 
                ++count;
            }
        }
        catch(const std::exception& e) {
            for (size_t i {0}; i < count; ++i) {
                new_arr[i].~T();
            }

            delete[] reinterpret_cast<std::byte*>(new_arr);

            std::cerr << e.what() << '\n';
            throw;
        }
        erase();
        arr = new_arr;
    }
    void realloc(const vector_data_type& other) {
        size_t count {0};

        try {
            for (size_t i {0}; i < other.size; ++i) {
                new (arr + i) T(other.arr[i]); 
                ++count;
            }
        }
        catch(const std::exception& e) {
            for (size_t i {0}; i < count; ++i) {
                arr[i].~T();
            }
            std::cerr << e.what() << '\n';
            throw;
        }
    }
    void reallocation(T* new_arr) {   
        realloc(new_arr, typename std::conditional<std::is_copy_constructible_v<T>, 
                                                   const T&, T&&>::type(arr[0]));
    }                                               
};

template<typename T>
vector<T>::vector() {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( type: ", typeid(T).name(), " ) created\n"}); 
#endif
}

template<typename T>
vector<T>::vector(size_t sz, const T& t) {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( type: ", typeid(T).name(), " ) created\n"}); 
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
vector<T>::vector(const std::initializer_list<T>& list) {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( std::init_list<T>: ", typeid(T).name(), " ) created\n"}); 
#endif

    reserve(list.size());
    const T* arr = list.begin();
    for (size_t i {0}; i < list.size(); ++i) {
        new (vector_data.arr + i) T(arr[i]);
    }    
    vector_data.size = list.size(); 
}

template<typename T>
vector<T>::vector(const vector& other) {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( &: ", typeid(T).name(), " ) copied\n"}); 
#endif

    reserve(other.vector_data.capacity);
    vector_data.realloc(other.vector_data);
    vector_data.size = other.vector_data.size;
}

template<typename T>
vector<T>& vector<T>::operator=(const vector& other) {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {" =( &: ", typeid(T).name(), " ) copied\n"}); 
#endif

    if (this != &other) {
        this->~vector();
        reserve(other.vector_data.capacity);
        vector_data.realloc(other.vector_data);
        vector_data.size = other.vector_data.size;
    }
    return *this;    
}

template<typename T>
vector<T>::vector(vector&& other) {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {"( &&: ", typeid(T).name(), " ) moved\n"}); 
#endif

    vector_data.arr = other.vector_data.arr;
    vector_data.size = other.vector_data.size;
    vector_data.capacity = other.vector_data.capacity;

    other.vector_data.arr = nullptr;
    other.vector_data.size = 0;
    other.vector_data.capacity = 0;
}

template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& other) {
#ifdef VECTOR_TEST
    tests::informator.PrintMess(vector_set, 
        {" =( &&: ", typeid(T).name(), " ) moved\n"}); 
#endif

    if (this != &other) {
        vector_data.erase();
        vector_data.arr = other.vector_data.arr;
        vector_data.size = other.vector_data.size;
        vector_data.capacity = other.vector_data.capacity;

        other.vector_data.arr = nullptr;
        other.vector_data.size = 0;
        other.vector_data.capacity = 0;
    }
    return *this;
}

template<typename T>
vector<T>::~vector() {
    vector_data.erase();

#ifdef VECTOR_TEST 
    tests::informator.PrintMess(vector_set, 
        {"( type: ", typeid(T).name(), " ) destroyed\n"}); 
#endif
}

template<typename T>
template<typename... Args>
void vector<T>::emplace_back(Args&... args) {
    if (vector_data.size == vector_data.capacity) {
        (vector_data.capacity == 0) ? reserve(1) : reserve(vector_data.capacity * 2);
    }

    try { 
        new (vector_data.arr + vector_data.size) T(std::forward<Args>(args)...);
        ++vector_data.size;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        throw;
    }
}

template<typename T>
void vector<T>::push_back(const T& obj) {
    emplace_back(obj);
}

template<typename T>
void vector<T>::push_back(T&& obj) {
    emplace_back(obj);
}

template<typename T>
void vector<T>::pop_back() {
    if (vector_data.size == 0) return;
    --vector_data.size;
    vector_data.arr[vector_data.size].~T();
}

template<typename T>
void vector<T>::reserve(size_t new_cap) {
#ifdef VECTOR_RESERVE_TEST    
#include <string>   
    const char* ch_cap = std::to_string(new_cap).c_str();
    mylib::tests::MsSettings vector_reserve_set {mylib::tests::Color::green, ""};    
    tests::informator.PrintMess(vector_reserve_set, 
        {" ----> reserve ", ch_cap, " places of objects \n"}); 
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
    vector_data.reallocation(reinterpret_cast<T*>(raw_mem));
    vector_data.capacity = new_cap;

#ifdef VECTOR_RESERVE_TEST    
    tests::informator.PrintMess(vector_reserve_set, 
        {"       reserved ",  ch_cap, " places of objects <-----\n"}); 
#endif
}    

template<typename T>
size_t vector<T>::size() const {
    return vector_data.size;
}

template<typename T>
size_t vector<T>::capacity() const {
    return vector_data.capacity;
}

// *** iterator ***
template<typename T>
vector<T>::iterator::iterator(): base_iterator<T>() {
}

template<typename T>
vector<T>::iterator::iterator(T* ptr): base_iterator<T>(ptr) {
}

template<typename T>
vector<T>::iterator::iterator(const iterator& other): base_iterator<T>(other) {
}

template<typename T>
typename vector<T>::iterator& vector<T>::iterator::operator=(const iterator& other) {
    if (this != &other) {
        this->it = nullptr;
        this->it = other.it;
    }
    return *this;
}

template<typename T>
vector<T>::iterator::iterator(iterator&& other): base_iterator<T>(std::move(other)) {
}

template<typename T>
typename vector<T>::iterator& vector<T>::iterator::operator=(iterator&& other) {
    if (this != &other) {
        this->it = nullptr;
        this->it = other.it;
        other.it = nullptr;
    }
    return *this;
}

template<typename T>
vector<T>::iterator::~iterator() {
}

template<typename T>
void vector<T>::iterator::operator++() {
    ++(this->it);
}

template<typename T>
bool vector<T>::iterator::operator!=(const base_iterator<T>& other) const {
    return (this->it != other.get());
}

template<typename T>
T* vector<T>::iterator::operator->() const {
    return this->it;
}

template<typename T>
T& vector<T>::iterator::operator*() const {
    return *(this->it);
}

template<typename T>
typename vector<T>::iterator vector<T>::begin() const {
    return typename vector<T>::iterator(&(this->vector_data.arr[0]));
}

template<typename T>
typename vector<T>::iterator vector<T>::end() const {
    return typename vector<T>::iterator(&(this->vector_data.arr[vector_data.size]));
}

}   // mylib