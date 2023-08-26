#pragma once
#include <iostream>

template<typename T>
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



