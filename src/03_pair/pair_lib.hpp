#pragma once
#include "unique_ptr.hpp"

namespace mylib {

template<typename T1, typename T2>
struct PairData;

template<typename T1, typename T2>
class pair {
private:
    unique_ptr<PairData<T1,T2>> pair_data;

public:
    pair();
    pair(const T1&, const T2&);
    pair(T1&&, T2&&);
    pair(const pair&);
    pair& operator=(const pair&);
    pair(pair&&);
    pair& operator=(pair&&);
    ~pair();
    T1* first() const;
    T2* second() const; 
};


}   // mylib