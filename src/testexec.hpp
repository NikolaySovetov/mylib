#pragma once
#include <iostream>
#include <type_traits>

/* template<typename T>
T fun(T&& var) {
    std::cout << var << '\n';
    return var;
}

template<typename... Args>
class MyClass{
public:
    MyClass(Args... args) {
        rpush_back(fun(args)...);
    } 
    void rpush_back(Args... args) {

    }   
};
 */

class NotCopiyed {
public:
    int value = 101;

public:
    NotCopiyed() {
        std::cout << "NotCopiyed()\n";        
    }
    NotCopiyed(const NotCopiyed& other) /* = delete; */ {
        std::cout << "NotCopiyed(const NotCopiyed& )\n";        
    }
    NotCopiyed& operator=(const NotCopiyed& other) /* = delete; */  {
        std::cout << "NotCopiyed=(const NotCopiyed& )\n";        
        return *this; 
    }
 
    NotCopiyed(NotCopiyed&& other) = delete;   /* {
        std::cout << "NotCopiyed(NotCopiyed&& )\n";        
    } */
    NotCopiyed& operator=(NotCopiyed&& other) /* = delete; */    {
        std::cout << "NotCopiyed=(NotCopiyed&& )\n";        
        return *this;
    } 

     ~NotCopiyed() {
        std::cout << "~NotCopiyed()\n";        
    }
};

template<typename T>
class vector {
private: 
    T* data;
    size_t size;
    size_t capasity;

public:
    vector(): data{nullptr}, size{0}, capasity{0} {
    }
   
    template<typename... Args> 
    vector(Args&&... args): data{nullptr}, size{0}, capasity{0} {
        //(push_back(std::forward<Args>(args))...) ;
        //std::move_if_noexcept
    }

    ~vector() {
        std::cout << "****** ~vector() ******\n";
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




