#pragma once
#include <iostream>

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

class First {
private:
    int first_val;

public:
    First(): first_val{101} {
        std::cout << "first class created\n";
    }
    int GetVal() { return first_val; }


    class Second {
    private:
        int second_val;

    public:
        Second() {
            std::cout << " second class created\n";
        }        
    };    
};

