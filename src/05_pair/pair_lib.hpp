#pragma once
//#include "unique_ptr.hpp"

namespace mylib {

template<typename T1, typename T2>
struct pair_data_type;

template<typename T1, typename T2>
class pair {
private:
    pair_data_type<T1,T2> pair_data;

public:
    pair();
    pair(const T1&, const T2&);
    pair(T1&&, T2&&);
    pair(const pair&);
    pair& operator=(const pair&);
    pair(pair&&);
    pair& operator=(pair&&);
    ~pair();
    T1* first();
    T2* second(); 
};


}   // mylib