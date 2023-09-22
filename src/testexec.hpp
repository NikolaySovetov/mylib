#pragma once
#include <iostream>
#include <type_traits>

//template<typename T>
template<typename T, typename... Args>
T* get_ptr(Args&... args) {
    std::byte* raw_mem = new std::byte[sizeof(T)];
    T* ptr_obj = reinterpret_cast<T*>(raw_mem);
    new (ptr_obj) T(std::forward<Args>(args)...);  
    //new (ptr_obj) T(std::forward<Args>(args...));

    std::cout << sizeof...(args) << '\n';

    return ptr_obj;
}


template<typename T>
class test_vector {
private: 
    T* data;
    size_t size;
    size_t capasity;

public:
    test_vector(): data{nullptr}, size{0}, capasity{0} {
    }
   
    template<typename... Args> 
    test_vector(Args&&... args): data{nullptr}, size{0}, capasity{0} {
        //(push_back(std::forward<Args>(args))...) ;
        //std::move_if_noexcept
    }

    ~test_vector() {
        std::cout << "****** ~test_vector() ******\n";
        for (size_t i {0}; i < capasity; ++i) {
            (data + i)->~T();
        }
        std::byte* old_mem = reinterpret_cast<std::byte*>(data);
        delete old_mem;
        data = nullptr;
    }

/* template<typename U>
using ref = typename std::conditional<std::is_move_constructible_v<U>, U&&, const U&>::value;
    void construct(T* ptr, ref) {
        new (ptr) U(ref);
}
 */
    void resize(size_t new_size) {
        std::cout << "***** resize(" << new_size << ") ******\n";
        if (new_size <= size) {
            return;
        }
        std::byte* mempool = new std::byte[sizeof(T) * new_size];     
        T* new_data = reinterpret_cast<T*>(mempool);

        if (size > 0) {
            std::cout << "////// reallocation //////\n";   

            for (size_t i {0}; i < capasity; ++i) {
                //new (new_data + i) T(std::move(*(data + i)));
                //new (new_data + i) T(std::move_if_noexcept(*(data + i)));
                new (new_data + i) 
                    T(typename std::conditional<std::is_move_constructible_v<T>, 
                                                 T&&, const T&>::type (*(data + i)));
            }

            std::cout << "///// ----------- /////\n";   
            for (size_t i {0}; i < capasity; ++i) {
                (data + i)->~T();    
            }
            std::cout << "///// stop resize /////\n";   
        }

        std::byte* old_mem = reinterpret_cast<std::byte*>(data);
        delete[] old_mem;
        data = new_data;
        size = new_size;
    }

    void push_back(const T& obj) {
        if (size == 0) {
            resize(1);
            new (data) T(obj);
            ++capasity;     
        } else if (capasity == size) {
            resize(size * 2);
            new (data + capasity) T(obj);    
            ++capasity;
        } else {
            new (data + capasity) T(obj);    
            ++capasity;
        } 
    }

    void push_back(T&& obj) {
        if (size == 0) {
            resize(1);
            new (data) T(std::move(obj));
            ++capasity;     
        } else if (capasity == size) {
            resize(size * 2);
            new (data + capasity) T(std::move(obj));    
            ++capasity;
        } else {
            new (data + capasity) T(std::move(obj));    
            ++capasity;
        } 
    }

};




